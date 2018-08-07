//
// Created by liuzikai on 2018/8/6.
//

/**
 * @file unit_test_common
 * @brief common code for unit tests
 * 1. Thread UnitTestBlinkLEDThread
 *      This thread blinks red and green leds alternatively each 2s.
 *      It's expected to get started in the main body of the unit test.
 */

#ifndef INSOULED_CHIBIOS_CPP_UNIT_TEST_COMMON_HPP
#define INSOULED_CHIBIOS_CPP_UNIT_TEST_COMMON_HPP

#include "ch.hpp"
#include "hal.h"
#include "led.hpp"

/**
 * @name UnitTestBlinkLEDThread
 * @brief blink red and green leds alternatively each 2s.
 * @usage start the thread in the main body of the unit test.
 */
class UnitTestBlinkLEDThread : public chibios_rt::BaseStaticThread<256> {
protected:
    void main(void) override;
};

#endif //INSOULED_CHIBIOS_CPP_UNIT_TEST_COMMON_HPP
