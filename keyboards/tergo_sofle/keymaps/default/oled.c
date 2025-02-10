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

#include "oled.h"
#include "art/moon_tergo.h"
#include "layers.h"

#define TERGO_ENABLE_ANIMATION

#ifdef OLED_ENABLE

const uint16_t TIME_BETWEEN_FRAMES_ANIMATION = OLED_UPDATE_INTERVAL; // Deve ser 50ms para teclados split por default
const uint16_t TIME_BETWEEN_LOOPING_ANIMATION = 7000;

uint8_t frame_count = 1;
uint16_t time_between_frames = 0;
uint16_t key_timer;
bool timer_initialized = false;
bool refresh_logo_right_away = false;

extern bool is_oled_enabled;
extern bool print_layer_number_instead_of_text;

void suspend_power_down_user(void) {
    oled_off();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master() || (get_highest_layer(layer_state) == _ADJUST) ) {
        return OLED_ROTATION_270;
    }
    return OLED_ROTATION_270;
    return rotation;
}

void render_logo(void) {
    //ToDo Tergo: adicionar animacao de cometa

    #ifndef TERGO_ENABLE_ANIMATION

    oled_write_raw_P(moon_tergo[0], sizeof(moon_tergo[0]));

    #else

    if (!timer_initialized) {
        key_timer = timer_read();
        timer_initialized = true;
    }

    if (frame_count == 0) {
        time_between_frames = TIME_BETWEEN_LOOPING_ANIMATION;
    }
    else {
        time_between_frames = TIME_BETWEEN_FRAMES_ANIMATION;
    }

    if ((timer_elapsed(key_timer) > time_between_frames) || (refresh_logo_right_away == true)) {
        refresh_logo_right_away = false;
        oled_write_raw_P(moon_tergo[frame_count], sizeof(moon_tergo[frame_count]));

        frame_count = (frame_count + 1) % TERGO_ANIMATION_NUM_OF_FRAMES;
        key_timer = timer_read();
    }

    #endif
}

#define PERCENTAGE_STR_SIZE 5

char percentage_str[PERCENTAGE_STR_SIZE];

void print_percentage_str(uint8_t value, uint8_t max_value) {
    uint8_t percentage = (value * 100) / max_value;

    snprintf(percentage_str, PERCENTAGE_STR_SIZE, "%3d%%", percentage);
    oled_write(percentage_str, false);
    //oled_write_P(PSTR("%"), false);
}

// Showed if you have RGB and when in _ADJUST layer
void render_adjust(uint8_t col, uint8_t line) {
    oled_set_cursor(col, line);

    oled_write_ln_P(PSTR("v1.06"), false);

    line += 2;
    oled_set_cursor(col, line);

    oled_write_P(PSTR(" RGB "), false);
    line += 2;
    oled_set_cursor(col, line);

    #ifndef RGB_MATRIX_ENABLE

    oled_write_P(PSTR(" No  "), false);

    #else

    bool    enabled = rgb_matrix_is_enabled();
    uint8_t mode    = rgb_matrix_get_mode();
    HSV     hsv     = rgb_matrix_get_hsv();
    uint8_t speed   = rgb_matrix_get_speed();

    if (!enabled) {
        oled_write_P(PSTR(" OFF "), false);
    }
    else {
        oled_write_P(PSTR(" ON  "), false);
    }

    line += 2;
    oled_set_cursor(col, line);

    oled_write_P(PSTR("B"), false);
    print_percentage_str(hsv.v, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    line += 2;
    oled_set_cursor(col, line);

    oled_write_P(PSTR("M"), false);
    oled_advance_char();
    oled_write(get_u8_str(mode, ' '), false);
    line += 2;
    oled_set_cursor(col, line);

    oled_write_P(PSTR("S"), false);
    print_percentage_str(hsv.s, 255);
    line += 2;
    oled_set_cursor(col, line);

    oled_write_P(PSTR("H"), false);
    oled_advance_char();
    oled_write(get_u8_str(hsv.h, ' '), false);
    line += 2;
    oled_set_cursor(col, line);

    oled_write_P(PSTR("P"), false);
    print_percentage_str(speed, 255);
    #endif
}


char buffer[9];

static void print_layer_number(uint8_t layer) {
    snprintf(buffer, sizeof(buffer), "Lyr%2d\n", layer);
    oled_write(buffer, false);
}


static void print_status_narrow(void) {
    // Print current mode
    oled_write_ln_P(PSTR("Tergo"), false);
    oled_write_ln_P(PSTR(""), false);

    oled_write_ln_P(PSTR("MODE "), false);

    if(print_layer_number_instead_of_text == true) {
        print_layer_number(get_highest_layer(default_layer_state));
    }
    else {
        switch (get_highest_layer(default_layer_state)) {
            case _BASIC:
                oled_write_ln_P(PSTR("Basic"), false);
                break;
            case _ADEPT:
                oled_write_ln_P(PSTR("Adept"), false);
                break;
            default:
                oled_write_ln_P(PSTR("Other"), false);
                break;
        }
    }
    oled_write_P(PSTR("\n"), false);

    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);

    if(print_layer_number_instead_of_text == true) {
        print_layer_number(get_highest_layer(layer_state));
    }
    else {
        switch (get_highest_layer(layer_state)) {
            case _BASIC:
                oled_write_ln_P(PSTR("Base "), false);
                break;
            case _ADEPT:
                oled_write_ln_P(PSTR("Base "), false);
                break;
            case _CUSTOM:
                oled_write_ln_P(PSTR("Base "), false);
                break;
            case _SYMB_AND_NAV:
                oled_write_ln_P(PSTR("SymNv"), false);
                break;
            case _ADJUST:
                oled_write_ln_P(PSTR("Confg"), false);
                break;
            case _MEDIA:
                oled_write_ln_P(PSTR("Media"), false);
                break;
            case _NUMPAD:
                oled_write_ln_P(PSTR("NumPd"), false);
                break;
            case _MOUSE:
                oled_write_ln_P(PSTR("Mouse"), false);
                break;
            default:
                print_layer_number(get_highest_layer(layer_state));
                break;
        }
    }

    oled_write_ln_P(PSTR(""), false);
    led_t led_usb_state = host_keyboard_led_state();

    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:
            oled_write_P(PSTR("NumLk"), led_usb_state.num_lock);
            break;
        case _MOUSE:
            oled_write_P(PSTR("ScrLk"), led_usb_state.scroll_lock);
            break;
        default:
            oled_write_P(PSTR("CpsLk"), led_usb_state.caps_lock || is_caps_word_on());
            break;
    }
}

bool oled_task_user(void) {

    if (is_keyboard_master()) {
        // master side forces OLEDs off if variable is false
        if (!is_oled_enabled) {
            oled_off();
            return false; // do nothing else
        }
        oled_on();
    }
    if(!is_oled_on()) {
        return false;
    }

    if (is_keyboard_master()) {
        print_status_narrow();
    }
    else {
        if (get_highest_layer(layer_state) == _ADJUST) {
            oled_clear();
            render_adjust(0, 0);
            refresh_logo_right_away = true;
            return false;
        }

        render_logo();
    }
    return false;
}

#endif
