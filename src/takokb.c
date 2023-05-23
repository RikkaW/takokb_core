#include <stdbool.h>
#include <memory.h>
#include "matrix.h"
#include "keyboard.h"
#include "keymap.h"
#include "takokb.h"
#include "report.h"

static matrix_row_t matrix_previous[MATRIX_ROWS] = {0};
static matrix_row_t matrix[MATRIX_ROWS] = {0};
static key_state_t key_states[MATRIX_ROWS][MATRIX_COLS] = {0};

static key_info_t changed_keys[MATRIX_ROWS * MATRIX_COLS] = {0};
static uint8_t changed_keys_size = 0;

static uint8_t default_layer = 0;
static bool layer_enabled[MAX_LAYERS] = {true};
static uint8_t current_layer = 0;
static uint8_t momentary_layer = 0;

static uint64_t time = 0;

extern action_t action_no;

/**
 * @brief Scan matrix and update changed_keys array.
 * @return If matrix is changed
 * */
bool matrix_task() {
    takokb_matrix_scan(matrix);

    changed_keys_size = 0;

    bool changed = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
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

            key_info_t *key_info = &changed_keys[changed_keys_size];

            if (pressed) {
                takokb_printf("matrix_task: (%d, %d) release -> pressed\n", row, colum);
            } else {
                takokb_printf("matrix_task: (%d, %d) pressed -> released\n", row, colum);
            }

            key_info->position.row = row;
            key_info->position.colum = colum;
            key_info->pressed = pressed;
            key_info->time = time;

            changed_keys_size++;
        }

        matrix_previous[row] = matrix[row];
    }

    return changed;
}

action_t *find_action(uint8_t top_layer, uint8_t row, uint8_t colum) {
    if (top_layer > 0 && layer_enabled[top_layer] == false) {
        return keymap_get_action(top_layer - 1, row, colum);
    }
    action_t *action = keymap_get_action(top_layer, row, colum);
    if (top_layer == 0) {
        return action;
    }
    if (action->type == TYPE_TRANSPARENT) {
        return keymap_get_action(top_layer - 1, row, colum);
    }
    return &action_no;
}

static void handle_changed_keys() {
    for (uint8_t index = 0; index < changed_keys_size; ++index) {
        key_info_t *key_info = &changed_keys[index];
        uint8_t row = key_info->position.row;
        uint8_t colum = key_info->position.colum;
        key_state_t *key_state = &key_states[row][colum];

        takokb_printf("handle_changed_keys: (%d, %d) %s\n",
                      key_info->position.row,
                      key_info->position.colum,
                      key_info->pressed ? "pressed" : "released");

        // If the new state is release, key_state should have been set, use action from it.
        // Otherwise, find action from keymap.
        action_t *action = key_info->pressed
                           ? find_action(momentary_layer, row, colum)
                           : key_state->action;
        if (key_info->pressed) {
            key_state->action = action;
        }

        if (action->type == TYPE_MOMENTARY_LAYER_TOGGLE) {
            momentary_layer = action->parameter.layer.id;
        } else if (action->type == TYPE_LAYER_TOGGLE) {
            layer_enabled[action->parameter.layer.id] = !layer_enabled[action->parameter.layer.id];
        }
    }

    takokb_printf("handle_changed_keys: momentary_layer = %d\n", momentary_layer);

    for (uint8_t index = 0; index < changed_keys_size; ++index) {
        key_info_t *key_info = &changed_keys[index];
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
        takokb_printf("hid_report_task: report has changed\n");
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
}

matrix_row_t *takokb_get_matrix(void) {
    return matrix;
}

void takokb_keymap_set_action(uint8_t layer, uint8_t row, uint8_t column, action_t *action) {
    keymap_set_action(layer, row, column, action);
}