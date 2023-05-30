#include <string.h>
#include "keyboard.h"
#include "keymap.h"

action_t keymaps[TAKOKB_MAX_LAYERS][TAKOKB_MATRIX_ROWS][TAKOKB_MATRIX_COLS];
action_t encoders[TAKOKB_MAX_LAYERS][TAKODB_ENCODER_COUNT][2];

extern action_t action_trans;

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

static void keymap_handle_income_action(const action_t *action, action_t *new_action) {
    memcpy(new_action, action, sizeof(action_t));

    if (action->id == TYPE_KEY) {
        uint8_t modifier_bits = keycode_to_modifier_bits(action->parameter.key.keycode);
        if (modifier_bits != 0) {
            new_action->id = TYPE_MODIFIER;
            memset(&new_action->parameter, 0, sizeof(new_action->parameter));
            new_action->parameter.key.modifiers = modifier_bits;
            return;
        }
    }

    *new_action = *action;
}

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


void keymap_set_action(uint8_t layer, uint8_t row, uint8_t column, const action_t *action) {
    action_t new_action;
    keymap_handle_income_action(action, &new_action);

    keymaps[layer][row][column] = new_action;
}

action_t *keymap_get_encoder_action(uint8_t layer, uint8_t encoder, uint8_t direction) {
    return &encoders[layer][encoder][direction];
}

void keymap_set_encoder_action(uint8_t layer, uint8_t encoder, uint8_t direction, const action_t *action) {
    action_t new_action;
    keymap_handle_income_action(action, &new_action);

    encoders[layer][encoder][direction] = *action;
}

size_t keymap_get_size(void) {
    return sizeof(keymaps);
}
