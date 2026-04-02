import argparse
import csv
import os
import socket
import struct
import sys
import time

# -------------------------------
# CLI
# -------------------------------
_script_dir = os.path.dirname(os.path.abspath(__file__))
_default_csv = os.path.join(_script_dir, "rotatordatanew.csv")

ap = argparse.ArgumentParser(
    description="Replay Baro/IMU/GPS packets from CSV over UDP (time and fc1 columns). Default window: t from -20 s to 180 s."
)
ap.add_argument("--csv", type=str, default=_default_csv,
                help=f"Path to CSV (default: {_default_csv})")
ap.add_argument("--udp", default="127.0.0.1:42099",
                help="UDP destination host:port (default: 127.0.0.1:42099)")
ap.add_argument("--broadcast", action="store_true",
                help="Enable UDP broadcast (also set --udp 255.255.255.255:PORT)")
ap.add_argument("--print", dest="do_print", action="store_true",
                help="Print packets as they are sent")
ap.add_argument("--source", type=str, default="10.0.0.81",
                help="Source IP for loopback packets (dashboard needs) (default: 10.0.0.81, FC)")
ap.add_argument("--from-time", type=float, default=-20.0, dest="from_time",
                help="Replay window start: keep rows where Time Reference(seconds) >= this (default: -20)")
ap.add_argument("--to-time", type=float, default=180.0, dest="to_time",
                help="Replay window end: keep rows where Time Reference(seconds) <= this (default: 180)")

args = ap.parse_args()

UDP_HOST, UDP_PORT = args.udp.rsplit(":", 1)
UDP_PORT = int(UDP_PORT)

# UDP socket
udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
if args.broadcast or UDP_HOST == "255.255.255.255":
    udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
udp_sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 2)

# -------------------------------
# Packet helpers (unchanged logic)
# -------------------------------
def compute_packet_checksum(packet_bytes: list[int]) -> int:
    """
    Compute checksum in the same way as the C code.

    Input packet_bytes layout (NO stored checksum inside):
    [ id, len, ts0, ts1, ts2, ts3, data... ]
    """
    if len(packet_bytes) < 6:
        return -1  # lost packet?

    pkt_id   = packet_bytes[0]
    pkt_len  = packet_bytes[1]
    ts_bytes = packet_bytes[2:6]
    data     = packet_bytes[6:6 + pkt_len]

    sum1 = 0
    sum2 = 0

    # id
    sum1 = (sum1 + pkt_id) & 0xFF
    sum2 = (sum2 + sum1)   & 0xFF

    # len
    sum1 = (sum1 + pkt_len) & 0xFF
    sum2 = (sum2 + sum1)    & 0xFF

    # timestamp[4]
    for b in ts_bytes:
        sum1 = (sum1 + b) & 0xFF
        sum2 = (sum2 + sum1) & 0xFF

    # data[0:len]
    for b in data:
        sum1 = (sum1 + b) & 0xFF
        sum2 = (sum2 + sum1) & 0xFF

    # final 16-bit value: high byte = sum2, low byte = sum1
    return (sum2 << 8) | sum1

def to_inner_bytes(packet_bytes: list[int]) -> bytes:
    # packet_bytes = [id, len, ts0..3, csum0, csum1, data...]
    if len(packet_bytes) < 8:
        return b""
    L = packet_bytes[1]
    return bytes([packet_bytes[0], packet_bytes[1]]          # id, len
                 + packet_bytes[2:6]                          # ts0..3
                 + packet_bytes[6:8]                          # csum low, high
                 + packet_bytes[8:8+L])                       # data

# -------------------------------
# CSV replay: packet IDs and payload builders (universalproto)
# BaroValues id=5, LowIMUValues id=8, GPSValues id=10
# -------------------------------
PKT_ID_BARO = 5
PKT_ID_LOW_IMU = 8
PKT_ID_GPS = 10

def _f32(v: float) -> bytes:
    return struct.pack("<f", float(v))

def _u32(v: int) -> bytes:
    return struct.pack("<I", int(v) & 0xFFFFFFFF)

def _u8(v: int) -> bytes:
    return bytes([int(v) & 0xFF])

def build_baro_packet(altitude: float, ts_bytes: list[int]) -> list[int]:
    # BaroValues: altitude, pressure, temperature (f32 each); we send only altitude, rest 0
    payload = _f32(altitude) + _f32(0.0) + _f32(0.0)
    return _make_packet(PKT_ID_BARO, ts_bytes, payload)

def build_low_imu_packet(accel_x: float, accel_y: float, accel_z: float,
                         gyro_x: float, gyro_y: float, gyro_z: float,
                         ts_bytes: list[int]) -> list[int]:
    payload = (_f32(accel_x) + _f32(accel_y) + _f32(accel_z) +
               _f32(gyro_x) + _f32(gyro_y) + _f32(gyro_z))
    return _make_packet(PKT_ID_LOW_IMU, ts_bytes, payload)

def build_gps_packet(latitude: float, longitude: float, altitude: float, ts_bytes: list[int]) -> list[int]:
    # GPSValues: lat, long, alt (f32), horizontalAccuracy, verticalAccuracy (u32), heading (f32), headingAccuracy (u32), fixType (u8)
    payload = (_f32(latitude) + _f32(longitude) + _f32(altitude) +
               _u32(0) + _u32(0) + _f32(0.0) + _u32(0) + _u8(0))
    return _make_packet(PKT_ID_GPS, ts_bytes, payload)

def _make_packet(pkt_id: int, ts_bytes: list[int], payload: bytes) -> list[int]:
    pkt_len = len(payload)
    inner = [pkt_id, pkt_len] + ts_bytes + list(payload)
    csum = compute_packet_checksum(inner)
    return [pkt_id, pkt_len] + ts_bytes + [csum & 0xFF, (csum >> 8) & 0xFF] + list(payload)

# -------------------------------
# CSV load: trimmed columns, time >= -60 s
# -------------------------------
CSV_COLUMNS = [
    "Time",
    "Time Reference(milisecond)",
    "Time Reference(seconds)",
    "fc1BaroValuesAltitude.distinct",
    "fc1GpsValuesAltitude.distinct",
    "fc1GpsValuesLongitude.distinct",
    "fc1GpsValuesLatitude.distinct",
    "fc1LowImuValuesAccelX.distinct",
    "fc1LowImuValuesAccelY.distinct",
    "fc1LowImuValuesAccelZ.distinct",
    "fc1LowImuValuesGyroX.distinct",
    "fc1LowImuValuesGyroY.distinct",
    "fc1LowImuValuesGyroZ.distinct",
]

def _parse_val(s: str):
    s = (s or "").strip()
    if s == "" or s.lower() == "undefined":
        return None
    try:
        return float(s)
    except ValueError:
        return None

def load_csv_trimmed(path: str, from_time_seconds: float, to_time_seconds: float):
    """Load CSV with only needed columns; keep rows where Time Reference(seconds) is in [from_time_seconds, to_time_seconds]."""
    rows = []
    with open(path, newline="", encoding="utf-8") as f:
        r = csv.DictReader(f)
        for row in r:
            out = {}
            for col in CSV_COLUMNS:
                if col in row:
                    out[col] = _parse_val(row[col])
                else:
                    out[col] = None
            t_sec = out.get("Time Reference(seconds)")
            if t_sec is None:
                continue
            if t_sec < from_time_seconds or t_sec > to_time_seconds:
                continue
            rows.append(out)
    rows.sort(key=lambda r: (r["Time Reference(seconds)"], r.get("Time Reference(milisecond)")))
    return rows

# -------------------------------
# Main loop
# -------------------------------
def _row_ts_bytes(row: dict, base_ms: float) -> list[int]:
    """4-byte little-endian timestamp from row time reference (ms), 0-based from base_ms."""
    ms = row.get("Time Reference(milisecond)")
    if ms is None:
        ms = (row.get("Time Reference(seconds)")) * 1000.0 if row.get("Time Reference(seconds)") is not None else 0
    else:
        ms = float(ms)
    t = int(ms - base_ms) & 0xFFFFFFFF
    return list(struct.pack("<I", t))

def _send_packet(packet_bytes: list[int], csv_t_sec: float | None = None):
    raw = to_inner_bytes(packet_bytes)
    if not raw:
        return
    if UDP_HOST == "127.0.0.1":
        udp_sock.sendto(len(args.source).to_bytes(1, "little") + args.source.encode("utf-8") + raw, (UDP_HOST, UDP_PORT))
    else:
        udp_sock.sendto(raw, (UDP_HOST, UDP_PORT))
    if packet_bytes[0] in (8, 10):
        udp_sock.sendto(raw, ("10.0.0.91", 42099))
    if args.do_print:
        time_prefix = f"{csv_t_sec:.3f} s  " if csv_t_sec is not None else ""
        print(f"{time_prefix}sent {len(raw)} bytes: id=0x{packet_bytes[0]:02X} len={packet_bytes[1]} ts={int.from_bytes(bytes(packet_bytes[2:6]), 'little')}")

def run_csv_replay():
    csv_path = os.path.abspath(args.csv)
    if not os.path.isfile(csv_path):
        print(f"CSV file not found: {csv_path}", file=sys.stderr)
        sys.exit(1)
    rows = load_csv_trimmed(csv_path, args.from_time, args.to_time)
    if not rows:
        print(f"No rows after trim (t in [{args.from_time}, {args.to_time}] s). Check CSV and --from-time / --to-time.", file=sys.stderr)
        sys.exit(1)
    def _row_ms(r):
        ms = r.get("Time Reference(milisecond)")
        if ms is not None:
            return float(ms)
        sec = r.get("Time Reference(seconds)")
        return (float(sec) * 1000.0) if sec is not None else 0.0
    base_ms = min(_row_ms(r) for r in rows)
    t_start_csv = rows[0].get("Time Reference(seconds)")
    if t_start_csv is None:
        t_start_csv = 0.0
    else:
        t_start_csv = float(t_start_csv)
    print(f"[csv] Replaying {len(rows)} rows from {csv_path} -> UDP {UDP_HOST}:{UDP_PORT} (t in [{args.from_time}, {args.to_time}] s)")
    t_start_real = time.perf_counter()
    drift_sum = 0.0
    drift_min = float("inf")
    drift_max = float("-inf")
    drift_n = 0
    for row in rows:
        t_sec = row.get("Time Reference(seconds)")
        if t_sec is not None:
            t_sec = float(t_sec)
        # Schedule by absolute target time so processing time doesn't accumulate (fixes drift)
        if t_sec is not None:
            target_real = t_start_real + (t_sec - t_start_csv)
            now = time.perf_counter()
            delay = target_real - now
            if delay > 0:
                time.sleep(delay)
        now = time.perf_counter()
        real_elapsed = now - t_start_real
        expected_elapsed = (t_sec - t_start_csv) if t_sec is not None else 0.0
        drift = real_elapsed - expected_elapsed
        if t_sec is not None:
            drift_n += 1
            drift_sum += drift
            if drift < drift_min:
                drift_min = drift
            if drift > drift_max:
                drift_max = drift
        ts_bytes = _row_ts_bytes(row, base_ms)
        baro_alt = row.get("fc1BaroValuesAltitude.distinct")
        gps_alt = row.get("fc1GpsValuesAltitude.distinct")
        gps_lon = row.get("fc1GpsValuesLongitude.distinct")
        gps_lat = row.get("fc1GpsValuesLatitude.distinct")
        acc_x = row.get("fc1LowImuValuesAccelX.distinct")
        acc_y = row.get("fc1LowImuValuesAccelY.distinct")
        acc_z = row.get("fc1LowImuValuesAccelZ.distinct")
        gyro_x = row.get("fc1LowImuValuesGyroX.distinct")
        gyro_y = row.get("fc1LowImuValuesGyroY.distinct")
        gyro_z = row.get("fc1LowImuValuesGyroZ.distinct")
        has_baro = baro_alt is not None
        has_gps = gps_lat is not None and gps_lon is not None and gps_alt is not None
        has_imu = all(
            v is not None
            for v in (acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z)
        )
        if has_baro:
            pkt = build_baro_packet(baro_alt, ts_bytes)
            _send_packet(pkt, csv_t_sec=t_sec)
        if has_imu:
            pkt = build_low_imu_packet(acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z, ts_bytes)
            _send_packet(pkt, csv_t_sec=t_sec)
        if has_gps:
            pkt = build_gps_packet(gps_lat, gps_lon, gps_alt, ts_bytes)
            _send_packet(pkt, csv_t_sec=t_sec)
    print("[csv] Replay finished.")
    if drift_n > 0:
        mean_drift = drift_sum / drift_n
        print(f"[csv] Timing (real elapsed vs CSV time): drift min={drift_min*1000:.2f} ms, max={drift_max*1000:.2f} ms, mean={mean_drift*1000:.2f} ms (positive = sent late)")

def main():
    run_csv_replay()

if __name__ == "__main__":
    main()