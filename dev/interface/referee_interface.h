//
// Created by Administrator on 2019/1/15 0015.
//

#ifndef META_INFANTRY_REFEREE_INTERFACE_H
#define META_INFANTRY_REFEREE_INTERFACE_H

#include "ch.hpp"
#include "hal.h"

#include "led.h"
#include "shell.h"

/**
 * @brief the interface for referee system
 * @pre hardware is properly connected and GPIOs are properly configured in board.h
 * @pre call start() to start UART port and start receive
 * @note the status machine of receiving:
 *       1. Receive byte one by one. If valid SOF 0xA5 is received, go to 2.
 *       2. Receive the remaining header. If header is valid (CRC8), go to 3. Otherwise, go back to 1.
 *       3. Receive cmdID. Check whether the id is valid and data length is correct. But even if there is error, still
 *          go to status 4, as data length given in header is validated, which is more credible than is unvalidated
 *          cmdID.
 *       4. Receive frameHeader.data_length bytes. Go to status 5.
 *       5. Validate data with CRC16. If it's valid, copy data to corresponding structure, or do nothing if failed.
 *          Go to status 1.
 * @attention Designed for 2017 referee system
 */
class Referee {

public:

    enum client_data_t{
        DATA_1,
        DATA_2,
        DATA_3
    };

    enum signal_light_t{
        SIGNAL_0 = 0,
        SIGNAL_1 = 1,
        SIGNAL_2 = 2,
        SIGNAL_3 = 3,
        SIGNAL_4 = 4,
        SIGNAL_5 = 5
    };

    __PACKED_STRUCT game_state_t {
        uint8_t game_type : 4;
        uint8_t game_progress : 4;
        uint16_t stage_remain_time;
    };

    __PACKED_STRUCT game_result_t {
        uint8_t winner;
    };

    __PACKED_STRUCT game_robot_survivors_t {
        uint16_t robot_legion;
    };

    __PACKED_STRUCT event_data_t {
        uint32_t event_type;
    };

    __PACKED_STRUCT supply_projectile_action_t {
        uint8_t supply_projectile_id;
        uint8_t supply_robot_id;
        uint8_t supply_projectile_step;
        uint8_t supply_projectile_num;
    };

    __PACKED_STRUCT supply_projectile_booking_t {
        uint8_t supply_projectile_id;
        uint8_t supply_robot_id;
        uint8_t supply_num;
    };

    __PACKED_STRUCT game_robot_state_t {
        uint8_t robot_id;
        uint8_t robot_level;
        uint16_t remain_HP;
        uint16_t max_HP;
        uint16_t shooter_heat0_cooling_rate;
        uint16_t shooter_heat0_cooling_limit;
        uint16_t shooter_heat1_cooling_rate;
        uint16_t shooter_heat1_cooling_limit;
        uint8_t mains_power_gimbal_output : 1;
        uint8_t mains_power_chassis_output : 1;
        uint8_t mains_power_shooter_output : 1;
    };

    __PACKED_STRUCT power_heat_data_t {
        uint16_t chassis_volt;
        uint16_t chassis_current;
        float chassis_power;
        uint16_t chassis_power_buffer;
        uint16_t shooter_heat0;
        uint16_t shooter_heat1;
    };

    __PACKED_STRUCT game_robot_pos_t {
        float x;
        float y;
        float z;
        float yaw;
    };

    __PACKED_STRUCT buff_musk_t {
        uint8_t power_rune_buff;
    };

    __PACKED_STRUCT aerial_robot_energy_t {
        uint8_t energy_point;
        uint8_t attack_time;
    };

    __PACKED_STRUCT robot_hurt_t {
        uint8_t armor_id : 4;
        uint8_t hurt_type : 4;
    };

    __PACKED_STRUCT shoot_data_t {
        uint8_t bullet_type;
        uint8_t bullet_freq;
        float bullet_speed;
    };

    __PACKED_STRUCT student_interactive_header_data_t {
            uint16_t data_cmd_id;
            uint16_t send_ID;
            uint16_t receiver_ID;
    };

    __PACKED_STRUCT client_custom_data_t{
            student_interactive_header_data_t header;
            float data1;
            float data2;
            float data3;
            uint8_t masks;
    };

    __PACKED_STRUCT robot_interactive_data_t{
            student_interactive_header_data_t header;
            uint8_t dataTBD_1;
            uint8_t dataTBD_2;
            uint8_t dataTBD_3;
    };

    /** Received Data **/
    static game_state_t  game_state;
    static game_result_t game_result;
    static game_robot_survivors_t game_robot_survivors;
    static event_data_t event_data;
    static supply_projectile_action_t supply_projectile_action;
    static supply_projectile_booking_t supply_projectile_booking;
    static game_robot_state_t game_robot_state;
    static power_heat_data_t power_heat_data;
    static game_robot_pos_t game_robot_pos;
    static buff_musk_t buff_musk;
    static aerial_robot_energy_t aerial_robot_energy;
    static robot_hurt_t robot_hurt;
    static shoot_data_t shoot_data;
    static robot_interactive_data_t robot_data_receive[7];

    /** Send Data **/
    static client_custom_data_t client_custom_data;
    static robot_interactive_data_t robot_data_send[7];

    static uint16_t robot_id;

    static uint16_t client_id;

    static bool is_blue;

    static void init();

    static void set_robot_info(int id);

    static void uart_rx_callback(UARTDriver *uartp);  // only for internal use

    static void set_client_data(client_data_t data_type, float data);

    static void set_signal_light(signal_light_t signalLight, bool turn_on);

    static void send_data(uint16_t receiver_id, uint16_t data_cmd_id = 0);


private:

    enum rx_status_t {
        WAIT_STARTING_BYTE,  // receive bytes one by one, waiting for 0xA5
        WAIT_REMAINING_HEADER,  // receive remaining header after SOF
        WAIT_CMD_ID_DATA_TAIL  // receive cmd_id, data section and 2-byte CRC16 tailing
    };

    static rx_status_t rx_status;

    static uint16_t tx_seq;

    __PACKED_STRUCT frame_header_t {
        uint8_t sof;  // start byte of header, 0xA5
        uint16_t data_length;
        uint8_t seq;
        uint8_t crc8;
    };

    static __PACKED_STRUCT package_t{
        frame_header_t header;
        uint16_t cmd_id;
        union{
                game_state_t game_state_;
                game_result_t  game_result_;
                game_robot_survivors_t game_robot_survivors_;
                event_data_t event_data_;
                supply_projectile_action_t supply_projectile_action_;
                supply_projectile_booking_t supply_projectile_booking_;
                game_robot_state_t game_robot_state_;
                power_heat_data_t power_heat_data_;
                game_robot_pos_t game_robot_pos_;
                buff_musk_t buff_musk_;
                aerial_robot_energy_t aerial_robot_energy_;
                robot_hurt_t robot_hurt_;
                shoot_data_t shoot_data_;
                robot_interactive_data_t robot_interactive_data_;
                client_custom_data_t client_custom_data_;
        };
        uint16_t tail;
    } pak;

    static constexpr size_t FRAME_HEADER_SIZE = 5;
    static constexpr size_t FRAME_SOF_SIZE = 1;
    static constexpr size_t CMD_ID_SIZE = 2;
    static constexpr size_t FRAME_TAIL_SIZE = 2;

    friend void uartStart(UARTDriver *uartp, const UARTConfig *config);
    friend void uartStartReceive(UARTDriver *uartp, size_t n, void *rxbuf);

    // See cpp file for configs
    static constexpr UARTDriver *UART_DRIVER = &UARTD7;
    static const UARTConfig UART_CONFIG;
};


#endif //META_INFANTRY_REFEREE_INTERFACE_H
