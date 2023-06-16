#include <cstdio>
#include "takokb.h"
#include "report.h"
#include "common.h"
#include "debug.h"

/*
 * This test tests layer switching.
 *
 *    0     1      2     3
 *    Layer 1:
 * 0: KC_D, TRANS, KC_E, TRANS
 *
 *    Layer 0:
 * 0: KC_A, MO(1), KC_B, KC_C
 *
 * Step 1:
 * PRESS(0, 1)
 * -> layer=1
 *
 * Step 2:
 * PRESS(0, 2)
 * -> layer=1, KC_E
 *
 * Step 3:
 * PRESS(0, 3)
 * -> layer=1, KC_E, KC_C
 *
 * Step 4:
 * RELEASE(0, 1)
 * -> layer=0, KC_E (When MO is released, previous pressed keys are not affected)
 *
 **/

static void set_keymap() {
    action_t action;
    action.state_machine = STATE_MACHINE_BASIC;

    action.type = TYPE_KEY;
    action.parameter.key.keycode = KC_A;
    takokb_keymap_set_action(0, 0, 0, &action);

    action.type = TYPE_MOMENTARY_LAYER;
    action.parameter.layer.id = 1;
    takokb_keymap_set_action(0, 0, 1, &action);

    action.type = TYPE_KEY;
    action.parameter.key.keycode = KC_B;
    takokb_keymap_set_action(0, 0, 2, &action);

    action.type = TYPE_KEY;
    action.parameter.key.keycode = KC_C;
    takokb_keymap_set_action(0, 0, 3, &action);

    action.type = TYPE_KEY;
    action.parameter.key.keycode = KC_D;
    takokb_keymap_set_action(1, 0, 0, &action);

    action.type = TYPE_KEY;
    action.parameter.key.keycode = KC_E;
    takokb_keymap_set_action(1, 0, 2, &action);
}

int main(int argc, char *argv[]) {
    takokb_init();
    set_keymap();
    takokb_debug_print_keymap();

    takokb_task();

    test_next_step();
    assert_active_layer_equals(1);

    test_next_step();
    assert_active_layer_equals(1);

    test_next_step();
    assert_active_layer_equals(1);

    test_next_step();
    assert_active_layer_equals(0);

    return success ? 0 : 1;
}

bool takokb_matrix_scan(matrix_row_t *matrix) {
    switch (test_step) {
        case 0:
            return false;
        case 1:
            PRESS(0, 1);
            return true;
        case 2:
            PRESS(0, 2);
            return true;
        case 3:
            PRESS(0, 3);
            return true;
        case 4:
            RELEASE(0, 1);
            return true;
        default:
            return false;
    }
}

void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
    switch (test_step) {
        case 1:
            assert_keycode_equals(report, 0, KC_NO);
            return;
        case 2:
            assert_keycode_equals(report, 0, KC_E);
            return;
        case 3:
            assert_keycode_equals(report, 0, KC_E);
            assert_keycode_equals(report, 1, KC_C);
            return;
        case 4:
            assert_keycode_equals(report, 0, KC_E);
            return;
        default:
            // This should never trigger
            success = false;
            fprintf(stderr, "Step %d: This should never trigger\n", test_step);
            return;
    }
}

void takokb_send_configurator_report(takokb_configurator_report_t *report, size_t size) {

}
