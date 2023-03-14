// Copyright 2023 Eduardo Ruiz Macias (@eduarbo) <eduarbo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE, // Prints QMK Firmware and board info
};

#define SUPER_MOD (MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL))
#define HYPER_MOD (MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT))

#define ACCENT A(KC_E)

#define SPC_RSFT MT(MOD_RSFT, KC_SPC)
#define TAB_SYMB LT(_SYMBOLS, KC_TAB)

#define ESC_SUPR MT(SUPER_MOD, KC_ESC)

#define ENT_RCTL MT(MOD_RCTL, KC_ENT)
#define ENT_RGUI MT(MOD_RGUI, KC_ENT)

// FIXME Even that I'm re-binding the key on Tap with process_record_user() to
// an advanced keycode, I use Mod-Tap here because I wasn't able to intercept
// the key if I used a basic keycode instead
#define ACC_RCTL MT(MOD_RCTL, KC_ESC)
#define ACC_RALT MT(MOD_RALT, KC_ESC)

#define OS_RCTL OSM(MOD_RALT)
#define OS_RGUI OSM(MOD_RGUI)

#define TG_WIN2 TG(_WINDOWS)
#define TG_GAME TG(_GAMEPAD)

#define TG_MODS OS_TOGG
