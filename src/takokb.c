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

action_t *takokb_keymap_get_action(uint8_t layer, uint8_t row, uint8_t column) {
    return keymap_get_action(layer, row, column);
}

void takokb_receive_configurator_report(takokb_configurator_report_t *report, size_t size) {
    configurator_receive_report(report, size);
}

__attribute__((weak)) bool takokb_matrix_scan(matrix_row_t *matrix) {
    return false;
}

__attribute__((weak)) void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
}

__attribute__((weak)) void takokb_send_configurator_report(takokb_configurator_report_t *report, size_t size) {

}

__attribute__((weak)) takokb_configuration_t *takokb_get_keyboard_configuration() {
    static takokb_configuration_t configuration;
    return &configuration;
}

__attribute__((weak)) void takokb_reboot_to_bootloader() {

}

__attribute__((weak)) void takokb_system_reset() {

}
