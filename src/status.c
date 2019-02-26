
long ms_last_status = 0;    // when did we last emit status?

// Defined by the application: Reset your system status
void status_reset();

// Defined by the application: Display your status across the given time-interval.
// Do not also reset status -- that will be called for you.
void status_display(long ms_duration);

// Call this as often as possible from your loop, supplying the current value of `millis()`.
void status_loop(long ms) {

  // Once in a while, print status
  long ms_since_last_status = ms - ms_last_status;
  if ( ms_since_last_status >= 1000 ) {
		status_display(ms_since_last_status);
    ms_last_status = ms;
		status_reset();
  }
}
