#include <cstdio>
#include "takokb.h"
#include "report.h"
#include "common.h"
#include "debug.h"
#include "configurator.h"

int main(int argc, char *argv[]) {
    takokb_init();

    takokb_configurator_report_t report;
    report.command_id = takokb_configurator_command_get_protocol_version;
    takokb_receive_configurator_report(&report, sizeof(report));

    return success ? 0 : 1;
}

bool takokb_matrix_scan(matrix_row_t *matrix) {
    return false;
}

void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size) {
}

void takokb_send_configurator_report(takokb_configurator_report_t *report, size_t size) {
    assert(report->protocol_version.protocol_version == TAKOKB_CONFIGURATOR_PROTOCOL_VERSION, "protocol version");
}
