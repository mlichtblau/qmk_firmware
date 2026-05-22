/* Copyright 2026
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include QMK_KEYBOARD_H

enum neo2_mac_layers {
    MAC_BASE,
    MAC_FN,
    NEO_3,
    NEO_4,
    WIN_BASE,
    WIN_FN,
};

bool            process_record_neo2_mac(uint16_t keycode, keyrecord_t *record);
layer_state_t layer_state_set_user(layer_state_t state);
