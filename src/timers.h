/*
	Subsystem in which you can register things to happen on certain time intervals, and they will be executed.
  The time intervals are based on wall-clock, and so will stay as aligned as possible to real time, not from
  the last execution.  However, if more than one wall-clock interval has passed, it will be triggered only
  the one time.
 */
#include <Arduino.h>

#define MAX_NUM_TIMERS	10

typedef void (*timer_cb)(unsigned long ms_interval);

class CTimers {
private:
	
	struct {
		unsigned long ms_last_triggered;
		unsigned long ms_interval;
		timer_cb callback;
	} timers[MAX_NUM_TIMERS];
	
public:
	
	// Call this function as often as possible, e.g. in the main loop.
	void loop();
	
	// Register a new timer, calling the given function on the given millisecond interval
	int create(unsigned long ms_interval, timer_cb cb);
	
};

extern CTimers Timers;
