/* Copyright 2022 Cipulot
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

#include "ec_switch.h"

#include "quantum.h"
#include "analog.h"
#include "print.h"

// pin connections
const uint8_t row_pins[]     = MATRIX_ROW_PINS;
const uint8_t col_channels[] = MATRIX_COL_CHANNELS;
const uint8_t mux_sel_pins[] = MUX_SEL_PINS;

_Static_assert(sizeof(mux_sel_pins) == 3, "invalid MUX_SEL_PINS");

static ecs_config_t config;
static uint16_t      ecs_adc_value[MATRIX_ROWS][MATRIX_COLS];

static inline void discharge_capacitor(void) { setPinOutput(DISCHARGE_PIN); }
static inline void charge_capacitor(uint8_t row) {
    setPinInput(DISCHARGE_PIN);
    writePinHigh(row_pins[row]);
}

static inline void clear_all_row_pins(void) {
    for (int row = 0; row < sizeof(row_pins); row++) {
        writePinLow(row_pins[row]);
    }
}

static inline void init_mux_sel(void) {
    for (int idx = 0; idx < sizeof(mux_sel_pins); idx++) {
        setPinOutput(mux_sel_pins[idx]);
        writePinLow(mux_sel_pins[idx]);
    }
}

static inline void select_mux(uint8_t col) {
    uint8_t ch = col_channels[col];
    writePin(mux_sel_pins[0], ch & 1);
    writePin(mux_sel_pins[1], ch & 2);
    writePin(mux_sel_pins[2], ch & 4);
}

static inline void init_row(void) {
    for (int idx = 0; idx < sizeof(row_pins); idx++) {
        setPinOutput(row_pins[idx]);
        writePinLow(row_pins[idx]);
    }
}

// Initialize pins
void ecs_init(ecs_config_t const* const ecs_config) {
    // save config
    config = *ecs_config;

    // initialize drive lines
    init_row();

    // initialize multiplexer select pin
    init_mux_sel();

    // Turn on extern circuit
    setPinOutput(POWER_PIN);
    writePinHigh(POWER_PIN);

    // Enable OpAmp
    setPinOutput(OPA_SHDN_PIN);
    writePinHigh(OPA_SHDN_PIN);

    // Enable AMUX
    setPinOutput(APLEX_EN_PIN);
    writePinLow(APLEX_EN_PIN);

    // initialize discharge pin as discharge mode
    setPinOutput(DISCHARGE_PIN);
    writePinLow(DISCHARGE_PIN);
}

// Read key value of key (row, col)
uint16_t ecs_readkey_raw(uint8_t row, uint8_t col) {
    uint16_t sw_value = 0;

    discharge_capacitor();

    wait_us(1);

    clear_all_row_pins();

    cli();

    charge_capacitor(row);
    wait_us(4);

    sw_value = analogReadPin(ANALOG_PORT);

    sei();

    return sw_value;
}

// Update press/release state of key at (row, col)
bool ecs_update_key(matrix_row_t* current_row, uint8_t col, uint16_t sw_value) {
    bool current_state = (*current_row >> col) & 1;

    // press to release
    if (current_state && sw_value < config.low_threshold) {
        *current_row &= ~(1 << col);
        return true;
    }

    // release to press
    if ((!current_state) && sw_value > config.high_threshold) {
        *current_row |= (1 << col);
        return true;
    }

    return false;
}

// Scan key values and update matrix state
bool ecs_matrix_scan(matrix_row_t current_matrix[]) {
    bool updated = false;

    for (int col = 0; col < sizeof(col_channels); col++) {

        discharge_capacitor();

        writePinHigh(APLEX_EN_PIN);

        select_mux(col);

        writePinLow(APLEX_EN_PIN);

        wait_us(30);

        for (int row = 0; row < sizeof(row_pins); row++) {
            ecs_adc_value[row][col] = ecs_readkey_raw(row, col);
            updated |= ecs_update_key(&current_matrix[row], col, ecs_adc_value[row][col]);
        }
    }

    discharge_capacitor();

    return updated;
}

// Print key values
void ecs_print_matrix(void) {
    for (int row = 0; row < sizeof(row_pins); row++) {
        for (int col = 0; col < sizeof(col_channels); col++) {
            xprintf("%4d", ecs_adc_value[row][col]);
        }
        xprintf("\n");
    }
}
