// Copyright 2023 Eduardo Ruiz Macias (@eduarbo) <eduarbo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

#include "process_records.h"

#ifdef OLED_ENABLE
#    include "oled_setup.h"
#endif

/* Define layer names */
enum userspace_layers {
    _BASE             = 0,
    _FKEYS,
    _WINDOWS,
    _ADJUST,
    _SYMBOLS,
    _GAMEPAD,
};
