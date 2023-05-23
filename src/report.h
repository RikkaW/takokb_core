#ifndef TAKOKB_REPORT_H
#define TAKOKB_REPORT_H

#ifdef __cplusplus
extern "C" {
#endif

void report_add_keycode(uint8_t keycode);

void report_remove_keycode(uint8_t keycode);

void report_add_modifiers(enum mods_bit mods);

void report_remove_modifiers(enum mods_bit mods);

bool report_has_changed();

void report_clear_changed();

report_keyboard_t *report_get_keyboard_hid_report();

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_REPORT_H
