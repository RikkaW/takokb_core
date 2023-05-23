#include <string.h>
#include "keyboard.h"
#include "keymap.h"

static action_t keymaps[TAKOKB_MAX_LAYERS][TAKOKB_MATRIX_ROWS][TAKOKB_MATRIX_COLS];

extern action_t action_no;

void keymap_init(void) {
    for (uint8_t layer = 0; layer < TAKOKB_MAX_LAYERS; ++layer) {
        for (uint8_t row = 0; row < TAKOKB_MATRIX_ROWS; ++row) {
            for (uint8_t colum = 0; colum < TAKOKB_MATRIX_COLS; ++colum) {
                keymaps[layer][row][colum] = action_no;
            }
        }
    }
}

action_t *keymap_get_action(uint8_t layer, uint8_t row, uint8_t column) {
    return &keymaps[layer][row][column];
}

void keymap_set_action(uint8_t layer, uint8_t row, uint8_t column, action_t *action) {
    keymaps[layer][row][column] = *action;
}