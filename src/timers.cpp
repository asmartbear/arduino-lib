#include "timers.h"

CTimers Timers;

int CTimers::loop() {
	unsigned long interval;
	
	// Load the current time
	unsigned long ms = millis();
	
	// Look for slots which need to be triggered
	int slot = MAX_NUM_TIMERS;
	while (slot--) {
		if (this->timers[slot].ms_interval && ms >= this->timers[slot].ms_next_trigger) {		// valid slot, and it's time to trigger?
			this->timers[slot].callback(ms - this->timers[slot].ms_last_triggered);		// trigger, and give the exact ms difference for things like rate calculations
			this->timers[slot].ms_last_triggered = ms;
			interval = this->timers[slot].ms_interval;
			this->timers[slot].ms_next_trigger = ((ms / interval) + 1) * interval;		// the millis() when we need to trigger again
			ms = millis();			// reset the current millisecond value, in case that call-back took a long time
		}
	}
	
	// Determine the longest we could sleep until the next timer
	unsigned long next_trigger = ms + 10000;			// longest we'll wait is 10 seconds from now
	slot = MAX_NUM_TIMERS;
	while (slot--) {
		if (this->timers[slot].ms_interval) {		// valid slot?
			interval = this->timers[slot].ms_next_trigger;
			next_trigger = min(next_trigger, interval);			// whichever trigger is sooner
		}
	}
	if (next_trigger <= ms) {		// no delay?
		return 0;
	}
	return next_trigger - ms;		// can delay this long
}

int CTimers::create(unsigned long ms_interval, timer_cb cb) {
	
	// Find the next available slot
	int slot = MAX_NUM_TIMERS;
	while (slot--) {
		if (this->timers[slot].ms_interval == 0) {
			break;
		}
	}
	if (slot < 0) {
		return -1;
	}
	
	// Fill the info of that slot and return the slot number
	unsigned long ms = millis();
	this->timers[slot].ms_interval = ms_interval;
	this->timers[slot].ms_last_triggered = ms;
	this->timers[slot].ms_next_trigger = ((ms / ms_interval) + 1) * ms_interval;			// whenever the time is right
	this->timers[slot].callback = cb;
	return slot;
}

void CTimers::remove(int slot) {
	this->timers[slot].ms_interval = 0;
}

