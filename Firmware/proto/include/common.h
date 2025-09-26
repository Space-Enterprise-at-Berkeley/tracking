
#pragma once
#include <cinttypes>
#include <array>
#include <EspComms.h>
#define PACKET_SPEC_VERSION 1

typedef enum SystemMode {
    LAUNCH = 0,
    HOTFIRE = 1,
    COLDFLOW = 2,
    COLDFLOW_WITH_IGNITER = 3,
    GASFLOW = 4,
    WATERFLOW = 5,
} SystemMode;

typedef enum AbortCode {
    MANUAL = 0,
    NOS_OVERPRESSURE = 1,
    IPA_OVERPRESSURE = 2,
    ENGINE_OVERTEMP = 3,
    FAILED_IGNITION = 4,
    IGNITER_NO_CONTINUITY = 5,
    BURNWIRE_NO_CONTINUITY = 6,
    BURNWIRE_NO_BURNT = 7,
    NO_DASHBOARD_COMMS = 8,
    PROPELLANT_RUNOUT = 9,
    BREAKWIRE_NO_CONTINUITY = 10,
    BREAKWIRE_BROKE_EARLY = 11,
} AbortCode;

typedef enum ACActuatorActions {
    RETRACT_FULL = 0,
    EXTEND_FULL = 1,
    RETRACT_TIMED = 2,
    EXTEND_TIMED = 3,
    ON = 4,
    OFF = 5,
} ACActuatorActions;

typedef enum ACActuatorStatesType {
    RETRACTING = 0,
    EXTENDING = 1,
    OFF_STATE = 2,
} ACActuatorStatesType;

#define CHANNEL_AC_BURNWIRE 0
#ifdef BOARD_AC_1
#define IS_BOARD_FOR_AC_BURNWIRE true
#else
#define IS_BOARD_FOR_AC_BURNWIRE false
#endif

#define CHANNEL_AC_BREAKWIRE 1
#ifdef BOARD_AC_1
#define IS_BOARD_FOR_AC_BREAKWIRE true
#else
#define IS_BOARD_FOR_AC_BREAKWIRE false
#endif

#define CHANNEL_AC_NOS_MAIN_PRESS 2
#ifdef BOARD_AC_1
#define IS_BOARD_FOR_AC_NOS_MAIN_PRESS true
#else
#define IS_BOARD_FOR_AC_NOS_MAIN_PRESS false
#endif

#define CHANNEL_AC_NOS_MAIN_VENT 3
#ifdef BOARD_AC_1
#define IS_BOARD_FOR_AC_NOS_MAIN_VENT true
#else
#define IS_BOARD_FOR_AC_NOS_MAIN_VENT false
#endif

#define CHANNEL_AC_IPA_MAIN_PRESS 4
#ifdef BOARD_AC_1
#define IS_BOARD_FOR_AC_IPA_MAIN_PRESS true
#else
#define IS_BOARD_FOR_AC_IPA_MAIN_PRESS false
#endif

#define CHANNEL_AC_IPA_MAIN_VENT 5
#ifdef BOARD_AC_1
#define IS_BOARD_FOR_AC_IPA_MAIN_VENT true
#else
#define IS_BOARD_FOR_AC_IPA_MAIN_VENT false
#endif

#define CHANNEL_AC_IGNITER 7
#ifdef BOARD_AC_1
#define IS_BOARD_FOR_AC_IGNITER true
#else
#define IS_BOARD_FOR_AC_IGNITER false
#endif

#define CHANNEL_AC_NOS_GEMS 0
#ifdef BOARD_AC_2
#define IS_BOARD_FOR_AC_NOS_GEMS true
#else
#define IS_BOARD_FOR_AC_NOS_GEMS false
#endif

#define CHANNEL_AC_NOS_EMERGENCY_VENT 1
#ifdef BOARD_AC_2
#define IS_BOARD_FOR_AC_NOS_EMERGENCY_VENT true
#else
#define IS_BOARD_FOR_AC_NOS_EMERGENCY_VENT false
#endif

#define CHANNEL_AC_NOS_FILL 2
#ifdef BOARD_AC_2
#define IS_BOARD_FOR_AC_NOS_FILL true
#else
#define IS_BOARD_FOR_AC_NOS_FILL false
#endif

#define CHANNEL_AC_NOS_LINE_VENT 3
#ifdef BOARD_AC_2
#define IS_BOARD_FOR_AC_NOS_LINE_VENT true
#else
#define IS_BOARD_FOR_AC_NOS_LINE_VENT false
#endif

#define CHANNEL_AC_NOS_DRAIN 4
#ifdef BOARD_AC_2
#define IS_BOARD_FOR_AC_NOS_DRAIN true
#else
#define IS_BOARD_FOR_AC_NOS_DRAIN false
#endif

#define CHANNEL_PT_NOS_TANK 1
#ifdef BOARD_PT_1
#define IS_BOARD_FOR_PT_NOS_TANK true
#else
#define IS_BOARD_FOR_PT_NOS_TANK false
#endif

#define CHANNEL_PT_NOS_POPPET 2
#ifdef BOARD_PT_1
#define IS_BOARD_FOR_PT_NOS_POPPET true
#else
#define IS_BOARD_FOR_PT_NOS_POPPET false
#endif

#define CHANNEL_PT_IPA_POPPET 3
#ifdef BOARD_PT_1
#define IS_BOARD_FOR_PT_IPA_POPPET true
#else
#define IS_BOARD_FOR_PT_IPA_POPPET false
#endif

#define CHANNEL_PT_IPA_TANK 4
#ifdef BOARD_PT_1
#define IS_BOARD_FOR_PT_IPA_TANK true
#else
#define IS_BOARD_FOR_PT_IPA_TANK false
#endif

#define CHANNEL_PT_NOS_INJECTOR 5
#ifdef BOARD_PT_1
#define IS_BOARD_FOR_PT_NOS_INJECTOR true
#else
#define IS_BOARD_FOR_PT_NOS_INJECTOR false
#endif

#define CHANNEL_PT_NOS_FILL_LINE 6
#ifdef BOARD_PT_1
#define IS_BOARD_FOR_PT_NOS_FILL_LINE true
#else
#define IS_BOARD_FOR_PT_NOS_FILL_LINE false
#endif

#define CHANNEL_PT_IPA_INJECTOR 7
#ifdef BOARD_PT_1
#define IS_BOARD_FOR_PT_IPA_INJECTOR true
#else
#define IS_BOARD_FOR_PT_IPA_INJECTOR false
#endif

#define CHANNEL_PT_CHAMBER 0
#ifdef BOARD_PT_2
#define IS_BOARD_FOR_PT_CHAMBER true
#else
#define IS_BOARD_FOR_PT_CHAMBER false
#endif

#define CHANNEL_PT_PNEUMATICS 1
#ifdef BOARD_PT_2
#define IS_BOARD_FOR_PT_PNEUMATICS true
#else
#define IS_BOARD_FOR_PT_PNEUMATICS false
#endif

#define CHANNEL_TC_NOS_INJ 7
#ifdef BOARD_TC_1
#define IS_BOARD_FOR_TC_NOS_INJ true
#else
#define IS_BOARD_FOR_TC_NOS_INJ false
#endif

#define CHANNEL_TC_IPA_INJ 7
#ifdef BOARD_TC_2
#define IS_BOARD_FOR_TC_IPA_INJ true
#else
#define IS_BOARD_FOR_TC_IPA_INJ false
#endif

#define CHANNEL_TC_NOS_TANK 5
#ifdef BOARD_TC_3
#define IS_BOARD_FOR_TC_NOS_TANK true
#else
#define IS_BOARD_FOR_TC_NOS_TANK false
#endif

#define CHANNEL_TC_ENGINE_2_1 1
#ifdef BOARD_TC_4
#define IS_BOARD_FOR_TC_ENGINE_2_1 true
#else
#define IS_BOARD_FOR_TC_ENGINE_2_1 false
#endif

#define CHANNEL_TC_ENGINE_2_2 2
#ifdef BOARD_TC_4
#define IS_BOARD_FOR_TC_ENGINE_2_2 true
#else
#define IS_BOARD_FOR_TC_ENGINE_2_2 false
#endif

#define CHANNEL_TC_ENGINE_2_4 3
#ifdef BOARD_TC_4
#define IS_BOARD_FOR_TC_ENGINE_2_4 true
#else
#define IS_BOARD_FOR_TC_ENGINE_2_4 false
#endif

#define CHANNEL_TC_ENGINE_3_1 4
#ifdef BOARD_TC_4
#define IS_BOARD_FOR_TC_ENGINE_3_1 true
#else
#define IS_BOARD_FOR_TC_ENGINE_3_1 false
#endif

#define CHANNEL_TC_ENGINE_3_2 5
#ifdef BOARD_TC_4
#define IS_BOARD_FOR_TC_ENGINE_3_2 true
#else
#define IS_BOARD_FOR_TC_ENGINE_3_2 false
#endif

#define CHANNEL_TC_ENGINE_3_3 6
#ifdef BOARD_TC_4
#define IS_BOARD_FOR_TC_ENGINE_3_3 true
#else
#define IS_BOARD_FOR_TC_ENGINE_3_3 false
#endif

#define CHANNEL_TC_ENGINE_3_4 7
#ifdef BOARD_TC_4
#define IS_BOARD_FOR_TC_ENGINE_3_4 true
#else
#define IS_BOARD_FOR_TC_ENGINE_3_4 false
#endif

#define CHANNEL_LC_ENGINE_1 1
#ifdef BOARD_LC_1
#define IS_BOARD_FOR_LC_ENGINE_1 true
#else
#define IS_BOARD_FOR_LC_ENGINE_1 false
#endif

#define CHANNEL_LC_ENGINE_2 2
#ifdef BOARD_LC_1
#define IS_BOARD_FOR_LC_ENGINE_2 true
#else
#define IS_BOARD_FOR_LC_ENGINE_2 false
#endif

#define CHANNEL_LC_ENGINE_3 3
#ifdef BOARD_LC_1
#define IS_BOARD_FOR_LC_ENGINE_3 true
#else
#define IS_BOARD_FOR_LC_ENGINE_3 false
#endif

#define CHANNEL_LC_NOS 0
#ifdef BOARD_LC_2
#define IS_BOARD_FOR_LC_NOS true
#else
#define IS_BOARD_FOR_LC_NOS false
#endif

#define CHANNEL_LC_IPA 2
#ifdef BOARD_LC_2
#define IS_BOARD_FOR_LC_IPA true
#else
#define IS_BOARD_FOR_LC_IPA false
#endif
