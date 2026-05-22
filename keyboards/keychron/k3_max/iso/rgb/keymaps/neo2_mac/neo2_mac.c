/* Copyright 2026
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include "neo2_mac.h"

/*
 * Tier-B Neo2 on macOS without Karabiner:
 *
 * - Layers 1–2: macOS "Deutsch (Neo 2)" + NE_* key positions in MAC_BASE.
 * - Layer 3: MO(NEO_3) on Mod3 keys; firmware holds KC_ROPT while keys are pressed.
 * - Layer 4: MO(NEO_4) on Mod4 keys; firmware holds KC_RCMD while keys are pressed.
 *
 * This mirrors the common Karabiner simple remaps (caps/extra → right_option,
 * Mod4 → right_command) so the system Neo2 layout driver produces layers 3–4.
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

static bool process_neo_modifier_layer(uint8_t layer, uint16_t keycode, keyrecord_t *record, uint8_t mod_key) {
    if (get_highest_layer(layer_state) != layer) {
        return true;
    }

    if (!is_neo_injectable(keycode)) {
        return true;
    }

    if (record->event.pressed) {
        register_code(mod_key);
        if (get_mods() & MOD_MASK_SHIFT) {
            register_code(KC_LSFT);
        }
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
        if (get_mods() & MOD_MASK_SHIFT) {
            unregister_code(KC_LSFT);
        }
        unregister_code(mod_key);
    }

    return false;
}

bool process_record_neo2_mac(uint16_t keycode, keyrecord_t *record) {
    if (!process_neo_modifier_layer(NEO_3, keycode, record, KC_ROPT)) {
        return false;
    }

    if (!process_neo_modifier_layer(NEO_4, keycode, record, KC_RCMD)) {
        return false;
    }

    return true;
}
