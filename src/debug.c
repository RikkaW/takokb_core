#include "takokb.h"
#include "debug.h"
#include "keymap.h"

#ifndef NDEBUG

const char *takokb_debug_modifier_bit_to_name(enum mods_bit bit) {
    switch (bit) {
        case MOD_LSFT:
            return "MOD_LSFT";
        case MOD_RSFT:
            return "MOD_RSFT";
        case MOD_LCTL:
            return "MOD_LCTL";
        case MOD_RCTL:
            return "MOD_RCTL";
        case MOD_LALT:
            return "MOD_LALT";
        case MOD_RALT:
            return "MOD_RALT";
        case MOD_LGUI:
            return "MOD_LGUI";
        case MOD_RGUI:
            return "MOD_RGUI";
        default:
            return "MOD_NONE";
    }
}

void takokb_debug_print_action(action_t *action) {
    switch (action->state_machine) {
        case STATE_MACHINE_BASIC: {
            switch (action->type) {
                case TYPE_KEY: {
                    takokb_debug_printf("TYPE_NORMAL_KEY (%s)",
                                        takokb_debug_keycode_to_name(action->parameter.key.keycode));
                    break;
                }
                case TYPE_MODIFIER: {
                    takokb_debug_printf("TYPE_MODIFIER (%s, ",
                                        takokb_debug_keycode_to_name(action->parameter.key.keycode));
                    for (int i = 0; i < 8; ++i) {
                        if (action->parameter.key.modifiers & (1 << i)) {
                            takokb_debug_printf("%s", takokb_debug_modifier_bit_to_name(1 << i));
                        }
                    }
                    takokb_debug_printf(")");
                    break;
                }
                case TYPE_TRANSPARENT: {
                    takokb_debug_printf("TYPE_TRANSPARENT");
                    break;
                }
                case TYPE_MOMENTARY_LAYER: {
                    takokb_debug_printf("TYPE_MOMENTARY_LAYER %d",
                                        action->parameter.layer.id);
                    break;
                }
                case TYPE_TOGGLE_LAYER: {
                    takokb_debug_printf("TYPE_TOGGLE_LAYER %d",
                                        action->parameter.layer.id);
                    break;
                }
                case TYPE_BOTTOM_LAYER: {
                    takokb_debug_printf("TYPE_BOTTOM_LAYER %d",
                                        action->parameter.layer.id);
                    break;
                }
                case TYPE_TAKOKB: {
                    takokb_debug_printf("TYPE_TAKOKB %d",
                                        action->parameter.custom.keycode);
                    break;
                }
                case TYPE_PROFILE: {
                    takokb_debug_printf("TYPE_PROFILE %d",
                                        action->parameter.profile.profile);
                    break;
                }
                case TYPE_USAGE_CONSUMER: {
                    takokb_debug_printf("TYPE_USAGE_CONSUMER 0x%x",
                                        action->parameter.consumer.usage | action->parameter.consumer.usage2 << 8);
                    break;
                }
                default:
                    takokb_debug_printf("(unknown action type)");
                    break;
            }
            break;
        }
        case STATE_MACHINE_TAP_HOLD: {
            switch (action->type) {
                case TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER:
                    takokb_debug_printf("TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER (%d, %s, ",
                                        action->parameter.layer.id,
                                        takokb_debug_keycode_to_name(action->parameter.tap_key_hold_layer.keycode),
                                        takokb_debug_modifier_bit_to_name(
                                                action->parameter.tap_key_hold_layer.modifiers));
                    for (int i = 0; i < 8; ++i) {
                        if (action->parameter.tap_key_hold_layer.modifiers & (1 << i)) {
                            takokb_debug_printf("%s", takokb_debug_modifier_bit_to_name(1 << i));
                        }
                    }
                    takokb_debug_printf(")");
                    break;
                default:
                    takokb_debug_printf("(unknown action type)");
                    break;
            }
            break;
        }
        default:
            takokb_debug_printf("(unknown state machine type %d)", action->state_machine);
            break;
    }
}

void takokb_debug_print_keymap(void) {
    for (uint8_t profile = 0; profile < TAKOKB_MAX_PROFILES; ++profile) {
        takokb_debug_printf("keymaps profile %d:\n", profile);

        for (uint8_t layer = 0; layer < TAKOKB_MAX_LAYERS; ++layer) {
            for (uint8_t row = 0; row < TAKOKB_MATRIX_ROWS; ++row) {
                for (uint8_t colum = 0; colum < TAKOKB_MATRIX_COLS; ++colum) {
                    action_t *action = &takokb_get_keyboard_configuration()->keymaps[profile][layer][row][colum];
                    takokb_debug_printf("keymaps[%d][%d][%d] = ", layer, row, colum);
                    takokb_debug_print_action(action);
                    takokb_debug_printf("\n");
                }
            }
        }
    }
}

const char *takokb_debug_keycode_to_name(enum keycodes keycode) {
    switch (keycode) {
        case KEY_NONE:
            return "KEY_NO";
        case KEY_A:
            return "KEY_A";
        case KEY_B:
            return "KEY_B";
        case KEY_C:
            return "KEY_C";
        case KEY_D:
            return "KEY_D";
        case KEY_E:
            return "KEY_E";
        case KEY_F:
            return "KEY_F";
        case KEY_G:
            return "KEY_G";
        case KEY_H:
            return "KEY_H";
        case KEY_I:
            return "KEY_I";
        case KEY_J:
            return "KEY_J";
        case KEY_K:
            return "KEY_K";
        case KEY_L:
            return "KEY_L";
        case KEY_M:
            return "KEY_M";
        case KEY_N:
            return "KEY_N";
        case KEY_O:
            return "KEY_O";
        case KEY_P:
            return "KEY_P";
        case KEY_Q:
            return "KEY_Q";
        case KEY_R:
            return "KEY_R";
        case KEY_S:
            return "KEY_S";
        case KEY_T:
            return "KEY_T";
        case KEY_U:
            return "KEY_U";
        case KEY_V:
            return "KEY_V";
        case KEY_W:
            return "KEY_W";
        case KEY_X:
            return "KEY_X";
        case KEY_Y:
            return "KEY_Y";
        case KEY_Z:
            return "KEY_Z";
        case KEY_1:
            return "KEY_1";
        case KEY_2:
            return "KEY_2";
        case KEY_3:
            return "KEY_3";
        case KEY_4:
            return "KEY_4";
        case KEY_5:
            return "KEY_5";
        case KEY_6:
            return "KEY_6";
        case KEY_7:
            return "KEY_7";
        case KEY_8:
            return "KEY_8";
        case KEY_9:
            return "KEY_9";
        case KEY_0:
            return "KEY_0";
        case KEY_ENTER:
            return "KEY_ENTER";
        case KEY_ESC:
            return "KEY_ESC";
        case KEY_BACKSPACE:
            return "KEY_BACKSPACE";
        case KEY_TAB:
            return "KEY_TAB";
        case KEY_SPACE:
            return "KEY_SPACE";
        case KEY_MINUS:
            return "KEY_MINUS";
        case KEY_EQUAL:
            return "KEY_EQUAL";
        case KEY_LEFT_BRACKET:
            return "KEY_LEFTBRACE";
        case KEY_RIGHT_BRACKET:
            return "KEY_RIGHTBRACE";
        case KEY_BACKSLASH:
            return "KEY_BACKSLASH";
        case KEY_NONUS_HASH:
            return "KEY_HASHTILDE";
        case KEY_SEMICOLON:
            return "KEY_SEMICOLON";
        case KEY_QUOTE:
            return "KEY_APOSTROPHE";
        case KEY_GRAVE:
            return "KEY_GRAVE";
        case KEY_COMMA:
            return "KEY_COMMA";
        case KEY_DOT:
            return "KEY_DOT";
        case KEY_SLASH:
            return "KEY_SLASH";
        case KEY_CAPSLOCK:
            return "KEY_CAPS_LOCK";
        case KEY_F1:
            return "KEY_F1";
        case KEY_F2:
            return "KEY_F2";
        case KEY_F3:
            return "KEY_F3";
        case KEY_F4:
            return "KEY_F4";
        case KEY_F5:
            return "KEY_F5";
        case KEY_F6:
            return "KEY_F6";
        case KEY_F7:
            return "KEY_F7";
        case KEY_F8:
            return "KEY_F8";
        case KEY_F9:
            return "KEY_F9";
        case KEY_F10:
            return "KEY_F10";
        case KEY_F11:
            return "KEY_F11";
        case KEY_F12:
            return "KEY_F12";
        case KEY_PRINT_SCREEN:
            return "KEY_PRINT_SCREEN";
        case KEY_SCROLL_LOCK:
            return "KEY_SCROLL_LOCK";
        case KEY_PAUSE:
            return "KEY_PAUSE";
        case KEY_INSERT:
            return "KEY_INSERT";
        case KEY_HOME:
            return "KEY_HOME";
        case KEY_PAGE_UP:
            return "KEY_PAGE_UP";
        case KEY_DELETE:
            return "KEY_DELETE";
        case KEY_END:
            return "KEY_END";
        case KEY_PAGE_DOWN:
            return "KEY_PAGE_DOWN";
        case KEY_RIGHT:
            return "KEY_RIGHT";
        case KEY_LEFT:
            return "KEY_LEFT";
        case KEY_DOWN:
            return "KEY_DOWN";
        case KEY_UP:
            return "KEY_UP";
        case KEY_NUMLOCK:
            return "KEY_NUMLOCK";
        case KEY_KP_SLASH:
            return "KEY_KP_SLASH";
        case KEY_KP_ASTERISK:
            return "KEY_KP_ASTERISK";
        case KEY_KP_MINUS:
            return "KEY_KP_MINUS";
        case KEY_KP_PLUS:
            return "KEY_KP_PLUS";
        case KEY_KP_ENTER:
            return "KEY_KP_ENTER";
        case KEY_KP_1:
            return "KEY_KP1";
        case KEY_KP_2:
            return "KEY_KP2";
        case KEY_KP_3:
            return "KEY_KP3";
        case KEY_KP_4:
            return "KEY_KP4";
        case KEY_KP_5:
            return "KEY_KP5";
        case KEY_KP_6:
            return "KEY_KP6";
        case KEY_KP_7:
            return "KEY_KP7";
        case KEY_KP_8:
            return "KEY_KP8";
        case KEY_KP_9:
            return "KEY_KP9";
        case KEY_KP_0:
            return "KEY_KP0";
        case KEY_KP_DOT:
            return "KEY_KP_DOT";
        case KEY_NONUS_BACKSLASH:
            return "KEY_NONUS_BACKSLASH";
        case KEY_APPLICATION:
            return "KEY_APPLICATION";
        case KEY_POWER:
            return "KEY_POWER";
        case KEY_KP_EQUAL:
            return "KEY_KP_EQUAL";
        case KEY_F13:
            return "KEY_F13";
        case KEY_F14:
            return "KEY_F14";
        case KEY_F15:
            return "KEY_F15";
        case KEY_F16:
            return "KEY_F16";
        case KEY_F17:
            return "KEY_F17";
        case KEY_F18:
            return "KEY_F18";
        case KEY_F19:
            return "KEY_F19";
        case KEY_F20:
            return "KEY_F20";
        case KEY_F21:
            return "KEY_F21";
        case KEY_F22:
            return "KEY_F22";
        case KEY_F23:
            return "KEY_F23";
        case KEY_F24:
            return "KEY_F24";
        case KEY_EXECUTE:
            return "KEY_OPEN";
        case KEY_HELP:
            return "KEY_HELP";
        case KEY_MENU:
            return "KEY_PROPS";
        case KEY_SELECT:
            return "KEY_FRONT";
        case KEY_STOP:
            return "KEY_STOP";
        case KEY_AGAIN:
            return "KEY_AGAIN";
        case KEY_UNDO:
            return "KEY_UNDO";
        case KEY_CUT:
            return "KEY_CUT";
        case KEY_COPY:
            return "KEY_COPY";
        case KEY_PASTE:
            return "KEY_PASTE";
        case KEY_FIND:
            return "KEY_FIND";
        case KEY_MUTE:
            return "KEY_MUTE";
        case KEY_VOLUME_UP:
            return "KEY_VOLUME_UP";
        case KEY_VOLUME_DOWN:
            return "KEY_VOLUME_DOWN";
        case KEY_KP_COMMA:
            return "KEY_KP_COMMA";
        case KEY_RO:
            return "KEY_RO";
        case KEY_KATAKANAHIRAGANA:
            return "KEY_KATAKANAHIRAGANA";
        case KEY_YEN:
            return "KEY_YEN";
        case KEY_HENKAN:
            return "KEY_HENKAN";
        case KEY_MUHENKAN:
            return "KEY_MUHENKAN";
        case KEY_KPJPCOMMA:
            return "KEY_KPJPCOMMA";
        case KEY_HANGEUL:
            return "KEY_HANGEUL";
        case KEY_HANJA:
            return "KEY_HANJA";
        case KEY_KATAKANA:
            return "KEY_KATAKANA";
        case KEY_HIRAGANA:
            return "KEY_HIRAGANA";
        case KEY_ZENKAKUHANKAKU:
            return "KEY_ZENKAKUHANKAKU";
        case KEY_KP_LEFT_PAREN:
            return "KEY_KPLEFTPAREN";
        case KEY_KP_RIGHT_PAREN:
            return "KEY_KPRIGHTPAREN";
        case KEY_LEFT_CTRL:
            return "KEY_LEFTCTRL";
        case KEY_LEFT_SHIFT:
            return "KEY_LEFTSHIFT";
        case KEY_LEFT_ALT:
            return "KEY_LEFTALT";
        case KEY_LEFT_GUI:
            return "KEY_LEFTMETA";
        case KEY_RIGHT_CTRL:
            return "KEY_RIGHTCTRL";
        case KEY_RIGHT_SHIFT:
            return "KEY_RIGHTSHIFT";
        case KEY_RIGHT_ALT:
            return "KEY_RIGHTALT";
        case KEY_RIGHT_GUI:
            return "KEY_RIGHTMETA";
        default:
            return "(keycode unnamed)";
    }
}

#endif
