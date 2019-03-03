/*
  Utilities for reading and writing pins, with features like debounce.
*/

// The values for a pull-up switch
#define SWITCH_DOWN   0
#define SWITCH_UP     1

// Additional switch-presses inside this time-threshold will be ignored
#define MS_BOUNCE_THRESHOLD	200

// Call during setup, to establish the pins for the switches.
// Supply a bitmap of which pin numbers should be configured as switches.
void setup_switches(int pin_bitmap);

// Call this from your main loop, as often as possible, supplying the current value
// of millis().  The return result is a bitmap of the pins of the switches which have
// just now been depressed, from a previous state of being released, and debounced.
int get_switches_down_just_now(long ms);

// Read from an analog pin, but if the change from the previous reading to the current
// reading is small enough, just return the previous reading.  This prevents flapping
// back and forth that often happens with, for example, pots.
int dampedRead(int pin);

