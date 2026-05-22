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
 * Layer 4: full keymap in [NEO_4] (see keymap.c).
 *
 * Fast typing (e.g. Mod3 + ? then Enter) can release MO(NEO_3) before the
 * character key; cleanup must run on key release even after leaving NEO_3.
 */

static uint8_t neo3_injection_count = 0;
static bool    neo3_shift_added     = false;

static void neo3_injection_reset(void) {
    unregister_code(KC_ROPT);
    if (neo3_shift_added) {
        unregister_code(KC_LSFT);
        neo3_shift_added = false;
    }
}

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
    if (!is_neo_injectable(keycode)) {
        return true;
    }

    if (!record->event.pressed) {
        if (neo3_injection_count == 0) {
            return true;
        }

        unregister_code16(keycode);
        neo3_injection_count--;
        if (neo3_injection_count == 0) {
            neo3_injection_reset();
        }

        return false;
    }

    if (get_highest_layer(layer_state) != NEO_3) {
        return true;
    }

    if (neo3_injection_count == 0) {
        register_code(KC_ROPT);
        if (get_mods() & MOD_MASK_SHIFT) {
            register_code(KC_LSFT);
            neo3_shift_added = true;
        }
    }

    register_code16(keycode);
    neo3_injection_count++;

    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (!layer_state_cmp(state, (1UL << NEO_3))) {
        neo3_injection_count = 0;
        neo3_injection_reset();
    }

    return state;
}

bool process_record_neo2_mac(uint16_t keycode, keyrecord_t *record) {
    if (!process_neo3_modifier(keycode, record)) {
        return false;
    }

    return true;
}
