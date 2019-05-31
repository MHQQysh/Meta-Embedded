//
// Created by liuzikai on 2019-04-22.
// This file contains common parameters for infantry
//

#ifndef META_INFANTRY_VEHICLE_INFANTRY_H
#define META_INFANTRY_VEHICLE_INFANTRY_H

/** Mechanism Parameters */
#define CHASSIS_WHEEL_BASE  420.0f                     // distance between front axle and the back axle [mm]
#define CHASSIS_WHEEL_TREAD 372.0f                     // distance between left and right wheels [mm]
#define CHASSIS_WHEEL_CIRCUMFERENCE 478.0f             // [mm]

#define SHOOT_DEGREE_PER_BULLER 40.0f                  // rotation degree of bullet loader for each bullet

/** Shooting Mechanism User Preference **/
#define GIMBAL_REMOTE_FRICTION_WHEEL_DUTY_CYCLE 0.5
#define GIMBAL_PC_FRICTION_WHEEL_DUTY_CYCLE 1.0

/** Gimbal Motor PID Params **/
#define GIMBAL_PID_YAW_V2I_KP 18.0f
#define GIMBAL_PID_YAW_V2I_KI 0.5f
#define GIMBAL_PID_YAW_V2I_KD 0.0f
#define GIMBAL_PID_YAW_V2I_I_LIMIT 1000.0f
#define GIMBAL_PID_YAW_V2I_OUT_LIMIT 3000.0f
#define GIMBAL_PID_YAW_V2I_PARAMS \
    {GIMBAL_PID_YAW_V2I_KP, GIMBAL_PID_YAW_V2I_KI, GIMBAL_PID_YAW_V2I_KD, \
    GIMBAL_PID_YAW_V2I_I_LIMIT, GIMBAL_PID_YAW_V2I_OUT_LIMIT}

#define GIMBAL_PID_YAW_A2V_KP 5.3f
#define GIMBAL_PID_YAW_A2V_KI 0.0f
#define GIMBAL_PID_YAW_A2V_KD 0.18f
#define GIMBAL_PID_YAW_A2V_I_LIMIT 1000.0f
#define GIMBAL_PID_YAW_A2V_OUT_LIMIT 3000.0f
#define GIMBAL_PID_YAW_A2V_PARAMS \
    {GIMBAL_PID_YAW_A2V_KP, GIMBAL_PID_YAW_A2V_KI, GIMBAL_PID_YAW_A2V_KD, \
    GIMBAL_PID_YAW_A2V_I_LIMIT, GIMBAL_PID_YAW_A2V_OUT_LIMIT}

#define GIMBAL_PID_PITCH_V2I_KP 19.0f
#define GIMBAL_PID_PITCH_V2I_KI 0.35f
#define GIMBAL_PID_PITCH_V2I_KD 0.0f
#define GIMBAL_PID_PITCH_V2I_I_LIMIT 1000.0f
#define GIMBAL_PID_PITCH_V2I_OUT_LIMIT 3000.0f
#define GIMBAL_PID_PITCH_V2I_PARAMS \
    {GIMBAL_PID_PITCH_V2I_KP, GIMBAL_PID_PITCH_V2I_KI, GIMBAL_PID_PITCH_V2I_KD, \
    GIMBAL_PID_PITCH_V2I_I_LIMIT, GIMBAL_PID_PITCH_V2I_OUT_LIMIT}

#define GIMBAL_PID_PITCH_A2V_KP 10.0f
#define GIMBAL_PID_PITCH_A2V_KI 0.0f
#define GIMBAL_PID_PITCH_A2V_KD 0.75f
#define GIMBAL_PID_PITCH_A2V_I_LIMIT 1000.0f
#define GIMBAL_PID_PITCH_A2V_OUT_LIMIT 3000.0f
#define GIMBAL_PID_PITCH_A2V_PARAMS \
    {GIMBAL_PID_PITCH_A2V_KP, GIMBAL_PID_PITCH_A2V_KI, GIMBAL_PID_PITCH_A2V_KD, \
    GIMBAL_PID_PITCH_A2V_I_LIMIT, GIMBAL_PID_PITCH_A2V_OUT_LIMIT}

// TODO: select a better params
#define GIMBAL_PID_BULLET_LOADER_V2I_KP 20.0f
#define GIMBAL_PID_BULLET_LOADER_V2I_KI 0.0f
#define GIMBAL_PID_BULLET_LOADER_V2I_KD 0.0f
#define GIMBAL_PID_BULLET_LOADER_V2I_I_LIMIT 0.0f
#define GIMBAL_PID_BULLET_LOADER_V2I_OUT_LIMIT 2000.0f
#define GIMBAL_PID_BULLET_LOADER_V2I_PARAMS \
    {GIMBAL_PID_BULLET_LOADER_V2I_KP, GIMBAL_PID_BULLET_LOADER_V2I_KI, GIMBAL_PID_BULLET_LOADER_V2I_KD, \
    GIMBAL_PID_BULLET_LOADER_V2I_I_LIMIT, GIMBAL_PID_BULLET_LOADER_V2I_OUT_LIMIT}

/*** Chassis PID Params ***/
#define CHASSIS_PID_V2I_KP 26.0f
#define CHASSIS_PID_V2I_KI 0.1f
#define CHASSIS_PID_V2I_KD 0.02f
#define CHASSIS_PID_V2I_I_LIMIT 2000.0f
#define CHASSIS_PID_V2I_OUT_LIMIT 6000.0f
#define CHASSIS_PID_V2I_PARAMS \
    {CHASSIS_PID_V2I_KP, CHASSIS_PID_V2I_KI, CHASSIS_PID_V2I_KD, \
    CHASSIS_PID_V2I_I_LIMIT, CHASSIS_PID_V2I_OUT_LIMIT}

#endif //META_INFANTRY_VEHICLE_INFANTRY_H