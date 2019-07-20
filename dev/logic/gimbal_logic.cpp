//
// Created by liuzikai on 2019-06-26.
//

/**
 * @file    gimbal_logic.cpp
 * @brief   By-passing logic-level module to control GimbalLG
 *
 * @addtogroup gimbal
 * @{
 */

#include "gimbal_logic.h"

GimbalLG::action_t GimbalLG::action = FORCED_RELAX_MODE;
GimbalLG::VisionThread GimbalLG::visionThread;
chibios_rt::ThreadReference GimbalLG::visionThreadReference;

void GimbalLG::init(tprio_t vision_thread_prio_) {
    visionThread.started = true;
    visionThreadReference = visionThread.start(vision_thread_prio_);
}

GimbalLG::action_t GimbalLG::get_action() {
    return action;
}

void GimbalLG::set_action(GimbalLG::action_t value) {
    if (value == action) return;  // avoid repeating setting target_theta, etc.

    action = value;
    if (action == FORCED_RELAX_MODE) {
        GimbalSKD::set_mode(GimbalSKD::FORCED_RELAX_MODE);
    } else if (action == ABS_ANGLE_MODE) {
        GimbalSKD::set_mode(GimbalSKD::ABS_ANGLE_MODE);
    } else if (action == VISION_MODE) {
        GimbalSKD::set_mode(GimbalSKD::ABS_ANGLE_MODE);
        // Resume the thread
        chSysLock();  /// ---------------------------------- Enter Critical Zone ----------------------------------
        if (!visionThread.started) {
            visionThread.started = true;
            chSchWakeupS(visionThreadReference.getInner(), 0);
        }
        chSysUnlock();  /// ---------------------------------- Exit Critical Zone ----------------------------------
    }
}

void GimbalLG::set_target(float yaw_target_angle, float pitch_target_angle) {
    if (action == ABS_ANGLE_MODE) {
        GimbalSKD::set_target_angle(yaw_target_angle, pitch_target_angle);
    } else {
        LOG_ERR("GimbalLG - set_target(): invalid mode");
    }
}

float GimbalLG::get_accumulated_angle(GimbalBase::motor_id_t motor) {
    return GimbalSKD::get_accumulated_angle(motor);
}

void GimbalLG::VisionThread::main() {
    setName("Vision");
    while (!shouldTerminate()) {

        chSysLock();  /// ---------------------------------- Enter Critical Zone ----------------------------------
        if (action != VISION_MODE) {
            started = false;
            chSchGoSleepS(CH_STATE_SUSPENDED);
        }
        chSysUnlock();  /// ---------------------------------- Exit Critical Zone ----------------------------------

//        VisionPort::send_gimbal(0, 0);

        if (VisionPort::last_update_time != last_apply_time) {
            GimbalSKD::set_target_angle(GimbalSKD::get_accumulated_angle(YAW) + VisionPort::enemy_info.yaw_angle,
                                        GimbalSKD::get_accumulated_angle(PITCH) + VisionPort::enemy_info.pitch_angle);
            last_apply_time = VisionPort::last_update_time;
        }
    }
}

/** @} */