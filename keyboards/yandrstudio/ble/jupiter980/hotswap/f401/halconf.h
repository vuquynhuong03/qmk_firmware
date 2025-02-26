/* Copyright 2020 QMK
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
#include_next <halconf.h>

#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE

#undef HAL_USE_SERIAL
#define HAL_USE_SERIAL TRUE

#undef HAL_USE_ADC
#define HAL_USE_ADC    TRUE

#undef  SERIAL_USB_BUFFERS_SIZE
#define SERIAL_USB_BUFFERS_SIZE 256

#undef  SERIAL_BUFFERS_SIZE
#define SERIAL_BUFFERS_SIZE 512

#undef  SPI_SELECT_MODE
#define SPI_SELECT_MODE SPI_SELECT_MODE_NONE

#undef  SPI_USE_WAIT
#define SPI_USE_WAIT TRUE

#undef  PAL_USE_CALLBACKS
#define PAL_USE_CALLBACKS TRUE
