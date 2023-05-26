#include <stdbool.h>
#include "keyboard.h"
#include "keymap.h"
#include "takokb.h"
#include "report.h"
#include "debug.h"
#include "action.h"

static matrix_row_t matrix_previous[TAKOKB_MATRIX_ROWS] = {0};
static matrix_row_t matrix[TAKOKB_MATRIX_ROWS] = {0};
static key_state_t key_states[TAKOKB_MATRIX_ROWS][TAKOKB_MATRIX_COLS] = {0};

static key_change_event_t changed_keys[TAKOKB_MATRIX_ROWS * TAKOKB_MATRIX_COLS] = {0};
static uint8_t changed_keys_size = 0;

static uint8_t top_layer = 0;
static uint8_t bottom_layer = 0;

static uint32_t synced_layers_mask = 0;
static uint32_t toggled_layers_mask = 0;

#define IS_LAYER_ACTIVATED(layer) ((synced_layers_mask & (1 << layer)) != 0)

static uint8_t momentary_layer_queue[MOMENTARY_LAYER_QUEUE_MAX_SIZE] = {0};
static uint8_t momentary_layer_queue_size = 0;

uint64_t time = 0;
static uint64_t last_sync_time = 0;

/**
 * @brief Scan matrix and update changed_keys array.
 * @return If matrix is changed
 * */
bool matrix_task() {
    takokb_matrix_scan(matrix);

    changed_keys_size = 0;

    bool changed = false;
    for (uint8_t row = 0; row < TAKOKB_MATRIX_ROWS; row++) {
        bool row_changed = matrix_previous[row] ^ matrix[row];
        if (!row_changed) {
            continue;
        }
        changed = true;

        for (uint8_t colum = 0; colum < 8; colum++) {
            bool pressed = matrix[row] & (1 << colum);
            bool pressed_previous = matrix_previous[row] & (1 << colum);
            if (pressed == pressed_previous) {
                continue;
            }

            key_change_event_t *key_info = &changed_keys[changed_keys_size];
            key_state_t *key_state = &key_states[row][colum];

            if (pressed) {
                takokb_debug_printf("matrix_task: (%d, %d) release -> pressed\n", row, colum);
            } else {
                takokb_debug_printf("matrix_task: (%d, %d) pressed -> released\n", row, colum);
            }

            key_info->position.row = row;
            key_info->position.colum = colum;
            key_info->pressed = pressed;

            changed_keys_size++;
        }

        matrix_previous[row] = matrix[row];
    }

    return changed;
}

static action_t *find_action(uint8_t layer, uint8_t row, uint8_t colum) {
    takokb_debug_printf("find_action: top_layer = %d, (%d, %d)\n", layer, row, colum);

    action_t *action = keymap_get_action(layer, row, colum);
    if (!IS_LAYER_ACTIVATED(layer)) {
        // If the layer is not activated, find action from lower layer.
        return find_action(layer - 1, row, colum);
    }

    if (layer == bottom_layer) {
        // If the layer is bottom layer, return action.
        return action;
    }

    if (action->type != TYPE_TRANSPARENT) {
        return action;
    }
    // If action is transparent, find action from lower layer.
    return find_action(layer - 1, row, colum);
}

uint8_t keyboard_momentary_layer_queue_insert(uint8_t layer) {
    if (momentary_layer_queue_size >= 32) {
        return MOMENTARY_LAYER_QUEUE_INDEX_INVALID;
    }
    momentary_layer_queue[momentary_layer_queue_size] = layer;
    momentary_layer_queue_size++;
    return momentary_layer_queue_size - 1;
}

void keyboard_momentary_layer_queue_remove(uint8_t index) {
    if (momentary_layer_queue_size == 0) {
        return;
    }
    momentary_layer_queue[index] = MOMENTARY_LAYER_QUEUE_INDEX_INVALID;
    if (index == momentary_layer_queue_size - 1) {
        momentary_layer_queue_size--;
    }
}

/**
 * @brief This function updates top_layer and activated_layers from momentary_layer_queue and activated_layers.
 */
static void sync_layer() {
    // Bottom layer is always activated.
    synced_layers_mask = (1 << bottom_layer);

    bool has_momentary_layer = false;
    for (uint8_t i = 0; i <momentary_layer_queue_size; i++) {
        uint8_t layer = momentary_layer_queue[i];
        if (layer == LAYER_ID_INVALID) {
            continue;
        }
        top_layer = layer;
        synced_layers_mask |= (1 << layer);
        has_momentary_layer = true;
    }

    if (has_momentary_layer) {
        takokb_debug_printf("sync_layer: momentary layer %d\n", top_layer);
    }

    synced_layers_mask |= toggled_layers_mask;
    if (!has_momentary_layer) {
        for (uint8_t i = 31; i >= 0; i--) {
            if (synced_layers_mask & (1 << i)) {
                top_layer = i;
                break;
            }
        }
    }

    takokb_debug_printf("sync_layer: top_layer = %d\n", top_layer);
}

static void handle_two_state_change(key_state_t *key_state, action_t *action, bool pressed) {
    switch (key_state->state) {
        case basic_IDLE:
            if (pressed) {
                key_state->state = basic_TAP;
                CALL_basic_TRANSITION_FUNC(action->type, IDLE, TAP);
            }
            break;
        case basic_TAP:
            if (!pressed) {
                key_state->state = basic_IDLE;
                CALL_basic_TRANSITION_FUNC(action->type, TAP, IDLE);
            }
            break;
        default:
            break;
    }
}

static void handle_tap_hold_state_change(key_state_t *key_state, action_t *action, bool pressed) {
    switch (key_state->state) {
        case tapHold_IDLE:
            if (pressed) {
                key_state->state = tapHold_TAP;
                key_state->extras.momentary_layer_tap_hold.threshold_time = time + 200;
                CALL_tapHold_TRANSITION_FUNC(action->type, IDLE, TAP);
            }
            break;
        case tapHold_TAP:
            if (time > key_state->extras.momentary_layer_tap_hold.threshold_time) {
                key_state->state = tapHold_HOLD;
                CALL_tapHold_TRANSITION_FUNC(action->type, TAP, HOLD);
            } else if (pressed) {
                key_state->state = tapHold_WAIT_FOR_RELEASE_INTERNAL;
                key_state->extras.momentary_layer_tap_hold.threshold_time = time + 50;
                CALL_tapHold_TRANSITION_FUNC(action->type, TAP, WAIT_FOR_RELEASE_INTERNAL);
            }
            break;
        case tapHold_HOLD:
            if (!pressed) {
                key_state->state = tapHold_IDLE;
                CALL_tapHold_TRANSITION_FUNC(action->type, HOLD, IDLE);
            }
            break;
        case tapHold_WAIT_FOR_RELEASE_INTERNAL:
            if (pressed) {
                key_state->state = tapHold_TAP_HOLD;
                CALL_tapHold_TRANSITION_FUNC(action->type, WAIT_FOR_RELEASE_INTERNAL, TAP_HOLD);
            } else if (time > key_state->extras.momentary_layer_tap_hold.threshold_time) {
                key_state->state = tapHold_WAIT_FOR_TAP_HOLD;
                key_state->extras.momentary_layer_tap_hold.threshold_time = time + 150;
                CALL_tapHold_TRANSITION_FUNC(action->type, WAIT_FOR_RELEASE_INTERNAL, HOLD_WAIT_FOR_HOLD);
            }
            break;
        case tapHold_WAIT_FOR_TAP_HOLD:
            if (time > key_state->extras.momentary_layer_tap_hold.threshold_time) {
                key_state->state = tapHold_IDLE;
                CALL_tapHold_TRANSITION_FUNC(action->type, WAIT_FOR_TAP_HOLD, IDLE);
            } else if (pressed) {
                key_state->state = tapHold_TAP_HOLD;
                CALL_tapHold_TRANSITION_FUNC(action->type, WAIT_FOR_TAP_HOLD, TAP_HOLD);
            }
        case tapHold_TAP_HOLD:
            if (!pressed) {
                key_state->state = tapHold_IDLE;
                CALL_tapHold_TRANSITION_FUNC(action->type, TAP_HOLD, IDLE);
            }
            break;
        default:
            break;
    }
}

static void handle_changed_keys() {
    uint8_t layer = top_layer;

    for (uint8_t index = 0; index < changed_keys_size; ++index) {
        key_change_event_t *change_event = &changed_keys[index];
        uint8_t row = change_event->position.row;
        uint8_t colum = change_event->position.colum;
        key_state_t *key_state = &key_states[row][colum];

        takokb_debug_printf("handle_changed_keys: (%d, %d) %s\n",
                            change_event->position.row,
                            change_event->position.colum,
                            change_event->pressed ? "pressed" : "released");

        // If the new state is release, key_state should have been set, use action from it.
        // Otherwise, find action from keymap.
        action_t *action = change_event->pressed
                           ? find_action(layer, row, colum)
                           : key_state->action;

        if (change_event->pressed) {
            key_state->action = action;
        }

        takokb_debug_printf("handle_changed_keys: action=");
        takokb_debug_print_action(action);
        takokb_debug_printf("\n");

        if (action->state_type == STATE_TYPE_BASIC) {
            handle_two_state_change(key_state, action, change_event->pressed);
        }
    }
}

void hid_report_task() {
    if (report_has_changed()) {
        takokb_debug_printf("hid_report_task: report has changed\n");
        takokb_send_keyboard_hid_report(report_get_keyboard_hid_report(), 8);
        report_clear_changed();
    }
}

void keyboard_task() {
    time = takokb_get_milliseconds();

    if (matrix_task()) {
        handle_changed_keys();
        sync_layer();
    }
    hid_report_task();
}

void keyboard_init() {
    keymap_init();

    for (uint8_t row = 0; row < TAKOKB_MATRIX_ROWS; row++) {
        for (uint8_t colum = 0; colum < TAKOKB_MATRIX_COLS; colum++) {
            key_states[row][colum].state = STATE_IDLE;
        }
    }

    sync_layer();
}

matrix_row_t *keyboard_get_matrix(void) {
    return matrix;
}

uint8_t keyboard_get_top_activated_layer(void) {
    return top_layer;
}

uint32_t *keyboard_get_toggled_layers_mask(void) {
    return &toggled_layers_mask;
}

void keyboard_set_bottom_layer(uint8_t layer) {
    bottom_layer = layer;
}
