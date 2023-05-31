#include "keyboard.h"
#include "keymap.h"
#include "takokb.h"
#include "configurator.h"

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

action_t *takokb_keymap_get_action(uint8_t layer, uint8_t row, uint8_t column) {
    return keymap_get_action(layer, row, column);
}

void takokb_receive_configurator_hid_report(configurator_hid_report_t *report, size_t size) {
    if (size < sizeof(configurator_hid_report_t)) {
        return;
    }
    configurator_receive_hid_report(report);
}

__attribute__((weak)) bool takokb_matrix_scan(matrix_row_t *matrix) {
    return false;
}

__attribute__((weak)) void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
}

__attribute__((weak)) void takokb_send_configurator_hid_report(configurator_hid_report_t *report, size_t size) {

}
