/*
	Subsystem in which you can register things to happen on certain time intervals, and they will be executed.
  The time intervals are based on wall-clock, and so will stay as aligned as possible to real time, not from
  the last execution.
 */


class CTimers {
public:
	
	int hello();
	
};

extern CTimers Timers;
