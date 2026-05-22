/* Copyright 2026
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include "neo2_mac.h"

/*
 * Layer 3: inject KC_ROPT + key so macOS Neo2 driver produces layer-3 symbols.
 *
 * Layer 4: full keymap in [NEO_4] (see keymap.c). Injecting KC_RCMD does not work
 * on macOS without Karabiner — it triggers normal Command shortcuts instead.
 */

static bool is_neo_injectable(uint16_t keycode) {
    if (!IS_QK_BASIC(keycode)) {
        return false;
    }

    switch (keycode) {
        case KC_ESC:
        case KC_TAB:
        case KC_BSPC:
        case KC_ENT:
        case KC_LSFT:
        case KC_RSFT:
        case KC_LCTL:
        case KC_RCTL:
        case KC_LALT:
        case KC_RALT:
        case KC_LGUI:
        case KC_RGUI:
        case KC_SPC:
        case KC_PGUP:
        case KC_PGDN:
        case KC_HOME:
        case KC_END:
        case KC_UP:
        case KC_DOWN:
        case KC_LEFT:
        case KC_RGHT:
            return false;
        default:
            return true;
    }
}

static bool process_neo3_modifier(uint16_t keycode, keyrecord_t *record) {
    if (get_highest_layer(layer_state) != NEO_3) {
        return true;
    }

    if (!is_neo_injectable(keycode)) {
        return true;
    }

    if (record->event.pressed) {
        register_code(KC_ROPT);
        if (get_mods() & MOD_MASK_SHIFT) {
            register_code(KC_LSFT);
        }
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
        if (get_mods() & MOD_MASK_SHIFT) {
            unregister_code(KC_LSFT);
        }
        unregister_code(KC_ROPT);
    }

    return false;
}

bool process_record_neo2_mac(uint16_t keycode, keyrecord_t *record) {
    if (!process_neo3_modifier(keycode, record)) {
        return false;
    }

    return true;
}
