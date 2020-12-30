/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE_WIN,  // default win layer
    BASE_OSX,  // default osx layer
    SYMB,  // symbols
    MDIA,  // media keys
};

enum custom_keycodes {
    VRSN = ML_SAFE_RANGE,
    SWITCH_OSX,
    SWITCH_WIN,
    TEST
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE_WIN] = LAYOUT_moonlander(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LEFT,           KC_RGHT, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_DEL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    SWITCH_OSX,        TG(SYMB), KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HYPR,           KC_MEH,  KC_H,    KC_J,    KC_K,    KC_L,    LT(MDIA, KC_SCLN), LGUI_T(KC_QUOT),
        KC_LSFT, LCTL_T(KC_Z),KC_X,KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  RCTL_T(KC_SLSH), KC_RSFT,
    LT(SYMB,KC_GRV),WEBUSB_PAIR,A(KC_LSFT),KC_LEFT, KC_RGHT,  LALT_T(KC_APP),    RCTL_T(KC_ESC),   KC_UP,   KC_DOWN, KC_LEFT, KC_RIGHT, MO(SYMB),
                                            KC_BSPC,  KC_TAB, KC_LGUI,           KC_LALT,  KC_ENT,  KC_SPC
    ),

    [BASE_OSX] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, SWITCH_WIN,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, LGUI_T(KC_Z),_______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,           _______,      _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [SYMB] = LAYOUT_moonlander(
        VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______,           _______, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  _______,           _______, KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, _______,
        _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                             KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, _______,
        EEP_RST, _______, _______, _______, _______,          RGB_VAI,           RGB_TOG,          RGB_SPI, KC_DOT,  KC_0,    KC_EQL,  _______,
                                            RGB_HUD, RGB_VAD, RGB_HUI, TOGGLE_LAYER_COLOR,RGB_MOD, _______
    ),

    [MDIA] = LAYOUT_moonlander(
        LED_LEVEL,_______,_______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, RESET,
        _______, _______, _______, KC_MS_U, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,           _______, _______, _______, _______, _______, _______, KC_MPLY,
        _______, _______, _______, _______, _______, _______,                             _______, _______, KC_MPRV, KC_MNXT, _______, _______,
        _______, _______, _______, KC_BTN1, KC_BTN2,         _______,            _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        case SWITCH_OSX:
            set_single_persistent_default_layer(BASE_OSX);
            return false;
        case SWITCH_WIN:
            set_single_persistent_default_layer(BASE_WIN);
            return false;
        case TEST:
            SEND_STRING ("YOU HAVE PRESSED THE TEST KEY");
            return false;
        }
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    ML_LED_1(false);
    ML_LED_2(false);
    ML_LED_3(false);
    ML_LED_4(false);
    ML_LED_5(false);
    ML_LED_6(false);

    switch (get_highest_layer(state)) {
        case BASE_WIN:
            ML_LED_1(1);
            break;
        case BASE_OSX:
            ML_LED_1(1);
            ML_LED_2(1);
            break;
        case SYMB:
            ML_LED_3(1);
            break;
        case MDIA:
            ML_LED_6(1);
            break;
        default:
            break;
    }

    return state;
}
