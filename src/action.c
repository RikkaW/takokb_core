#include "takokb_action.h"
#include "keyboard.h"
#include "report.h"
#include "action.h"

action_t action_no = {TYPE_KEY, STATE_TYPE_BASIC, {.key = KC_NO}};
action_t action_trans = {TYPE_TRANSPARENT, STATE_TYPE_BASIC};

// -------- TYPE_KEY --------
STATE_BASIC_FUNC_DEF(TYPE_KEY, STATE_BASIC_IDLE_TO_TAP) {
    report_add_keycode(action->parameter.key.keycode);
}

STATE_BASIC_FUNC_DEF(TYPE_KEY, STATE_BASIC_TAP_TO_IDLE) {
    report_remove_keycode(action->parameter.key.keycode);
}

// -------- TYPE_MODIFIER --------
STATE_BASIC_FUNC_DEF(TYPE_MODIFIER, STATE_BASIC_IDLE_TO_TAP) {
    report_add_modifiers(action->parameter.key.modifiers);
}

STATE_BASIC_FUNC_DEF(TYPE_MODIFIER, STATE_BASIC_TAP_TO_IDLE) {
    report_remove_modifiers(action->parameter.key.modifiers);
}

// -------- TYPE_TRANSPARENT --------
STATE_BASIC_FUNC_DEF(TYPE_TRANSPARENT, STATE_BASIC_IDLE_TO_TAP) {
}

STATE_BASIC_FUNC_DEF(TYPE_TRANSPARENT, STATE_BASIC_TAP_TO_IDLE) {
}

// -------- TYPE_MOMENTARY_LAYER --------
STATE_BASIC_FUNC_DEF(TYPE_MOMENTARY_LAYER, STATE_BASIC_IDLE_TO_TAP) {
    uint8_t queue_index = keyboard_momentary_layer_queue_insert(action->parameter.layer.id);
    if (queue_index != MOMENTARY_LAYER_QUEUE_INDEX_INVALID) {
        key_state->extras.momentary_layer.queue_index = queue_index;
    }
}

STATE_BASIC_FUNC_DEF(TYPE_MOMENTARY_LAYER, STATE_BASIC_TAP_TO_IDLE) {
    keyboard_momentary_layer_queue_remove(key_state->extras.momentary_layer.queue_index);
}

// -------- TYPE_TOGGLE_LAYER --------
STATE_BASIC_FUNC_DEF(TYPE_TOGGLE_LAYER, STATE_BASIC_IDLE_TO_TAP) {
    uint8_t mask = (1 << action->parameter.layer.id);
    if (*keyboard_get_toggled_layers_mask() & mask) {
        *keyboard_get_toggled_layers_mask() &= ~mask;
    } else {
        *keyboard_get_toggled_layers_mask() |= mask;
    }
}

STATE_BASIC_FUNC_DEF(TYPE_TOGGLE_LAYER, STATE_BASIC_TAP_TO_IDLE) {
}

// -------- TYPE_BOTTOM_LAYER --------
STATE_BASIC_FUNC_DEF(TYPE_BOTTOM_LAYER, STATE_BASIC_IDLE_TO_TAP) {
    keyboard_set_bottom_layer(action->parameter.layer.id);
}

STATE_BASIC_FUNC_DEF(TYPE_BOTTOM_LAYER, STATE_BASIC_TAP_TO_IDLE) {
}
