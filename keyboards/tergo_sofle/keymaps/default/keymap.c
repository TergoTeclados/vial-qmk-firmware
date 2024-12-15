/* Copyright 2024 Tergo Teclados
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

//#define PERSIST_DEFAULT_LAYER_TOGGLE // ToDo Tergo: a ser testado

#include "layers.h"
#include "oled.h"

#ifdef VIAL_ENABLE // Required by Vial documentations to show custom keycodes
    #define CUSTOM_KC_START_VALUE QK_KB_0
#else
    #define CUSTOM_KC_START_VALUE SAFE_RANGE
#endif

enum custom_keycodes {
    KC_TG_OLED = CUSTOM_KC_START_VALUE,
    KC_TEXT_TYPE,
    KC_TG_CAPS_WORD
};

#ifdef ENCODER_MAP_ENABLE
// If there is an encoder, for each layer should be defined keymaps
// rev0 only
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [ 0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
    [ 1] = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [ 2] = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [ 3] = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [ 4] = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [ 5] = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [ 6] = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [ 7] = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
};
#endif

// Keymaps for each layer. The visualization should be easier in Vial interface.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASIC] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, MO(_MEDIA),       MO(_ADJUST), KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,  KC_ENT,
            MO(_NUMPAD), KC_LGUI, KC_LALT, KC_SPC, MO(_SYMB_AND_NAV),  KC_ENT, KC_BSPC, KC_DEL, KC_RGUI, KC_RCTL
),

[_ADEPT] = LAYOUT(
  _______,   _______,   _______,    _______,    _______,    _______,                     _______,    _______,    _______,    _______,    _______,  _______,
  _______,   _______,   _______,    _______,    _______,    _______,                     _______,    _______,    _______,    _______,    _______,  _______,
  _______,  LGUI_T(KC_A),   LALT_T(KC_S),    LCTL_T(KC_D),    LSFT_T(KC_F),    _______, _______,    RSFT_T(KC_J),    RCTL_T(KC_K),    LALT_T(KC_L),    RGUI_T(KC_SCLN),  _______,
  _______,  _______,   _______,    _______,    _______,    _______, _______,     _______,_______,    _______, _______,  _______, _______,  _______,
                 _______ , _______, _______, LT(_MOUSE, KC_SPC), LT(_SYMB_AND_NAV, KC_TAB),        _______, _______, _______, _______, _______
),

[_CUSTOM] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, MO(_MEDIA),       MO(_ADJUST), KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,  KC_ENT,
            MO(_NUMPAD), KC_LGUI, KC_LALT, KC_SPC, MO(_SYMB_AND_NAV),  KC_ENT, KC_BSPC, KC_DEL, KC_RGUI, KC_RCTL
),

[_SYMB_AND_NAV] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                          KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  _______,    KC_GRV,  KC_CIRCUMFLEX,  KC_PLUS,    KC_LCBR,    KC_RCBR,            KC_PGUP, KC_HOME,   KC_UP, KC_END, KC_INS,  KC_F12,
  _______,  KC_TILD,   KC_EQUAL, KC_MINS,  KC_LPRN, KC_RPRN,                     KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_PSCR, XXXXXXX,
  _______,  KC_BSLS, KC_PIPE, KC_UNDS, KC_LBRC, KC_RBRC, _______,       _______, KC_CAPS, LCTL(KC_LEFT), KC_ESC, LCTL(KC_RGHT), KC_BRK, XXXXXXX,
                       _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),

// You can try it if you want a separated layer for navigation keys
// [_NAV] = LAYOUT(
//   _______, _______ , _______ , _______ , LALT(KC_F4), _______,                           _______,  _______  , KC_F8,  _______ ,  _______ , _______,
//   _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP, KC_HOME,   KC_UP, KC_END, XXXXXXX, _______,
//   _______, KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT, XXXXXXX,                       KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  XXXXXXX, _______,
//   _______, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX,  _______,       _______, _______,  LCTL(KC_LEFT), KC_ESC, LCTL(KC_RGHT), XXXXXXX, _______,
//                          _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
// ),

[_ADJUST] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ , _______,
  RGB_SPI,  RGB_VAI,  RGB_SAI,   RGB_HUI,  RGB_MOD, RGB_TOG,                        XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, _______,
  RGB_SPD, RGB_VAD,  RGB_SAD,  RGB_HUD,  RGB_RMOD, KC_TG_OLED,                       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, _______,
  _______, XXXXXXX, DF(_BASIC), DF(_ADEPT), DF(_CUSTOM), KC_TEXT_TYPE,  _______,       _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, _______,
                         _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),

[_MEDIA] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ , _______,
  _______, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                       XXXXXXX,  KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP,  XXXXXXX, _______,
  _______, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______,       _______, XXXXXXX, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK,   XXXXXXX, _______,
                         _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),

[_NUMPAD] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                      XXXXXXX,  KC_NUM  , KC_PSLS,  KC_PAST ,  KC_PMNS , _______,
  _______, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                        XXXXXXX, KC_P7,   KC_P8, KC_P9, KC_PPLS, _______,
  _______, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                        XXXXXXX,  KC_P4, KC_P5, KC_P6,  KC_PPLS, _______,
  _______, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______,       _______,XXXXXXX, KC_P1, KC_P2, KC_P3,   KC_PENT, _______,
                         _______, _______, _______, _______, _______,       _______, _______, KC_P0, KC_P0, KC_PDOT
),

[_MOUSE] = LAYOUT(
  _______,   _______,   _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,  _______,
  _______,   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                KC_WH_U,    XXXXXXX,    KC_MS_U,    XXXXXXX,    XXXXXXX,  _______,
  _______,  KC_LGUI,    KC_LALT,  KC_LCTL,  KC_LSFT,    XXXXXXX,                    KC_WH_D,    KC_MS_L,    KC_MS_D,    KC_MS_R,    XXXXXXX,  _______,
  _______,  LCTL(KC_Z),    LCTL(KC_X),     LCTL(KC_C),    LCTL(KC_V), XXXXXXX,      _______,     XXXXXXX,XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  _______,
                             _______ , _______, _______, _______, _______,              KC_BTN2, KC_BTN1, KC_BTN3, _______, _______
)
};

// Custom code to turn oled on and off
#ifdef OLED_ENABLE
bool     is_oled_enabled = true, is_oled_locked = false;
uint32_t oled_timer                             = 0;
uint8_t temp_oled_brightness = OLED_BRIGHTNESS;

bool print_layer_number_instead_of_text = false;

void oled_timer_reset(void) {
    oled_timer = timer_read32();
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        is_oled_enabled = is_oled_locked ? false : !(timer_elapsed32(oled_timer) > OLED_TIMEOUT);
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

#ifdef OLED_ENABLE
    // Custom code to turn oled on and off
    if (record->event.pressed) {
        oled_timer_reset();
    }
#endif

  switch (keycode) {
    case KC_TG_CAPS_WORD:
        if (record->event.pressed) {
            caps_word_toggle();
        }
        return false;

    #ifdef OLED_ENABLE
    case KC_TEXT_TYPE:
      if (record->event.pressed) {
        print_layer_number_instead_of_text = !print_layer_number_instead_of_text; // Toggles
      }
      return false;

    #define OLED_MAX_BRIGHTNESS 255 // Default. Do not change

    case KC_TG_OLED:
      // Custom code to turn oled on and off
      if (record->event.pressed) {
            is_oled_locked = !is_oled_locked;
            if (is_oled_locked) {
                oled_off();
            }
      }
      return false;
    #endif

    default:
      return true; // Process all other keycodes normally
  }
}

// These configurations do not work with Vial, but do work with default QMK (with VIA interface).
// If you want to define tap-hold with different behaviors and tapping terms, try default QMK.
#ifndef VIAL_ENABLE

// Custom tapping term for different keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    const uint16_t _BIGGER_TAPPING_TERM = 300;

    switch (keycode) {
        default:
            return TAPPING_TERM;
    }
}


bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return false;
    }
}
#endif
