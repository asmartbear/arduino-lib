/*
	Subsystem in which you can register things to happen on certain time intervals, and they will be executed.
  The time intervals are based on wall-clock, and so will stay as aligned as possible to real time, not from
  the last execution.  However, if more than one wall-clock interval has passed, it will be triggered only
  the one time.
 */
#include <Arduino.h>

#define MAX_NUM_TIMERS	8

typedef void (*timer_cb)(unsigned long ms, unsigned long ms_delta);

class CTimers {
private:
	
	struct {
		unsigned long ms_next_trigger;		// millis() after which we need to trigger again
		unsigned long ms_last_triggered;  // millis() when we last triggered
		unsigned long ms_interval;				// millisecond interval upon which we want to be triggered
		timer_cb callback;
	} timers[MAX_NUM_TIMERS];
	
public:
	
	// Call this function as often as possible, e.g. in the main loop.
	// Returns the number of milliseconds before the next timer will be invoked.
	// You can pass the return value to delay() to reduce CPU time.
	int loop();
	
	// Register a new timer, calling the given function on the given millisecond interval.
	// Returns the timer slot number, which can be used to remove the timer.
	int create(unsigned long ms_interval, timer_cb cb);
	
	// Un-registers the timer from the given slot.
	void remove(int slot);
	
};

extern CTimers Timers;
