#include "arduino.h"

#define BYTE_ANGLE_120 85		// the byte-value in [0,255] mapping to 120 degrees
#define BYTE_ANGLE_240 171		// the byte-value in [0,255] mapping to 240 degrees

// Sets the pin to the given value, but does nothing if that is last value set.
// This prevents a material number of function calls and thus speeds up the process.
int prev_color_values[3] = { 0, 0, 0 };
void smart_set_color(int pin, int color, int value) {
	value = constrain(value, 0, 255);
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

// Sets the RGB-LED to the color represented by an "angle" in the range [0,255], where red is
// 0, and green and blue are at 120-degrees forward and backwards.  The LEDs are powered with
// a linear motion, "outlining" the edge of the hexagonal HSV space with maximum S and V mapped
// to the available RGB range, rather than a sin/cos style "angle."
void set_rgb(int *pins, int byte_angle) {
  int r, g, b;
  
  // Red: Centered on 0°
  if (byte_angle < BYTE_ANGLE_120) {
	  r = (BYTE_ANGLE_120 - byte_angle)*3;
  } else if (byte_angle > BYTE_ANGLE_240) {
  	r = (byte_angle - BYTE_ANGLE_240)*3;
  } else {
  	r = 0;
  }
  
  // Green: Centered on 120°
  if (byte_angle <= BYTE_ANGLE_120) {
	  g = byte_angle*3;
  } else if (byte_angle < BYTE_ANGLE_240) {
  	g = (BYTE_ANGLE_240 - byte_angle)*3;
  } else {
  	g = 0;
  }
  
  // Blue: Centered on 240°
  if (byte_angle >= BYTE_ANGLE_240) {
	  b = (256-byte_angle)*3;
  } else if (byte_angle > BYTE_ANGLE_120) {
  	b = (byte_angle - BYTE_ANGLE_120)*3;
  } else {
  	b = 0;
  }
  
  smart_set_color(pins[0], 0, r);
  smart_set_color(pins[1], 1, g);
  smart_set_color(pins[2], 2, b);
  
  // Serial.print(byte_angle);
  // Serial.print(": ");
  // Serial.print(r);
  // Serial.print(",");
  // Serial.print(g);
  // Serial.print(",");
  // Serial.println(b);
}

