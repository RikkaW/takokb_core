#include "takokb.h"

static_assert(sizeof(action_t) == 4, "action_t should be 4 bytes");

int main(int argc, char *argv[]) {
    return 0;
}

bool takokb_matrix_scan(matrix_row_t *matrix) {
    return false;
}

void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
}
