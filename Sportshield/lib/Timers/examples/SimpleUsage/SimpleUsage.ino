#include "Timers.h"

Timers timer;
    
void setup() {
  timer.start(5000); //time in ms
}

void loop() {
  if (timer.available()) {
    timer.stop();
    //Do something
    timer.start(5000);
  }
}
