#include "takokb_action.h"
#include "keyboard.h"
#include "report.h"
#include "action.h"

action_t action_no = {
        .state_machine=STATE_MACHINE_BASIC,
        .type=TYPE_KEY,
        .parameter={.key = KEY_NONE}
};

action_t action_trans = {
        .state_machine=STATE_MACHINE_BASIC,
        .type=TYPE_TRANSPARENT,
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

// -------- TYPE_TAKOKB --------
STATE_BASIC_FUNC_DEF(TYPE_TAKOKB, IDLE, TAP) {
    switch (action->parameter.custom.keycode) {
        case TAKO_BOOTLOADER:
            takokb_reboot_to_bootloader();
            break;
        case TAKO_SYSTEM_RESET:
            takokb_system_reset();
            break;
        case TAKO_NONE:
        default:
            break;
    }
}

STATE_BASIC_FUNC_DEF(TYPE_TAKOKB, TAP, IDLE) {
}

// -------- TYPE_PROFILE --------
STATE_BASIC_FUNC_DEF(TYPE_PROFILE, IDLE, TAP) {
}

STATE_BASIC_FUNC_DEF(TYPE_PROFILE, TAP, IDLE) {
    keyboard_schedule_switch_profile(action->parameter.profile.profile);
}

// -------- TYPE_USAGE_CONSUMER --------
STATE_BASIC_FUNC_DEF(TYPE_USAGE_CONSUMER, IDLE, TAP) {
    report_consumer_set(action->parameter.consumer.usage | action->parameter.consumer.usage2 << 8);
}

STATE_BASIC_FUNC_DEF(TYPE_USAGE_CONSUMER, TAP, IDLE) {
    report_consumer_set(0);
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
