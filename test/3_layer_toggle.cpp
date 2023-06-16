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
 * 0: TRANS, TRANS, TRANS, TRANS
 *
 *    Layer 0:
 * 0: TRANS, TG(2), MO(1), TRANS
 *
 * Step 1:
 * PRESS(0, 1)
 * -> layer=2
 *
 * Step 2:
 * PRESS(0, 2)
 * -> layer=1 (as momentary layer has the priority)
 *
 * Step 3:
 * RELEASE(0, 2)
 * -> layer=2
 *
 * Step 4:
 * RELEASE(0, 1)
 * -> layer=2
 *
 * Step 4:
 * PRESS(0, 1)
 * -> layer=0 (layer 2 is off)
 *
 **/

static void set_keymap() {
    action_t action;
    action.state_machine = STATE_MACHINE_BASIC;

    action.type = TYPE_TOGGLE_LAYER;
    action.parameter.layer.id = 2;
    takokb_keymap_set_action(0, 0, 1, &action);

    action.type = TYPE_MOMENTARY_LAYER;
    action.parameter.layer.id = 1;
    takokb_keymap_set_action(0, 0, 2, &action);
}

int main(int argc, char *argv[]) {
    takokb_init();
    set_keymap();
    takokb_debug_print_keymap();

    takokb_task();

    test_next_step();
    assert_active_layer_equals(2);

    test_next_step();
    assert_active_layer_equals(1);

    test_next_step();
    assert_active_layer_equals(2);

    test_next_step();
    assert_active_layer_equals(2);

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
            RELEASE(0, 2);
            return true;
        case 4:
            RELEASE(0, 1);
            return true;
        case 5:
            PRESS(0, 1);
            return true;
        default:
            return false;
    }
}

void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
    // This should never trigger
    success = false;
    fprintf(stderr, "Step %d: This should never trigger\n", test_step);
}

void takokb_send_configurator_report(configurator_report_t *report, size_t size) {

}
