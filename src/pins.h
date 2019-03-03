/*
  Utilities for reading and writing pins, with features like debounce.
*/

// The values for a pull-up switch
#define SWITCH_DOWN   0
#define SWITCH_UP     1

// Additional switch-presses inside this time-threshold will be ignored
#define MS_BOUNCE_THRESHOLD	200

// Call-back when a switch is pushed.
typedef void (*cb_switch_pushed)(int pin);

// Call during setup, to establish the pins for the switches.
// Supply a bitmap of which pin numbers should be configured as switches.
void setup_switch(int pin, cb_switch_pushed cb);

// Read from an analog pin, but if the change from the previous reading to the current
// reading is small enough, just return the previous reading.  This prevents flapping
// back and forth that often happens with, for example, pots.
int analog_read_debounced(int pin);

// Same as analogWrite(), but constrains to [0,255], and does nothing if the value is the same as the current value,
// which saves CPU time and is common.
void analog_write(int pin, int val);

