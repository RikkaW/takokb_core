#include <cstdio>
#include "takokb.h"
#include "report.h"
#include "common.h"
#include "debug.h"
#include "configurator.h"

int main(int argc, char *argv[]) {
    takokb_init();

    uint8_t report[8]{0};
    report[0] = get_protocol_version;
    takokb_receive_configurator_hid_report(report, sizeof(report) );

    return success ? 0 : 1;
}

bool takokb_matrix_scan(matrix_row_t *matrix) {
    return false;
}

void takokb_send_configurator_hid_report(uint8_t *report, size_t size) {
    assert(report[1] == TAKOKB_CONFIGURATOR_PROTOCOL_VERSION, "protocol version");
}
