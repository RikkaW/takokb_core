#ifndef TAKOKB_TAKOKB_ACTION_H
#define TAKOKB_TAKOKB_ACTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "takokb.h"

enum types {

    /**
     * Normal keycode.
     *
     * Parameter: keycode (8) */
    TYPE_NORMAL_KEY = 0x00,

    /**
     * Modifier + normal keycode
     *
     * Parameter: mod_bits (8), keycode (8) */
    TYPE_MODIFIER = 0x01,

    /**
     * Find action from a lower layer.
     *
     * Parameter: (none)
     * */
    TYPE_TRANSPARENT = 0x02,

    /**
     * Momentary turn a layer on, momentary layers has higher priority than TYPE_TOGGLE_LAYER.
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

enum mods_bit {
    MOD_LCTL = 1,
    MOD_LSFT = 1 << 1,
    MOD_LALT = 1 << 2,
    MOD_LGUI = 1 << 3,
    MOD_RCTL = 1 << 4,
    MOD_RSFT = 1 << 5,
    MOD_RALT = 1 << 6,
    MOD_RGUI = 1 << 7,
};

enum keycodes {
    KC_NO = 0x0000,
    KC_A = 0x0004,
    KC_B = 0x0005,
    KC_C = 0x0006,
    KC_D = 0x0007,
    KC_E = 0x0008,
    KC_F = 0x0009,
    KC_G = 0x000A,
    KC_H = 0x000B,
    KC_I = 0x000C,
    KC_J = 0x000D,
    KC_K = 0x000E,
    KC_L = 0x000F,
    KC_M = 0x0010,
    KC_N = 0x0011,
    KC_O = 0x0012,
    KC_P = 0x0013,
    KC_Q = 0x0014,
    KC_R = 0x0015,
    KC_S = 0x0016,
    KC_T = 0x0017,
    KC_U = 0x0018,
    KC_V = 0x0019,
    KC_W = 0x001A,
    KC_X = 0x001B,
    KC_Y = 0x001C,
    KC_Z = 0x001D,
    KC_1 = 0x001E,
    KC_2 = 0x001F,
    KC_3 = 0x0020,
    KC_4 = 0x0021,
    KC_5 = 0x0022,
    KC_6 = 0x0023,
    KC_7 = 0x0024,
    KC_8 = 0x0025,
    KC_9 = 0x0026,
    KC_0 = 0x0027,
    KC_ENTER = 0x0028,
    KC_ESCAPE = 0x0029,
    KC_BACKSPACE = 0x002A,
    KC_TAB = 0x002B,
    KC_SPACE = 0x002C,
    KC_MINUS = 0x002D,
    KC_EQUAL = 0x002E,
    KC_LEFT_BRACKET = 0x002F,
    KC_RIGHT_BRACKET = 0x0030,
    KC_BACKSLASH = 0x0031,
    KC_NONUS_HASH = 0x0032,
    KC_SEMICOLON = 0x0033,
    KC_QUOTE = 0x0034,
    KC_GRAVE = 0x0035,
    KC_COMMA = 0x0036,
    KC_DOT = 0x0037,
    KC_SLASH = 0x0038,
    KC_CAPS_LOCK = 0x0039,
    KC_F1 = 0x003A,
    KC_F2 = 0x003B,
    KC_F3 = 0x003C,
    KC_F4 = 0x003D,
    KC_F5 = 0x003E,
    KC_F6 = 0x003F,
    KC_F7 = 0x0040,
    KC_F8 = 0x0041,
    KC_F9 = 0x0042,
    KC_F10 = 0x0043,
    KC_F11 = 0x0044,
    KC_F12 = 0x0045,
    KC_PRINT_SCREEN = 0x0046,
    KC_SCROLL_LOCK = 0x0047,
    KC_PAUSE = 0x0048,
    KC_INSERT = 0x0049,
    KC_HOME = 0x004A,
    KC_PAGE_UP = 0x004B,
    KC_DELETE = 0x004C,
    KC_END = 0x004D,
    KC_PAGE_DOWN = 0x004E,
    KC_RIGHT = 0x004F,
    KC_LEFT = 0x0050,
    KC_DOWN = 0x0051,
    KC_UP = 0x0052,
    KC_NUM_LOCK = 0x0053,
    KC_KP_SLASH = 0x0054,
    KC_KP_ASTERISK = 0x0055,
    KC_KP_MINUS = 0x0056,
    KC_KP_PLUS = 0x0057,
    KC_KP_ENTER = 0x0058,
    KC_KP_1 = 0x0059,
    KC_KP_2 = 0x005A,
    KC_KP_3 = 0x005B,
    KC_KP_4 = 0x005C,
    KC_KP_5 = 0x005D,
    KC_KP_6 = 0x005E,
    KC_KP_7 = 0x005F,
    KC_KP_8 = 0x0060,
    KC_KP_9 = 0x0061,
    KC_KP_0 = 0x0062,
    KC_KP_DOT = 0x0063,
    KC_NONUS_BACKSLASH = 0x0064,
    KC_APPLICATION = 0x0065,
    KC_KB_POWER = 0x0066,
    KC_KP_EQUAL = 0x0067,
    KC_F13 = 0x0068,
    KC_F14 = 0x0069,
    KC_F15 = 0x006A,
    KC_F16 = 0x006B,
    KC_F17 = 0x006C,
    KC_F18 = 0x006D,
    KC_F19 = 0x006E,
    KC_F20 = 0x006F,
    KC_F21 = 0x0070,
    KC_F22 = 0x0071,
    KC_F23 = 0x0072,
    KC_F24 = 0x0073,
    KC_EXECUTE = 0x0074,
    KC_HELP = 0x0075,
    KC_MENU = 0x0076,
    KC_SELECT = 0x0077,
    KC_STOP = 0x0078,
    KC_AGAIN = 0x0079,
    KC_UNDO = 0x007A,
    KC_CUT = 0x007B,
    KC_COPY = 0x007C,
    KC_PASTE = 0x007D,
    KC_FIND = 0x007E,
    KC_KB_MUTE = 0x007F,
    KC_KB_VOLUME_UP = 0x0080,
    KC_KB_VOLUME_DOWN = 0x0081,
    KC_LOCKING_CAPS_LOCK = 0x0082,
    KC_LOCKING_NUM_LOCK = 0x0083,
    KC_LOCKING_SCROLL_LOCK = 0x0084,
    KC_KP_COMMA = 0x0085,
    KC_KP_EQUAL_AS400 = 0x0086,
    KC_INTERNATIONAL_1 = 0x0087,
    KC_INTERNATIONAL_2 = 0x0088,
    KC_INTERNATIONAL_3 = 0x0089,
    KC_INTERNATIONAL_4 = 0x008A,
    KC_INTERNATIONAL_5 = 0x008B,
    KC_INTERNATIONAL_6 = 0x008C,
    KC_INTERNATIONAL_7 = 0x008D,
    KC_INTERNATIONAL_8 = 0x008E,
    KC_INTERNATIONAL_9 = 0x008F,
    KC_LANGUAGE_1 = 0x0090,
    KC_LANGUAGE_2 = 0x0091,
    KC_LANGUAGE_3 = 0x0092,
    KC_LANGUAGE_4 = 0x0093,
    KC_LANGUAGE_5 = 0x0094,
    KC_LANGUAGE_6 = 0x0095,
    KC_LANGUAGE_7 = 0x0096,
    KC_LANGUAGE_8 = 0x0097,
    KC_LANGUAGE_9 = 0x0098,
    KC_ALTERNATE_ERASE = 0x0099,
    KC_SYSTEM_REQUEST = 0x009A,
    KC_CANCEL = 0x009B,
    KC_CLEAR = 0x009C,
    KC_PRIOR = 0x009D,
    KC_RETURN = 0x009E,
    KC_SEPARATOR = 0x009F,
    KC_OUT = 0x00A0,
    KC_OPER = 0x00A1,
    KC_CLEAR_AGAIN = 0x00A2,
    KC_CRSEL = 0x00A3,
    KC_EXSEL = 0x00A4,
    KC_SYSTEM_POWER = 0x00A5,
    KC_SYSTEM_SLEEP = 0x00A6,
    KC_SYSTEM_WAKE = 0x00A7,
    KC_AUDIO_MUTE = 0x00A8,
    KC_AUDIO_VOL_UP = 0x00A9,
    KC_AUDIO_VOL_DOWN = 0x00AA,
    KC_MEDIA_NEXT_TRACK = 0x00AB,
    KC_MEDIA_PREV_TRACK = 0x00AC,
    KC_MEDIA_STOP = 0x00AD,
    KC_MEDIA_PLAY_PAUSE = 0x00AE,
    KC_MEDIA_SELECT = 0x00AF,
    KC_MEDIA_EJECT = 0x00B0,
    KC_MAIL = 0x00B1,
    KC_CALCULATOR = 0x00B2,
    KC_MY_COMPUTER = 0x00B3,
    KC_WWW_SEARCH = 0x00B4,
    KC_WWW_HOME = 0x00B5,
    KC_WWW_BACK = 0x00B6,
    KC_WWW_FORWARD = 0x00B7,
    KC_WWW_STOP = 0x00B8,
    KC_WWW_REFRESH = 0x00B9,
    KC_WWW_FAVORITES = 0x00BA,
    KC_MEDIA_FAST_FORWARD = 0x00BB,
    KC_MEDIA_REWIND = 0x00BC,
    KC_BRIGHTNESS_UP = 0x00BD,
    KC_BRIGHTNESS_DOWN = 0x00BE,
    KC_CONTROL_PANEL = 0x00BF,
    KC_ASSISTANT = 0x00C0,
    KC_MISSION_CONTROL = 0x00C1,
    KC_LAUNCHPAD = 0x00C2,
    KC_MS_UP = 0x00CD,
    KC_MS_DOWN = 0x00CE,
    KC_MS_LEFT = 0x00CF,
    KC_MS_RIGHT = 0x00D0,
    KC_MS_BTN1 = 0x00D1,
    KC_MS_BTN2 = 0x00D2,
    KC_MS_BTN3 = 0x00D3,
    KC_MS_BTN4 = 0x00D4,
    KC_MS_BTN5 = 0x00D5,
    KC_MS_BTN6 = 0x00D6,
    KC_MS_BTN7 = 0x00D7,
    KC_MS_BTN8 = 0x00D8,
    KC_MS_WH_UP = 0x00D9,
    KC_MS_WH_DOWN = 0x00DA,
    KC_MS_WH_LEFT = 0x00DB,
    KC_MS_WH_RIGHT = 0x00DC,
    KC_MS_ACCEL0 = 0x00DD,
    KC_MS_ACCEL1 = 0x00DE,
    KC_MS_ACCEL2 = 0x00DF,
    KC_LEFT_CTRL = 0x00E0,
    KC_LEFT_SHIFT = 0x00E1,
    KC_LEFT_ALT = 0x00E2,
    KC_LEFT_GUI = 0x00E3,
    KC_RIGHT_CTRL = 0x00E4,
    KC_RIGHT_SHIFT = 0x00E5,
    KC_RIGHT_ALT = 0x00E6,
    KC_RIGHT_GUI = 0x00E7,
};

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_TAKOKB_ACTION_H
