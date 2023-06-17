#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include "takokb.h"

static uint64_t ms = 0;

uint64_t takokb_get_milliseconds(void) {
    return ms;
}

#ifndef NDEBUG
int takokb_debug_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int res = vprintf(format, args);
    va_end(args);
    return res;
}
#endif

takokb_configuration_t *takokb_get_keyboard_configuration() {
    static takokb_configuration_t configuration;
    return &configuration;
}

// ----------------------------------------

int test_step = 0;
bool success = true;

void test_tick(uint64_t milliseconds) {
    ms += milliseconds;
}

void test_next_step(void) {
    test_step++;
    printf("=== Step %d\n", test_step);
    takokb_task();
}

void assert_active_layer_equals(int layer) {
    uint8_t current_layer = takokb_get_top_activated_layer();
    if (current_layer != layer) {
        fprintf(stdout, "!!! Step %d: layer should be %d, current %d\n", test_step, layer, current_layer);
        success = false;
    } else {
        printf("--- Step %d: layer is %d\n", test_step, layer);
    }
}

void assert_keycode_equals(report_keyboard_t *report, int index, uint8_t keycode) {
    if (report->keys[index] != keycode) {
        fprintf(stdout, "!!! Step %d: key[%d] should be 0x%02x, current 0x%02x\n", test_step, index, keycode,
                report->keys[index]);
        success = false;
    } else {
        printf("--- Step %d: key[%d] is 0x%02x\n", test_step, index, keycode);
    }
}

void assert_modifiers_equals(report_keyboard_t *report, enum mods_bit bits) {
    if (report->mods == bits) {
        printf("--- Step %d: modifier bits 0x%02x\n", test_step, bits);
    } else {
        fprintf(stdout, "!!! Step %d: should have modifier bits 0x%02x, current 0x%02x\n", test_step, bits,
                report->mods);
        success = false;
    }
}


void assert_equals(bool changed, bool b, const char *message) {
    if (changed != b) {
        fprintf(stdout, "!!! Step %d: %s\n", test_step, message);
        success = false;
    } else {
        printf("--- Step %d: %s\n", test_step, message);
    }
}

void assert(bool value, const char *message) {
    if (!value) {
        fprintf(stdout, "!!! Step %d: %s\n", test_step, message);
        success = false;
    } else {
        printf("--- Step %d: %s\n", test_step, message);
    }
}

void takokb_reboot_to_bootloader(void) {

}

void takokb_system_reset(void) {

}

void takokb_reset_configuration(void) {

}

void takokb_configuration_changed(size_t offset, size_t nbytes) {

}
