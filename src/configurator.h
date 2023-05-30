#ifndef TAKOKB_CONFIGURATOR_H
#define TAKOKB_CONFIGURATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "takokb.h"

enum __attribute__((__packed__)) configurator_commands {
    get_protocol_version = 0x01,
    get_keyboard_info_metadata = 0x02,
    get_keyboard_info = 0x03,
    get_keycode = 0x04,
    set_keycode = 0x05,
};

typedef struct configurator_hid_report {

    enum configurator_commands command_id;

    union {
        uint8_t raw[7];

        struct {
            uint8_t protocol_version;
        } __attribute__((packed)) protocol_version;

        struct {
            uint8_t version;
            uint32_t size;
            uint16_t pages;
        } __attribute__((packed)) keyboard_info_metadata;

        struct {
            uint16_t page;
            uint8_t payload[5];
        } __attribute__((packed)) keyboard_info_payload;

        struct {
            uint8_t layer;
            uint8_t row;
            uint8_t column;
            action_t action;
        }__attribute__((packed)) keycode;
    };

} configurator_hid_report_t;

void configurator_receive_hid_report(configurator_hid_report_t *report);

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_CONFIGURATOR_H
