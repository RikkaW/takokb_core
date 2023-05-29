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

#define TAKOKB_CONFIGURATOR_PROTOCOL_VERSION 1

#ifndef TAKOKB_KEYBOARD_INFO_VERSION
#define TAKOKB_KEYBOARD_INFO_VERSION 1
#endif

#ifndef TAKOKB_KEYBOARD_INFO_SIZE
#define TAKOKB_KEYBOARD_INFO_SIZE 0
#endif

// ---------- action ----------

typedef struct action {
    uint8_t state_machine: 3;
    uint8_t id: 5;

    union parameter {
        uint8_t raw[3];

        struct action_key {
            uint8_t keycode: 8;
            uint8_t modifiers: 8;
        } key;

        struct action_layer {
            uint8_t id: 8;
            uint8_t enabled: 8;
        } layer;

        struct action_layer_tap {
            uint8_t layer_id: 8;
            uint8_t keycode: 8;
            uint8_t modifiers: 8;
        } tap_key_hold_layer;

    } parameter;

} __attribute__((packed)) action_t;

_Static_assert(sizeof(action_t) == 4, "configurator_hid_report must be 32 bits");

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

void takokb_keymap_set_action(uint8_t layer, uint8_t row, uint8_t column, const action_t *action);

uint8_t takokb_get_top_activated_layer(void);

size_t takokb_keymap_get_size(void);

action_t *takokb_keymap_get_action(uint8_t layer, uint8_t row, uint8_t column);

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
__TAKOKB_WEAK int takokb_debug_printf(const char *format, ...);
#else
#define takokb_debug_printf(...)
#endif

__TAKOKB_WEAK void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size);

__TAKOKB_WEAK void takokb_send_configurator_hid_report(uint8_t *report, size_t size);

void takokb_receive_configurator_hid_report(uint8_t *report, size_t size);

#ifdef __cplusplus
}
#endif

#endif //KEYBOARD_API_H
