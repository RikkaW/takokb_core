#include "takokb.h"
#include "debug.h"
#include "keymap.h"

#ifndef NDEBUG

extern action_t keymaps[TAKOKB_MAX_LAYERS][TAKOKB_MATRIX_ROWS][TAKOKB_MATRIX_COLS];

const char *takokb_debug_modifier_bit_to_name(enum mods_bit bit) {
    switch (bit) {
        case MOD_LSFT:
            return "MOD_LSFT";
        case MOD_RSFT:
            return "MOD_RSFT";
        case MOD_LCTL:
            return "MOD_LCTL";
        case MOD_RCTL:
            return "MOD_RCTL";
        case MOD_LALT:
            return "MOD_LALT";
        case MOD_RALT:
            return "MOD_RALT";
        case MOD_LGUI:
            return "MOD_LGUI";
        case MOD_RGUI:
            return "MOD_RGUI";
        default:
            return "MOD_NONE";
    }
}

void takokb_debug_print_action(action_t *action) {
    switch (action->type) {
        case TYPE_NORMAL_KEY: {
            takokb_debug_printf("TYPE_NORMAL_KEY (%s)",
                                takokb_debug_keycode_to_name(action->parameter.key.keycode));
            break;
        }
        case TYPE_MODIFIER: {
            takokb_debug_printf("TYPE_MODIFIER (%s, ",
                                takokb_debug_keycode_to_name(action->parameter.key.keycode));
            for (int i = 0; i < 8; ++i) {
                if (action->parameter.key.modifier & (1 << i)) {
                    takokb_debug_printf("%s", takokb_debug_modifier_bit_to_name(1 << i));
                }
            }
            takokb_debug_printf(")");
            break;
        }
        case TYPE_TRANSPARENT: {
            takokb_debug_printf("TYPE_TRANSPARENT");
            break;
        }
        case TYPE_MOMENTARY_LAYER: {
            takokb_debug_printf("TYPE_MOMENTARY_LAYER %d",
                                action->parameter.layer.id);
            break;
        }
        case TYPE_TOGGLE_LAYER: {
            takokb_debug_printf("TYPE_TOGGLE_LAYER %d",
                                action->parameter.layer.id);
            break;
        }
        case TYPE_BOTTOM_LAYER: {
            takokb_debug_printf("TYPE_BOTTOM_LAYER %d",
                                action->parameter.layer.id);
            break;
        }
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
