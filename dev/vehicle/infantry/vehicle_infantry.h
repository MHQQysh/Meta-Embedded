//
// Created by liuzikai on 2019-04-22.
// This file contains common parameters for infantry
//

#ifndef META_INFANTRY_VEHICLE_INFANTRY_H
#define META_INFANTRY_VEHICLE_INFANTRY_H

/// Module Enable
#define INFANTRY_GIMBAL_ENABLE              TRUE
#define INFANTRY_CHASSIS_ENABLE             TRUE
#define INFANTRY_SUPER_CAPACITOR_ENABLE     TRUE
#define INFANTRY_VISION_ENABLE              TRUE

/// AHRS Configurations
#define ON_BOARD_AHRS_MATRIX {{0.0f, -1.0f, 0.0f}, \
                              {1.0f, 0.0f, 0.0f}, \
                              {0.0f, 0.0f, 1.0f}}


/// Gimbal and Shoot Installation Configurations

#define GIMBAL_YAW_CAN_CHANNEL      (GimbalIF::can_channel_2)
#define GIMBAL_PITCH_CAN_CHANNEL    (GimbalIF::can_channel_1)
#define GIMBAL_SUB_PITCH_CAN_CHANNEL (GimbalIF::none_can_channel)
#define GIMBAL_BULLET_CAN_CHANNEL   (GimbalIF::can_channel_1)
#define GIMBAL_FW_LEFT_CAN_CHANNEL  (GimbalIF::can_channel_1)
#define GIMBAL_FW_RIGHT_CAN_CHANNEL (GimbalIF::can_channel_1)

#define GIMBAL_YAW_CAN_ID         4
#define GIMBAL_PITCH_CAN_ID       5
#define GIMBAL_SUB_PITCH_CAN_ID   7
#define GIMBAL_BULLET_CAN_ID      6
#define GIMBAL_FW_LEFT_CAN_ID     2
#define GIMBAL_FW_RIGHT_CAN_ID    3

#define GIMBAL_YAW_MOTOR_TYPE      (CANInterface::GM6020)
#define GIMBAL_PITCH_MOTOR_TYPE    (CANInterface::GM6020)
#define GIMBAL_SUB_PITCH_MOTOR_TYPE (CANInterface::NONE_MOTOR)
#define SHOOT_BULLET_MOTOR_TYPE    (CANInterface::M2006)
#define GIMBAL_FW_LEFT_MOTOR_TYPE  (CANInterface::M3508)
#define GIMBAL_FW_RIGHT_MOTOR_TYPE (CANInterface::M3508)

#define GIMBAL_MOTOR_CONFIG \
{ {GIMBAL_YAW_CAN_CHANNEL,          GIMBAL_YAW_CAN_ID,          GIMBAL_YAW_MOTOR_TYPE}, \
  {GIMBAL_PITCH_CAN_CHANNEL,        GIMBAL_PITCH_CAN_ID,        GIMBAL_PITCH_MOTOR_TYPE}, \
  {GIMBAL_SUB_PITCH_CAN_CHANNEL,    GIMBAL_SUB_PITCH_CAN_ID,    GIMBAL_SUB_PITCH_MOTOR_TYPE}, \
  {GIMBAL_BULLET_CAN_CHANNEL,       GIMBAL_BULLET_CAN_ID,       SHOOT_BULLET_MOTOR_TYPE}, \
  {GIMBAL_FW_LEFT_CAN_CHANNEL,      GIMBAL_FW_LEFT_CAN_ID,      GIMBAL_FW_LEFT_MOTOR_TYPE}, \
  {GIMBAL_FW_RIGHT_CAN_CHANNEL,     GIMBAL_FW_RIGHT_CAN_ID,     GIMBAL_FW_RIGHT_MOTOR_TYPE} }

#define CHASSIS_FR_CHANNEL      (ChassisIF::can_channel_2)
#define CHASSIS_FL_CHANNEL      (ChassisIF::can_channel_2)
#define CHASSIS_BL_CHANNEL      (ChassisIF::can_channel_2)
#define CHASSIS_BR_CHANNEL      (ChassisIF::can_channel_2)

#define CHASSIS_FR_CAN_ID      0
#define CHASSIS_FL_CAN_ID      1
#define CHASSIS_BL_CAN_ID      2
#define CHASSIS_BR_CAN_ID      3

#define CHASSIS_FR_MOTOR_TYPE  (CANInterface::M3508)
#define CHASSIS_FL_MOTOR_TYPE  (CANInterface::M3508)
#define CHASSIS_BL_MOTOR_TYPE  (CANInterface::M3508)
#define CHASSIS_BR_MOTOR_TYPE  (CANInterface::M3508)

#define CHASSIS_MOTOR_CONFIG \
{ {CHASSIS_FR_CHANNEL, CHASSIS_FR_CAN_ID, CHASSIS_FR_MOTOR_TYPE}, \
  {CHASSIS_FL_CHANNEL, CHASSIS_FL_CAN_ID, CHASSIS_FL_MOTOR_TYPE}, \
  {CHASSIS_BL_CHANNEL, CHASSIS_BL_CAN_ID, CHASSIS_BL_MOTOR_TYPE}, \
  {CHASSIS_BR_CHANNEL, CHASSIS_BR_CAN_ID, CHASSIS_BR_MOTOR_TYPE} }

#define GIMBAL_YAW_INSTALL_DIRECTION    (GimbalSKD::POSITIVE)
#define GIMBAL_PITCH_INSTALL_DIRECTION  (GimbalSKD::POSITIVE)
#define GIMBAL_SUB_PITCH_INSTALL_DIRECTION (GimbalSKD::POSITIVE) // Todo: measure the real value
#define SHOOT_BULLET_INSTALL_DIRECTION  (ShootSKD::POSITIVE)
#define SHOOT_DEGREE_PER_BULLET 45.0f  // rotation degree of bullet loader for each bullet

#define GIMBAL_ANGLE_INSTALLATION_MATRIX {{1.0f, 0.0f, 0.0f}, \
                                          {0.0f, 1.0f, 0.0f}, \
                                          {0.0f, 0.0f, -1.0f}}


#define GIMBAL_GYRO_INSTALLATION_MATRIX {{0.0f,  1.0f, 0.0f}, \
                                         {0.0f,  0.0f,  -1.0f}, \
                                         {-1.0f, 0.0f,  0.0f}}

#define MPU6500_BIAS_DATA_ID 0x0001

/// Gimbal and Shoot PID Parameters
#define GIMBAL_PID_YAW_A2V_KP 25.0f
#define GIMBAL_PID_YAW_A2V_KI 0.0f
#define GIMBAL_PID_YAW_A2V_KD 1600.00f
#define GIMBAL_PID_YAW_A2V_I_LIMIT 0.0f
#define GIMBAL_PID_YAW_A2V_OUT_LIMIT 720.0f
#define GIMBAL_PID_YAW_A2V_PARAMS \
    {GIMBAL_PID_YAW_A2V_KP, GIMBAL_PID_YAW_A2V_KI, GIMBAL_PID_YAW_A2V_KD, \
    GIMBAL_PID_YAW_A2V_I_LIMIT, GIMBAL_PID_YAW_A2V_OUT_LIMIT}

#define GIMBAL_PID_YAW_V2I_KP 25.0f
#define GIMBAL_PID_YAW_V2I_KI 0.15f
#define GIMBAL_PID_YAW_V2I_KD 0.0f
#define GIMBAL_PID_YAW_V2I_I_LIMIT 5000.0f
#define GIMBAL_PID_YAW_V2I_OUT_LIMIT 30000.0f
#define GIMBAL_PID_YAW_V2I_PARAMS \
    {GIMBAL_PID_YAW_V2I_KP, GIMBAL_PID_YAW_V2I_KI, GIMBAL_PID_YAW_V2I_KD, \
    GIMBAL_PID_YAW_V2I_I_LIMIT, GIMBAL_PID_YAW_V2I_OUT_LIMIT}

#define GIMBAL_PID_PITCH_A2V_KP 30.0f
#define GIMBAL_PID_PITCH_A2V_KI 0.0f
#define GIMBAL_PID_PITCH_A2V_KD 400.0f
#define GIMBAL_PID_PITCH_A2V_I_LIMIT 0.0f
#define GIMBAL_PID_PITCH_A2V_OUT_LIMIT 720.0f
#define GIMBAL_PID_PITCH_A2V_PARAMS \
    {GIMBAL_PID_PITCH_A2V_KP, GIMBAL_PID_PITCH_A2V_KI, GIMBAL_PID_PITCH_A2V_KD, \
    GIMBAL_PID_PITCH_A2V_I_LIMIT, GIMBAL_PID_PITCH_A2V_OUT_LIMIT}

#define GIMBAL_PID_PITCH_V2I_KP 100.0f
#define GIMBAL_PID_PITCH_V2I_KI 1.0f
#define GIMBAL_PID_PITCH_V2I_KD 0.00f
#define GIMBAL_PID_PITCH_V2I_I_LIMIT 5000.0f
#define GIMBAL_PID_PITCH_V2I_OUT_LIMIT 30000.0f
#define GIMBAL_PID_PITCH_V2I_PARAMS \
    {GIMBAL_PID_PITCH_V2I_KP, GIMBAL_PID_PITCH_V2I_KI, GIMBAL_PID_PITCH_V2I_KD, \
    GIMBAL_PID_PITCH_V2I_I_LIMIT, GIMBAL_PID_PITCH_V2I_OUT_LIMIT}

#define GIMBAL_RESTRICT_YAW_MIN_ANGLE -90
#define GIMBAL_RESTRICT_YAW_MAX_ANGLE 90
#define GIMBAL_RESTRICT_YAW_VELOCITY 20

#define GIMBAL_PID_SUB_PITCH_A2V_KP 7.8f
#define GIMBAL_PID_SUB_PITCH_A2V_KI 0.0f
#define GIMBAL_PID_SUB_PITCH_A2V_KD 0.08f
#define GIMBAL_PID_SUB_PITCH_A2V_I_LIMIT 1000.0f
#define GIMBAL_PID_SUB_PITCH_A2V_OUT_LIMIT 3000.0f
#define GIMBAL_PID_SUB_PITCH_A2V_PARAMS \
    {GIMBAL_PID_SUB_PITCH_A2V_KP, GIMBAL_PID_SUB_PITCH_A2V_KI, GIMBAL_PID_SUB_PITCH_A2V_KD, \
    GIMBAL_PID_SUB_PITCH_A2V_I_LIMIT, GIMBAL_PID_SUB_PITCH_A2V_OUT_LIMIT}

#define GIMBAL_PID_SUB_PITCH_V2I_KP 24.0f
#define GIMBAL_PID_SUB_PITCH_V2I_KI 0.21f
#define GIMBAL_PID_SUB_PITCH_V2I_KD 0.0f
#define GIMBAL_PID_SUB_PITCH_V2I_I_LIMIT 10000.0f
#define GIMBAL_PID_SUB_PITCH_V2I_OUT_LIMIT 30000.0f
#define GIMBAL_PID_SUB_PITCH_V2I_PARAMS \
    {GIMBAL_PID_SUB_PITCH_V2I_KP, GIMBAL_PID_SUB_PITCH_V2I_KI, GIMBAL_PID_SUB_PITCH_V2I_KD, \
    GIMBAL_PID_SUB_PITCH_V2I_I_LIMIT, GIMBAL_PID_SUB_PITCH_V2I_OUT_LIMIT}

#define SHOOT_PID_BULLET_LOADER_A2V_KP 20.0f  // a number large enough, see shoot speed note at ShootSKD
#define SHOOT_PID_BULLET_LOADER_A2V_KI 0.0f
#define SHOOT_PID_BULLET_LOADER_A2V_KD 0.0f
#define SHOOT_PID_BULLET_LOADER_A2V_I_LIMIT 0.0f
#define SHOOT_PID_BULLET_LOADER_A2V_OUT_LIMIT 360.0f  // will be replaced, see shoot speed note at ShootSKD
#define SHOOT_PID_BULLET_LOADER_A2V_PARAMS \
    {SHOOT_PID_BULLET_LOADER_A2V_KP, SHOOT_PID_BULLET_LOADER_A2V_KI, SHOOT_PID_BULLET_LOADER_A2V_KD, \
    SHOOT_PID_BULLET_LOADER_A2V_I_LIMIT, SHOOT_PID_BULLET_LOADER_A2V_OUT_LIMIT}

#define SHOOT_PID_BULLET_LOADER_V2I_KP 55.0f
#define SHOOT_PID_BULLET_LOADER_V2I_KI 5.0f
#define SHOOT_PID_BULLET_LOADER_V2I_KD 0.0f
#define SHOOT_PID_BULLET_LOADER_V2I_I_LIMIT 10000.0f
#define SHOOT_PID_BULLET_LOADER_V2I_OUT_LIMIT 10000.0f
#define SHOOT_PID_BULLET_LOADER_V2I_PARAMS \
    {SHOOT_PID_BULLET_LOADER_V2I_KP, SHOOT_PID_BULLET_LOADER_V2I_KI, SHOOT_PID_BULLET_LOADER_V2I_KD, \
    SHOOT_PID_BULLET_LOADER_V2I_I_LIMIT, SHOOT_PID_BULLET_LOADER_V2I_OUT_LIMIT}

//TODO: Need to revised to the newest pid params.
#define SHOOT_PID_FW_LEFT_V2I_KP 26.0f
#define SHOOT_PID_FW_LEFT_V2I_KI 0.1f
#define SHOOT_PID_FW_LEFT_V2I_KD 0.02f
#define SHOOT_PID_FW_LEFT_V2I_I_LIMIT 2000.0f
#define SHOOT_PID_FW_LEFT_V2I_OUT_LIMIT 6000.0f
#define SHOOT_PID_FW_LEFT_V2I_PARAMS \
    {SHOOT_PID_FW_LEFT_V2I_KP, SHOOT_PID_FW_LEFT_V2I_KI, SHOOT_PID_FW_LEFT_V2I_KD, \
    SHOOT_PID_FW_LEFT_V2I_I_LIMIT, SHOOT_PID_FW_LEFT_V2I_OUT_LIMIT}

//TODO: Need to revised to the newest pid params.
#define SHOOT_PID_FW_RIGHT_V2I_KP 26.0f
#define SHOOT_PID_FW_RIGHT_V2I_KI 0.1f
#define SHOOT_PID_FW_RIGHT_V2I_KD 0.02f
#define SHOOT_PID_FW_RIGHT_V2I_I_LIMIT 2000.0f
#define SHOOT_PID_FW_RIGHT_V2I_OUT_LIMIT 6000.0f
#define SHOOT_PID_FW_RIGHT_V2I_PARAMS \
    {SHOOT_PID_FW_RIGHT_V2I_KP, SHOOT_PID_FW_RIGHT_V2I_KI, SHOOT_PID_FW_RIGHT_V2I_KD, \
    SHOOT_PID_FW_RIGHT_V2I_I_LIMIT, SHOOT_PID_FW_RIGHT_V2I_OUT_LIMIT}

/// Chassis Mechanism Parameters
#define CHASSIS_WHEEL_BASE  420.0f                     // distance between front axle and the back axle [mm]
#define CHASSIS_WHEEL_TREAD 372.0f                     // distance between left and right wheels [mm]
#define CHASSIS_WHEEL_CIRCUMFERENCE 478.0f             // circumference of wheels [mm]


/// Chassis PID Parameters
#define CHASSIS_PID_V2I_KP 26.0f
#define CHASSIS_PID_V2I_KI 0.1f
#define CHASSIS_PID_V2I_KD 0.02f
#define CHASSIS_PID_V2I_I_LIMIT 2000.0f
#define CHASSIS_PID_V2I_OUT_LIMIT 6000.0f
#define CHASSIS_PID_V2I_PARAMS \
    {CHASSIS_PID_V2I_KP, CHASSIS_PID_V2I_KI, CHASSIS_PID_V2I_KD, \
    CHASSIS_PID_V2I_I_LIMIT, CHASSIS_PID_V2I_OUT_LIMIT}

#define CHASSIS_CLIP_PID_V2I_KP 26.0f
#define CHASSIS_CLIP_PID_V2I_KI 0.1f
#define CHASSIS_CLIP_PID_V2I_KD 0.02f
#define CHASSIS_CLIP_PID_V2I_I_LIMIT 2000.0f
#define CHASSIS_CLIP_PID_V2I_OUT_LIMIT 6000.0f
#define CHASSIS_CLIP_PID_V2I_PARAMS \
    {CHASSIS_CLIP_PID_V2I_KP, CHASSIS_CLIP_PID_V2I_KI, CHASSIS_CLIP_PID_V2I_KD, \
    CHASSIS_CLIP_PID_V2I_I_LIMIT, CHASSIS_CLIP_PID_V2I_OUT_LIMIT}
// Infantry clip PID params of no use that is set to handle conflicts between Hero and Infantry

#define CHASSIS_CLIP_PID_THETA2V_KP 10.0f
#define CHASSIS_CLIP_PID_THETA2V_KI 0.02f
#define CHASSIS_CLIP_PID_THETA2V_KD 0.0f
#define CHASSIS_CLIP_PID_THETA2V_I_LIMIT 60.0f
#define CHASSIS_CLIP_PID_THETA2V_OUT_LIMIT 270.0f
#define CHASSIS_CLIP_PID_THETA2V_PARAMS \
    {CHASSIS_CLIP_PID_THETA2V_KP, CHASSIS_CLIP_PID_THETA2V_KI, CHASSIS_CLIP_PID_THETA2V_KD, \
    CHASSIS_CLIP_PID_THETA2V_I_LIMIT, CHASSIS_CLIP_PID_THETA2V_OUT_LIMIT}

#define CHASSIS_FOLLOW_PID_THETA2V_KP 15.0f
#define CHASSIS_FOLLOW_PID_THETA2V_KI 0.00f
#define CHASSIS_FOLLOW_PID_THETA2V_KD 10.0f
#define CHASSIS_FOLLOW_PID_THETA2V_I_LIMIT 60.0f
#define CHASSIS_FOLLOW_PID_THETA2V_OUT_LIMIT 540.0f
#define CHASSIS_FOLLOW_PID_THETA2V_PARAMS \
    {CHASSIS_FOLLOW_PID_THETA2V_KP, CHASSIS_FOLLOW_PID_THETA2V_KI, CHASSIS_FOLLOW_PID_THETA2V_KD, \
    CHASSIS_FOLLOW_PID_THETA2V_I_LIMIT, CHASSIS_FOLLOW_PID_THETA2V_OUT_LIMIT}

#define CHASSIS_DODGE_PID_THETA2V_KP 10.0f
#define CHASSIS_DODGE_PID_THETA2V_KI 0.02f
#define CHASSIS_DODGE_PID_THETA2V_KD 0.0f
#define CHASSIS_DODGE_PID_THETA2V_I_LIMIT 60.0f
#define CHASSIS_DODGE_PID_THETA2V_OUT_LIMIT 270.0f
#define CHASSIS_DODGE_PID_THETA2V_PARAMS \
    {CHASSIS_DODGE_PID_THETA2V_KP, CHASSIS_DODGE_PID_THETA2V_KI, CHASSIS_DODGE_PID_THETA2V_KD, \
    CHASSIS_DODGE_PID_THETA2V_I_LIMIT, CHASSIS_DODGE_PID_THETA2V_OUT_LIMIT}

#define CHASSIS_LOGIC_DODGE_OMEGA2VOLT_KP 30.0f
#define CHASSIS_LOGIC_DODGE_OMEGA2VOLT_KI 15.0f
#define CHASSIS_LOGIC_DODGE_OMEGA2VOLT_KD 0.0f
#define CHASSIS_LOGIC_DODGE_OMEGA2VOLT_I_LIMIT 720.0f
#define CHASSIS_LOGIC_DODGE_OMEGA2VOLT_OUT_LIMIT 720.0f
#define CHASSIS_LOGIC_DODGE_OMEGA2VOLT_PARAMS \
    {CHASSIS_LOGIC_DODGE_OMEGA2VOLT_KP, CHASSIS_LOGIC_DODGE_OMEGA2VOLT_KI, CHASSIS_LOGIC_DODGE_OMEGA2VOLT_KD,\
     CHASSIS_LOGIC_DODGE_OMEGA2VOLT_I_LIMIT, CHASSIS_LOGIC_DODGE_OMEGA2VOLT_OUT_LIMIT}
#define CHASSIS_DODGE_MODE_THETA   45
#define CHASSIS_DODGE_MODE_INTERVAL   300
#define CHASSIS_BIASED_ANGLE 0

/// Vision
#define VISION_BASIC_CONTROL_DELAY      100   /* ms */
#define VISION_BASIC_SHOOT_DELAY        0   /* ms */
#define VISION_DEFAULT_BULLET_SPEED     14.0f /* mm/ms = m/s */
#define VISION_SHOOT_TOLERANCE          7   /* ms */

/// Thread Priority List
#define THREAD_CAN1_RX_PRIO                 (HIGHPRIO - 1)
#define THREAD_CAN1_TX_PRIO                 (HIGHPRIO - 2)
#define THREAD_CAN2_RX_PRIO                 (HIGHPRIO - 3)
#define THREAD_CAN2_TX_PRIO                 (HIGHPRIO - 4)
#define THREAD_MPU_PRIO                     (HIGHPRIO - 5)
#define THREAD_IST_PRIO                     (HIGHPRIO - 6)
#define THREAD_AHRS_PRIO                    (HIGHPRIO - 7)
#define THREAD_GIMBAL_SKD_PRIO              (NORMALPRIO + 3)
#define THREAD_CHASSIS_SKD_PRIO             (NORMALPRIO + 2)
#define THREAD_SHOOT_SKD_PRIO               (NORMALPRIO + 1)
#define THREAD_USER_PRIO                    (NORMALPRIO)
#define THREAD_USER_ACTION_PRIO             (NORMALPRIO - 1)
#define THREAD_SHOOT_LG_VISION_PRIO         (NORMALPRIO - 1)
#define THREAD_GIMBAL_LG_VISION_PRIO        (NORMALPRIO - 1)
#define THREAD_CHASSIS_LG_DODGE_PRIO        (NORMALPRIO - 2)
#define THREAD_CHASSIS_POWER_SET_PRIO       (NORMALPRIO - 3)
#define THREAD_SHOOT_LG_STUCK_DETECT_PRIO   (NORMALPRIO - 4)
#define THREAD_REFEREE_SENDING_PRIO         (NORMALPRIO - 6)
#define THREAD_SUPERCAP_INIT_PRIO           (NORMALPRIO - 8)
#define THREAD_INSPECTOR_PRIO               (NORMALPRIO - 10)
#define THREAD_SHOOT_BULLET_COUNTER_PRIO    (LOWPRIO + 7)
#define THREAD_USER_CLIENT_DATA_SEND_PRIO   (LOWPRIO + 6)
#define THREAD_SHELL_PRIO                   (LOWPRIO + 5)
#define THREAD_BUZZER_SKD_PRIO              (LOWPRIO)

/// Dev Board LED Usage List
#define DEV_BOARD_LED_SYSTEM_INIT 1
#define DEV_BOARD_LED_CAN         2
#define DEV_BOARD_LED_AHRS        3
#define DEV_BOARD_LED_REMOTE      4
#define DEV_BOARD_LED_GIMBAL      5
#define DEV_BOARD_LED_CHASSIS     6
#define DEV_BOARD_LED_REFEREE     7  // used in infantry ShootLG BulletCounterThread
#define DEV_BOARD_LED_SD_CARD     8

/// User Client Usage List
#define USER_CLIENT_FW_STATE_LIGHT                  0
#define USER_CLIENT_DODGE_MODE_LIGHT                1
#define USER_CLIENT_SUPER_CAPACITOR_STATUS_LIGHT    2
#define USER_CLIENT_SPEED_LEVEL_3_LIGHT             3
#define USER_CLIENT_SPEED_LEVEL_2_LIGHT             4
#define USER_CLIENT_SPEED_LEVEL_1_LIGHT             5

#define USER_CLIENT_FW_SPEED_NUM                    2
//#define USER_CLIENT_REMAINING_HEAT_NUM              2
#define USER_CLIENT_ACQUIRED_BULLET_NUM             3
//#define USER_CLIENT_ACTUAL_POWER_NUM                2
#define USER_CLIENT_SUPER_CAPACITOR_VOLTAGE_NUM     1

/// Super Capacitor Configurations
#define SUPER_CAPACITOR_WARNING_VOLTAGE   15


#endif //META_INFANTRY_VEHICLE_INFANTRY_H
