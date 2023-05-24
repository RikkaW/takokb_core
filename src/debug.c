#include "takokb.h"
#include "debug.h"
#include "keymap.h"

#ifndef NDEBUG

extern action_t keymaps[TAKOKB_MAX_LAYERS][TAKOKB_MATRIX_ROWS][TAKOKB_MATRIX_COLS];

void takokb_debug_print_action(action_t *action) {
    if (action->type == TYPE_NORMAL_KEY) {
        takokb_debug_printf("TYPE_NORMAL_KEY, %s",
                            takokb_debug_keycode_to_name(action->parameter.key.keycode));
    } else if (action->type == TYPE_TRANSPARENT) {
        takokb_debug_printf("TYPE_TRANSPARENT");
    } else if (action->type == TYPE_MOMENTARY_LAYER_TOGGLE) {
        takokb_debug_printf("TYPE_MOMENTARY_LAYER_TOGGLE, %d",
                            action->parameter.layer.id);
    }
}

void takokb_debug_print_keymap(void) {
    for (uint8_t layer = 0; layer < TAKOKB_MAX_LAYERS; ++layer) {
        for (uint8_t row = 0; row < TAKOKB_MATRIX_ROWS; ++row) {
            for (uint8_t colum = 0; colum < TAKOKB_MATRIX_COLS; ++colum) {
                action_t *action = &keymaps[layer][row][colum];
                takokb_debug_printf("keymaps[%d][%d][%d] = ", layer, row, colum);
                takokb_debug_print_action(action);
                takokb_debug_printf("\n");
            }
        }
    }
}

const char *takokb_debug_keycode_to_name(enum keycodes keycode) {
    switch (keycode) {
        case KC_NO:
            return "KC_NO";
        case KC_A:
            return "KC_A";
        case KC_B:
            return "KC_B";
        case KC_C:
            return "KC_C";
        case KC_D:
            return "KC_D";
        case KC_E:
            return "KC_E";
        case KC_F:
            return "KC_F";
        case KC_G:
            return "KC_G";
        case KC_H:
            return "KC_H";
        case KC_I:
            return "KC_I";
        case KC_J:
            return "KC_J";
        case KC_K:
            return "KC_K";
        case KC_L:
            return "KC_L";
        default:
            return "Unknown";
    }
}

#endif
