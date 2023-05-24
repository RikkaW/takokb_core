#include <string.h>
#include <stdbool.h>
#include "keyboard.h"
#include "takokb.h"

#define MAX_KEYS 6

static report_keyboard_t report_keyboard = {0};
static bool report_changed = false;

void report_add_keycode(uint8_t keycode) {
    uint8_t index;

    for (index = 0; index < MAX_KEYS; index++) {
        if (report_keyboard.keys[index] == keycode) {
            return;
        }
        if (report_keyboard.keys[index] == KC_NO) {
            break;
        }
    }

    if (index == MAX_KEYS) {
        return;
    }

    report_keyboard.keys[index] = keycode;

    report_changed = true;

    takokb_debug_printf("report_add_keycode: 0x%02x\n", keycode);
}

void report_remove_keycode(uint8_t keycode) {
    uint8_t index;

    for (index = 0; index < MAX_KEYS; index++) {
        if (report_keyboard.keys[index] == keycode) {
            break;
        }
    }

    if (index == MAX_KEYS) {
        return;
    }

    memcpy(&report_keyboard.keys[index], &report_keyboard.keys[index + 1], MAX_KEYS - index - 1);
    report_keyboard.keys[MAX_KEYS - 1] = KC_NO;

    report_changed = true;

    takokb_debug_printf("report_remove_keycode: 0x%02x\n", keycode);
}

void report_add_modifiers(enum mods_bit mods) {
    uint8_t new_mods = report_keyboard.mods | mods;
    if (new_mods != report_keyboard.mods) {
        report_keyboard.mods = new_mods;
        report_changed = true;

        takokb_debug_printf("report_add_modifiers: 0x%02x\n", mods);
    }
}

void report_remove_modifiers(enum mods_bit mods) {
    uint8_t new_mods = report_keyboard.mods & ~mods;
    if (new_mods != report_keyboard.mods) {
        report_keyboard.mods = new_mods;
        report_changed = true;

        takokb_debug_printf("report_remove_modifiers: 0x%02x\n", mods);
    }
}

bool report_has_changed() {
    return report_changed;
}

void report_clear_changed() {
    report_changed = false;
}

report_keyboard_t *report_get_keyboard_hid_report() {
    return &report_keyboard;
}