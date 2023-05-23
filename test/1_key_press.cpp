#include <cstdio>
#include "takokb.h"

static bool success = true;

static int test_step = 0;

/*
 * Step 1:
 * Tap (0, 0) KC_A
 *
 * Step 2:
 * Tap (0, 1) KC_B
 *
 * Step 3:
 * Release (0, 0) KC_A
 **/

int main(int argc, char *argv[]) {
    takokb_init();

    action_t action;
    action.type = TYPE_NORMAL_KEY;
    action.parameter.key.keycode = KC_A;
    takokb_keymap_set_action(0, 0, 0, &action);
    action.parameter.key.keycode = KC_B;
    takokb_keymap_set_action(0, 0, 1, &action);

    takokb_task();
    test_step = 1;
    takokb_task();
    test_step = 2;
    takokb_task();
    test_step = 3;
    takokb_task();

    return success ? 0 : 1;
}

bool takokb_matrix_scan(matrix_row_t *matrix) {
    switch (test_step) {
        case 0:
            return false;
        case 1:
            matrix[0] |= (1 << 0);
            return true;
        case 2:
            matrix[0] |= (1 << 1);
            return true;
        case 3:
            matrix[0] &= ~(1 << 0);
            return true;
        default:
            return false;
    }
}

void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
    switch (test_step) {
        case 1:
            success &= (report->keys[0] == KC_A);
            if (!success) {
                fprintf(stderr, "Step 1: report->keys[0] == KC_A\n");
            }
            return;
        case 2:
            success &= (report->keys[0] == KC_A);
            if (!success) {
                fprintf(stderr, "Step 2: report->keys[0] == KC_A\n");
            }
            success &= (report->keys[1] == KC_B);
            if (!success) {
                fprintf(stderr, "Step 2: report->keys[1] == KC_B\n");
            }
            return;
        case 3:
            success &= (report->keys[0] == KC_B);
            if (!success) {
                fprintf(stderr, "Step 3: report->keys[0] == KC_B\n");
            }
            return;
        default:
            // This should never trigger
            success = false;
            fprintf(stderr, "Step %d: This should never trigger\n", test_step);
            return;
    }
}