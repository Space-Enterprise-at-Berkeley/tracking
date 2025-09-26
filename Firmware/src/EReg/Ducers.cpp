#include "Ducers.h"

namespace Ducers {

    float upstreamPT;
    float downstreamPT;

    void updateUpstreamPT() {
        upstreamPT = HAL::readPTVoltage(2);
    }

    void updateDownstreamPT() {
        downstreamPT = HAL::readPTVoltage(3);
    }

    float interpolate1000(double rawValue) {
        return (rawValue - 0.5) * 250;
    }

    float interpolate5000(double rawValue) {
        return (rawValue * 1000);
    }

    float readPressurantPT() {
        updateUpstreamPT();
        return max((float)1, interpolate5000(upstreamPT));
    }

    float readTankPT() {
        updateDownstreamPT();
        return max((float)1, interpolate1000(downstreamPT));
    }

    float readDownstreamPT() {
        return readTankPT();
    }

    float readUpstreamPT() {
        return readPressurantPT();
    }




}