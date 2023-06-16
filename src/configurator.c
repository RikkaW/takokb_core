#include "configurator.h"
#include "keymap.h"

void configurator_receive_report(configurator_report_t *report) {
    switch (report->command_id) {
        case takokb_configurator_command_get_protocol_version: {
            report->result_code = takokb_configurator_result_success;
            report->protocol_version.protocol_version = TAKOKB_CONFIGURATOR_PROTOCOL_VERSION;
            break;
        }
        case takokb_configurator_command_get_keyboard_info_metadata: {
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
            action_t *action = keymap_get_action(report->keycode.layer, report->keycode.row, report->keycode.column);
            report->keycode.action = *action;
            break;
        }
        case takokb_configurator_command_set_action: {
            // TODO: verify if the action is valid
            keymap_set_action(report->keycode.layer, report->keycode.row, report->keycode.column, &report->keycode.action);
            break;
        }
        default: {
            break;
        }
    }

    takokb_send_configurator_report(report, sizeof(configurator_report_t));
}
