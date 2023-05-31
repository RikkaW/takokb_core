#include "configurator.h"
#include "keymap.h"

void configurator_receive_hid_report(configurator_hid_report_t *report) {
    switch (report->command_id) {
        case get_protocol_version: {
            report->protocol_version.protocol_version = TAKOKB_CONFIGURATOR_PROTOCOL_VERSION;
            break;
        }
        case get_keyboard_info_metadata: {
            if (report->keyboard_info_metadata.version == TAKOKB_KEYBOARD_INFO_VERSION) {
                takokb_debug_printf("Host has cached keyboard information version %d.\n", TAKOKB_KEYBOARD_INFO_VERSION);
                break;
            }
            report->keyboard_info_metadata.version = TAKOKB_KEYBOARD_INFO_VERSION;
            report->keyboard_info_metadata.size = TAKOKB_KEYBOARD_INFO_SIZE;
            report->keyboard_info_metadata.pages = (TAKOKB_KEYBOARD_INFO_SIZE + 4) / 5;
            break;
        }
        case get_keyboard_info: {
            // TODO
            return;
        }
        case get_keycode: {
            action_t *action = keymap_get_action(report->keycode.layer, report->keycode.row, report->keycode.column);
            report->keycode.action = *action;
            break;
        }
        case set_keycode: {
            // TODO: verify if the action is valid
            keymap_set_action(report->keycode.layer, report->keycode.row, report->keycode.column, &report->keycode.action);
            break;
        }
        default:
        case failed: {
            return;
        }
    }

    takokb_send_configurator_hid_report((uint8_t *) report, sizeof(configurator_hid_report_t));
}
