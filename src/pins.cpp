#include "pins.h"

// Any digital pin can be a switch, so our state-array includes slots for any of them to be switches.
static long ms_debounce_threshold[NUM_DIGITAL_PINS];		// the value of millis() when we'll look at switch state again, to debounce.
static int prev_switch_state[NUM_DIGITAL_PINS];			// the previous UP/DOWN value we saw on this switch.
static int switch_active[NUM_DIGITAL_PINS];				// 1 if this is an active switch, 0 otherwise.

void setup_switches(int pin_bitmap) {
	for ( int k = NUM_DIGITAL_PINS ; k-- ; ) {
		if (bitRead(pin_bitmap, k)) {
			switch_active[k] = 1;
			prev_switch_state[k] = SWITCH_UP;
			pinMode(k, INPUT_PULLUP);
		}
	}
}

int get_switches_down_just_now(long ms) {
	int curr_state, down_bitmap;
	
	down_bitmap = 0;
	for ( int k = NUM_DIGITAL_PINS ; k-- ; ) {
		if (switch_active[k]) {
			curr_state = digitalRead(k);
			if (curr_state == SWITCH_DOWN && prev_switch_state[k] == SWITCH_UP && ms > ms_debounce_threshold[k]) {
				bitSet(down_bitmap, k);
				ms_debounce_threshold[k] = ms + MS_BOUNCE_THRESHOLD;
			}
			prev_switch_state[k] = curr_state;
		}
	}
	return down_bitmap;
}

