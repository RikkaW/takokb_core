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
 *
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

    test_next_step();
    assert_active_layer_equals(1);

    test_tick(400);
    test_next_step();
    takokb_task();
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
        default:
            return false;
    }
}

void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
    switch (test_step) {
        case 1:
        case 2:
            assert_keycode_equals(report, 0, KC_NO);
            return;
        default:
            // This should never trigger
            success = false;
            fprintf(stderr, "Step %d: This should never trigger\n", test_step);
            return;
    }
}