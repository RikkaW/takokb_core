#include <string.h>
#include "configurator.h"
#include "keymap.h"

void configurator_receive_report(takokb_configurator_report_t *report, size_t size) {
    if (size != sizeof(takokb_configurator_report_t)) {
        return;
    }

    switch (report->command_id) {
        case takokb_configurator_command_get_protocol_version: {
            report->result_code = takokb_configurator_result_success;
            report->protocol_version.protocol_version = TAKOKB_CONFIGURATOR_PROTOCOL_VERSION;
            break;
        }
        case takokb_configurator_command_get_keyboard_info_metadata: {
            report->result_code = takokb_configurator_result_success;
            if (report->keyboard_info_metadata.version == TAKOKB_KEYBOARD_INFO_VERSION) {
                takokb_debug_printf("Host has cached keyboard information version %d.\n", TAKOKB_KEYBOARD_INFO_VERSION);
                break;
            }
            report->keyboard_info_metadata.version = TAKOKB_KEYBOARD_INFO_VERSION;
            report->keyboard_info_metadata.size = TAKOKB_KEYBOARD_INFO_SIZE;
            report->keyboard_info_metadata.pages = (TAKOKB_KEYBOARD_INFO_SIZE + 4) / 5;
            break;
        }
        case takokb_configurator_command_get_keyboard_info: {
            // TODO
            return;
        }
        case takokb_configurator_command_get_action: {
            action_t *action = keymap_get_action(report->action.layer, report->action.row, report->action.col);
            report->action.action = *action;
            report->result_code = takokb_configurator_result_success;
            break;
        }
        case takokb_configurator_command_set_action: {
            // TODO: verify if the action is valid

            // Use memcpy to avoid alignment issues as GUI application assumes there are no padding bytes.
            action_t action;
            memcpy(&action, &report->action.action, sizeof(action_t));

            keymap_set_action(report->action.layer, report->action.row, report->action.col, &action);
            report->result_code = takokb_configurator_result_success;
            break;
        }
        default: {
            takokb_debug_printf("Unknown command ID: %d\n", report->command_id);
            return;
        }
    }

    takokb_send_configurator_report(report, sizeof(takokb_configurator_report_t));
}
