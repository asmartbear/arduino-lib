/*
  Utilities for handling switches, with features like debounce.
*/
#include "arduino.h"

// The values for a pull-up switch
#define SWITCH_DOWN   0
#define SWITCH_UP     1

// Additional switch-presses inside this time-threshold will be ignored
#define MS_BOUNCE_THRESHOLD	200

// Any digital pin can be a switch, so our state-array includes slots for any of them to be switches.
static long ms_debounce_threshold[NUM_DIGITAL_PINS];		// the value of millis() when we'll look at switch state again, to debounce.
static int prev_switch_state[NUM_DIGITAL_PINS];			// the previous UP/DOWN value we saw on this switch.
static int switch_active[NUM_DIGITAL_PINS];				// 1 if this is an active switch, 0 otherwise.

// Call during setup, to establish the pins for the switches.
// Supply a bitmap of which pin numbers should be configured as switches.
void setup_switches(int pin_bitmap) {
	for ( int k = NUM_DIGITAL_PINS ; k-- ; ) {
		if (bitRead(pin_bitmap, k)) {
			switch_active[k] = 1;
			prev_switch_state[k] = SWITCH_UP;
			pinMode(k, INPUT_PULLUP);
		}
	}
}

// Call this from your main loop, as often as possible, supplying the current value
// of millis().  The return result is a bitmap of the pins of the switches which have
// just now been depressed, from a previous state of being released, and debounced.
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

