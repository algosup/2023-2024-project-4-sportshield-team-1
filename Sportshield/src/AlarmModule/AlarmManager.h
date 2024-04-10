#ifndef AlarmManager_h
#define AlarmManager_h

#include <Arduino.h>

class AlarmManager {
public:
    AlarmManager(int buzzerPin); // Constructor with buzzer pin
    void triggerLightAlarm(); // Triggers a light alarm sequence
    void triggerStrongAlarm(); // Triggers a strong alarm sequence
    void stopAlarm(); // Stops the alarm
    
private:
    int _buzzerPin; // Pin connected to the buzzer
    void beep(int note, int duration); // Function to control buzzer frequency and duration
};

#endif
