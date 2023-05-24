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
 * 0: TRANS, TRANS, KC_E, TRANS
 *
 *    Layer 0:
 * 0: BTM(1), TRANS, TRANS, TRANS
 *
 * Step 1:
 * PRESS(0, 0)
 * -> layer=1, KC_NO
 *
 * Step 2:
 * PRESS(0, 1)
 * -> layer=1, KC_NO
 *
 * Step 3:
 * PRESS(0, 2)
 * -> layer=1, KC_E
 *
 **/

static void set_keymap() {
    action_t action;

    action.type = TYPE_BOTTOM_LAYER;
    action.parameter.layer.id = 1;
    takokb_keymap_set_action(0, 0, 0, &action);

    action.type = TYPE_NORMAL_KEY;
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
            PRESS(0, 2);
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
        case 3:
            assert_keycode_equals(report, 0, KC_E);
            return;
        default:
            // This should never trigger
            success = false;
            fprintf(stderr, "Step %d: This should never trigger\n", test_step);
            return;
    }
}
