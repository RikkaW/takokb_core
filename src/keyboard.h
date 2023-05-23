#ifndef TAKOKB_KEYBOARD_H
#define TAKOKB_KEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "takokb_action.h"
#include "takokb.h"

typedef struct {
    struct position_t {
        uint8_t row: 5;
        uint8_t colum: 3;
    } __attribute__((packed)) position;
    uint8_t pressed: 1;
    /* When the key is pressed */
    uint64_t time: 63;
} __attribute__((packed)) key_info_t;

typedef struct {
    volatile key_info_t info;
    action_t *action;
} key_state_t;

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_KEYBOARD_H
