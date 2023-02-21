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

enum corne_layers { _BASE, _LEGACY, _SYMBOLS, _FKEYS, _GAMING, _ADJUST };

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap Dance declarations
enum tapdances { TD_LGUI_SUPER, TD_LCTL_HYPER, TD_RALT_FKEYS };

td_state_t cur_dance(qk_tap_dance_state_t *state);

void dance_SUPER_finished (qk_tap_dance_state_t *state, void *user_data);
void dance_SUPER_reset (qk_tap_dance_state_t *state, void *user_data);
void dance_HYPER_finished (qk_tap_dance_state_t *state, void *user_data);
void dance_HYPER_reset (qk_tap_dance_state_t *state, void *user_data);
void dance_FKEYS_finished (qk_tap_dance_state_t *state, void *user_data);
void dance_FKEYS_reset (qk_tap_dance_state_t *state, void *user_data);


#define GAMING TG(_GAMING)
#define BASE DF(_BASE)
#define LEGACY DF(_LEGACY)

#define SPC_LSFT MT(MOD_LSFT, KC_SPC)
#define ESC_SYMB LT(_SYMBOLS, KC_ESC)
#define OSM_RSFT OSM(MOD_RSFT)
#define OSL_SYMB OSL(_SYMBOLS)
#define OSL_ADJT OSL(_ADJUST)
#define LGUI_SUP TD(TD_LGUI_SUPER)
#define LCTL_HYP TD(TD_LCTL_HYPER)
#define RALT_FKY TD(TD_RALT_FKEYS)
#define ACCENT LALT(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // TODO Call adjust mod when holding down both CMD keys
  [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  ACCENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OSL_SYMB,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,OSM_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         LCTL_HYP,SPC_LSFT,LGUI_SUP,   LGUI_SUP,ESC_SYMB,RALT_FKY
                                      //`--------------------------'  `--------------------------'
  ),

  [_LEGACY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_LCTL,  KC_SPC,     KC_SPC, KC_RCTL, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_BSLS,    KC_7,    KC_8,    KC_9,    KC_0,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_MINS,    KC_4,    KC_5,    KC_6,  KC_EQL,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, CAPSWRD,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LBRC,    KC_1,    KC_2,    KC_3, KC_RBRC,                       KC_ENT, KC_BSPC, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______,  _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_FKEYS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_INS,  KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,                       KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|--------|
     OSL_ADJT,  KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,                       KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,OSL_ADJT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|--------|
     OSM_RSFT,  KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,                       KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,OSM_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_LSFT,  _______,   _______, KC_RSFT, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAMING] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_E,   KC_UP,    KC_R,    KC_T,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB, KC_BSPC, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_ENT,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, KC_LSFT,  KC_SPC,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,   RESET,   DEBUG, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                         BASE,  GAMING, CG_TOGG,  LEGACY, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, XXXXXXX,  XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
};

// TAP DANCE -------------------------------------------------

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed)
            return TD_DOUBLE_TAP;
        else
            return TD_DOUBLE_HOLD;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

// Single-tap: LGUI
// Double-tap: SUPER OneShot Mod

static td_tap_t lgui_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void dance_SUPER_finished (qk_tap_dance_state_t *state, void *user_data) {
  lgui_tap_state.state = cur_dance(state);
  switch (lgui_tap_state.state) {
    case TD_SINGLE_TAP: register_code(KC_LGUI); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case TD_SINGLE_HOLD: register_mods(MOD_LGUI); break;
    case TD_DOUBLE_TAP: set_oneshot_mods(MOD_LGUI | MOD_LCTL | MOD_LALT); break;
    case TD_DOUBLE_HOLD: register_mods(MOD_LGUI | MOD_LCTL | MOD_LALT); break;
    case TD_TRIPLE_HOLD: layer_on(_ADJUST); break;
    default: break;
  }
}

void dance_SUPER_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lgui_tap_state.state) {
    case TD_SINGLE_TAP: unregister_code(KC_LGUI); break;
    case TD_SINGLE_HOLD: unregister_mods(MOD_LGUI); break;
    case TD_DOUBLE_TAP: break;
    case TD_DOUBLE_HOLD: unregister_mods(MOD_LGUI | MOD_LCTL | MOD_LALT); break;
    case TD_TRIPLE_HOLD: layer_off(_ADJUST); break;
    default: break;
  }
  lgui_tap_state.state = TD_NONE;
}

// Single-tap: LCTL
// Double-tap: HYPER OneShot Mod

static td_tap_t ctl_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void dance_HYPER_finished (qk_tap_dance_state_t *state, void *user_data) {
  ctl_tap_state.state = cur_dance(state);
  switch (ctl_tap_state.state) {
    case TD_SINGLE_TAP: register_code(KC_LCTL); break;
    case TD_SINGLE_HOLD: register_code(KC_LCTL); break;
    case TD_DOUBLE_TAP: set_oneshot_mods(MOD_HYPR); break;
    case TD_DOUBLE_HOLD: register_mods(MOD_HYPR); break;
    default: break;
  }
}

void dance_HYPER_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ctl_tap_state.state) {
    case TD_SINGLE_TAP: unregister_code(KC_LCTL); break;
    case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
    case TD_DOUBLE_TAP: break;
    case TD_DOUBLE_HOLD: unregister_mods(MOD_HYPR); break;
    default: break;
  }
  ctl_tap_state.state = TD_NONE;
}

// Single-tap: RALT
// Double-tap: F-Keys OneShot Layer

static td_tap_t alt_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void dance_FKEYS_finished (qk_tap_dance_state_t *state, void *user_data) {
  alt_tap_state.state = cur_dance(state);
  switch (alt_tap_state.state) {
    case TD_SINGLE_TAP: register_code(KC_RALT); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case TD_SINGLE_HOLD: register_mods(MOD_RALT); break;
    case TD_DOUBLE_TAP: set_oneshot_layer(_FKEYS, ONESHOT_START); break;
    case TD_DOUBLE_HOLD: layer_on(_FKEYS); break;
    default: break;
  }
}

void dance_FKEYS_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alt_tap_state.state) {
    case TD_SINGLE_TAP: unregister_code(KC_RALT); break;
    case TD_SINGLE_HOLD: unregister_mods(MOD_RALT); break;
    case TD_DOUBLE_TAP: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case TD_DOUBLE_HOLD: layer_off(_FKEYS); break;
    default: break;
  }
  alt_tap_state.state = TD_NONE;
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LGUI_SUPER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_SUPER_finished, dance_SUPER_reset),
    [TD_LCTL_HYPER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_HYPER_finished, dance_HYPER_reset),
    [TD_RALT_FKEYS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_FKEYS_finished, dance_FKEYS_reset),
};

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
        case _BASE:
            oled_write_P(PSTR("Base"), false);
            break;
        case _LEGACY:
            oled_write_P(PSTR("Legcy"), false);
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("Symb"), false);
            break;
        case _FKEYS:
            oled_write_P(PSTR("F-Key"), false);
            break;
        case _GAMING:
            oled_write_P(PSTR("Game"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjst"), false);
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
