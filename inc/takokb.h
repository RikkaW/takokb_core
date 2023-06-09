#ifndef TAKOKB_PUBLIC_API_H
#define TAKOKB_PUBLIC_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <takokb_action.h>

#ifndef TAKOKB_MAX_PROFILES
#define TAKOKB_MAX_PROFILES 1
#endif

#ifndef TAKOKB_MAX_LAYERS
#define TAKOKB_MAX_LAYERS 4
#endif

#ifndef TAKOKB_MATRIX_ROWS
#define TAKOKB_MATRIX_ROWS 1
#endif

#ifndef TAKOKB_MATRIX_COLS
#define TAKOKB_MATRIX_COLS 4
#endif

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
#define TAKOKB_CONFIGURATOR_DATA_VERSION     1

#ifndef TAKODB_ENCODER_COUNT
#define TAKODB_ENCODER_COUNT 0
#endif

// ---------- action ----------

typedef struct action {
    uint8_t state_machine: 3;
    uint8_t type: 5;

    union parameter {
        uint8_t raw[3];

        struct action_key {
            enum keycodes keycode: 8;
            enum mods_bit modifiers: 8;
        } key;

        struct action_layer {
            uint8_t id: 8;
            uint8_t enabled: 8;
        } layer;

        struct action_layer_tap {
            uint8_t layer_id: 8;
            enum keycodes keycode: 8;
            enum mods_bit modifiers: 8;
        } tap_key_hold_layer;

        struct action_custom {
            enum takokb_keycodes keycode: 8;
        } custom;

        struct action_profile {
            uint8_t profile: 8;
        } profile;

        struct action_consumer {
            uint8_t usage;
            uint8_t usage2;
        } consumer;
    } parameter;

// On chips that not support unaligned memory access, action_t must be 4 byte aligned
} __attribute__((aligned(4))) action_t;

#ifdef __cplusplus
static_assert(sizeof(action_t) == 4, "action_t must be 4 byte");
#else
_Static_assert(sizeof(action_t) == 4, "action_t must be 4 byte");
#endif

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

// ---------- configurator ----------

enum __attribute__((__packed__)) takokb_configurator_commands {
    takokb_configurator_command_get_protocol_version = 0x01,
    takokb_configurator_command_get_keyboard_info_metadata = 0x02,
    takokb_configurator_command_get_keyboard_info = 0x03,
    takokb_configurator_command_get_action = 0x04,
    takokb_configurator_command_set_action = 0x05,
    takokb_configurator_request_reboot_to_bootloader = 0x06,
    takokb_configurator_command_custom_start = 0x80,
};

enum __attribute__((__packed__)) takokb_configurator_result_codes {
    takokb_configurator_result_success = 0x00,
    takokb_configurator_result_invalid = 0x01,
};

typedef struct configurator_report {

    enum takokb_configurator_commands command_id;
    enum takokb_configurator_result_codes result_code;

    union {
        uint8_t raw[62];

        struct {
            uint32_t protocol_version;
        } __attribute__((packed)) protocol_version;

        struct {
            uint32_t version;
            uint32_t size;
            uint32_t pages;
        } __attribute__((packed)) keyboard_info_metadata;

        struct {
            uint32_t page;
            uint8_t size;
            uint8_t payload[57];
        } __attribute__((packed)) keyboard_info_payload;

        struct {
            uint8_t profile;
            uint8_t layer;
            uint8_t row;
            uint8_t col;
            action_t action;
        } __attribute__((packed)) action;
    };

} __attribute__((packed)) takokb_configurator_report_t;

// ----------------------------

// ---------- keyboard configuration ----------

typedef struct takokb_configuration {
    uint32_t version;
    uint8_t current_profile;
    action_t keymaps[TAKOKB_MAX_PROFILES][TAKOKB_MAX_LAYERS][TAKOKB_MATRIX_ROWS][TAKOKB_MATRIX_COLS];
    action_t encoders[TAKOKB_MAX_PROFILES][TAKOKB_MAX_LAYERS][TAKODB_ENCODER_COUNT][2];
} __attribute((aligned(4))) takokb_configuration_t;

// ---------- public functions ----------

void takokb_init(void);

void takokb_task(void);

matrix_row_t *takokb_get_matrix(void);

void takokb_keymap_set_action(uint8_t profile, uint8_t layer, uint8_t row, uint8_t column, const action_t *action);

uint8_t takokb_get_top_activated_layer(void);

uint8_t takokb_get_current_profile(void);

action_t *takokb_keymap_get_action(uint8_t profile, uint8_t layer, uint8_t row, uint8_t column);

/**
 *
 * @param configuration
 * @return Return true if the configuration changed (e.g., version is different), otherwise false
 */
bool takokb_keymap_set_configuration(takokb_configuration_t *configuration);

void takokb_keymap_disable_save_configuration();

// ---------- weak functions ----------

/**
 * @return Current milliseconds
 */
uint64_t takokb_get_milliseconds(void);

void takokb_delay_ms(uint32_t ms);

void takokb_delay_us(uint32_t us);

bool takokb_matrix_scan(matrix_row_t *matrix);

#ifndef NDEBUG
int takokb_debug_printf(const char *format, ...);
#else
#define takokb_debug_printf(...)
#endif

void takokb_send_keyboard_hid_report(report_keyboard_t *report, size_t size);

void takokb_send_configurator_report(takokb_configurator_report_t *report, size_t size);

void takokb_receive_configurator_report(takokb_configurator_report_t *report, size_t size);

takokb_configuration_t *takokb_get_keyboard_configuration(void);

void takokb_send_consumer_usage(uint16_t usage);

/**
 * @brief Called when TAKOKB_BOOTLOADER key is pressed
 */
void takokb_reboot_to_bootloader(void);

/**
 * @brief Called when TAKOKB_SYSTEM_RESET key is pressed
 */
void takokb_system_reset(void);

void takokb_configuration_changed(size_t offset, size_t nbytes);

void takokb_reset_configuration(void);

/**
 * @brief Called when active layer changed.
 * @param layer Layer number
 * @param from_key True if layer changed by user press, otherwise false
 */
void takokb_on_active_layer_changed(uint8_t layer);

/**
 * @brief Called when profile changed.
 * @param profile Profile number
 */
void takokb_on_profile_changed(uint8_t profile);

/**
 * @return Keyboard info array
 */
const uint8_t *takokb_get_keyboard_info(void);

/**
 * @return Keyboard info array size
 */
size_t takokb_get_keyboard_info_size(void);

/**
 * @return Keyboard info version
 */
uint32_t takokb_get_keyboard_info_version(void);

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_PUBLIC_API_H
