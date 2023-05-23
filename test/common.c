#include <stdint.h>
#include <sys/time.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include "takokb.h"

static uint64_t ms = 0;

void takokb_test_tick(void) {
    ms++;
}

uint64_t takokb_get_milliseconds(void) {
    return ms;
}

int takokb_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int res = vprintf(format, args);
    va_end(args);
    return res;
}