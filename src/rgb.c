#include "arduino.h"
#include "trig.c"

// The 2D vectors that each color represents
float color_vectors[3][2] = {
  {  1  ,  0    },   // red along x-axis
  { -0.5,  0.866 },   // green 120 degrees from red
  { -0.5, -0.866 },   // blue 120 degrees from green
};

// Sets the pin to the given value, but does nothing if that is last value set.
// This prevents a material number of function calls and thus speeds up the process.
int prev_color_values[3] = { 0, 0, 0 };
void smart_set_color(int pin, int color, int value) {
  if (prev_color_values[color] != value) {
    prev_color_values[color] = value;
    analogWrite(pin, value);
  }
}

// Call once to set up the RGB LED pins and state.
void setup_rgb(int *pins) {
	
  // Establish the mode of the pins, and set to the "previous," i.e. the initial state.
  for ( int k = 3 ; k-- ; ) {
    pinMode(pins[k], OUTPUT);
    digitalWrite(pins[k], prev_color_values[0]);
  }
}

// Sets the RGB-LED to the color represented by the given floating-point angle.
void set_rgb(int *pins, float a) {
  int value;
  float intensity, x, y;

  // Compute the color
  cos_sin(a, &x, &y);
  for (int k = 0 ; k < 3 ; ++k) {
    intensity = x * color_vectors[k][0] + y * color_vectors[k][1];
    if (intensity < 0.03) {    // peg zero, especially if negative meaning pointing away
      value = 0;
    } else if (intensity >= 0.97) {    // peg full-on when close to the top
      value = 255;
    } else {
      value = (int)(intensity * 255);
    }
    smart_set_color(pins[k], k, value);
  }
}

