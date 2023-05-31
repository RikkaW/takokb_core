#include "takokb.h"
#include "configurator.h"

static_assert(sizeof(action_t) == 4, "action_t should be 4 bytes");
static_assert(sizeof(enum configurator_commands) == 1, "configurator_commands must be 8 bits");
static_assert(sizeof(configurator_hid_report_t) == 8, "configurator_hid_report must be 64 bits");

int main(int argc, char *argv[]) {
    return 0;
}

bool takokb_matrix_scan(matrix_row_t *matrix) {
    return false;
}

void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
}

void takokb_send_configurator_hid_report(configurator_hid_report_t *report, size_t size) {

}
