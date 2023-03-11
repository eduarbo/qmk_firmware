// Copyright 2023 Eduardo Ruiz Macias (@eduarbo) <eduarbo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE, // Prints QMK Firmware and board info
};

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
#define TG_WIN2 TG(_WINDOWS)
#define TG_GAME TG(_GAMEPAD)

#define TG_MODS OS_TOGG
