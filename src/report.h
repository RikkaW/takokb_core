#ifndef TAKOKB_REPORT_H
#define TAKOKB_REPORT_H

#ifdef __cplusplus
extern "C" {
#endif

// -------- Keyboard --------

void report_add_keycode(uint8_t keycode);

void report_remove_keycode(uint8_t keycode);

void report_add_modifiers(enum mods_bit mods);

void report_remove_modifiers(enum mods_bit mods);

bool report_keyboard_has_changed();

report_keyboard_t *report_get_keyboard_hid_report();

void report_keyboard_clear_changed();

// -------- Consumer --------

void report_consumer_set(uint16_t usage);

uint16_t report_consumer_get();

bool report_consumer_has_changed();

void report_consumer_clear_changed();

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_REPORT_H
