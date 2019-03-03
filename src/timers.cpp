#include "timers.h"

CTimers Timers;

void CTimers::loop() {
	unsigned long interval, last;
	
	// Load the current time
	unsigned long ms = millis();
	
	// Look for slots which need to be triggered
	int slot = MAX_NUM_TIMERS;
	while (slot--) {
		if (this->timers[slot].ms_interval) {		// valid slot?
			interval = this->timers[slot].ms_interval;
			last = this->timers[slot].ms_last_triggered;
			if ((ms / interval) > (last / interval)) {		// have we entered a new interval?
				this->timers[slot].callback(ms - last);
				this->timers[slot].ms_last_triggered = ms;
			}
		}
	}
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
	this->timers[slot].ms_interval = ms_interval;
	this->timers[slot].ms_last_triggered = 0;
	this->timers[slot].callback = cb;
	return slot;
}

