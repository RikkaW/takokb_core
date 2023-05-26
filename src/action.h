#ifndef TAKOKB_ACTION_H
#define TAKOKB_ACTION_H

#include "keyboard.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void(action_function_t)(key_state_t *key_state, action_t *action);

#define STATE_TWO_IDLE_TO_PRESSED 0
#define STATE_TWO_PRESSED_TO_IDLE 1

#define TWO_STATE_FUNC(type, state) state_two_##type##_##state

#define TWO_STATE_FUNC_ARRAY(type) [type] = { \
    (action_function_t*) TWO_STATE_FUNC(type, STATE_TWO_IDLE_TO_PRESSED), \
    (action_function_t*) TWO_STATE_FUNC(type, STATE_TWO_PRESSED_TO_IDLE), \
}

#define TWO_STATE_FUNC_DEF(type, state) void state_two_##type##_##state(key_state_t *key_state, action_t *action)

#define TWO_STATE_FUNCS_DEF(type) \
void state_two_##type##_STATE_TWO_IDLE_TO_PRESSED(key_state_t *key_state, action_t *action); \
void state_two_##type##_STATE_TWO_PRESSED_TO_IDLE(key_state_t *key_state, action_t *action)

TWO_STATE_FUNCS_DEF(TYPE_KEY);

TWO_STATE_FUNCS_DEF(TYPE_MODIFIER);

TWO_STATE_FUNCS_DEF(TYPE_TRANSPARENT);

TWO_STATE_FUNCS_DEF(TYPE_MOMENTARY_LAYER);

TWO_STATE_FUNCS_DEF(TYPE_TOGGLE_LAYER);

TWO_STATE_FUNCS_DEF(TYPE_BOTTOM_LAYER);


#ifdef __cplusplus
}
#endif
#endif //TAKOKB_ACTION_H
