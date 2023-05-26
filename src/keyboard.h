#ifndef TAKOKB_KEYBOARD_H
#define TAKOKB_KEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "takokb_action.h"
#include "takokb.h"

enum key_change {
    KEY_CHANGE_RELEASE = 0,
    KEY_CHANGE_PRESS,
    KEY_CHANGE_UNCHANGED,
};

/**
 * @brief This struct holds the information about the key change event. Cleared every scan.
 **/
typedef struct key_change_event {
    struct position {
        uint8_t row;
        uint8_t colum;
    } __attribute__((packed)) position;

    /* If the key is pressed or released */
    enum key_change change;
} __attribute__((packed)) key_change_event_t;

#define STATE_IDLE 0

enum key_state_basic {
    basic_IDLE = STATE_IDLE,
    basic_TAP,
};

enum key_state_tap_hold {
    tapHold_IDLE = STATE_IDLE,
    tapHold_TAP,
    tapHold_HOLD,
    tapHold_WAIT_FOR_RELEASE_INTERNAL,
    tapHold_WAIT_FOR_TAP_HOLD,
    tapHold_TAP_HOLD,
};

typedef struct key_state {
    uint8_t state: 8;

    union extras {
        uint8_t raw[8];
        struct {
            uint8_t layer_queue_index: 8;
            uint64_t threshold_time: 56;
        } __attribute__((packed)) tap_key_hold_layer;
        struct {
            uint8_t layer_queue_index: 8;
        } __attribute__((packed)) momentary_layer;
    } extras;

    /* Action the key is bound */
    action_t *action;

} __attribute__((packed)) key_state_t;

#define MOMENTARY_LAYER_QUEUE_MAX_SIZE 32
#define MOMENTARY_LAYER_QUEUE_INDEX_INVALID UINT8_MAX
#define LAYER_ID_INVALID UINT8_MAX

bool matrix_task();

void keyboard_task();

void keyboard_init();

matrix_row_t *keyboard_get_matrix();

uint8_t keyboard_get_top_activated_layer(void);

uint8_t keyboard_momentary_layer_queue_insert(uint8_t layer);

void keyboard_momentary_layer_queue_remove(uint8_t layer);

uint32_t *keyboard_get_toggled_layers_mask(void);

void keyboard_set_bottom_layer(uint8_t layer);

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_KEYBOARD_H
