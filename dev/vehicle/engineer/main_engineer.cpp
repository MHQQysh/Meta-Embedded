//
// Created by Kerui Zhu on 7/10/2019.
// Modified by LaiXinyi on 7/19/2019.
//

/// Headers
#include "ch.hpp"
#include "hal.h"

#include "led.h"
#include "buzzer.h"
#include "common_macro.h"

#include "shell.h"
#include "can_interface.h"
#include "ahrs.h"
#include "remote_interpreter.h"
#include "sd_card_interface.h"

#include "chassis_interface.h"
#include "engineer_elevator_interface.h"
//#include "robotic_arm_interface.h"

#include "engineer_chassis_skd.h"
#include "engineer_elevator_skd.h"
//#include "robotic_arm_skd.h"

#include "engineer_elevator_logic.h"

#include "inspector_engineer.h"
#include "user_engineer.h"

#include "settings_engineer.h"

/// Vehicle Specific Configurations
#if defined(ENGINEER)
#include "vehicle_engineer.h"
#else
#error "File main_engineer.cpp should only be used for Engineer."
#endif

CANInterface can1(&CAND1);
CANInterface can2(&CAND2);

int main() {

    /*** --------------------------- Period 0. Fundamental Setup --------------------------- ***/

    halInit();
    chibios_rt::System::init();

    /*** ---------------------- Period 1. Modules Setup and Self-Check ---------------------- ***/

    /// Preparation of Period 1
    InspectorE::init(&can1, &can2);
    LED::all_off();

    /// Setup Shell
    Shell::start(THREAD_SHELL_PRIO);
    Shell::addCommands(mainProgramCommands);

    /// Setup SDCard
    if (SDCard::init()) {
        SDCard::read_all();
        LED::led_on(DEV_BOARD_LED_SD_CARD);  // LED 8 on if SD card inserted
    }

    LED::led_on(DEV_BOARD_LED_SYSTEM_INIT);  // LED 1 on now

    /// Setup CAN1 & CAN2
    can1.start(THREAD_CAN1_PRIO);
    can2.start(THREAD_CAN2_PRIO);
    chThdSleepMilliseconds(5);
    InspectorE::startup_check_can();  // check no persistent CAN Error. Block for 100 ms
    LED::led_on(DEV_BOARD_LED_CAN);  // LED 2 on now

    /// Start DMS Interface
    DMSInterface::init(4);
    // TODO: check DMS
    LED::led_on(DEV_BOARD_LED_DMS);  // LED 3 on now

    /// Setup Remote
    Remote::start();
    InspectorE::startup_check_remote();  // check Remote has signal. Block for 50 ms
    LED::led_on(DEV_BOARD_LED_REMOTE);  // LED 4 on now

    /// Setup GimbalIF
    EngineerGimbalIF::init();

    /// Setup Robotic Arm
    // TODO: write robotic arm

    /// Setup ElevatorIF
    EngineerElevatorIF::init(&can2);
    chThdSleepMilliseconds(10);
    InspectorE::startup_check_elevator_feedback();  // check elevator motors has continuous feedback. Block for 20 ms
    LED::led_on(DEV_BOARD_LED_ELEVATOR);  // LED 5 on now

    /// Setup ChassisIF
    ChassisIF::init(&can1);
    chThdSleepMilliseconds(10);
    InspectorE::startup_check_chassis_feedback();  // check chassis motors has continuous feedback. Block for 20 ms
    LED::led_on(DEV_BOARD_LED_CHASSIS);  // LED 6 on now

    /// Setup Referee
    Referee::init();

    /// Complete Period 1
    LED::green_on();  // LED Green on now


    /*** ------------ Period 2. Calibration and Start Logic Control Thread ----------- ***/

    /// Start SKDs
    EngineerChassisSKD::start(CHASSIS_WHEEL_BASE, CHASSIS_WHEEL_TREAD, CHASSIS_WHEEL_CIRCUMFERENCE, THREAD_CHASSIS_SKD_PRIO);
    EngineerChassisSKD::load_pid_params(CHASSIS_PID_V2I_PARAMS);
    EngineerElevatorSKD::start(THREAD_ELEVATOR_SKD_PRIO);
    EngineerElevatorSKD::load_pid_params(ELEVATOR_PID_A2V_PARAMS, ELEVATOR_PID_V2I_PARAMS, AIDED_MOTOR_PID_V2I_PARAMS, {0, 0, 0, 0, 0});

    /// Start LGs
    EngineerElevatorLG::init(THREAD_ELEVATOR_LG_PRIO);

    /// Start Inspector and User Threads
    InspectorE::start_inspection(THREAD_INSPECTOR_PRIO, THREAD_INSPECTOR_REFEREE_PRIO);
    UserE::start(THREAD_USER_PRIO, THREAD_USER_ACTION_PRIO, THREAD_USER_CLIENT_DATA_SEND_PRIO);

    /// Complete Period 2
    Buzzer::play_sound(Buzzer::sound_startup_intel, THREAD_BUZZER_PRIO);  // Now play the startup sound


    /*** ------------------------ Period 3. End of main thread ----------------------- ***/

    // Entering empty loop with low priority
#if CH_CFG_NO_IDLE_THREAD  // See chconf.h for what this #define means.
    // ChibiOS idle thread has been disabled, main() should implement infinite loop
    while (true) {}
#else
    // When vehicle() quits, the vehicle thread will somehow enter an infinite loop, so we set the
    // priority to lowest before quitting, to let other threads run normally
    chibios_rt::BaseThread::setPriority(IDLEPRIO);
#endif
    return 0;
}