#include "Timers.h"
    
Timers guard_timer;
bool data_received = false;
	
void setup() {
  guard_timer.start(5000); //time in ms
}

void loop() {
  if (data_received) {
	guard_timer.restart();
  }
  if (guard_timer.available()) {
	guard_timer.stop();
	//Send alert that timer elapsed
	guard_timer.start(5000);
  }
}