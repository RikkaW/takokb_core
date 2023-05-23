#ifndef KEYBOARD_API_H
#define KEYBOARD_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "takokb_action.h"

#if (TAKOKB_MATRIX_COLS <= 8)
typedef uint8_t matrix_row_t;
#elif (TAKOKB_MATRIX_COLS <= 16)
typedef uint16_t matrix_row_t;
#elif (TAKOKB_MATRIX_COLS <= 32)
typedef uint32_t matrix_row_t;
#else
#    error "TAKOKB_MATRIX_COLS must be less than 32"
#endif

// ---------- action ----------

typedef union {
    uint32_t raw: 24;

    struct action_key {
        uint8_t keycode: 8;
        uint32_t reserved: 16;
    } key;

    struct action_layer {
        uint8_t id: 8;
        uint8_t enabled: 8;
        uint32_t reserved: 16;
    } layer;

} __attribute__((packed)) action_parameter_t;

typedef struct {
    uint8_t type;
    action_parameter_t parameter;
} __attribute__((packed)) action_t;

// ----------------------------

// ---------- report ----------

#define KEYBOARD_REPORT_KEYS 6U

typedef union {
    uint8_t raw[KEYBOARD_REPORT_KEYS + 2];
    struct {
        uint8_t mods;
        uint8_t reserved;
        uint8_t keys[KEYBOARD_REPORT_KEYS];
    };
} __attribute__((packed)) report_keyboard_t;

// ----------------------------

void takokb_init(void);

void takokb_task(void);

matrix_row_t *takokb_get_matrix(void);

void takokb_keymap_set_action(uint8_t layer, uint8_t row, uint8_t column, action_t *action);

// ---------- weak functions ----------
#ifdef TAKOKB_TEST
#define __TAKOKB_WEAK
#else
#define __TAKOKB_WEAK __attribute__((weak))
#endif
/**
 * @return Current milliseconds
 */
__TAKOKB_WEAK uint64_t takokb_get_milliseconds(void);

__TAKOKB_WEAK bool takokb_matrix_scan(matrix_row_t *matrix);

#ifndef NDEBUG
__TAKOKB_WEAK int takokb_printf(const char *format, ...);
#else
#define takokb_printf(...)
#endif

__TAKOKB_WEAK void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size);

#ifdef __cplusplus
}
#endif

#endif //KEYBOARD_API_H
