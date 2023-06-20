#include <string.h>
#include "takokb.h"
#include "keymap.h"

extern action_t action_trans;

static uint8_t keycode_to_modifier_bits(uint8_t keycode) {
    switch (keycode) {
        case KEY_LEFT_SHIFT:
            return MOD_LSFT;
        case KEY_RIGHT_SHIFT:
            return MOD_RSFT;
        case KEY_LEFT_CTRL:
            return MOD_LCTL;
        case KEY_RIGHT_CTRL:
            return MOD_RCTL;
        case KEY_LEFT_ALT:
            return MOD_LALT;
        case KEY_RIGHT_ALT:
            return MOD_RALT;
        case KEY_LEFT_GUI:
            return MOD_LGUI;
        case KEY_RIGHT_GUI:
            return MOD_RGUI;
        default:
            return 0;
    }
}

static void keymap_handle_set_action(const action_t *input, action_t *output) {
    memcpy(output, input, sizeof(action_t));

    if (input->type == TYPE_KEY) {
        uint8_t modifier_bits = keycode_to_modifier_bits(input->parameter.key.keycode);
        if (modifier_bits != 0) {
            output->type = TYPE_MODIFIER;
            memset(&output->parameter, 0, sizeof(output->parameter));
            output->parameter.key.modifiers = modifier_bits;
            return;
        }
    }
}

void keymap_init(void) {
    takokb_get_keyboard_configuration()->version = TAKOKB_CONFIGURATOR_DATA_VERSION;
    takokb_get_keyboard_configuration()->current_profile = 0;

    for (uint8_t profile = 0; profile < TAKOKB_MAX_PROFILES; ++profile) {
        for (uint8_t layer = 0; layer < TAKOKB_MAX_LAYERS; ++layer) {
            for (uint8_t row = 0; row < TAKOKB_MATRIX_ROWS; ++row) {
                for (uint8_t colum = 0; colum < TAKOKB_MATRIX_COLS; ++colum) {
                    takokb_get_keyboard_configuration()->keymaps[profile][layer][row][colum] = action_trans;
                }
            }

            for (uint8_t row = 0; row < TAKODB_ENCODER_COUNT; ++row) {
                takokb_get_keyboard_configuration()->encoders[profile][layer][row][0] = action_trans;
                takokb_get_keyboard_configuration()->encoders[profile][layer][row][1] = action_trans;
            }
        }
    }
}

action_t *keymap_get_action(uint8_t profile, uint8_t layer, uint8_t row, uint8_t column) {
    return &takokb_get_keyboard_configuration()->keymaps[profile][layer][row][column];
}

void keymap_set_action(uint8_t profile, uint8_t layer, uint8_t row, uint8_t column, const action_t *action) {
    keymap_handle_set_action(action, &takokb_get_keyboard_configuration()->keymaps[profile][layer][row][column]);
    takokb_configuration_changed(offsetof(takokb_configuration_t, keymaps[profile][layer][row][column]), sizeof(action_t));
}

action_t *keymap_get_encoder_action(uint8_t profile, uint8_t layer, uint8_t encoder, uint8_t direction) {
    return &takokb_get_keyboard_configuration()->encoders[profile][layer][encoder][direction];
}

void keymap_set_encoder_action(uint8_t profile, uint8_t layer, uint8_t encoder, uint8_t direction, const action_t *action) {
    keymap_handle_set_action(action, &takokb_get_keyboard_configuration()->encoders[profile][layer][encoder][direction]);
    takokb_configuration_changed(offsetof(takokb_configuration_t, encoders[profile][layer][encoder][direction]), sizeof(action_t));
}
