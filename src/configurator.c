#include "configurator.h"
#include "takokb.h"

void configurator_receive_hid_report(configurator_hid_report_t *report) {
    switch (report->command_id) {
        case get_protocol_version:
            report->protocol_version.protocol_version = TAKOKB_CONFIGURATOR_PROTOCOL_VERSION;
            break;
    }

    takokb_send_configurator_hid_report((uint8_t *) report, sizeof(configurator_hid_report_t));
}
