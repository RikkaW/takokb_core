#include <cstdio>
#include "takokb.h"
#include "report.h"
#include "common.h"
#include "debug.h"

/*
 * This test tests tap=key, hold=layer.
 *
 *    0                         1      2     3
 *    Layer 1:
 * 0: TRANS,                    TRANS, KC_E, TRANS
 *
 *    Layer 0:
 * 0: LT(1, KC_A, MOD_LSFT),    TRANS, TRANS, TRANS
 *
 * Step 1:
 * PRESS(0, 0)
 * -> layer=1, KC_NO
 *
 * Step 2:
 * Wait for 400ms
 * RELEASE(0, 1)
 * -> layer=0
 *
 * Step 3:
 * PRESS(0, 0)
 * -> layer=1, KC_NO
 *
 * Step 4:
 * Wait for 50ms
 * RELEASE(0, 1)
 * -> layer=0, KC_A, MOD_LSFT
 *
 * Step5 :
 * Wait for 100ms
 * -> layer=0, KC_NO
 *
 * Step 6:
 * PRESS(0, 0)
 * -> layer=0, KC_A, MOD_LSFT
 *
 * Step 7:
 * Wait 1000ms
 * -> layer=0, KC_A, MOD_LSFT
 *
 * Step 8:
 * RELEASE(0, 0)
 * -> layer=0, KC_NO
 **/

static void set_keymap() {
    action_t action;

    action.id = TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER;
    action.state_machine = STATE_MACHINE_TAP_HOLD;
    action.parameter.tap_key_hold_layer.layer_id = 1;
    action.parameter.tap_key_hold_layer.keycode = KC_A;
    action.parameter.tap_key_hold_layer.modifiers = MOD_LSFT;
    takokb_keymap_set_action(0, 0, 0, &action);

    action.id = TYPE_KEY;
    action.state_machine = STATE_MACHINE_BASIC;
    action.parameter.key.keycode = KC_E;
    takokb_keymap_set_action(1, 0, 2, &action);
}

int main(int argc, char *argv[]) {
    takokb_init();
    set_keymap();
    takokb_debug_print_keymap();

    takokb_task();

    // Step 1
    test_next_step();
    assert_active_layer_equals(1);

    // Step 2
    test_tick(400);
    test_next_step();
    takokb_task();
    assert_active_layer_equals(0);

    // Step 3
    test_next_step();
    assert_active_layer_equals(1);

    // Step 4
    test_tick(50);
    test_next_step();
    assert_active_layer_equals(0);

    // Step 5
    test_tick(100);
    test_next_step();
    assert_active_layer_equals(0);

    // Step 6
    test_next_step();
    assert_active_layer_equals(0);

    // Step 7
    test_tick(1000);
    test_next_step();
    assert_active_layer_equals(0);

    // Step 8
    test_next_step();
    assert_active_layer_equals(0);

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
            RELEASE(0, 0);
            return true;
        case 3:
            PRESS(0, 0);
            return true;
        case 4:
            RELEASE(0, 0);
            return true;
        case 6:
            PRESS(0, 0);
            return true;
        case 8:
            RELEASE(0, 0);
            return true;
        case 7:
        case 5:
        default:
            return false;
    }
}

void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
    switch (test_step) {
        case 1:
        case 2:
        case 3:
            assert_keycode_equals(report, 0, KC_NO);
            return;
        case 4:
            assert_keycode_equals(report, 0, KC_A);
            assert_modifiers_equals(report, MOD_LSFT);
            return;
        case 5:
            assert_keycode_equals(report, 0, KC_NO);
            return;
        case 6:
        case 7:
            assert_keycode_equals(report, 0, KC_A);
            assert_modifiers_equals(report, MOD_LSFT);
            return;
        case 8:
            assert_keycode_equals(report, 0, KC_NO);
            return;
        default:
            // This should never trigger
            success = false;
            fprintf(stderr, "Step %d: This should never trigger\n", test_step);
            return;
    }
}

void takokb_send_configurator_hid_report(uint8_t *report, size_t size) {

}
