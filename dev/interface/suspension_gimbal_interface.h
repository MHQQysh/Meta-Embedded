//
// Created by zhukerui on 2019/6/8.
//

#ifndef META_INFANTRY_SUSPENSION_GIMBAL_INTERFACE_H
#define META_INFANTRY_SUSPENSION_GIMBAL_INTERFACE_H
#include "ch.hpp"
#include "hal.h"
#include "can_interface.h"

/* Board Guard */
#if defined(BOARD_RM_2018_A)
#elif defined(BOARD_RM_2017)
#else
#error "GimbalInterface has not been defined for selected board"
#endif

/*
 * Enable clip at the moment of sending current.
 * Only for safety. There is NO signal for clipping. Be sure to eliminate it if more current is needed.
 */
#define SUSPENSION_GIMBAL_INTERFACE_ENABLE_CLIP TRUE

#if SUSPENSION_GIMBAL_INTERFACE_ENABLE_CLIP
#define SUSPENSION_YAW_MAX_VOLTAGE 30000
#define SUSPENSION_PITCH_MAX_VOLTAGE 29000
#define SUSPENSION_GIMBAL_INTERFACE_BULLET_LOADER_MAX_CURRENT 3000
#define MAX_YAW_ANGLE 170 // degree
#define MAX_PITCH_ANGLE 40 // degree
#define BULLET_LOADER_SPEED 40 // degree/s
#endif

/**
 * @name SuspensionGimbalIF
 * @brief Interface to process feedback from suspension gimbal and send control signals to gimbal, including Yaw, Pitch, Bullet
 *        Loader (using CAN) and friction wheels (by PWM).
 * @pre Hardware is connected properly (see ONES doc)
 * @pre PWM pins are set properly in board.h (I5 - alt 3, I6 - alt 3)
 * @usage 1. Call init(CANInterface *). The interface should be properly initialized.
 *        2. Read feedback from variables.
 *           Write target voltage / target current / duty cycle to variables, then call send_gimbal_currents.
 */
class SuspensionGimbalIF {

public:

    typedef enum {
        YAW_ID = 0,
        PIT_ID = 1,
        BULLET_LOADER_ID = 2
    } motor_id_t;

    typedef enum {
        OFF = 0,
        AWAIT = 1,
        SHOOT = 2,
    } shoot_mode_t;

    /**
     * Interface for each motor, which is used for yaw, pitch and bullet loader motors
     */
    class MotorInterface {

    public:

        float angular_velocity = 0.0f;  // instant angular velocity [degree/s], positive when counter-clockwise, negative otherwise

        bool status(){ return  enabled;}
        int get_target_signal(){ return target_signal;}
        float get_angular_position(){
            return actual_angle + 360.0f * round_count;
        }

    private:
        motor_id_t id;

        bool enabled = false;  // if not enabled, 0 current will be sent in send_gimbal_currents

        // +: clockwise, -: counter-clockwise
        int target_signal = 0;  // the current/voltage that we want the motor to have

        /**
         * Normalized Angle and Rounds
         */
        float actual_angle = 0.0f; // the actual angle [degree] of the gimbal, compared with the front
        uint16_t last_angle_raw = 0;  // the raw angle of the newest feedback, in [0, 8191]
        int round_count = 0;  // the rounds that the gimbal turns
        float target_angle = 0;

        // Some const parameters for feedback processing
        int angle_movement_lower_bound;
        int angle_movement_upper_bound;
        float actual_angle_lower_bound;
        float actual_angle_upper_bound;
        float deceleration_ratio;

        /**
         * @brief set current actual angle as the front angle
         */
        void reset_front_angle(){
            actual_angle = 0;
            round_count = 0;
            target_angle = 0;
        }

        friend SuspensionGimbalIF;
        friend class SuspensionGimbalController;
    };
    static MotorInterface yaw;
    static MotorInterface pitch;
    static MotorInterface bullet_loader;

    static shoot_mode_t shoot_status(){
        return  shoot_mode;
    }

    /**
     * @brief set the CAN interface, start PWM driver and set the PID
     * @param can_interface
     * @param yaw_front_angle_raw   raw angle of yaw when gimbal points straight forward, depending on installation.
     * @param pitch_front_angle_raw   raw angle of pitch when gimbal points straight forward, depending on installation.
     */
    static void init(CANInterface *can_interface, uint16_t yaw_front_angle_raw = 0, uint16_t pitch_front_angle_raw = 0);

    /**
     * @brief send target_current of each motor
     * @return
     */
    static bool send_gimbal_currents();


private:

    static CANInterface *can_;

    friend CANInterface;
    friend class SuspensionGimbalController;

    /**
     * @brief process CAN rx frame
     * @param rxmsg
     */
    static void process_motor_feedback(CANRxFrame const *rxmsg);

    // Count of feedback for one sample of angular velocity
    static constexpr int VELOCITY_SAMPLE_INTERVAL = 50;

    static constexpr PWMDriver *FRICTION_WHEEL_PWM_DRIVER = &PWMD8;

    enum friction_wheel_channel_t {
        FW_LEFT = 0,  // The left friction wheel, PI5, channel 0
        FW_RIGHT = 1  // The right friction wheel, PI6, channel 1
    };

    static shoot_mode_t shoot_mode;
    static float shoot_duty_cycles[3];  // the array contains the duty cycles for different shoot modes

    static constexpr PWMConfig FRICTION_WHEELS_PWM_CFG = {
            50000,   // frequency
            1000,    // period
            nullptr, // callback
            {
                    {PWM_OUTPUT_ACTIVE_HIGH, nullptr}, // CH0
                    {PWM_OUTPUT_ACTIVE_HIGH, nullptr}, // CH1
                    {PWM_OUTPUT_DISABLED, nullptr},    // CH2
                    {PWM_OUTPUT_DISABLED, nullptr}     // CH3
            },
            0,
            0
    };
};


#endif //META_INFANTRY_SUSPENSION_GIMBAL_INTERFACE_H
