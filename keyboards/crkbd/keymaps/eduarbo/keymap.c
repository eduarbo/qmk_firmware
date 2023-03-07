/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "oled_utils.h"

enum corne_layers { _BASE, _FKEYS, _WINDOWS, _ADJUST, _SYMBOLS, _GAMING };

#define SUPER_MOD (MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL))
#define HYPER_MOD (MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT))

#define QUO_SUPR MT(SUPER_MOD, KC_QUOT)
#define SPC_RSFT MT(MOD_RSFT, KC_SPC)
#define ESC_RGUI MT(MOD_RGUI, KC_ESC)
#define TAB_SYMB LT(_SYMBOLS, KC_TAB)
#define GRV_RCTL MT(MOD_RCTL, KC_GRV)

#define GRV_RALT MT(MOD_RALT, KC_GRV)
#define ESC_RCTL MT(MOD_RCTL, KC_ESC)

#define ACCENT A(KC_E)
#define WINDOWS TG(_WINDOWS)
#define GAMING TG(_GAMING)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // TODO Call adjust mod when holding down both CMD keys
  [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT,  ACCENT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         QUO_SUPR,SPC_RSFT,ESC_RGUI,   ESC_RGUI,TAB_SYMB,GRV_RCTL
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_HOME,    KC_7,    KC_8,    KC_9,    KC_0,                      KC_BSLS, KC_LBRC, KC_RBRC, KC_SLSH, KC_PGUP, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_END,    KC_4,    KC_5,    KC_6,  KC_EQL,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_PGDN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_F13,    KC_1,    KC_2,    KC_3, KC_MINS,                      KC_BSPC,  KC_ENT, _______, _______, CAPSWRD, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_WINDOWS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         QUO_SUPR,SPC_RSFT,ESC_RCTL,   ESC_RCTL,TAB_SYMB,GRV_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_FKEYS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_INS,  KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,                       KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|--------|
      WINDOWS,  KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,                       KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,  GAMING,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|--------|
      KC_RSFT,  KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,                       KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_LSFT,  _______,   _______, KC_RSFT, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,   RESET,   DEBUG, XXXXXXX,  EE_CLR, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                      XXXXXXX, WINDOWS,  GAMING, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, XXXXXXX,  XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAMING] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,   KC_UP,    KC_R,    KC_T,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A, KC_LEFT, KC_DOWN,KC_RIGHT,    KC_G,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_SPC,  KC_LCTL,   ESC_RCTL,TAB_SYMB,GRV_RALT
                                      //`--------------------------'  `--------------------------'
  ),
};

// CAPS WORD -------------------------------------------------------------------

// Define custom Caps Word continuity characters
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_TILD:
        case KC_UNDS:
        case KC_DQT:
        case KC_COLN:
        case KC_RSFT:
        case KC_LSFT:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_GRV:
        case KC_MINS:
        case KC_QUOT:
        case KC_SCLN:
        case KC_BSPC:
        case KC_DEL:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}


// INTERCEPT KEYS --------------------------------------------------------------

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mods = get_mods();
    /* const uint8_t oneshot_mods = get_oneshot_mods(); */

    switch (keycode) {
        case SPC_RSFT:
            if (IS_LAYER_ON(_SYMBOLS) && record->tap.count && record->event.pressed) {
                tap_code16(S(KC_SPC));
                return false; // Return false to ignore further processing of key
            }
            break;

        case QUO_SUPR: {
            if (record->tap.count && record->event.pressed) {
                // on tap
                if (IS_LAYER_ON(_SYMBOLS)) {
                    tap_code16(S(KC_QUOT));
                    return false;
                }
            } else if (record->event.pressed) {
                // on hold keydown
                if (IS_LAYER_ON(_SYMBOLS)) {
                    layer_off(_SYMBOLS);
                    register_mods(HYPER_MOD);
                    return false;
                } else if ((mods & MOD_BIT(KC_RCTL)) == MOD_BIT(KC_RCTL)) {
                    unregister_code(KC_RCTL);
                    if (IS_LAYER_ON(_WINDOWS)) {
                        layer_on(_ADJUST);
                    } else {
                        layer_on(_FKEYS);
                    }
                    return false;
                } else if ((mods & MOD_BIT(KC_RGUI)) == MOD_BIT(KC_RGUI)) {
                    unregister_code(KC_RGUI);
                    layer_on(_ADJUST);
                    return false;
                } else if ((mods & MOD_BIT(KC_RALT)) == MOD_BIT(KC_RALT)) {
                    unregister_code(KC_RALT);
                    layer_on(_ADJUST);
                    return false;
                }
            } else {
                // oh hold keyup
                if ((mods & HYPER_MOD) == HYPER_MOD) {
                    unregister_mods(HYPER_MOD);
                    layer_on(_SYMBOLS);
                    return false;
                } else if (IS_LAYER_ON(_FKEYS)) {
                    layer_off(_FKEYS);
                    if (IS_LAYER_ON(_WINDOWS)) {
                        register_code(KC_RALT);
                    } else {
                        register_code(KC_RCTL);
                    }
                    return false;
                } else if (IS_LAYER_ON(_ADJUST)) {
                    layer_off(_ADJUST);
                    if (IS_LAYER_ON(_WINDOWS)) {
                        register_code(KC_RCTL);
                    } else {
                        register_code(KC_RGUI);
                    }
                    return false;
                }
            }
            break;
        }

        case TAB_SYMB: {
            if (record->tap.count && record->event.pressed) {
                // on tap
            } else if (record->event.pressed) {
                // on hold keydown
                if ((mods & SUPER_MOD) == SUPER_MOD) {
                    register_mods(HYPER_MOD);
                    return false;
                }
            } else {
                // oh hold keyup
                if ((mods & HYPER_MOD) == HYPER_MOD) {
                    unregister_code(KC_LSFT);
                    return false;
                }
            }
            break;
        }

        case ESC_RCTL:
        case ESC_RGUI: {
            if (record->tap.count && record->event.pressed) {
                // on tap
                if (IS_LAYER_ON(_SYMBOLS)) {
                    tap_code16(S(KC_ESC));
                    return false;
                }
            } else if (record->event.pressed) {
                // on hold keydown
                if ((mods & SUPER_MOD) == SUPER_MOD) {
                    unregister_mods(SUPER_MOD);
                    layer_on(_ADJUST);
                    return false;
                } else if (IS_LAYER_ON(_GAMING) && ((mods & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT))) {
                    unregister_code(KC_LALT);
                    layer_on(_ADJUST);
                    return false;
                }
            } else {
                // oh hold keyup
                if (IS_LAYER_ON(_ADJUST)) {
                    layer_off(_ADJUST);
                    if (IS_LAYER_ON(_GAMING)) {
                        register_code(KC_LALT);
                    } else {
                        register_mods(SUPER_MOD);
                    }
                    return false;
                }
            }
            break;
        }

        case GRV_RALT:
        case GRV_RCTL: {
            if (record->tap.count && record->event.pressed) {
                // on tap
            } else if (record->event.pressed) {
                // on hold keydown
                if ((mods & SUPER_MOD) == SUPER_MOD) {
                    unregister_mods(SUPER_MOD);
                    layer_on(_FKEYS);
                    return false;
                }
            } else {
                // oh hold keyup
                if (IS_LAYER_ON(_FKEYS)) {
                    layer_off(_FKEYS);
                    register_mods(SUPER_MOD);
                    return false;
                }
            }
            break;
        }

        case KC_LALT: {
            if (record->tap.count && record->event.pressed) {
                // on tap
            } else if (record->event.pressed) {
                // on hold keydown
                if ((mods & MOD_BIT(KC_RCTL)) == MOD_BIT(KC_RCTL)) {
                    unregister_code(KC_RCTL);
                    layer_on(_ADJUST);
                    return false;
                }
            } else {
                // oh hold keyup
                if (IS_LAYER_ON(_ADJUST)) {
                    layer_off(_ADJUST);
                    register_code(KC_RCTL);
                    return false;
                }
            }
            break;
        }

        // Shift + Backspace = Delete, see: https://docs.qmk.fm/#/feature_advanced_keycodes?id=shift-backspace-for-delete
        /* case KC_BSPC: { */
        /*     // Initialize a boolean variable that keeps track */
        /*     // of the delete key status: registered or not? */
        /*     static bool delkey_registered; */
        /*     if (record->event.pressed) { */
        /*         // Detect the activation of either shift keys */
        /*         if (mods & MOD_MASK_SHIFT) { */
        /*             // First temporarily canceling both shifts so that */
        /*             // shift isn't applied to the KC_DEL keycode */
        /*             unregister_mods(MOD_MASK_SHIFT); */
        /*             register_code(KC_DEL); */
        /*             // Update the boolean variable to reflect the status of KC_DEL */
        /*             delkey_registered = true; */
        /*             // Reapplying modifier state so that the held shift key(s) */
        /*             // still work even after having tapped the Backspace/Delete key. */
        /*             set_mods(mods); */
        /*             return false; */
        /*         } */
        /*     } else { // on release of KC_BSPC */
        /*         // In case KC_DEL is still being sent even after the release of KC_BSPC */
        /*         if (delkey_registered) { */
        /*             unregister_code(KC_DEL); */
        /*             delkey_registered = false; */
        /*             return false; */
        /*         } */
        /*     } */
        /*     // Let QMK process the KC_BSPC keycode as usual outside of shift */
        /*     return true; */
        /* } */
    }
    return true;
}


// OLED CODE -------------------------------------------------
#ifdef OLED_ENABLE

#    ifdef USE_OLED_COMPRESSION
static void oled_write_compressed_P(const char* input_block_map, const char* input_block_list) {
    uint16_t block_index = 0;
    for (uint16_t i = 0; i < NUM_OLED_BYTES; i++) {
        uint8_t bit          = i % 8;
        uint8_t map_index    = i / 8;
        uint8_t _block_map   = (uint8_t)pgm_read_byte_near(input_block_map + map_index);
        uint8_t nonzero_byte = (_block_map & (1 << bit));
        if (nonzero_byte) {
            const char data = (const char)pgm_read_byte_near(input_block_list + block_index++);
            oled_write_raw_byte(data, i);
        } else {
            const char data = (const char)0x00;
            oled_write_raw_byte(data, i);
        }
    }
}
#    endif // USE_OLED_COMPRESSION

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master() && !is_keyboard_left()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    } else if (!is_keyboard_master() && !is_keyboard_left()) {
        return OLED_ROTATION_270;
    } else if (!is_keyboard_master() && is_keyboard_left()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}
#    define L_BASE 0

// Writes the current layer state on the screen wherever the cursor is
void render_layer_state(void) {
    if (oled_horizontal) {
        oled_set_cursor(0, 0);
    } else {
        oled_set_cursor(0, 15);
    }

    switch (get_highest_layer(layer_state)) {
        case _GAMING:
            oled_write_P(PSTR("GAME "), false);
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("SYMB "), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJST"), false);
            break;
        case _WINDOWS:
            oled_write_P(PSTR("WIN  "), false);
            break;
        case _FKEYS:
            oled_write_P(PSTR("F-KEY"), false);
            break;
        case _BASE:
            oled_write_P(PSTR("     "), false);
            break;
        default:
            oled_write_P(PSTR("?????"), false);
    }
}

void animation_phase(void) {
    if (get_current_wpm() <= IDLE_SPEED) {
        current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
        uint8_t idx        = abs((IDLE_FRAMES - 1) - current_idle_frame);
#    ifdef USE_OLED_COMPRESSION
        oled_write_compressed_P(idle_maps[idx], idle_lists[idx]);
#    else
        oled_write_raw_P(idle[idx], ANIM_SIZE);
#    endif // USE_OLED_COMPRESSION
    }
    if (get_current_wpm() > IDLE_SPEED && get_current_wpm() < TAP_SPEED) {
#    ifdef USE_OLED_COMPRESSION
        oled_write_compressed_P(prep_map, prep_list);
#    else
        oled_write_raw_P(prep[0], ANIM_SIZE); // remove if IDLE_FRAMES >1
                                              // oled_write_raw_P(prep[abs((PREP_FRAMES-1)-current_prep_frame)], ANIM_SIZE);
#    endif // USE_OLED_COMPRESSION
    }
    if (get_current_wpm() >= TAP_SPEED) {
        current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
        uint8_t idx       = abs((TAP_FRAMES - 1) - current_tap_frame);
#    ifdef USE_OLED_COMPRESSION
        oled_write_compressed_P(tap_maps[idx], tap_lists[idx]);
#    else
        oled_write_raw_P(tap[idx], ANIM_SIZE);
#    endif
    }
}

static void render_bongo_cat(void) {
    // assumes 1 frame prep stagen
    if (get_current_wpm() != 000) {
        oled_on(); // not essential but turns on animation OLED with any alpha keypress
        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

// Update WPM counters
static void render_wpm_counters(int current_wpm) {
    int cursorposition_cur = 2;
    int cursorposition_max = 1;
    if (oled_horizontal == false) {
        cursorposition_cur = 13;
        cursorposition_max = 14;
    }

    char wpm_counter[4];
    wpm_counter[3] = '\0';
    wpm_counter[2] = '0' + current_wpm % 10;
    wpm_counter[1] = '0' + (current_wpm / 10) % 10;
    wpm_counter[0] = '0' + (current_wpm / 100) % 10;
    oled_set_cursor(0, cursorposition_cur);
    oled_write(wpm_counter, false);

    if (current_wpm > max_wpm) {
        max_wpm   = current_wpm;
        wpm_limit = max_wpm + 20;
        oled_set_cursor(0, cursorposition_max);
        oled_write(wpm_counter, false);
    }
}

// Toggles pixel on/off, converts horizontal coordinates to vertical equivalent if necessary
static void write_pixel(int x, int y, bool onoff) {
    if (oled_horizontal) {
        oled_write_pixel(x, y, onoff);
    } else {
        oled_write_pixel(y, 127 - x, onoff);
    }
}

// Update WPM snail icon
static void render_wpm_icon(int current_wpm) {
    // wpm_icon is used to prevent unnecessary redraw
    if ((current_wpm < icon_med_wpm) && (wpm_icon != 0)) {
        wpm_icon = 0;
    } else if ((current_wpm >= icon_med_wpm) && (current_wpm < icon_fast_wpm) && (wpm_icon != 1)) {
        wpm_icon = 1;
    } else if ((current_wpm >= icon_fast_wpm) && (wpm_icon != 2)) {
        wpm_icon = 2;
    } else {
        return;
    }
    static const char PROGMEM snails[][2][24] = {{{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0xA0, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x50, 0x88, 0x04, 0x00, 0x00}, {0x40, 0x60, 0x50, 0x4E, 0x51, 0x64, 0x4A, 0x51, 0x54, 0x49, 0x41, 0x62, 0x54, 0x49, 0x46, 0x41, 0x40, 0x30, 0x09, 0x04, 0x02, 0x01, 0x00, 0x00}}, {{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x04, 0x98, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00}, {0x60, 0x50, 0x54, 0x4A, 0x51, 0x64, 0x4A, 0x51, 0x55, 0x49, 0x41, 0x62, 0x54, 0x49, 0x46, 0x41, 0x21, 0x10, 0x0A, 0x08, 0x05, 0x02, 0x00, 0x00}}, {{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x10, 0x10, 0x10, 0x20, 0x40, 0x40, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00}, {0x60, 0x58, 0x54, 0x62, 0x49, 0x54, 0x52, 0x51, 0x55, 0x49, 0x62, 0x52, 0x4D, 0x45, 0x46, 0x22, 0x21, 0x11, 0x10, 0x0A, 0x08, 0x05, 0x02, 0x00}}};
    if (oled_horizontal) {
        oled_set_cursor(3, 1);
        oled_write_raw_P(snails[wpm_icon][0], sizeof(snails[wpm_icon][0]));
        oled_set_cursor(3, 2);
        oled_write_raw_P(snails[wpm_icon][1], sizeof(snails[wpm_icon][1]));
    } else {
        oled_set_cursor(0, 11);
        oled_write_raw_P(snails[wpm_icon][0], sizeof(snails[wpm_icon][0]));
        oled_set_cursor(0, 12);
        oled_write_raw_P(snails[wpm_icon][1], sizeof(snails[wpm_icon][1]));
    }
}

// To make your own pixel art:
// save a png/jpeg of an 128x32 image (resource: https://www.pixilart.com/draw )
// follow this guide up to and including "CONVERT YOUR IMAGE" https://docs.splitkb.com/hc/en-us/articles/360013811280-How-do-I-convert-an-image-for-use-on-an-OLED-display-
// replace numbers in brackets with your own
static void render_eduarbo(void) {
    static const char PROGMEM eduarbo_logo_l_1[] = {0xdc, 0x44, 0x44, 0x4c, 0x44, 0x44, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    static const char PROGMEM eduarbo_logo_l_2[] = {0x5d, 0x55, 0x55, 0xd5, 0x55, 0x55, 0xd4, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x12, 0x1e, 0xfc};
    static const char PROGMEM eduarbo_logo_l_3[] = {0xa5, 0xa5, 0xa5, 0xbd, 0x95, 0x95, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x38, 0x45, 0x47, 0x47, 0x7f};
    static const char PROGMEM eduarbo_logo_l_4[] = {0x77, 0x54, 0x54, 0x53, 0x52, 0x52, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    static const char PROGMEM eduarbo_logo_r_1[] = {0x8e, 0x4a, 0x4a, 0xca, 0x2a, 0x2a, 0xee, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    static const char PROGMEM eduarbo_logo_r_2[] = {0xb1, 0xa9, 0xa9, 0xbd, 0xa5, 0xa5, 0xa5, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xe2, 0xe2, 0xa2, 0x1c};
    static const char PROGMEM eduarbo_logo_r_3[] = {0x2b, 0xaa, 0xaa, 0xab, 0xaa, 0xaa, 0xba, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x78, 0x48, 0x08, 0x07};
    static const char PROGMEM eduarbo_logo_r_4[] = {0x3b, 0x22, 0x22, 0x32, 0x22, 0x22, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    if (is_keyboard_left()) {
        oled_set_cursor(1, 0);
        oled_write_raw_P(eduarbo_logo_l_1, sizeof(eduarbo_logo_l_1));
        oled_set_cursor(1, 1);
        oled_write_raw_P(eduarbo_logo_l_2, sizeof(eduarbo_logo_l_2));
        oled_set_cursor(1, 2);
        oled_write_raw_P(eduarbo_logo_l_3, sizeof(eduarbo_logo_l_3));
        oled_set_cursor(1, 3);
        oled_write_raw_P(eduarbo_logo_l_4, sizeof(eduarbo_logo_l_4));
    } else {
        oled_set_cursor(1, 0);
        oled_write_raw_P(eduarbo_logo_r_1, sizeof(eduarbo_logo_r_1));
        oled_set_cursor(1, 1);
        oled_write_raw_P(eduarbo_logo_r_2, sizeof(eduarbo_logo_r_2));
        oled_set_cursor(1, 2);
        oled_write_raw_P(eduarbo_logo_r_3, sizeof(eduarbo_logo_r_3));
        oled_set_cursor(1, 3);
        oled_write_raw_P(eduarbo_logo_r_4, sizeof(eduarbo_logo_r_4));
    }
}

// Update WPM graph
static void render_wpm_graph(int current_wpm) {
    int line_height = ((current_wpm / graph_top_wpm) * 7);
    if (line_height > 7) {
        line_height = 7;
    }
    // Count graph line pixels, return if nothing to draw
    int pixel_count = line_height;
    for (int i = 0; i < 63; i++) {
        pixel_count += graph_lines[i];
    }
    if (pixel_count == 0) {
        return;
    }
    // Shift array elements left or right depending on graph_direction, append new graph line
    if (graph_direction) {
        for (int i = 0; i < 63; i++) {
            graph_lines[i] = graph_lines[i + 1];
        }
        graph_lines[63] = line_height;
    } else {
        for (int i = 63; i > 0; i--) {
            graph_lines[i] = graph_lines[i - 1];
        }
        graph_lines[0] = line_height;
    }
    // Draw all graph lines (left to right, bottom to top)
    int draw_count, arrpos;
    for (int x = 1; x <= 127; x += 2) {
        arrpos     = x / 2;
        draw_count = graph_lines[arrpos];
        for (int y = 31; y >= 25; y--) {
            if (draw_count > 0) {
                write_pixel(x, y, true);
                draw_count--;
            } else {
                write_pixel(x, y, false);
            }
        }
    }
}

bool oled_task_user(void) {
    int current_wpm = get_current_wpm();
    if (is_keyboard_master()) {
        render_bongo_cat();
        render_eduarbo();
    } else {
        // oled_render_logo();
        // render_wpm(current_wpm);
        // Update the layer state
        render_layer_state();
        // Update WPM counters
        render_wpm_counters(current_wpm);
        // Update WPM snail icon
        render_wpm_icon(current_wpm);
        // Update WPM graph every graph_refresh milliseconds
        if (timer_elapsed(timer) > graph_refresh) {
            render_wpm_graph(current_wpm);
            timer = timer_read();
        }
    }
    return false;
}

#endif // OLED_ENABLE
