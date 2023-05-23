#include <string.h>
#include "keyboard.h"
#include "keymap.h"

static action_t keymaps[MAX_LAYERS][MATRIX_ROWS][MATRIX_COLS];

extern action_t action_no;

void keymap_init(void) {
    for (uint8_t layer = 0; layer < MAX_LAYERS; ++layer) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t colum = 0; colum < MATRIX_COLS; ++colum) {
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