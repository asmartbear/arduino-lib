/*
  Fills in stuff Arduino defines for us implicitly.
*/


#define NUM_DIGITAL_PINS 13			// this is what the Uno has
#define INPUT_PULLUP 123			// doesn't matter exactly what the value is

#define bitRead(_x, _b)  (((_x) >> (_b)) & 1)
#define bitSet(_x, _b)   _x |= (1 << (_b))

void pinMode(int pin, int mode);
int digitalRead(int pin);