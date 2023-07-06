#include <string.h>
#include <stdbool.h>
#include "keyboard.h"
#include "takokb.h"

#define MAX_KEYS 6

static report_keyboard_t report_keyboard = {0};
static uint8_t report_changed = 0;

#define CHANGED_KEYBOARD 0x01
#define CHANGED_CONSUMER 0x02

void report_add_keycode(uint8_t keycode) {
    if (keycode == KEY_NONE) {
        return;
    }

    uint8_t index;

    for (index = 0; index < MAX_KEYS; index++) {
        if (report_keyboard.keys[index] == keycode) {
            return;
        }
        if (report_keyboard.keys[index] == KEY_NONE) {
            break;
        }
    }

    if (index == MAX_KEYS) {
        return;
    }

    report_keyboard.keys[index] = keycode;

    report_changed |= CHANGED_KEYBOARD;

    takokb_debug_printf("report_add_keycode: 0x%02x\n", keycode);
}

void report_remove_keycode(uint8_t keycode) {
    if (keycode == KEY_NONE) {
        return;
    }

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
    report_keyboard.keys[MAX_KEYS - 1] = KEY_NONE;

    report_changed |= CHANGED_KEYBOARD;

    takokb_debug_printf("report_remove_keycode: 0x%02x\n", keycode);
}

void report_add_modifiers(enum mods_bit mods) {
    if (mods == 0) {
        return;
    }

    uint8_t new_mods = report_keyboard.mods | mods;
    if (new_mods != report_keyboard.mods) {
        report_keyboard.mods = new_mods;
        report_changed |= CHANGED_KEYBOARD;

        takokb_debug_printf("report_add_modifiers: 0x%02x\n", mods);
    }
}

void report_remove_modifiers(enum mods_bit mods) {
    if (mods == 0) {
        return;
    }

    uint8_t new_mods = report_keyboard.mods & ~mods;
    if (new_mods != report_keyboard.mods) {
        report_keyboard.mods = new_mods;
        report_changed |= CHANGED_KEYBOARD;

        takokb_debug_printf("report_remove_modifiers: 0x%02x\n", mods);
    }
}

bool report_keyboard_has_changed() {
    return report_changed & CHANGED_KEYBOARD;
}

void report_keyboard_clear_changed() {
    report_changed &= ~CHANGED_KEYBOARD;
}

report_keyboard_t *report_get_keyboard_hid_report() {
    return &report_keyboard;
}

static uint16_t consumer_usage = 0;

void report_consumer_set(uint16_t usage) {
    if (consumer_usage == usage) {
        return;
    }
    consumer_usage = usage;
    report_changed |= CHANGED_CONSUMER;
}

uint16_t report_consumer_get() {
    return consumer_usage;
}

bool report_consumer_has_changed() {
    return report_changed & CHANGED_CONSUMER;
}

void report_consumer_clear_changed() {
    report_changed &= ~CHANGED_CONSUMER;
}
