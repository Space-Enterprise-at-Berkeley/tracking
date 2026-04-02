#!/usr/bin/env python3
"""
Test receiver for packet-csv.py UDP output.

Usage:
  1. Start the receiver first (it binds to the port):
       python3 test_packet_receiver.py [--port 42099] [--print] [--count N] [--out received.csv]

  2. In another terminal, run the sender:
       python3 packet-csv.py [--udp 127.0.0.1:42099] [--print]

  3. Receiver will log packets, verify checksums, decode Baro/IMU/GPS and optionally
     write to CSV for comparison with rotatordatanew.csv.

  Options:
    --port    UDP port to listen on (default: 42099)
    --print   Print each packet (id, ts, decoded fields)
    --count N Stop after N packets (default: run until Ctrl+C)
    --out F   Append received packets to CSV F (columns: t_sec, pkt_id, baro_alt, gps_lat, gps_lon, gps_alt, accel_x,y,z, gyro_x,y,z)
"""
import argparse
import socket
import struct
import sys

PKT_ID_BARO = 5
PKT_ID_LOW_IMU = 8
PKT_ID_GPS = 10

def compute_checksum(packet_bytes: list[int]) -> int:
    if len(packet_bytes) < 6:
        return -1
    pkt_id, pkt_len = packet_bytes[0], packet_bytes[1]
    ts_bytes = packet_bytes[2:6]
    data = packet_bytes[6:6 + pkt_len]
    sum1 = sum2 = 0
    for b in [pkt_id, pkt_len] + ts_bytes + data:
        sum1 = (sum1 + b) & 0xFF
        sum2 = (sum2 + sum1) & 0xFF
    return (sum2 << 8) | sum1

def verify_packet(raw: bytes) -> bool:
    if len(raw) < 8:
        return False
    pkt_id, pkt_len = raw[0], raw[1]
    if pkt_len > 256 or 8 + pkt_len > len(raw):
        return False
    inner = list(raw[:6]) + list(raw[8:8 + pkt_len])
    csum = compute_checksum(inner)
    return csum == (raw[6] | (raw[7] << 8))

def decode_baro(data: bytes):
    if len(data) < 12:
        return None
    return struct.unpack("<fff", data[:12])  # altitude, pressure, temp

def decode_imu(data: bytes):
    if len(data) < 24:
        return None
    return struct.unpack("<ffffff", data[:24])  # accel x,y,z, gyro x,y,z

def decode_gps(data: bytes):
    if len(data) < 29:
        return None
    lat, lon, alt = struct.unpack("<fff", data[:12])
    return (lat, lon, alt)

def main():
    ap = argparse.ArgumentParser(description="UDP receiver to test packet-csv.py output")
    ap.add_argument("--port", type=int, default=42099, help="UDP port to bind")
    ap.add_argument("--print", dest="do_print", action="store_true", help="Print each packet")
    ap.add_argument("--count", type=int, default=0, help="Stop after N packets (0 = forever)")
    ap.add_argument("--out", type=str, default="", help="Append decoded rows to CSV file")
    args = ap.parse_args()

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind(("0.0.0.0", args.port))
    print(f"Listening on 0.0.0.0:{args.port} (start packet-csv.py in another terminal). Ctrl+C to stop.", file=sys.stderr)

    out_f = None
    if args.out:
        out_f = open(args.out, "a", encoding="utf-8")
        need_header = out_f.tell() == 0
        if need_header:
            out_f.write("t_sec,pkt_id,baro_alt,gps_lat,gps_lon,gps_alt,accel_x,accel_y,accel_z,gyro_x,gyro_y,gyro_z\n")

    n = 0
    try:
        while True:
            raw, _ = sock.recvfrom(65535)
            # Loopback format: 1 byte length + source IP + inner packet
            if len(raw) > 1 and raw[0] < 20 and raw[0] > 0:
                raw = raw[1 + raw[0]:]
            if len(raw) < 8:
                continue
            if not verify_packet(raw):
                print("BAD checksum", len(raw), file=sys.stderr)
                continue
            n += 1
            pkt_id, pkt_len = raw[0], raw[1]
            ts = struct.unpack("<I", raw[2:6])[0]
            data = raw[8:8 + pkt_len]
            t_sec = ts / 1000.0  # approximate for display

            row = {"t_sec": "", "pkt_id": pkt_id, "baro_alt": "", "gps_lat": "", "gps_lon": "", "gps_alt": "",
                   "accel_x": "", "accel_y": "", "accel_z": "", "gyro_x": "", "gyro_y": "", "gyro_z": ""}
            row["t_sec"] = f"{t_sec:.3f}"

            if pkt_id == PKT_ID_BARO:
                dec = decode_baro(data)
                if dec:
                    row["baro_alt"] = f"{dec[0]:.6f}"
                    if args.do_print:
                        print(f"Baro  ts={ts} alt={dec[0]:.4f} pressure={dec[1]} temp={dec[2]}")
            elif pkt_id == PKT_ID_LOW_IMU:
                dec = decode_imu(data)
                if dec:
                    row["accel_x"], row["accel_y"], row["accel_z"] = f"{dec[0]:.6f}", f"{dec[1]:.6f}", f"{dec[2]:.6f}"
                    row["gyro_x"], row["gyro_y"], row["gyro_z"] = f"{dec[3]:.6f}", f"{dec[4]:.6f}", f"{dec[5]:.6f}"
                    if args.do_print:
                        print(f"IMU   ts={ts} accel=({dec[0]:.4f},{dec[1]:.4f},{dec[2]:.4f}) gyro=({dec[3]:.4f},{dec[4]:.4f},{dec[5]:.4f})")
            elif pkt_id == PKT_ID_GPS:
                dec = decode_gps(data)
                if dec:
                    row["gps_lat"], row["gps_lon"], row["gps_alt"] = f"{dec[0]:.6f}", f"{dec[1]:.6f}", f"{dec[2]:.6f}"
                    if args.do_print:
                        print(f"GPS   ts={ts} lat={dec[0]:.4f} lon={dec[1]:.4f} alt={dec[2]:.4f}")
            else:
                if args.do_print:
                    print(f"id={pkt_id} len={pkt_len} ts={ts}")

            if out_f:
                out_f.write(",".join([row["t_sec"], str(row["pkt_id"]), row["baro_alt"], row["gps_lat"], row["gps_lon"],
                                      row["gps_alt"], row["accel_x"], row["accel_y"], row["accel_z"],
                                      row["gyro_x"], row["gyro_y"], row["gyro_z"]]) + "\n")
                out_f.flush()

            if args.count and n >= args.count:
                break
    except KeyboardInterrupt:
        pass
    finally:
        if out_f:
            out_f.close()
    print(f"Received {n} packets.", file=sys.stderr)

if __name__ == "__main__":
    main()
