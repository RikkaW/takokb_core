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

    /* TakoKB custom keycode.
     *
     * Parameter: keycode (8) */
    TYPE_TAKOKB = 0x07,

    /* Set current profile.
     *
     * Parameter: profile # (8) */
    TYPE_PROFILE = 0x08,

    /* User custom keycode.
     *
     * Parameter: keycode (8) */
    TYPE_USER = 0x80,
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
    MOD_NONE = 0,
    MOD_LCTL = 1,
    MOD_LSFT = 1 << 1,
    MOD_LALT = 1 << 2,
    MOD_LGUI = 1 << 3,
    MOD_RCTL = 1 << 4,
    MOD_RSFT = 1 << 5,
    MOD_RALT = 1 << 6,
    MOD_RGUI = 1 << 7,
};

/*
 * Keyboard/Keypad Page (0x07)
 **/
enum __attribute__((packed)) keycodes {
    // No key pressed
    KEY_NONE = 0x00,
    //  Keyboard Error Roll Over - used for all slots if too many keys are pressed ("Phantom key")
    KEY_ERR_OVF = 0x01,
    //=0x02, //  Keyboard POST Fail
    //=0x03, //  Keyboard Error Undefined

    // Keyboard a and A
    KEY_A = 0x04,
    // Keyboard b and B
    KEY_B = 0x05,
    // Keyboard c and C
    KEY_C = 0x06,
    // Keyboard d and D
    KEY_D = 0x07,
    // Keyboard e and E
    KEY_E = 0x08,
    // Keyboard f and F
    KEY_F = 0x09,
    // Keyboard g and G
    KEY_G = 0x0a,
    // Keyboard h and H
    KEY_H = 0x0b,
    // Keyboard i and I
    KEY_I = 0x0c,
    // Keyboard j and J
    KEY_J = 0x0d,
    // Keyboard k and K
    KEY_K = 0x0e,
    // Keyboard l and L
    KEY_L = 0x0f,
    // Keyboard m and M
    KEY_M = 0x10,
    // Keyboard n and N
    KEY_N = 0x11,
    // Keyboard o and O
    KEY_O = 0x12,
    // Keyboard p and P
    KEY_P = 0x13,
    // Keyboard q and Q
    KEY_Q = 0x14,
    // Keyboard r and R
    KEY_R = 0x15,
    // Keyboard s and S
    KEY_S = 0x16,
    // Keyboard t and T
    KEY_T = 0x17,
    // Keyboard u and U
    KEY_U = 0x18,
    // Keyboard v and V
    KEY_V = 0x19,
    // Keyboard w and W
    KEY_W = 0x1a,
    // Keyboard x and X
    KEY_X = 0x1b,
    // Keyboard y and Y
    KEY_Y = 0x1c,
    // Keyboard z and Z
    KEY_Z = 0x1d,

    // Keyboard 1 and !
    KEY_1 = 0x1e,
    // Keyboard 2 and @
    KEY_2 = 0x1f,
    // Keyboard 3 and #
    KEY_3 = 0x20,
    // Keyboard 4 and $
    KEY_4 = 0x21,
    // Keyboard 5 and %
    KEY_5 = 0x22,
    // Keyboard 6 and ^
    KEY_6 = 0x23,
    // Keyboard 7 and &
    KEY_7 = 0x24,
    // Keyboard 8 and *
    KEY_8 = 0x25,
    // Keyboard 9 and (
    KEY_9 = 0x26,
    // Keyboard 0 and )
    KEY_0 = 0x27,

    // Keyboard Return (ENTER)
    KEY_ENTER = 0x28,
    // Keyboard ESCAPE
    KEY_ESC = 0x29,
    // Keyboard DELETE (Backspace)
    KEY_BACKSPACE = 0x2a,
    // Keyboard Tab
    KEY_TAB = 0x2b,
    // Keyboard Spacebar
    KEY_SPACE = 0x2c,
    // Keyboard - and _
    KEY_MINUS = 0x2d,
    // Keyboard = and +
    KEY_EQUAL = 0x2e,
    // Keyboard [ and {
    KEY_LEFT_BRACKET = 0x2f,
    // Keyboard ] and }
    KEY_RIGHT_BRACKET = 0x30,
    // Keyboard \ and |
    KEY_BACKSLASH = 0x31,
    // Keyboard Non-US # and ~
    KEY_NONUS_HASH = 0x32,
    // Keyboard ; and :
    KEY_SEMICOLON = 0x33,
    // Keyboard ' and "
    KEY_QUOTE = 0x34,
    // Keyboard ` and ~
    KEY_GRAVE = 0x35,
    // Keyboard , and <
    KEY_COMMA = 0x36,
    // Keyboard . and >
    KEY_DOT = 0x37,
    // Keyboard / and ?
    KEY_SLASH = 0x38,
    // Keyboard Caps Lock
    KEY_CAPSLOCK = 0x39,

    // Keyboard F1
    KEY_F1 = 0x3a,
    // Keyboard F2
    KEY_F2 = 0x3b,
    // Keyboard F3
    KEY_F3 = 0x3c,
    // Keyboard F4
    KEY_F4 = 0x3d,
    // Keyboard F5
    KEY_F5 = 0x3e,
    // Keyboard F6
    KEY_F6 = 0x3f,
    // Keyboard F7
    KEY_F7 = 0x40,
    // Keyboard F8
    KEY_F8 = 0x41,
    // Keyboard F9
    KEY_F9 = 0x42,
    // Keyboard F10
    KEY_F10 = 0x43,
    // Keyboard F11
    KEY_F11 = 0x44,
    // Keyboard F12
    KEY_F12 = 0x45,

    // Keyboard Print Screen
    KEY_PRINT_SCREEN = 0x46,
    // Keyboard Scroll Lock
    KEY_SCROLL_LOCK = 0x47,
    // Keyboard Pause
    KEY_PAUSE = 0x48,
    // Keyboard Insert
    KEY_INSERT = 0x49,
    // Keyboard Home
    KEY_HOME = 0x4a,
    // Keyboard Page Up
    KEY_PAGE_UP = 0x4b,
    // Keyboard Delete Forward
    KEY_DELETE = 0x4c,
    // Keyboard End
    KEY_END = 0x4d,
    // Keyboard Page Down
    KEY_PAGE_DOWN = 0x4e,
    // Keyboard Right Arrow
    KEY_RIGHT = 0x4f,
    // Keyboard Left Arrow
    KEY_LEFT = 0x50,
    // Keyboard Down Arrow
    KEY_DOWN = 0x51,
    // Keyboard Up Arrow
    KEY_UP = 0x52,

    // Keyboard Num Lock and Clear
    KEY_NUMLOCK = 0x53,
    // Keypad /
    KEY_KP_SLASH = 0x54,
    // Keypad *
    KEY_KP_ASTERISK = 0x55,
    // Keypad -
    KEY_KP_MINUS = 0x56,
    // Keypad +
    KEY_KP_PLUS = 0x57,
    // Keypad ENTER
    KEY_KP_ENTER = 0x58,
    // Keypad 1 and End
    KEY_KP_1 = 0x59,
    // Keypad 2 and Down Arrow
    KEY_KP_2 = 0x5a,
    // Keypad 3 and PageDn
    KEY_KP_3 = 0x5b,
    // Keypad 4 and Left Arrow
    KEY_KP_4 = 0x5c,
    // Keypad 5
    KEY_KP_5 = 0x5d,
    // Keypad 6 and Right Arrow
    KEY_KP_6 = 0x5e,
    // Keypad 7 and Home
    KEY_KP_7 = 0x5f,
    // Keypad 8 and Up Arrow
    KEY_KP_8 = 0x60,
    // Keypad 9 and Page Up
    KEY_KP_9 = 0x61,
    // Keypad 0 and Insert
    KEY_KP_0 = 0x62,
    // Keypad . and Delete
    KEY_KP_DOT = 0x63,

    // Keyboard Non-US \ and |
    KEY_NONUS_BACKSLASH = 0x64,
    // Keyboard Application
    KEY_APPLICATION = 0x65,
    // Keyboard Power
    KEY_POWER = 0x66,
    // Keypad =
    KEY_KP_EQUAL = 0x67,

    // Keyboard F13
    KEY_F13 = 0x68,
    // Keyboard F14
    KEY_F14 = 0x69,
    // Keyboard F15
    KEY_F15 = 0x6a,
    // Keyboard F16
    KEY_F16 = 0x6b,
    // Keyboard F17
    KEY_F17 = 0x6c,
    // Keyboard F18
    KEY_F18 = 0x6d,
    // Keyboard F19
    KEY_F19 = 0x6e,
    // Keyboard F20
    KEY_F20 = 0x6f,
    // Keyboard F21
    KEY_F21 = 0x70,
    // Keyboard F22
    KEY_F22 = 0x71,
    // Keyboard F23
    KEY_F23 = 0x72,
    // Keyboard F24
    KEY_F24 = 0x73,

    // Keyboard Execute
    KEY_EXECUTE = 0x74,
    // Keyboard Help
    KEY_HELP = 0x75,
    // Keyboard Menu
    KEY_MENU = 0x76,
    // Keyboard Select
    KEY_SELECT = 0x77,
    // Keyboard Stop
    KEY_STOP = 0x78,
    // Keyboard Again
    KEY_AGAIN = 0x79,
    // Keyboard Undo
    KEY_UNDO = 0x7a,
    // Keyboard Cut
    KEY_CUT = 0x7b,
    // Keyboard Copy
    KEY_COPY = 0x7c,
    // Keyboard Paste
    KEY_PASTE = 0x7d,
    // Keyboard Find
    KEY_FIND = 0x7e,
    // Keyboard Mute
    KEY_MUTE = 0x7f,
    // Keyboard Volume Up
    KEY_VOLUME_UP = 0x80,
    // Keyboard Volume Down
    KEY_VOLUME_DOWN = 0x81,
    // Keyboard Locking Caps Lock
    KEY_LOCKING_NUM_CAPS_LOCK = 0x82,
    // Keyboard Locking Num Lock
    KEY_LOCKING_NUM_LOCK = 0x83,
    // Keyboard Locking Scroll Lock
    KEY_LOCKING_SCROLL_LOCK = 0x84,

    // Keypad Comma
    KEY_KP_COMMA = 0x85,
    // Keypad Equal Sign
    KEY_KP_EQUAL_SIGN = 0x86,

    // Keyboard International1
    KEY_RO = 0x87,
    // Keyboard International2
    KEY_KATAKANAHIRAGANA = 0x88,
    // Keyboard International3
    KEY_YEN = 0x89,
    // Keyboard International4
    KEY_HENKAN = 0x8a,
    // Keyboard International5
    KEY_MUHENKAN = 0x8b,
    // Keyboard International6
    KEY_KPJPCOMMA = 0x8c,
    // Keyboard International7
    KEY_INTL7 = 0x8d,
    // Keyboard International8
    KEY_INTL8 = 0x8e,
    // Keyboard International9
    KEY_INTL9 = 0x8f,

    // Keyboard LANG1
    KEY_HANGEUL = 0x90,
    // Keyboard LANG2
    KEY_HANJA = 0x91,
    // Keyboard LANG3
    KEY_KATAKANA = 0x92,
    // Keyboard LANG4
    KEY_HIRAGANA = 0x93,
    // Keyboard LANG5
    KEY_ZENKAKUHANKAKU = 0x94,
    // Keyboard LANG6
    KEY_LANG6 = 0x95,
    // Keyboard LANG7
    KEY_LANG7 = 0x96,
    // Keyboard LANG8
    KEY_LANG8 = 0x97,
    // Keyboard LANG9
    KEY_LANG9 = 0x98,
    // Keyboard Alternate Erase
    KEY_ALTERASE = 0x99,
    // Keyboard SysReq/Attention
    KEY_SYSREQ = 0x9a,
    // Keyboard Cancel
    KEY_CANCEL = 0x9b,
    // Keyboard Clear
    KEY_CLEAR = 0x9c,
    // Keyboard Prior
    KEY_PRIOR = 0x9d,
    // Keyboard Return
    KEY_RETURN = 0x9e,
    // Keyboard Separator
    KEY_SEPARATOR = 0x9f,
    // Keyboard Out
    KEY_OUT = 0xa0,
    // Keyboard Oper
    KEY_OPER = 0xa1,
    // Keyboard Clear/Again
    KEY_CLEARAGAIN = 0xa2,
    // Keyboard CrSel/Props
    KEY_CRSEL = 0xa3,
    // Keyboard ExSel
    KEY_EXSEL = 0xa4,

    // A5-AF Reserved

    // Keypad 00
    KEY_KP_00 = 0xb0,
    // Keypad 000
    KEY_KP_000 = 0xb1,
    // Thousands Separator
    KEY_THOUSANDS_SEPARATOR = 0xb2,
    // Decimal Separator
    KEY_DECIMAL_SEPARATOR = 0xb3,
    // Currency Unit
    KEY_CURRENCY_UNIT = 0xb4,
    // Currency Sub-unit
    KEY_CURRENCY_SUB_UNIT = 0xb5,

    // Keypad (
    KEY_KP_LEFT_PAREN = 0xb6,
    // Keypad )
    KEY_KP_RIGHT_PAREN = 0xb7,
    // Keypad {
    KEY_KP_LEFT_BRACE = 0xb8,
    // Keypad }
    KEY_KP_RIGHT_BRACE = 0xb9,
    // Keypad Tab
    KEY_KP_TAB = 0xba,
    // Keypad Backspace
    KEY_KP_BACKSPACE = 0xbb,
    // Keypad A
    KEY_KP_A = 0xbc,
    // Keypad B
    KEY_KP_B = 0xbd,
    // Keypad C
    KEY_KP_C = 0xbe,
    // Keypad D
    KEY_KP_D = 0xbf,
    // Keypad E
    KEY_KP_E = 0xc0,
    // Keypad F
    KEY_KP_F = 0xc1,
    // Keypad XOR
    KEY_KP_XOR = 0xc2,
    // Keypad ^
    KEY_KP_POWER = 0xc3,
    // Keypad %
    KEY_KP_PERCENT = 0xc4,
    // Keypad <
    KEY_KP_LESS = 0xc5,
    // Keypad >
    KEY_KP_GREATER = 0xc6,
    // Keypad &
    KEY_KP_AMPERSAND = 0xc7,
    // Keypad &&
    KEY_KP_DBLAMPERSAND = 0xc8,
    // Keypad |
    KEY_KP_VERTICALBAR = 0xc9,
    // Keypad ||
    KEY_KP_DBLVERTICALBAR = 0xca,
    // Keypad :
    KEY_KP_COLON = 0xcb,
    // Keypad #
    KEY_KP_HASH = 0xcc,
    // Keypad Space
    KEY_KP_SPACE = 0xcd,
    // Keypad @
    KEY_KP_AT = 0xce,
    // Keypad !
    KEY_KP_EXCLAM = 0xcf,
    // Keypad Memory Store
    KEY_KP_MEMSTORE = 0xd0,
    // Keypad Memory Recall
    KEY_KP_MEMRECALL = 0xd1,
    // Keypad Memory Clear
    KEY_KP_MEMCLEAR = 0xd2,
    // Keypad Memory Add
    KEY_KP_MEMADD = 0xd3,
    // Keypad Memory Subtract
    KEY_KP_MEMSUBTRACT = 0xd4,
    // Keypad Memory Multiply
    KEY_KP_MEMMULTIPLY = 0xd5,
    // Keypad Memory Divide
    KEY_KP_MEMDIVIDE = 0xd6,
    // Keypad +/-
    KEY_KP_PLUSMINUS = 0xd7,
    // Keypad Clear
    KEY_KP_CLEAR = 0xd8,
    // Keypad Clear Entry
    KEY_KP_CLEARENTRY = 0xd9,
    // Keypad Binary
    KEY_KP_BINARY = 0xda,
    // Keypad Octal
    KEY_KP_OCTAL = 0xdb,
    // Keypad Decimal
    KEY_KP_DECIMAL = 0xdc,
    // Keypad Hexadecimal
    KEY_KP_HEXADECIMAL = 0xdd,

    // DE-DF Reserved

    // Keyboard Left Control
    KEY_LEFT_CTRL = 0xe0,
    // Keyboard Left Shift
    KEY_LEFT_SHIFT = 0xe1,
    // Keyboard Left Alt
    KEY_LEFT_ALT = 0xe2,
    // Keyboard Left GUI
    KEY_LEFT_GUI = 0xe3,
    // Keyboard Right Control
    KEY_RIGHT_CTRL = 0xe4,
    // Keyboard Right Shift
    KEY_RIGHT_SHIFT = 0xe5,
    // Keyboard Right Alt
    KEY_RIGHT_ALT = 0xe6,
    // Keyboard Right GUI
    KEY_RIGHT_GUI = 0xe7,

    KEY_MEDIA_PLAYPAUSE = 0xe8,
    KEY_MEDIA_STOPCD = 0xe9,
    KEY_MEDIA_PREVIOUSSONG = 0xea,
    KEY_MEDIA_NEXTSONG = 0xeb,
    KEY_MEDIA_EJECTCD = 0xec,
    KEY_MEDIA_VOLUMEUP = 0xed,
    KEY_MEDIA_VOLUMEDOWN = 0xee,
    KEY_MEDIA_MUTE = 0xef,
    KEY_MEDIA_WWW = 0xf0,
    KEY_MEDIA_BACK = 0xf1,
    KEY_MEDIA_FORWARD = 0xf2,
    KEY_MEDIA_STOP = 0xf3,
    KEY_MEDIA_FIND = 0xf4,
    KEY_MEDIA_SCROLLUP = 0xf5,
    KEY_MEDIA_SCROLLDOWN = 0xf6,
    KEY_MEDIA_EDIT = 0xf7,
    KEY_MEDIA_SLEEP = 0xf8,
    KEY_MEDIA_COFFEE = 0xf9,
    KEY_MEDIA_REFRESH = 0xfa,
    KEY_MEDIA_CALC = 0xfb,

    // E8-FFFF Reserved
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
