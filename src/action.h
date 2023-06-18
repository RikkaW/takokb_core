#ifndef TAKOKB_ACTION_H
#define TAKOKB_ACTION_H

#include "keyboard.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void(action_function_t)(key_state_t *key_state, action_t *action);

// -------- STATE_BASIC --------
#define basic_IDLE_to_TAP 0
#define basic_TAP_to_IDLE 1
#define basic_NUM_TRANSITIONS 2

#define STATE_BASIC_FUNC_NAME(type, stateA, stateB) state_basic_##type##_##stateA##_to_##stateB
#define STATE_BASIC_FUNC_DEF(type, stateA, stateB) void STATE_BASIC_FUNC_NAME(type, stateA, stateB)(key_state_t *key_state, action_t *action)

#define STATE_BASIC_FUNC_ARRAY(type) [type] = { \
    (action_function_t*) STATE_BASIC_FUNC_NAME(type, IDLE, TAP), \
    (action_function_t*) STATE_BASIC_FUNC_NAME(type, TAP, IDLE), \
}

#define STATE_BASIC_FUNCS_DEF(type) \
STATE_BASIC_FUNC_DEF(type, IDLE, TAP); \
STATE_BASIC_FUNC_DEF(type, TAP, IDLE)

STATE_BASIC_FUNCS_DEF(TYPE_KEY);

STATE_BASIC_FUNCS_DEF(TYPE_MODIFIER);

STATE_BASIC_FUNCS_DEF(TYPE_TRANSPARENT);

STATE_BASIC_FUNCS_DEF(TYPE_MOMENTARY_LAYER);

STATE_BASIC_FUNCS_DEF(TYPE_TOGGLE_LAYER);

STATE_BASIC_FUNCS_DEF(TYPE_BOTTOM_LAYER);

STATE_BASIC_FUNCS_DEF(TYPE_MACRO);

STATE_BASIC_FUNCS_DEF(TYPE_TAKOKB);

STATE_BASIC_FUNCS_DEF(TYPE_PROFILE);

static action_function_t *state_basic_functions[][basic_NUM_TRANSITIONS] = {
        STATE_BASIC_FUNC_ARRAY(TYPE_KEY),
        STATE_BASIC_FUNC_ARRAY(TYPE_MODIFIER),
        STATE_BASIC_FUNC_ARRAY(TYPE_TRANSPARENT),
        STATE_BASIC_FUNC_ARRAY(TYPE_MOMENTARY_LAYER),
        STATE_BASIC_FUNC_ARRAY(TYPE_TOGGLE_LAYER),
        STATE_BASIC_FUNC_ARRAY(TYPE_BOTTOM_LAYER),
        STATE_BASIC_FUNC_ARRAY(TYPE_MACRO),
        STATE_BASIC_FUNC_ARRAY(TYPE_TAKOKB),
        STATE_BASIC_FUNC_ARRAY(TYPE_PROFILE),
};

#define NUM_STATE_BASIC_TYPES 6

#define CALL_basic_TRANSITION_FUNC(type, stateA, stateB) \
    state_basic_functions[type][basic_##stateA##_to_##stateB]((key_state_t*) key_state, (action_t*) action)

// -------- STATE_TAP_HOLD --------
#define tapHold_IDLE_to_TAP 0
#define tapHold_TAP_to_HOLD 1
#define tapHold_HOLD_to_IDLE 2
#define tapHold_TAP_to_WAIT_FOR_RELEASE_INTERNAL 3
#define tapHold_WAIT_FOR_RELEASE_INTERNAL_to_TAP_HOLD 4
#define tapHold_WAIT_FOR_RELEASE_INTERNAL_to_HOLD_WAIT_FOR_HOLD 5
#define tapHold_WAIT_FOR_TAP_HOLD_to_IDLE 6
#define tapHold_WAIT_FOR_TAP_HOLD_to_TAP_HOLD 7
#define tapHold_TAP_HOLD_to_IDLE 8
#define tapHold_NUM_TRANSITIONS 9

#define STATE_TAP_HOLD_FUNC_NAME(type, stateA, stateB) state_tapHold_##type##_##stateA##_to_##stateB
#define STATE_TAP_HOLD_FUNC_DEF(type, stateA, stateB) void STATE_TAP_HOLD_FUNC_NAME(type, stateA, stateB)(key_state_t *key_state, action_t *action)

#define STATE_TAP_HOLD_FUNC_ARRAY(type) [type] = { \
    (action_function_t*) STATE_TAP_HOLD_FUNC_NAME(type, IDLE, TAP), \
    (action_function_t*) STATE_TAP_HOLD_FUNC_NAME(type, TAP, HOLD), \
    (action_function_t*) STATE_TAP_HOLD_FUNC_NAME(type, HOLD, IDLE), \
    (action_function_t*) STATE_TAP_HOLD_FUNC_NAME(type, TAP, WAIT_FOR_RELEASE_INTERNAL), \
    (action_function_t*) STATE_TAP_HOLD_FUNC_NAME(type, WAIT_FOR_RELEASE_INTERNAL, TAP_HOLD), \
    (action_function_t*) STATE_TAP_HOLD_FUNC_NAME(type, WAIT_FOR_RELEASE_INTERNAL, HOLD_WAIT_FOR_HOLD), \
    (action_function_t*) STATE_TAP_HOLD_FUNC_NAME(type, WAIT_FOR_TAP_HOLD, IDLE), \
    (action_function_t*) STATE_TAP_HOLD_FUNC_NAME(type, WAIT_FOR_TAP_HOLD, TAP_HOLD), \
    (action_function_t*) STATE_TAP_HOLD_FUNC_NAME(type, TAP_HOLD, IDLE), \
}

#define STATE_TAP_HOLD_FUNCS_DEF(type) \
STATE_TAP_HOLD_FUNC_DEF(type, IDLE, TAP); \
STATE_TAP_HOLD_FUNC_DEF(type, TAP, HOLD); \
STATE_TAP_HOLD_FUNC_DEF(type, HOLD, IDLE); \
STATE_TAP_HOLD_FUNC_DEF(type, TAP, WAIT_FOR_RELEASE_INTERNAL); \
STATE_TAP_HOLD_FUNC_DEF(type, WAIT_FOR_RELEASE_INTERNAL, TAP_HOLD); \
STATE_TAP_HOLD_FUNC_DEF(type, WAIT_FOR_RELEASE_INTERNAL, HOLD_WAIT_FOR_HOLD); \
STATE_TAP_HOLD_FUNC_DEF(type, WAIT_FOR_TAP_HOLD, IDLE); \
STATE_TAP_HOLD_FUNC_DEF(type, WAIT_FOR_TAP_HOLD, TAP_HOLD); \
STATE_TAP_HOLD_FUNC_DEF(type, TAP_HOLD, IDLE)

STATE_TAP_HOLD_FUNCS_DEF(TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER);

static action_function_t *state_tapHold_functions[][tapHold_NUM_TRANSITIONS] = {
        STATE_TAP_HOLD_FUNC_ARRAY(TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER)
};

#define CALL_tapHold_TRANSITION_FUNC(type, stateA, stateB) \
    state_tapHold_functions[type][tapHold_##stateA##_to_##stateB]((key_state_t*) key_state, (action_t*) action)

#ifdef __cplusplus
}
#endif
#endif //TAKOKB_ACTION_H
