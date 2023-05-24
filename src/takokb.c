#include <stdbool.h>
#include <memory.h>
#include <unistd.h>
#include "keyboard.h"
#include "keymap.h"
#include "takokb.h"
#include "report.h"
#include "debug.h"

#define MOMENTARY_LAYER_QUEUE_MAX_SIZE 32
#define MOMENTARY_LAYER_QUEUE_INDEX_INVALID UINT8_MAX
#define LAYER_ID_INVALID UINT8_MAX

static matrix_row_t matrix_previous[TAKOKB_MATRIX_ROWS] = {0};
static matrix_row_t matrix[TAKOKB_MATRIX_ROWS] = {0};
static key_state_t key_states[TAKOKB_MATRIX_ROWS][TAKOKB_MATRIX_COLS] = {0};

static key_change_event_t changed_keys[TAKOKB_MATRIX_ROWS * TAKOKB_MATRIX_COLS] = {0};
static uint8_t changed_keys_size = 0;

static uint8_t top_layer = 0;
static uint8_t bottom_layer = 0;

static uint32_t activated_layers = 0;
static uint32_t permanent_activated_layers = 0;
static uint8_t top_permanent_layer = 0;

#define IS_LAYER_ACTIVATED(layer) ((activated_layers & (1 << layer)) != 0)
#define IS_LAYER_PERMANENT_ACTIVATED(layer) ((permanent_activated_layers & (1 << layer)) != 0)

static uint8_t momentary_layer_queue[MOMENTARY_LAYER_QUEUE_MAX_SIZE] = {0};
static uint8_t momentary_layer_queue_size = 0;

static uint64_t time = 0;

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

            key_state->key_change_event = key_info;
            key_state->time = time;

            changed_keys_size++;
        }

        matrix_previous[row] = matrix[row];
    }

    return changed;
}

action_t *find_action(uint8_t layer, uint8_t row, uint8_t colum) {
    takokb_debug_printf("find_action: top_layer = %d, (%d, %d)\n", layer, row, colum);

    action_t *action = keymap_get_action(layer, row, colum);

    if (action->type != TYPE_TRANSPARENT) {
        return action;
    } else {
        // If action is transparent, find action from lower layer.
        return find_action(layer - 1, row, colum);
    }
}

static uint8_t momentary_layer_queue_insert(uint8_t layer) {
    if (momentary_layer_queue_size >= 32) {
        return MOMENTARY_LAYER_QUEUE_INDEX_INVALID;
    }
    momentary_layer_queue[momentary_layer_queue_size] = layer;
    momentary_layer_queue_size++;
    return momentary_layer_queue_size - 1;
}

static void momentary_layer_queue_remove(uint8_t index) {
    if (momentary_layer_queue_size == 0) {
        return;
    }
    momentary_layer_queue[index] = MOMENTARY_LAYER_QUEUE_INDEX_INVALID;
    if (index == momentary_layer_queue_size - 1) {
        momentary_layer_queue_size--;
    }
}

static uint8_t momentary_layer_queue_peek() {
    if (momentary_layer_queue_size == 0) {
        return LAYER_ID_INVALID;
    }
    return momentary_layer_queue[momentary_layer_queue_size - 1];
}

/**
 * @brief This function updates top_layer and activated_layers from momentary_layer_queue and activated_layers
 */
static void sync_layer() {
    // Bottom layer is always activated.
    activated_layers = (1<<bottom_layer);

    bool has_momentary_layer = false;
    for (uint8_t i = 0; i < momentary_layer_queue_size; i++) {
        uint8_t layer = momentary_layer_queue[i];
        if (layer == LAYER_ID_INVALID) {
            continue;
        }
        top_layer = layer;
        activated_layers |= (1 << layer);
        has_momentary_layer = true;
    }

    if (has_momentary_layer) {
        takokb_debug_printf("sync_layer: momentary layer %d\n", top_layer);
    }

    activated_layers |= permanent_activated_layers;
    if (!has_momentary_layer) {
        for (uint8_t i = 31; i >= 0; i--) {
            if (activated_layers & (1 << i)) {
                top_layer = i;
                break;
            }
        }
    }
}

static void handle_changed_keys() {
    for (uint8_t index = 0; index < changed_keys_size; ++index) {
        key_change_event_t *key_info = &changed_keys[index];
        uint8_t row = key_info->position.row;
        uint8_t colum = key_info->position.colum;
        key_state_t *key_state = &key_states[row][colum];

        takokb_debug_printf("handle_changed_keys: (%d, %d) %s\n",
                            key_info->position.row,
                            key_info->position.colum,
                            key_info->pressed ? "pressed" : "released");

        // If the new state is release, key_state should have been set, use action from it.
        // Otherwise, find action from keymap.
        action_t *action = key_info->pressed
                           ? find_action(top_layer, row, colum)
                           : key_state->action;

        takokb_debug_printf("handle_changed_keys: action=");
        takokb_debug_print_action(action);
        takokb_debug_printf("\n");

        if (key_info->pressed) {
            key_state->action = action;
        }

        if (action->type == TYPE_MOMENTARY_LAYER_TOGGLE) {
            if (key_info->pressed) {
                uint8_t queue_index = momentary_layer_queue_insert(action->parameter.layer.id);
                if (queue_index != MOMENTARY_LAYER_QUEUE_INDEX_INVALID) {
                    key_state->momentary_layer_queue_index = queue_index;
                }
            } else {
                momentary_layer_queue_remove(key_state->momentary_layer_queue_index);
            }
            top_layer = action->parameter.layer.id;
            takokb_debug_printf("handle_changed_keys: current_layer = %d\n", top_layer);
        } else if (action->type == TYPE_LAYER_TOGGLE) {
        }
    }

    sync_layer();

    for (uint8_t index = 0; index < changed_keys_size; ++index) {
        key_change_event_t *key_info = &changed_keys[index];
        uint8_t row = key_info->position.row;
        uint8_t colum = key_info->position.colum;
        key_state_t *key_state = &key_states[row][colum];

        action_t *action = key_state->action;

        switch (action->type) {
            case TYPE_NORMAL_KEY: {
                uint8_t keycode = action->parameter.key.keycode;
                if (key_info->pressed) {
                    report_add_keycode(keycode);
                } else {
                    report_remove_keycode(keycode);
                }
                break;
            }
            default: {
                break;
            }
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

/*
 * Call this function in your main loop.
 */
void takokb_task() {
    time = takokb_get_milliseconds();

    if (matrix_task()) {
        handle_changed_keys();
    }
    hid_report_task();
}

void takokb_init(void) {
    keymap_init();
    //memset(layer_enabled, true, sizeof(layer_enabled));
}

matrix_row_t *takokb_get_matrix(void) {
    return matrix;
}

void takokb_keymap_set_action(uint8_t layer, uint8_t row, uint8_t column, action_t *action) {
    keymap_set_action(layer, row, column, action);
}

uint8_t takokb_get_active_layer(void) {
    return top_layer;
}
