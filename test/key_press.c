#include "takokb.h"

static bool press = false;
static int result = 0;

int main(int argc, char *argv[]) {
    action_t action;
    action.type = TYPE_NORMAL_KEY;
    action.parameter.key.keycode = KC_A;

    takokb_init();
    takokb_keymap_set_action(0, 0, 0, &action);

    takokb_task();
    press = true;
    takokb_task();

    return result;
}

bool takokb_matrix_scan(matrix_row_t *matrix) {
    if (press) {
        matrix[0] = 1;
        return true;
    }
    return false;
}

void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
    result = (report->keys[0] == KC_A) ? 0 : 1;
}