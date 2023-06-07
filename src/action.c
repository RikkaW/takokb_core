#include "takokb_action.h"
#include "keyboard.h"
#include "report.h"
#include "action.h"

action_t action_no = {
        .state_machine= STATE_MACHINE_BASIC,
        .id=TYPE_KEY,
        .parameter={.key = KC_NO}
};

action_t action_trans = {
        .state_machine=STATE_MACHINE_BASIC,
        .id=TYPE_TRANSPARENT,
};

// -------- TYPE_KEY --------
STATE_BASIC_FUNC_DEF(TYPE_KEY, IDLE, TAP) {
    report_add_keycode(action->parameter.key.keycode);
}

STATE_BASIC_FUNC_DEF(TYPE_KEY, TAP, IDLE) {
    report_remove_keycode(action->parameter.key.keycode);
}

// -------- TYPE_MODIFIER --------
STATE_BASIC_FUNC_DEF(TYPE_MODIFIER, IDLE, TAP) {
    report_add_keycode(action->parameter.key.keycode);
    report_add_modifiers(action->parameter.key.modifiers);
}

STATE_BASIC_FUNC_DEF(TYPE_MODIFIER, TAP, IDLE) {
    report_remove_keycode(action->parameter.key.keycode);
    report_remove_modifiers(action->parameter.key.modifiers);
}

// -------- TYPE_TRANSPARENT --------
STATE_BASIC_FUNC_DEF(TYPE_TRANSPARENT, IDLE, TAP) {
}

STATE_BASIC_FUNC_DEF(TYPE_TRANSPARENT, TAP, IDLE) {
}

// -------- TYPE_MOMENTARY_LAYER --------
STATE_BASIC_FUNC_DEF(TYPE_MOMENTARY_LAYER, IDLE, TAP) {
    uint8_t queue_index = keyboard_momentary_layer_queue_insert(action->parameter.layer.id);
    if (queue_index != MOMENTARY_LAYER_QUEUE_INDEX_INVALID) {
        key_state->extras.momentary_layer.layer_queue_index = queue_index;
    }
}

STATE_BASIC_FUNC_DEF(TYPE_MOMENTARY_LAYER, TAP, IDLE) {
    keyboard_momentary_layer_queue_remove(key_state->extras.momentary_layer.layer_queue_index);
}

// -------- TYPE_TOGGLE_LAYER --------
STATE_BASIC_FUNC_DEF(TYPE_TOGGLE_LAYER, IDLE, TAP) {
    uint8_t mask = (1 << action->parameter.layer.id);
    if (*keyboard_get_toggled_layers_mask() & mask) {
        *keyboard_get_toggled_layers_mask() &= ~mask;
    } else {
        *keyboard_get_toggled_layers_mask() |= mask;
    }
}

STATE_BASIC_FUNC_DEF(TYPE_TOGGLE_LAYER, TAP, IDLE) {
}

// -------- TYPE_BOTTOM_LAYER --------
STATE_BASIC_FUNC_DEF(TYPE_BOTTOM_LAYER, IDLE, TAP) {
    keyboard_set_bottom_layer(action->parameter.layer.id);
}

STATE_BASIC_FUNC_DEF(TYPE_BOTTOM_LAYER, TAP, IDLE) {
}

// -------- TYPE_MACRO --------
STATE_BASIC_FUNC_DEF(TYPE_MACRO, IDLE, TAP) {
}

STATE_BASIC_FUNC_DEF(TYPE_MACRO, TAP, IDLE) {
}

// -------- TYPE_CUSTOM --------
STATE_BASIC_FUNC_DEF(TYPE_CUSTOM, IDLE, TAP) {
    if (action->parameter.custom.keycode == TAKO_BOOTLOADER) {
        takokb_reboot_to_bootloader();
    } else if (action->parameter.custom.keycode == TAKO_SYSTEM_RESET) {
        takokb_system_reset();
    }
}

STATE_BASIC_FUNC_DEF(TYPE_CUSTOM, TAP, IDLE) {
}


// ================================================================================

// -------- TYPE_MOMENTARY_LAYER_KEY --------
STATE_TAP_HOLD_FUNC_DEF(TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER, IDLE, TAP) {
    // Acquire momentary layer
    uint8_t queue_index = keyboard_momentary_layer_queue_insert(action->parameter.tap_key_hold_layer.layer_id);
    if (queue_index != MOMENTARY_LAYER_QUEUE_INDEX_INVALID) {
        key_state->extras.tap_key_hold_layer.layer_queue_index = queue_index;
    }
}

STATE_TAP_HOLD_FUNC_DEF(TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER, TAP, HOLD) {
    // Do nothing
}

STATE_TAP_HOLD_FUNC_DEF(TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER, HOLD, IDLE) {
    // Release momentary layer
    keyboard_momentary_layer_queue_remove(key_state->extras.tap_key_hold_layer.layer_queue_index);
}

STATE_TAP_HOLD_FUNC_DEF(TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER, TAP, WAIT_FOR_RELEASE_INTERNAL) {
    // Press keycode & modifiers
    report_add_keycode(action->parameter.tap_key_hold_layer.keycode);
    report_add_modifiers(action->parameter.tap_key_hold_layer.modifiers);

    // Release momentary layer
    keyboard_momentary_layer_queue_remove(key_state->extras.tap_key_hold_layer.layer_queue_index);
}

STATE_TAP_HOLD_FUNC_DEF(TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER, WAIT_FOR_RELEASE_INTERNAL, TAP_HOLD) {
    // Release keycode & modifiers
    report_remove_keycode(action->parameter.tap_key_hold_layer.keycode);
    report_remove_modifiers(action->parameter.tap_key_hold_layer.modifiers);
}

STATE_TAP_HOLD_FUNC_DEF(TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER, WAIT_FOR_RELEASE_INTERNAL, HOLD_WAIT_FOR_HOLD) {
    // Release keycode & modifiers
    report_remove_keycode(action->parameter.tap_key_hold_layer.keycode);
    report_remove_modifiers(action->parameter.tap_key_hold_layer.modifiers);
}

STATE_TAP_HOLD_FUNC_DEF(TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER, WAIT_FOR_TAP_HOLD, IDLE) {
    // Do nothing
}

STATE_TAP_HOLD_FUNC_DEF(TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER, WAIT_FOR_TAP_HOLD, TAP_HOLD) {
    // Press keycode & modifiers
    report_add_keycode(action->parameter.tap_key_hold_layer.keycode);
    report_add_modifiers(action->parameter.tap_key_hold_layer.modifiers);
}

STATE_TAP_HOLD_FUNC_DEF(TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER, TAP_HOLD, IDLE) {
    // Release keycode & modifiers
    report_remove_keycode(action->parameter.tap_key_hold_layer.keycode);
    report_remove_modifiers(action->parameter.tap_key_hold_layer.modifiers);
}
