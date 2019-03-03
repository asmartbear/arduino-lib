#include <Arduino.h>
#include "pins.h"
#include "timers.h"

// Any digital pin can be a switch, so our state-array includes slots for any of them to be switches.
static long ms_debounce_threshold[NUM_DIGITAL_PINS];		// the value of millis() when we'll look at switch state again, to debounce.
static int prev_pin_state[NUM_DIGITAL_PINS];			// the previous value we saw on this pin, both switches, digital, and analog pins.
static cb_switch_pushed switch_cbs[NUM_DIGITAL_PINS];				// call-backs for active switches
static int timer_slot_switch_checker = -1;

static void switches_timer(unsigned long ms, unsigned long ms_delta) {
	int curr_state;
	
	for ( int k = NUM_DIGITAL_PINS ; k-- ; ) {
		if (switch_cbs[k]) {
			curr_state = digitalRead(k);
			if (curr_state == SWITCH_DOWN && prev_pin_state[k] == SWITCH_UP && ms > ms_debounce_threshold[k]) {
				ms_debounce_threshold[k] = ms + MS_BOUNCE_THRESHOLD;
				switch_cbs[k](k);
			}
			prev_pin_state[k] = curr_state;
		}
	}
}

void setup_switch(int pin, cb_switch_pushed cb) {
	
	// Set up pin state
	switch_cbs[pin] = cb;
	prev_pin_state[pin] = SWITCH_UP;
	pinMode(pin, INPUT_PULLUP);
	
	// Install timer to read from all switches
	if (timer_slot_switch_checker < 0) {			// check hasn't already been installed
		Timers.create(25, switches_timer);
	}
}

int analog_read_debounced(int pin) {
	int prev = prev_pin_state[pin];
  int curr = analogRead(pin);
  if (abs(curr - prev) >= 3) {
    return prev_pin_state[pin] = curr;
  }
  return prev;
}

void analog_write(int pin, int val) {
	val = constrain(val, 0, 255);
	if (val != prev_pin_state[pin]) {
		prev_pin_state[pin] = val;
		analogWrite(pin, val);
	}
}

