#include "status.h"

long ms_last_status = 0;    // when did we last emit status?

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
