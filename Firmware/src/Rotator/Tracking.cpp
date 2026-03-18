#include "Tracking.h"

namespace Tracking {
    void resetTracking(){
        trackingState = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Xpos, Xvel, Xaccel, Ypos, ...
        // Insert other preflight initialization (e.g. zeroing baro) here
    }
    bool accelUpdate(Comms::Packet packet, uint8_t ip){
        // Insert accel callback here
        return true; // whether or not the packet was accepted
    }
    bool GPSUpdate(Comms::Packet packet, uint8_t ip){
        // Insert GPS callback here
        return true;
    }
    bool baroUpdate(Comms::Packet packet, uint8_t ip){
        // Insert baro callback here
        return true;
    }
}