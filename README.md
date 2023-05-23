# Tako Keyboard Library Core

Tako Keyboard core is a keyboard firmware library for embedded devices.

## Background

Although the mainstream keyboard firmwares (such as QMK) are very powerful, but they all have some common disadvantages. Their code is tied to the MCU (because RTOS is used, for example, QMK uses ChibiOS), so it is more difficult to port to chips that are not yet supported. The code of each keyboard must also be included in the repo, which makes the repo very bloated.

So I created this library with the core goal of completely separating the keyboard logic from the MCU code.

