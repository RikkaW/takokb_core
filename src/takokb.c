#include "keyboard.h"
#include "keymap.h"
#include "takokb.h"

/*
 * Call this function in your main loop.
 */
void takokb_task() {
    keyboard_task();
}

void takokb_init(void) {
    keyboard_init();
}

matrix_row_t *takokb_get_matrix(void) {
    return keyboard_get_matrix();
}

void takokb_keymap_set_action(uint8_t layer, uint8_t row, uint8_t column, const action_t *action) {
    keymap_set_action(layer, row, column, action);
}

uint8_t takokb_get_top_activated_layer(void) {
    return keyboard_get_top_activated_layer();
}

size_t takokb_keymap_get_size(void) {
    return keymap_get_size();
}
