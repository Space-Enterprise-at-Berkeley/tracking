#pragma once

#include <Arduino.h>
#include <data_buff.h>
#include <PIDController.h>
#include <TimeUtil.h>
#include "ERegHat/StateMachine.h"
#include "ERegHat/HAL.h"
#include "ERegHat/Util.h"
#include "ERegHat/Comms.h"
#include "ERegHat/Config.h"
#include "ERegHat/FlowProfiles.h"
#include "ERegHat/Packets.h"

namespace StateMachine {
    
    class FlowState {
        private:
        PIDController *innerController_ = Util::getInnerController();
        PIDController *outerController_ = Util::getOuterController();
        unsigned long timeStarted_;
        unsigned long lastPrint_;
        float pressureSetpoint_;
        float angleSetpoint_;

        public:
        FlowState();
        void init();
        void update();
    };

    FlowState* getFlowState();

}