#include <stdint.h>
#include <sys/time.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include "takokb.h"

static uint64_t ms = 0;

int test_step = 0;
bool success = true;

void test_tick(void) {
    ms++;
}

void test_next_step(void) {
    test_step++;
    printf("=== Step %d\n", test_step);
    takokb_task();
}

void assert_active_layer_equals(int layer) {
    uint8_t current_layer = takokb_get_active_layer();
    if (current_layer != layer) {
        fprintf(stdout, "!!! Step %d: layer should be %d, current %d\n", test_step, layer, current_layer);
        success = false;
    } else {
        printf("--- Step %d: layer is %d\n", test_step, layer);
    }
}

void assert_keycode_equals(report_keyboard_t *report, int index, uint8_t keycode) {
    if (report->keys[index] != keycode) {
        fprintf(stdout, "!!! Step %d: key[%d] should be 0x%02x, current 0x%02x\n", test_step, index, keycode, report->keys[index]);
        success = false;
    } else {
        printf("--- Step %d: key[%d] is 0x%02x\n", test_step, index, keycode);
    }
}

uint64_t takokb_get_milliseconds(void) {
    return ms;
}

int takokb_debug_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int res = vprintf(format, args);
    va_end(args);
    return res;
}

void assert_equals(bool changed, bool b, const char *message) {
    if (changed != b) {
        fprintf(stdout, "!!! Step %d: %s\n", test_step, message);
        success = false;
    } else {
        printf("--- Step %d: %s\n", test_step, message);
    }
}
