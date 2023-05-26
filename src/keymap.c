#include <string.h>
#include "keyboard.h"
#include "keymap.h"

action_t keymaps[TAKOKB_MAX_LAYERS][TAKOKB_MATRIX_ROWS][TAKOKB_MATRIX_COLS];

extern action_t action_trans;

void keymap_init(void) {
    for (uint8_t layer = 0; layer < TAKOKB_MAX_LAYERS; ++layer) {
        for (uint8_t row = 0; row < TAKOKB_MATRIX_ROWS; ++row) {
            for (uint8_t colum = 0; colum < TAKOKB_MATRIX_COLS; ++colum) {
                keymaps[layer][row][colum] = action_trans;
            }
        }
    }
}

action_t *keymap_get_action(uint8_t layer, uint8_t row, uint8_t column) {
    return &keymaps[layer][row][column];
}

static uint8_t keycode_to_modifier_bits(uint8_t keycode) {
    switch (keycode) {
        case KC_LEFT_SHIFT:
            return MOD_LSFT;
        case KC_RIGHT_SHIFT:
            return MOD_RSFT;
        case KC_LEFT_CTRL:
            return MOD_LCTL;
        case KC_RIGHT_CTRL:
            return MOD_RCTL;
        case KC_LEFT_ALT:
            return MOD_LALT;
        case KC_RIGHT_ALT:
            return MOD_RALT;
        case KC_LEFT_GUI:
            return MOD_LGUI;
        case KC_RIGHT_GUI:
            return MOD_RGUI;
        default:
            return 0;
    }
}

static uint8_t get_state_type(const action_t *action) {
    switch (action->type) {
        case TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER:
            return STATE_TYPE_TAP_HOLD;
        default:
            return STATE_TYPE_BASIC;
    }
}

void keymap_set_action(uint8_t layer, uint8_t row, uint8_t column, const action_t *action) {
    action_t new_action = {
            .type = action->type,
            .state_type=get_state_type(action),
            .parameter.raw = action->parameter.raw
    };

    if (action->type == TYPE_KEY) {
        uint8_t modifier_bits = keycode_to_modifier_bits(action->parameter.key.keycode);
        if (modifier_bits != 0) {
            new_action.type = TYPE_MODIFIER;
            new_action.parameter.raw = 0;
            new_action.parameter.key.modifiers = modifier_bits;
            keymaps[layer][row][column] = new_action;
            return;
        }
    }

    keymaps[layer][row][column] = new_action;
}
