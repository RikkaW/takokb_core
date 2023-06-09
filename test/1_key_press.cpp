#include <cstdio>
#include "takokb.h"
#include "common.h"
#include "debug.h"

/*
 * Step 1:
 * PRESS(0, 0) KC_A
 *
 * Step 2:
 * PRESS(0, 1) KC_B
 *
 * Step 3:
 * RELEASE(0, 0) KC_A
 **/

int main(int argc, char *argv[]) {
    takokb_init();

    action_t action;
    action.id = TYPE_KEY;
    action.state_machine = STATE_MACHINE_BASIC;
    action.parameter.key.keycode = KC_A;
    takokb_keymap_set_action(0, 0, 0, &action);
    action.parameter.key.keycode = KC_LEFT_SHIFT;
    takokb_keymap_set_action(0, 0, 1, &action);
    takokb_debug_print_keymap();

    test_next_step();
    test_next_step();
    test_next_step();

    return success ? 0 : 1;
}

bool takokb_matrix_scan(matrix_row_t *matrix) {
    switch (test_step) {
        case 0:
            return false;
        case 1:
            PRESS(0, 0);
            return true;
        case 2:
            PRESS(0, 1);
            return true;
        case 3:
            RELEASE(0, 0);
            return true;
        default:
            return false;
    }
}

void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
    switch (test_step) {
        case 1:
            assert_keycode_equals(report, 0, KC_A);
            return;
        case 2:
            assert_keycode_equals(report, 0, KC_A);
            assert_modifiers_equals(report, MOD_LSFT);
            return;
        case 3:
            assert_keycode_equals(report, 0, KC_NO);
            assert_modifiers_equals(report, MOD_LSFT);
            return;
        default:
            // This should never trigger
            success = false;
            fprintf(stderr, "Step %d: This should never trigger\n", test_step);
            return;
    }
}

void takokb_send_configurator_report(configurator_report_t *report, size_t size) {

}
