/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#undef PRODUCT
#define PRODUCT Eduarbo Hacked Corne Keyboard

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#undef USE_I2C
#undef SSD1306OLED
#define OLED_FONT_H "keyboards/crkbd/keymaps/eduarbo/glcdfont.c"

#define USE_SERIAL_PD2

// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
// #define PREVENT_STUCK_MODIFIERS

// Tapping this number of times holds the key until tapped this number of times again
#define ONESHOT_TAP_TOGGLE 5
// Time (in ms) before the one shot key is released
#define ONESHOT_TIMEOUT 2000

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200
#define TAPPING_TOGGLE  2

#undef RGBLED_NUM
#define RGBLED_NUM 6
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

// Enable all the animations
// #define RGBLIGHT_ANIMATIONS

// Reduce Memory Footprint by selectively enabling the animations we want
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
/* #define RGBLIGHT_EFFECT_RAINBOW_SWIRL */
#define RGBLIGHT_EFFECT_SNAKE
/* #define RGBLIGHT_EFFECT_KNIGHT */
/* #define RGBLIGHT_EFFECT_CHRISTMAS */
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
/* #define RGBLIGHT_EFFECT_RGB_TEST */
/* #define RGBLIGHT_EFFECT_ALTERNATING */
