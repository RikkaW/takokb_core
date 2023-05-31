#ifndef TAKOKB_PUBLIC_CONFIGURATOR_H
#define TAKOKB_PUBLIC_CONFIGURATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "takokb_action.h"

enum __attribute__((__packed__)) configurator_commands {
    get_protocol_version = 0x01,
    get_keyboard_info_metadata = 0x02,
    get_keyboard_info = 0x03,
    get_keycode = 0x04,
    set_keycode = 0x05,
    custom_command_start = 0x80,
    failed = 0xff
};

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_PUBLIC_CONFIGURATOR_H
