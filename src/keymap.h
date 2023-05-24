#ifndef TAKOKB_KEYMAP_H
#define TAKOKB_KEYMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "takokb_action.h"

void keymap_init(void);

action_t *keymap_get_action(uint8_t layer, uint8_t row, uint8_t column);

void keymap_set_action(uint8_t layer, uint8_t row, uint8_t column, const action_t *action);

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_KEYMAP_H
