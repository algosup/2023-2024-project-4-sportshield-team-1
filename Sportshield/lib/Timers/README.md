
# arduino-simple-timers
Simple timer library for Arduino

This library was created make it a little bit easier to monitor elapsed time.

## Examples
### Simple usage

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
	
As you can see, usage is pretty basic. Please remember to stop timer after available function return `true`. Without that `available()` will return `true` indefinitely.
You need to remember that after stoping a timer, a full start is needed.
### Watchdog timer

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

In this example you can use timer as a watchdog reseting it every time a condition is met. Using "restart" function will cause with zeroing elapsed time and will allow you to monitor a situation when this condition is not met within designed timeline.

## Limitations
1. uin32_t types which are used will overflow eventually, after a little bit more than 49 days