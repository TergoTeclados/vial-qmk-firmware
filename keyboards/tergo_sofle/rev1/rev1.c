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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
  // Physical Layout
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //                                           ROWS
  // 11 12 21 22 31 32       32 31 22 21 12 11  0
  //    01    02    03       03    02    01
  // 10 13 20 23 30 33       33 30 23 20 13 10  1
  //                       
  // 09 14 19 24 29 34       34 29 24 19 14 09  2
  //
  // 08 15 18 25 28 35 36 36 35 28 25 18 15 08  3
  //
  //     07 16 17 26 27     27 26 17 16 07      4
  //    06    05    04       04    05    06

led_config_t g_led_config = {
    {
        {  10,  11,  20,  21,  30,  31 },
        {  9,   12,  19,  22,  29,  32 },
        {  8,   13,  18,  23,  28,  33 },
        {  7,   14,  17,  24,  27,  34 },
        {  6,   15,  16,  25,  26,  35 },
        {  46,  47,  56,  57,  66,  67 },
        {  45,  48,  55,  58,  65,  68 },
        {  44,  49,  54,  59,  64,  69 },
        {  43,  50,  53,  60,  63,  70 },
        {  42,  51,  52,  61,  62,  71 }
    },
    {
       // Left side underglow
        {16, 20}, {48, 10}, {80, 18}, {88, 60}, {56, 57}, {24,60},
        // Left side Matrix
        {32, 57}, { 0, 48}, { 0, 36}, { 0, 24}, { 0, 12},
        {16, 12}, {16, 24}, {16, 36}, {16, 48}, {48, 55},
        {64, 57}, {32, 45}, {32, 33}, {32, 21}, {32,  9},
        {48,  7}, {48, 19}, {48, 31}, {48, 43}, {80, 59},
        {96, 64}, {64, 45}, {64, 33}, {64, 21}, {64,  9},
        {80, 10}, {80, 22}, {80, 34}, {80, 47}, {96, 47},


        // Right side underglow
        {208, 20}, {176, 10}, {144, 18}, {136, 60}, {168, 57}, {200,60},
        // Right side Matrix
        {192, 57}, {224, 48}, {224, 36}, {224, 24}, {224, 12},
        {208, 12}, {208, 24}, {208, 36}, {208, 48}, {176, 55},
        {160, 57}, {192, 45}, {192, 33}, {192, 21}, {192,  9},
        {176,  7}, {176, 19}, {176, 31}, {176, 43}, {144, 59},
        {128, 64}, {160, 45}, {160, 33}, {160, 21}, {160,  9},
        {144, 10}, {144, 22}, {144, 34}, {144, 47}, {128, 47},
    },
    {
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
    }
};
#endif
