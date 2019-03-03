#include "timers.h"

CTimers Timers;

int CTimers::loop() {
	unsigned long interval, next;
	
	// Load the current time
	unsigned long ms = millis();
	
	// Look for slots which need to be triggered
	unsigned long next_trigger = ms + 60000;			// also look for the next time we'll trigger something
	int slot = MAX_NUM_TIMERS;
	while (slot--) {
		interval = this->timers[slot].ms_interval;
		if (interval > 0) {
			
			// Check for trigger
			next = this->timers[slot].ms_next_trigger;
			if (ms >= next) {		// valid slot, and it's time to trigger?
				this->timers[slot].callback(ms, ms - this->timers[slot].ms_last_triggered);		// trigger, and give the exact ms difference for things like rate calculations
				this->timers[slot].ms_last_triggered = ms;
				this->timers[slot].ms_next_trigger = next = ((ms / interval) + 1) * interval;		// the millis() when we need to trigger again
				ms = millis();			// reset the current millisecond value, in case that call-back took a long time
			}
			
			// Accumulate the minimum next trigger moment
			next_trigger = min(next_trigger, next);
		}
	}
	
	// Determine the longest we could sleep until the next timer
	return (next_trigger <= ms) ? 0 : (next_trigger - ms);
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
	this->timers[slot].ms_next_trigger = ((ms / ms_interval) + 1) * ms_interval;			// the next interval
	this->timers[slot].callback = cb;
	return slot;
}

void CTimers::remove(int slot) {
	this->timers[slot].ms_interval = 0;
}

