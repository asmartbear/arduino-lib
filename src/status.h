
// Defined by the application: Reset your system status
void status_reset();

// Defined by the application: Display your status across the given time-interval.
// Do not also reset status -- that will be called for you.
void status_display(long ms_duration);

// Call this as often as possible from your loop, supplying the current value of `millis()`.
void status_loop(long ms);