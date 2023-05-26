#ifndef TAKOKB_ACTION_H
#define TAKOKB_ACTION_H

#include "keyboard.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void(action_function_t)(key_state_t *key_state, action_t *action);

// -------- STATE_BASIC --------
#define STATE_BASIC_IDLE_TO_TAP 0
#define STATE_BASIC_TAP_TO_IDLE 1

#define STATE_BASIC_FUNC(type, state) state_basic_##type##_##state

#define STATE_BASIC_FUNC_ARRAY(type) [type] = { \
    (action_function_t*) STATE_BASIC_FUNC(type, STATE_BASIC_IDLE_TO_TAP), \
    (action_function_t*) STATE_BASIC_FUNC(type, STATE_BASIC_TAP_TO_IDLE), \
}

#define STATE_BASIC_FUNC_DEF(type, state) void state_basic_##type##_##state(key_state_t *key_state, action_t *action)

#define STATE_BASIC_FUNCS_DEF(type) \
void state_basic_##type##_STATE_BASIC_IDLE_TO_TAP(key_state_t *key_state, action_t *action); \
void state_basic_##type##_STATE_BASIC_TAP_TO_IDLE(key_state_t *key_state, action_t *action)

STATE_BASIC_FUNCS_DEF(TYPE_KEY);

STATE_BASIC_FUNCS_DEF(TYPE_MODIFIER);

STATE_BASIC_FUNCS_DEF(TYPE_TRANSPARENT);

STATE_BASIC_FUNCS_DEF(TYPE_MOMENTARY_LAYER);

STATE_BASIC_FUNCS_DEF(TYPE_TOGGLE_LAYER);

STATE_BASIC_FUNCS_DEF(TYPE_BOTTOM_LAYER);

// -------- STATE_THREE --------


#ifdef __cplusplus
}
#endif
#endif //TAKOKB_ACTION_H
