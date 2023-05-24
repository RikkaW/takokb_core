#ifndef TAKOKB_KEYBOARD_H
#define TAKOKB_KEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "takokb_action.h"
#include "takokb.h"

/**
 * @brief This struct holds the information about the key change event. Cleared every scan.
 **/
typedef struct {
    struct position_t {
        uint8_t row: 5;
        uint8_t colum: 3;
    } __attribute__((packed)) position;

    /* If the key is pressed or released */
    uint8_t pressed: 1;
} __attribute__((packed)) key_change_event_t;

typedef struct {
    key_change_event_t *key_change_event;

    /* When the key is pressed */
    uint64_t time: 63;

    /* Action the key is bound */
    action_t *action;

    uint8_t momentary_layer_queue_index;

} key_state_t;

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_KEYBOARD_H
