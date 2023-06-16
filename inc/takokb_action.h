#ifndef TAKOKB_PUBLIC_ACTION_H
#define TAKOKB_PUBLIC_ACTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define STATE_MACHINE_BASIC 0x00
#define STATE_MACHINE_TAP_HOLD 0x01

enum __attribute__((packed)) basic_types {

    /**
     * Send a keyboard HID keycode.
     *
     * Parameter: keycode (8) */
    TYPE_KEY = 0x00,

    /**
     * Modifier, with keycode.
     *
     * Parameter: mod_bits (8), keycode (8) */
    TYPE_MODIFIER = 0x01,

    /**
     * Find action from a lower layer, this is to make keymap clean.
     *
     * Parameter: (none)
     * */
    TYPE_TRANSPARENT = 0x02,

    /**
     * Turn a layer on if the key is pressed, off when released.
     * This has higher priority than TYPE_TOGGLE_LAYER. For example, even a higher level layer is on, keys are found
     * from the layer that is turned on by this action.
     *
     * Parameter: layer # (8) */
    TYPE_MOMENTARY_LAYER = 0x03,

    /**
     * Permanently turn a layer on or off.
     *
     * Parameter: layer # (8) */
    TYPE_TOGGLE_LAYER = 0x04,

    /**
     * Set the bottom layer, the bottom layer is always on.
     * Action is found from the top layer that is on to the bottom layer.
     *
     * Parameter: layer # (8) */
    TYPE_BOTTOM_LAYER = 0x05,

    /**
     * Send a pre-defined Macro.
     *
     * Parameter: macro # (8) */
    TYPE_MACRO = 0x06,

    /* Custom function. (TBD)
     *
     * Parameter: TBD */
    TYPE_CUSTOM = 0x07,
};

enum __attribute__((packed)) tap_hold_types {

    /**
     * Momentary turn a layer, send normal key if the key is released in 200ms.
     * Modifiers are also supported.
     *
     * Parameter: layer # (8), keycode (8), mod_bits (8) */
    TYPE_TAP_KEY_HOLD_MOMENTARY_LAYER = 0x00,
};

enum __attribute__((packed)) mods_bit {
    MOD_LCTL = 1,
    MOD_LSFT = 1 << 1,
    MOD_LALT = 1 << 2,
    MOD_LGUI = 1 << 3,
    MOD_RCTL = 1 << 4,
    MOD_RSFT = 1 << 5,
    MOD_RALT = 1 << 6,
    MOD_RGUI = 1 << 7,
};

enum __attribute__((packed)) keycodes {
    KC_NO = 0x00,
    KC_A = 0x04,
    KC_B = 0x05,
    KC_C = 0x06,
    KC_D = 0x07,
    KC_E = 0x08,
    KC_F = 0x09,
    KC_G = 0x0A,
    KC_H = 0x0B,
    KC_I = 0x0C,
    KC_J = 0x0D,
    KC_K = 0x0E,
    KC_L = 0x0F,
    KC_M = 0x10,
    KC_N = 0x11,
    KC_O = 0x12,
    KC_P = 0x13,
    KC_Q = 0x14,
    KC_R = 0x15,
    KC_S = 0x16,
    KC_T = 0x17,
    KC_U = 0x18,
    KC_V = 0x19,
    KC_W = 0x1A,
    KC_X = 0x1B,
    KC_Y = 0x1C,
    KC_Z = 0x1D,
    KC_1 = 0x1E,
    KC_2 = 0x1F,
    KC_3 = 0x20,
    KC_4 = 0x21,
    KC_5 = 0x22,
    KC_6 = 0x23,
    KC_7 = 0x24,
    KC_8 = 0x25,
    KC_9 = 0x26,
    KC_0 = 0x27,
    KC_ENTER = 0x28,
    KC_ESCAPE = 0x29,
    KC_BACKSPACE = 0x2A,
    KC_TAB = 0x2B,
    KC_SPACE = 0x2C,
    KC_MINUS = 0x2D,
    KC_EQUAL = 0x2E,
    KC_LEFT_BRACKET = 0x2F,
    KC_RIGHT_BRACKET = 0x30,
    KC_BACKSLASH = 0x31,
    KC_NONUS_HASH = 0x32,
    KC_SEMICOLON = 0x33,
    KC_QUOTE = 0x34,
    KC_GRAVE = 0x35,
    KC_COMMA = 0x36,
    KC_DOT = 0x37,
    KC_SLASH = 0x38,
    KC_CAPS_LOCK = 0x39,
    KC_F1 = 0x3A,
    KC_F2 = 0x3B,
    KC_F3 = 0x3C,
    KC_F4 = 0x3D,
    KC_F5 = 0x3E,
    KC_F6 = 0x3F,
    KC_F7 = 0x40,
    KC_F8 = 0x41,
    KC_F9 = 0x42,
    KC_F10 = 0x43,
    KC_F11 = 0x44,
    KC_F12 = 0x45,
    KC_PRINT_SCREEN = 0x46,
    KC_SCROLL_LOCK = 0x47,
    KC_PAUSE = 0x48,
    KC_INSERT = 0x49,
    KC_HOME = 0x4A,
    KC_PAGE_UP = 0x4B,
    KC_DELETE = 0x4C,
    KC_END = 0x4D,
    KC_PAGE_DOWN = 0x4E,
    KC_RIGHT = 0x4F,
    KC_LEFT = 0x50,
    KC_DOWN = 0x51,
    KC_UP = 0x52,
    KC_NUM_LOCK = 0x53,
    KC_KP_SLASH = 0x54,
    KC_KP_ASTERISK = 0x55,
    KC_KP_MINUS = 0x56,
    KC_KP_PLUS = 0x57,
    KC_KP_ENTER = 0x58,
    KC_KP_1 = 0x59,
    KC_KP_2 = 0x5A,
    KC_KP_3 = 0x5B,
    KC_KP_4 = 0x5C,
    KC_KP_5 = 0x5D,
    KC_KP_6 = 0x5E,
    KC_KP_7 = 0x5F,
    KC_KP_8 = 0x60,
    KC_KP_9 = 0x61,
    KC_KP_0 = 0x62,
    KC_KP_DOT = 0x63,
    KC_NONUS_BACKSLASH = 0x64,
    KC_APPLICATION = 0x65,
    KC_KB_POWER = 0x66,
    KC_KP_EQUAL = 0x67,
    KC_F13 = 0x68,
    KC_F14 = 0x69,
    KC_F15 = 0x6A,
    KC_F16 = 0x6B,
    KC_F17 = 0x6C,
    KC_F18 = 0x6D,
    KC_F19 = 0x6E,
    KC_F20 = 0x6F,
    KC_F21 = 0x70,
    KC_F22 = 0x71,
    KC_F23 = 0x72,
    KC_F24 = 0x73,
    KC_EXECUTE = 0x74,
    KC_HELP = 0x75,
    KC_MENU = 0x76,
    KC_SELECT = 0x77,
    KC_STOP = 0x78,
    KC_AGAIN = 0x79,
    KC_UNDO = 0x7A,
    KC_CUT = 0x7B,
    KC_COPY = 0x7C,
    KC_PASTE = 0x7D,
    KC_FIND = 0x7E,
    KC_KB_MUTE = 0x7F,
    KC_KB_VOLUME_UP = 0x80,
    KC_KB_VOLUME_DOWN = 0x81,
    KC_LOCKING_CAPS_LOCK = 0x82,
    KC_LOCKING_NUM_LOCK = 0x83,
    KC_LOCKING_SCROLL_LOCK = 0x84,
    KC_KP_COMMA = 0x85,
    KC_KP_EQUAL_AS400 = 0x86,
    KC_INTERNATIONAL_1 = 0x87,
    KC_INTERNATIONAL_2 = 0x88,
    KC_INTERNATIONAL_3 = 0x89,
    KC_INTERNATIONAL_4 = 0x8A,
    KC_INTERNATIONAL_5 = 0x8B,
    KC_INTERNATIONAL_6 = 0x8C,
    KC_INTERNATIONAL_7 = 0x8D,
    KC_INTERNATIONAL_8 = 0x8E,
    KC_INTERNATIONAL_9 = 0x8F,
    KC_LANGUAGE_1 = 0x90,
    KC_LANGUAGE_2 = 0x91,
    KC_LANGUAGE_3 = 0x92,
    KC_LANGUAGE_4 = 0x93,
    KC_LANGUAGE_5 = 0x94,
    KC_LANGUAGE_6 = 0x95,
    KC_LANGUAGE_7 = 0x96,
    KC_LANGUAGE_8 = 0x97,
    KC_LANGUAGE_9 = 0x98,
    KC_ALTERNATE_ERASE = 0x99,
    KC_SYSTEM_REQUEST = 0x9A,
    KC_CANCEL = 0x9B,
    KC_CLEAR = 0x9C,
    KC_PRIOR = 0x9D,
    KC_RETURN = 0x9E,
    KC_SEPARATOR = 0x9F,
    KC_OUT = 0xA0,
    KC_OPER = 0xA1,
    KC_CLEAR_AGAIN = 0xA2,
    KC_CRSEL = 0xA3,
    KC_EXSEL = 0xA4,
    KC_SYSTEM_POWER = 0xA5,
    KC_SYSTEM_SLEEP = 0xA6,
    KC_SYSTEM_WAKE = 0xA7,
    KC_AUDIO_MUTE = 0xA8,
    KC_AUDIO_VOL_UP = 0xA9,
    KC_AUDIO_VOL_DOWN = 0xAA,
    KC_MEDIA_NEXT_TRACK = 0xAB,
    KC_MEDIA_PREV_TRACK = 0xAC,
    KC_MEDIA_STOP = 0xAD,
    KC_MEDIA_PLAY_PAUSE = 0xAE,
    KC_MEDIA_SELECT = 0xAF,
    KC_MEDIA_EJECT = 0xB0,
    KC_MAIL = 0xB1,
    KC_CALCULATOR = 0xB2,
    KC_MY_COMPUTER = 0xB3,
    KC_WWW_SEARCH = 0xB4,
    KC_WWW_HOME = 0xB5,
    KC_WWW_BACK = 0xB6,
    KC_WWW_FORWARD = 0xB7,
    KC_WWW_STOP = 0xB8,
    KC_WWW_REFRESH = 0xB9,
    KC_WWW_FAVORITES = 0xBA,
    KC_MEDIA_FAST_FORWARD = 0xBB,
    KC_MEDIA_REWIND = 0xBC,
    KC_BRIGHTNESS_UP = 0xBD,
    KC_BRIGHTNESS_DOWN = 0xBE,
    KC_CONTROL_PANEL = 0xBF,
    KC_ASSISTANT = 0xC0,
    KC_MISSION_CONTROL = 0xC1,
    KC_LAUNCHPAD = 0xC2,
    KC_MS_UP = 0xCD,
    KC_MS_DOWN = 0xCE,
    KC_MS_LEFT = 0xCF,
    KC_MS_RIGHT = 0xD0,
    KC_MS_BTN1 = 0xD1,
    KC_MS_BTN2 = 0xD2,
    KC_MS_BTN3 = 0xD3,
    KC_MS_BTN4 = 0xD4,
    KC_MS_BTN5 = 0xD5,
    KC_MS_BTN6 = 0xD6,
    KC_MS_BTN7 = 0xD7,
    KC_MS_BTN8 = 0xD8,
    KC_MS_WH_UP = 0xD9,
    KC_MS_WH_DOWN = 0xDA,
    KC_MS_WH_LEFT = 0xDB,
    KC_MS_WH_RIGHT = 0xDC,
    KC_MS_ACCEL0 = 0xDD,
    KC_MS_ACCEL1 = 0xDE,
    KC_MS_ACCEL2 = 0xDF,
    KC_LEFT_CTRL = 0xE0,
    KC_LEFT_SHIFT = 0xE1,
    KC_LEFT_ALT = 0xE2,
    KC_LEFT_GUI = 0xE3,
    KC_RIGHT_CTRL = 0xE4,
    KC_RIGHT_SHIFT = 0xE5,
    KC_RIGHT_ALT = 0xE6,
    KC_RIGHT_GUI = 0xE7,
};

enum __attribute__((packed)) takokb_keycodes {
    TAKO_NONE = 0x00,
    TAKO_BOOTLOADER = 0x01,
    TAKO_SYSTEM_RESET = 0x02,
};

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_PUBLIC_ACTION_H
