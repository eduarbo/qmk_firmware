// Copyright 2023 Eduardo Ruiz Macias (@eduarbo) <eduarbo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "eduarbo.h"
#include "version.h"

/**
 * @brief Main user keycode handler
 *
 * This handles all of the keycodes for the user, including calling feature handlers.
 *
 * @param keycode Keycode from matrix
 * @param record keyrecord_t data structure
 * @return true Continue processing keycode and send to host
 * @return false Stop process keycode and do not send to host
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mods    = get_mods();
    const uint8_t os_mods = get_oneshot_mods();
    /* const uint8_t oneshot_mods = get_oneshot_mods(); */

    switch (keycode) {
        case VRSN: // Prints firmware version
            if (record->event.pressed) {
                send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
            }
            break;

        case SPC_RSFT:
            if (IS_LAYER_ON(_SYMBOLS) && record->tap.count && record->event.pressed) {
                tap_code16(S(KC_SPC));
                return false; // Return false to ignore further processing of key
            }
            break;

        case ESC_SUPR: {
            if (record->tap.count && record->event.pressed) {
                // on tap
                if (IS_LAYER_ON(_SYMBOLS)) {
                    tap_code16(S(KC_ESC));
                    return false;
                } else if (os_mods && !has_oneshot_mods_timed_out()) {
                    // Clear one shot mods when pressing ESC
                    clear_oneshot_mods();
                    unregister_mods(os_mods);
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
                if ((mods & SUPER_MOD) == SUPER_MOD) {
                    if (IS_LAYER_ON(_WINDOWS)) {
                        set_oneshot_mods(os_mods | MOD_BIT(KC_RGUI));
                    } else {
                        set_oneshot_mods(os_mods | MOD_BIT(KC_RALT));
                    }
                    return false;
                }
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

        case ENT_RCTL:
        case ENT_RGUI: {
#ifdef OLED_ENABLE
            is_calm = (record->event.pressed) ? true : false;
#endif

            if (record->tap.count && record->event.pressed) {
                // on tap
                if ((mods & SUPER_MOD) == SUPER_MOD) {
                    if (keycode == ENT_RCTL) {
                        set_oneshot_mods(os_mods | MOD_BIT(KC_RCTL));
                    } else if (keycode == ENT_RGUI) {
                        set_oneshot_mods(os_mods | MOD_BIT(KC_RGUI));
                    }
                    return false;
                } else if (IS_LAYER_ON(_SYMBOLS)) {
                    tap_code16(S(KC_ENT));
                    return false;
                }
            } else if (record->event.pressed) {
                // on hold keydown
                if ((mods & SUPER_MOD) == SUPER_MOD) {
                    unregister_mods(SUPER_MOD);
                    layer_on(_ADJUST);
                    return false;
                } else if (IS_LAYER_ON(_GAMEPAD) && ((mods & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT))) {
                    unregister_code(KC_LALT);
                    layer_on(_ADJUST);
                    return false;
                }
            } else {
                // oh hold keyup
                if (IS_LAYER_ON(_ADJUST)) {
                    layer_off(_ADJUST);
                    if (IS_LAYER_ON(_GAMEPAD)) {
                        register_code(KC_LALT);
                    } else {
                        register_mods(SUPER_MOD);
                    }
                    return false;
                }
            }
            break;
        }

        case ACC_RALT:
        case ACC_RCTL: {
            if (record->tap.count && record->event.pressed) {
                // on tap
                if ((mods & SUPER_MOD) == SUPER_MOD) {
                    if (keycode == ACC_RALT) {
                        set_oneshot_mods(os_mods | MOD_BIT(KC_RALT));
                    } else if (keycode == ACC_RCTL) {
                        set_oneshot_mods(os_mods | MOD_BIT(KC_RCTL));
                    }
                    return false;
                } else if ((mods & MOD_BIT(KC_RSFT)) == MOD_BIT(KC_RSFT)) {
                    caps_word_toggle();
                } else {
                    if (keycode == ACC_RALT) {
                        // Mod-Tap AltGr to simulate common accent behavior and allow typing `ñ` with the same key:
                        // Type accent key, then the vowel to be accented. If `n` is pressed, returns `ñ`
                        set_oneshot_mods(os_mods | MOD_BIT(KC_ALGR));
                    } else if (keycode == ACC_RCTL) {
                        tap_code16(ACCENT);
                    }
                }
                return false;

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
