#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
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
enum crkbd_layers {
  _QWERTY,
  _MAC,
  _SHIFTED,
  _SYMB,
  _NAV,
  _ADJUST
};

enum custom_keycodes {
  MAC = SAFE_RANGE,
  QWERTY,
  EPRM,
  SYMB,
  NAV,
  ADJUST,
  RGBRST
};

#define KC_      KC_TRNS
#define KC_XXX   KC_NO
#define KC_RST   RESET
#define KC_EPRM  EPRM  // Useful to unfuck the RGB Underglow
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_LRMOD RGB_RMOD
#define KC_VTOG  VLK_TOG
#define KC_NAV   MO(_NAV)
#define KC_ADJ   MO(_ADJUST)

// Spanish
#define KC_ACCNT A(KC_E)
#define KC_NTILD A(KC_N)
#define KC_OEXLM A(KC_1)
#define KC_OQUS  S(A(KC_QUES))

// Media
#define KC_MUT  KC__MUTE
#define KC_VDW  KC__VOLDOWN
#define KC_VUP  KC__VOLUP

// One shot modifiers
/* #define KC_OS_LSFT     SFT_T(OSL(_ADJUST)) */
/* #define KC_OS_LSFT     OSM(MOD_LSFT) */
#define KC_OS_LSFT     LM(_NAV, MOD_LSFT)
#define KC_OS_SHFT     OSL(_SHIFTED)
#define KC_OS_SYMB     OSL(_SYMB)
#define KC_OS_NAV      OSL(_NAV)

// Mod-Tap
#define KC_CTL_ENT  CTL_T(KC_ENT)
#define KC_ALT_ESC  ALT_T(KC_ESC)
#define KC_GUI_SPC  GUI_T(KC_SPC)

#define KC_GUI_ENT  GUI_T(KC_ENT)
#define KC_SYM_SPC  LT(_SYMB, KC_SPC)
#define KC_SFT_ESC  SFT_T(KC_ESC)

// Toggles
#define KC_T_SYM    TG(_SYMB)
#define KC_T_ADJ    TG(_ADJUST)

// Shifted
#define KC_S_Q   S(KC_Q)
#define KC_S_W   S(KC_W)
#define KC_S_E   S(KC_E)
#define KC_S_R   S(KC_R)
#define KC_S_T   S(KC_T)
#define KC_S_Y   S(KC_Y)
#define KC_S_U   S(KC_U)
#define KC_S_I   S(KC_I)
#define KC_S_O   S(KC_O)
#define KC_S_P   S(KC_P)
#define KC_S_A   S(KC_A)
#define KC_S_S   S(KC_S)
#define KC_S_D   S(KC_D)
#define KC_S_F   S(KC_F)
#define KC_S_G   S(KC_G)
#define KC_S_H   S(KC_H)
#define KC_S_J   S(KC_J)
#define KC_S_K   S(KC_K)
#define KC_S_L   S(KC_L)
#define KC_S_Z   S(KC_Z)
#define KC_S_X   S(KC_X)
#define KC_S_C   S(KC_C)
#define KC_S_V   S(KC_V)
#define KC_S_B   S(KC_B)
#define KC_S_N   S(KC_N)
#define KC_S_M   S(KC_M)
#define KC_S_GRV S(KC_GRV)
#define KC_S_BSP S(KC_BSPC)
#define KC_S_TAB S(KC_TAB)
#define KC_SRBRC S(KC_RBRC)
#define KC_SLBRC S(KC_LBRC)
#define KC_SSCLN S(KC_SCLN)
#define KC_SQUOT S(KC_QUOTE)
#define KC_SSLSH S(KC_SLASH)
#define KC_SDOT  S(KC_DOT)
#define KC_SCOMM S(KC_COMMA)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAC] = LAYOUT_kc( \
  //┌─────┬─────┬─────┬─────┬─────┬─────┐              ┌─────┬─────┬─────┬─────┬─────┬─────┐
      TAB ,  Q  ,  W  ,  E  ,  R  ,  T  ,                 Y  ,  U  ,  I  ,  O  ,  P  , LBRC,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
      CAPS,  A  ,  S  ,  D  ,  F  ,  G  ,                 H  ,  J  ,  K  ,  L  , SCLN,QUOTE,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
      LSFT,  Z  ,  X  ,  C  ,  V  ,  B  ,                 N  ,  M  ,COMMA, DOT ,SLASH, RSFT,\
  //└─────┴─────┼─────┴───┬─┴─────┴─┬───┴─────┐  ┌─────┴───┬─┴─────┴─┬───┴─────┼────┬┴─────┘
                    LALT  ,   LCMD  ,   SPC   ,      SPC   ,   RCMD  ,   RALT   \
  //            └─────────┴─────────┴─────────┘  └─────────┴─────────┴─────────┘
  ),

  [_QWERTY] = LAYOUT_kc( \
  //┌─────┬─────┬─────┬─────┬─────┬─────┐              ┌─────┬─────┬─────┬─────┬─────┬─────┐
      TAB ,  Q  ,  W  ,  E  ,  R  ,  T  ,                 Y  ,  U  ,  I  ,  O  , LBRC, RBRC,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
      BSPC,  A  ,  S  ,  D  ,  F  ,  G  ,                 H  ,  J  ,  K  ,  L  ,  P  , SCLN,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
      GRV ,  Z  ,  X  ,  C  ,  V  ,  B  ,                 N  ,  M  ,COMMA, DOT ,SLASH,QUOTE,\
  //└─────┴─────┼─────┴───┬─┴─────┴─┬───┴─────┐  ┌─────┴───┬─┴─────┴─┬───┴─────┼────┬┴─────┘
                  CTL_ENT , OS_SYMB , GUI_SPC ,    GUI_SPC , OS_SHFT , ALT_ESC  \
  //            └─────────┴─────────┴─────────┘  └─────────┴─────────┴─────────┘
  ),

    [_SHIFTED] = LAYOUT_kc( \
  //┌─────┬─────┬─────┬─────┬─────┬─────┐              ┌─────┬─────┬─────┬─────┬─────┬─────┐
     S_TAB, S_Q , S_W , S_E , S_R , S_T ,                S_Y , S_U , S_I , S_O ,SLBRC,SRBRC,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
     S_BSP, S_A , S_S , S_D , S_F , S_G ,                S_H , S_J , S_K , S_L , S_P ,SSCLN,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
     S_GRV, S_Z , S_X , S_C , S_V , S_B ,                S_N , S_M ,SCOMM,SDOT ,SSLSH,SQUOT,\
  //└─────┴─────┼─────┴───┬─┴─────┴─┬───┴─────┐  ┌─────┴───┬─┴─────┴─┬───┴─────┼────┬┴─────┘
                          ,   NAV   ,         ,            ,  OS_NAV ,          \
  //            └─────────┴─────────┴─────────┘  └─────────┴─────────┴─────────┘
  ),


  [_SYMB] = LAYOUT_kc( \
  //┌─────┬─────┬─────┬─────┬─────┬─────┐              ┌─────┬─────┬─────┬─────┬─────┬─────┐
          , EXLM,  AT , HASH, DLR , PERC,                CIRC, AMPR, ASTR, LPRN, RPRN, MINS,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
          ,  1  ,  2  ,  3  ,  4  ,  5  ,                 6  ,  7  ,  8  ,  9  ,  0  , PLUS,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
      F13 ,OEXLM, PIPE, UNDS, EQL , BSLS,               NTILD,ACCNT,     ,     ,     , OQUS,\
  //└─────┴─────┼─────┴───┬─┴─────┴─┬───┴─────┐  ┌─────┴───┬─┴─────┴─┬───┴─────┼────┬┴─────┘
                          ,  OS_NAV ,         ,            ,   NAV   ,          \
  //            └─────────┴─────────┴─────────┘  └─────────┴─────────┴─────────┘
  ),

  [_NAV] = LAYOUT_kc( \
  //┌─────┬─────┬─────┬─────┬─────┬─────┐              ┌─────┬─────┬─────┬─────┬─────┬─────┐
          , MUT , VDW,   UP , VUP , XXX ,                XXX , PGDN, PGUP, XXX , XXX , CAPS,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
          , BRMD, LEFT, DOWN, RGHT, BRMU,                LEFT, DOWN,  UP , RGHT, XXX ,T_SYM,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
          , XXX , MRWD, MPLY, MFFD, XXX ,                XXX , END , HOME, XXX , XXX ,T_ADJ,\
  //└─────┴─────┼─────┴───┬─┴─────┴─┬───┴─────┐  ┌─────┴───┬─┴─────┴─┬───┴─────┼────┬┴─────┘
                          ,  LSFT   ,         ,            ,   LSFT  ,          \
  //            └─────────┴─────────┴─────────┘  └─────────┴─────────┴─────────┘
  ),

  [_ADJUST] = LAYOUT_kc( \
  //┌─────┬─────┬─────┬─────┬─────┬─────┐              ┌─────┬─────┬─────┬─────┬─────┬─────┐
          , F1  , F2  , F3  , F4  ,     ,                RST , LRST, LTOG, VTOG,     , CAPS,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
          , F5  , F6  , F7  , F8  ,     ,                LMOD, LHUI, LSAI, LVAI,     ,T_SYM,\
  //├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
          , F9  , F10 , F11 , F12 ,     ,               LRMOD, LHUD, LSAD, LVAD,     ,T_ADJ,\
  //└─────┴─────┼─────┴───┬─┴─────┴─┬───┴─────┐  ┌─────┴───┬─┴─────┴─┬───┴─────┼────┬┴─────┘
                          ,   ADJ   ,         ,            ,   ADJ   ,          \
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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // set_timelog();
  }

  switch (keycode) {
    case EPRM:
      if (record->event.pressed) {
          eeconfig_init();
      }
      return false;
      break;
    case MAC:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_MAC);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case KC_ALT_ESC:
        //Cancel one-shot mods and layers
        if (record->event.pressed && get_oneshot_mods() && !has_oneshot_mods_timed_out()) {
            clear_oneshot_mods();
            return false;
        }
        if (record->event.pressed && is_oneshot_layer_active()) {
            clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            return false;
        }
        return true;
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
  }
  return true;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
        /* return rotation; */
    }
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}


void render_status(void) {

    oled_write_P(PSTR("Layer"), false);
    switch (biton32(layer_state)) {
        case 0:
            oled_write_P(PSTR("Base "), false);
            break;
        case _SYMB:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjst"), false);
            break;
        default:
            oled_write_P(PSTR("Unkn "), false);
            break;
    }
    oled_write_P(PSTR("Lyout"), false);
    switch (biton32(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWRTY"), false);
            break;
    }

    uint8_t modifiers = get_mods();
    uint8_t one_shot = get_oneshot_mods();

    oled_write_P(PSTR("Mods:"), false);
    oled_write_P( (modifiers & MOD_MASK_SHIFT || one_shot & MOD_MASK_SHIFT) ? PSTR(" SFT ") : PSTR("     "), false);
    oled_write_P( (modifiers & MOD_MASK_CTRL  || one_shot & MOD_MASK_CTRL ) ? PSTR(" CTL ") : PSTR("     "), false);
    oled_write_P( (modifiers & MOD_MASK_ALT   || one_shot & MOD_MASK_ALT  ) ? PSTR(" ALT ") : PSTR("     "), false);
    oled_write_P( (modifiers & MOD_MASK_GUI   || one_shot & MOD_MASK_GUI  ) ? PSTR(" GUI ") : PSTR("     "), false);


    oled_write_P(PSTR("BTMGK"), false);

    if (keymap_config.swap_lalt_lgui) {
        oled_write_P(PSTR(" Win "), false);
    } else {
        oled_write_P(PSTR(" Mac "), false);
    }

    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK)    ? PSTR(" NUM ") : PSTR("     "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK)   ? PSTR(" CAPS") : PSTR("     "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR(" SCRL") : PSTR("     "), false);
}


void oled_task_user(void) {
    if (is_master) {
        render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_crkbd_logo();
        /* oled_scroll_left();  // Turns on scrolling */
    }
}
#endif
