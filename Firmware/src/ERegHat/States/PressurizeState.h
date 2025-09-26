#pragma once

#include <Arduino.h>
#include <PIDController.h>
#include "ERegHat/StateMachine.h"
#include "ERegHat/HAL.h"
#include "ERegHat/Util.h"
#include "ERegHat/Packets.h"
#include "ERegHat/Config.h"

namespace StateMachine {

    class PressurizeState {
        private:
        PIDController *innerController_ = Util::getInnerController(); 
        PIDController *outerController_ = Util::getOuterController(); 
        unsigned long timeStarted_;
        unsigned long lastPrint_;
        float pressureSetpoint_ = Config::pressureSetpoint;;
        float angleSetpoint_;

        public:
        PressurizeState();
        void init();
        void update();
    };

    PressurizeState* getPressurizeState();
}