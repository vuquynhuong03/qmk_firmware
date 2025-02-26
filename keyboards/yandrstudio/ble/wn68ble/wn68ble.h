/* Copyright 2021 JasonRen(biu)
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
#pragma once

#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310,       K312,       K314, K315, \
    K400, K401, K402,             K405,             K408,       K410,       K412, K413, K414, K415  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015 }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  K115 }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214,  K215 }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  KC_NO, K312,  KC_NO, K314,  K315 }, \
    { K400,  K401,  K402,  KC_NO, KC_NO, K405,  KC_NO, KC_NO, K408,  KC_NO, K410,  KC_NO, K412,  K413,  K414,  K415 }  \
}

enum keyboard_keycodes {
#ifdef VIA_ENABLE
    LOCK_GUI = USER00,
#else
    LOCK_GUI = SAFE_RANGE,
#endif
#ifdef RGB_MATRIX_ENABLE
    KC_KEY_UNDER_RGBSW,
#endif
    TOG_MACOS_KEYMAP,
    KC_MISSION_CONTROL,
    KC_LAUNCHPAD,
#ifdef VIA_ENABLE
    NEW_SAFE_RANGE = SAFE_RANGE  // Important!
#else
    NEW_SAFE_RANGE   // Important!
#endif


};

#define KC_LG     LOCK_GUI
#define KC_MACOS  TOG_MACOS_KEYMAP
#define KC_MCTL   KC_MISSION_CONTROL
#define KC_LPAD   KC_LAUNCHPAD
#ifdef RGB_MATRIX_ENABLE
#   define RGB_KG_T  KC_KEY_UNDER_RGBSW
#else
#   define RGB_KG_T  KC_F14
#endif
