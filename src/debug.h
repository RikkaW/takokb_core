#ifndef TAKOKB_DEBUG_H
#define TAKOKB_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "takokb_action.h"

#ifndef NDEBUG
void takokb_debug_print_action(action_t *action);

void takokb_debug_print_keymap(void);

const char *takokb_debug_keycode_to_name(enum keycodes keycode);

const char *takokb_debug_modifier_bit_to_name(enum mods_bit bit);
#else
#define takokb_debug_print_action(action)

#define takokb_debug_print_keymap()

#define takokb_debug_keycode_to_name(keycode)

#define takokb_debug_modifier_bit_to_name(bit)
#endif
#ifdef __cplusplus
}
#endif
#endif //TAKOKB_DEBUG_H
