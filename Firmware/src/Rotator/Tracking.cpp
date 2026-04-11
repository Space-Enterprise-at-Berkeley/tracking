#include "Tracking.h"
#include <cmath>

namespace Tracking {
    void resetTracking(){
        tracking = true;
        trackingState = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Xpos, Xvel, Xaccel, Ypos, ...
        accelCalSamples = 0;
        GPSCalSamples = 0;
        baroCalSamples = 0;
        quat = {1, 0, 0, 0};
        apogeeReached = false;
        // TODO: reset all calibration constants (check all of them)
        // Insert other preflight initialization (e.g. zeroing baro) here
    }
    void stopTracking(){
        tracking = false;
    }
    bool accelUpdate(Comms::Packet packet, uint8_t ip){
        if(!tracking || apogeeReached) return false;

        // Insert accel callback here
        PacketLowIMUValues parsed_packet = PacketLowIMUValues::fromRawPacket(&packet);

        float accelZ = parsed_packet.m_AccelZ;
        float accelY = parsed_packet.m_AccelY;
        float accelX = parsed_packet.m_AccelX; 

        float gyroX = parsed_packet.m_GyroX;
        float gyroY = parsed_packet.m_GyroY;
        float gyroZ = parsed_packet.m_GyroZ;

        if(accelCalSamples < accelCalThreshold){
            accelCalSamples ++;
            // average = last * (n-1)/n + new * 1/n
            // Do initial averaging
            launchAcceleration[0] = (1/accelCalSamples)*(launchAcceleration[0] * (accelCalSamples-1) + accelX);
            launchAcceleration[1] = (1/accelCalSamples)*(launchAcceleration[1] * (accelCalSamples-1) + accelY);
            launchAcceleration[2] = (1/accelCalSamples)*(launchAcceleration[2] * (accelCalSamples-1) + accelZ);
            launchGyro[0] = (1/accelCalSamples)*(launchGyro[0] * (accelCalSamples-1) + gyroX);
            launchGyro[1] = (1/accelCalSamples)*(launchGyro[1] * (accelCalSamples-1) + gyroY);
            launchGyro[2] = (1/accelCalSamples)*(launchGyro[2] * (accelCalSamples-1) + gyroZ);
            return false; //data validated, and we have set our launch acceleration and gyro

            // TODO: divide to make the average correct
        }

        //reduce biases from launch accel and gyro
        accelX = (accelX - (launchAcceleration[0] - 1)) * 9.80655; 
        accelY = (accelY - launchAcceleration[1]) * 9.80655;
        accelZ = (accelZ - launchAcceleration[2]) * 9.80655;
        gyroX = (gyroX - launchGyro[0])*(PI/180);
        gyroY = (gyroY - launchGyro[1])*(PI/180);
        gyroZ = (gyroZ - launchGyro[2])*(PI/180);

        Quaternion qDot;
        qDot.w = 0.5 * (-quat.x * gyroX - quat.y * gyroY - quat.z * gyroZ);
        qDot.x = 0.5 * (quat.w * gyroX + quat.y * gyroZ - quat.z * gyroY);
        qDot.y = 0.5 * (quat.w * gyroY - quat.x * gyroZ + quat.z * gyroX);
        qDot.z = 0.5 * (quat.w * gyroZ + quat.x * gyroY - quat.y * gyroX);

        quat.w += qDot.w * dt;
        quat.x += qDot.x * dt;
        quat.y += qDot.y * dt;
        quat.z += qDot.z * dt;

        quat.normalize();

        Quaternion accelQuat = {0, accelX, accelY, accelZ};
        Quaternion qConj = quat.conjugate();
        // rotated = q * accel * q^-1
        Quaternion temp = multiply(q, accelQuat);
        Quaternion rotated = multiply(temp, qConj);

        float ax_world = rotated.x - 9.80655;
        float ay_world = rotated.y;
        float az_world = rotated.z;

        //Kalman filter update here!!!!
        //simple integration to get velocity and position
        trackingState[7] += ax_world * dt; //since x is actually upward
        trackingState[4] += ay_world * dt; 
        trackingState[1] += az_world * dt; //since z is actually forward
        trackingState[0] += trackingState[1] * dt;
        trackingState[3] += trackingState[4] * dt;
        trackingState[6] += trackingState[7] * dt;

        if(trackingState[6] > apoAltThresh && trackingState[7] < apoVelThresh){ //if vertical velocity is negative for some time, we have reached apogee
            apogeeReached = true;
        }
        return true; //data validated
    }
    bool GPSUpdate(Comms::Packet packet, uint8_t ip){
        if (!tracking) return false;

        // Insert GPS callback here
        PacketGPSValues parsed_packet = PacketGPSValues::fromRawPacket(&packet);
        float lat = parsed_packet.m_Latitude;
        float lon = parsed_packet.m_Longitude;
        float alt = parsed_packet.m_Altitude;
        uint8_t siv = parsed_packet.m_Siv;

        if (siv < 10) return false;

        if(GPSCalSamples < GPSCalThreshold){
            // TODO: do the same averaging here
            launchPosition[0] = lat;
            launchPosition[1] = lon;
            launchPosition[2] = alt;
            GPSCalSamples++;
            return false; //calibration
        }

        float rocketPosition[] = {lat,lon,alt};
        float enu[3];
        Rotator::gpsSeparationENU(rocketPosition, launchPosition.data(), enu);
        //Update the tracker with the new position
        //Something something Kalman Filter here
        trackingState[0] = enu[0];
        trackingState[3] = enu[1];
        trackingState[6] = enu[2];
        return true; //data validated
    }
    bool baroUpdate(Comms::Packet packet, uint8_t ip){
        if (!tracking) return false;

        // Insert baro callback here
        PacketBaroValues parsed_packet = PacketBaroValues::fromRawPacket(&packet);
        float altitude = parsed_packet.m_Altitude;
        float pressure = parsed_packet.m_Pressure;

        if(baroCalSamples < baroCalThreshold){
            // TODO: Calibration
            launchPressure = pressure;
            launchPosition[2] = altitude;
            baroCalSamples ++;
            return false;
        }
        //if barometer altitude doesn't differ by a huge amount according to our last update
        if(std::abs(altitude - trackingState[6]) < 500){
            if(trackingState[6] == 0.0 && trackingState[0] == 0.0 && trackingState[3] == 0.0){
                //if GPS is bad, use the barometer to estimate vertical position
                //Kalman filter here!!!!
                trackingState[6] = altitude - launchPosition[2];
                return true;
                //data validated, but we are using barometer data instead of GPS, so we only update the Z position
            }
        }
        return false; //data not validated
    }


}