#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  EPRM
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_      KC_TRNS
#define KC_XXX   KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

#define KC_VTOG  VLK_TOG
#define KC_LRMOD RGB_RMOD
#define KC_SCL_A LT(_ADJUST, KC_SCLN)
#define KC_EPRM  EPRM  // Useful to unfuck the RGB Underglow

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //┌─────┬─────┬─────┬─────┬─────┬─────┐              ┌─────┬─────┬─────┬─────┬─────┬─────┐
      TAB ,  Q  ,  W  ,  E  ,  R  ,  T  ,                 Y  ,  U  ,  I  ,  O  ,  P  , LBRC,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
      CAPS,  A  ,  S  ,  D  ,  F  ,  G  ,                 H  ,  J  ,  K  ,  L  ,SCL_A,QUOTE,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
      LSFT,  Z  ,  X  ,  C  ,  V  ,  B  ,                 N  ,  M  ,COMMA, DOT ,SLASH, RSFT,\
  //└─────┴─────┼─────┴───┬─┴─────┴─┬───┴─────┐  ┌─────┴───┬─┴─────┴─┬───┴─────┼────┬┴─────┘
                    LALT  ,   LCMD  ,   SPC   ,      SPC   ,   RCMD  ,   RALT   \
  //            └─────────┴─────────┴─────────┘  └─────────┴─────────┴─────────┘
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,    F8,    F9,   F10,  XXX ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,   F11,   F12,   F13,   F14,   F15,                    F16,   F17,   F18,   F19,   F20,  XXX ,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, LOWER,   SPC,      ENT, RAISE, ALTKN \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,                   MINS,   EQL,  LCBR,  RCBR,  PIPE,   GRV,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,                   UNDS,  PLUS,  LBRC,  RBRC,  BSLS,  TILD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, LOWER,   SPC,      ENT, RAISE, ALTKN \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //┌─────┬─────┬─────┬─────┬─────┬─────┐              ┌─────┬─────┬─────┬─────┬─────┬─────┐
      XXX , F1  , F2  , F3  , F4  , XXX ,                EPRM, LRST, LTOG, VTOG, XXX , XXX ,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
      CAPS, F5  , F6  , F7  , F8  , XXX ,                LMOD, LHUI, LSAI, LVAI, XXX , XXX ,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
      XXX , F9  , F10 , F11 , F12 , XXX ,               LRMOD, LHUD, LSAD, LVAD, XXX , XXX ,\
  //└─────┴─────┼─────┴───┬─┴─────┴─┬───┴─────┐  ┌─────┴───┬─┴─────┴─┬───┴─────┼────┬┴─────┘
                          ,         ,         ,            ,         ,          \
  //            └─────────┴─────────┴─────────┘  └─────────┴─────────┴─────────┘
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return rotation;
        /* return OLED_ROTATION_270; */
    } else {
        return OLED_ROTATION_270;
        /* return rotation; */
    }
}

void render_logo(void) {
    static const char PROGMEM eduarbo_logo[] = {
        0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f,
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(eduarbo_logo, false);
}


void render_status(void) {

    // Render the titles
    static const char PROGMEM titles[3][6] = {
        {0x20,0x95,0x96,0x97,0x98,0}, // Lock
        {0x20,0xb5,0xb6,0xb7,0xb8,0}, // Lyout
        {0x20,0xd5,0xd6,0xd7,0xd8,0} }; // Layer

    oled_write_P(titles[2], false);
    oled_write_P(PSTR("     "), false);
    switch (biton32(layer_state)) {
        case 0:
            oled_write_P(PSTR("Base "), false);
            break;
        /* case _SHIFTED: */
        /*     oled_write_P(PSTR("Shft "), false); */
        /*     break; */
        /* case _SYMB: */
        /*     oled_write_P(PSTR("Symb "), false); */
        /*     break; */
        /* case _NAV: */
        /*     oled_write_P(PSTR("Nav  "), false); */
        /*     break; */
        case _ADJUST:
            oled_write_P(PSTR("Adjst"), false);
            break;
        default:
            oled_write_P(PSTR("Unkn "), false);
            break;
    }
    oled_write_P(PSTR("     "), false);
    oled_write_P(PSTR("     "), false);
    oled_write_P(PSTR("     "), false);

    oled_write_P(titles[1], false);
    oled_write_P(PSTR("     "), false);
    switch (biton32(default_layer_state)) {
        /* case _MAC: */
        /*     oled_write_P(PSTR("MAC  "), false); */
        /*     break; */
        case _QWERTY:
            oled_write_P(PSTR("QWRTY"), false);
            break;
    }
    oled_write_P(PSTR("     "), false);
    oled_write_P(PSTR("     "), false);
    oled_write_P(PSTR("     "), false);

    static const char PROGMEM lock_icons[4][3] = {
        {0x20,0x20,0}, // NONE
        {0x99,0x20,0}, // NUM
        {0xb9,0x20,0}, // CAPS
        {0xd9,0x20,0} }; // SCROLL

    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(titles[0], false);
    oled_write_P(PSTR("     "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK)    ? lock_icons[1] : lock_icons[0], false);
    oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK)   ? lock_icons[2] : lock_icons[0], false);
    oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? lock_icons[3] : lock_icons[0], false);
}


void oled_task_user(void) {
    if (is_master) {
        render_logo();
        /* render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc) */
    } else {
        render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        /* render_logo(); */
        /* oled_scroll_left();  // Turns on scrolling */
    }
}
#endif//OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case EPRM:
      if (record->event.pressed) {
          eeconfig_init();
      }
      return false;
      break;
  }
  return true;
}
