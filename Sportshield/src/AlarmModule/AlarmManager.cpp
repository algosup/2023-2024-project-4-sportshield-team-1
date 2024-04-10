#include "AlarmManager.h"

AlarmManager::AlarmManager(int buzzerPin) : _buzzerPin(buzzerPin) {
    pinMode(_buzzerPin, OUTPUT); // Set the buzzer pin as output
}

void AlarmManager::triggerLightAlarm() {
    for (int i = 0; i < 3; i++) {
        beep(2000, 100); // Example frequency and duration for light alarm
        delay(100); // Short delay between beeps
    }
}

void AlarmManager::triggerStrongAlarm() {
    for (int i = 0; i < 5; i++) {
        beep(2500, 500); // Example frequency and duration for strong alarm
        delay(500); // Delay between beeps
    }
}

void AlarmManager::stopAlarm() {
    noTone(_buzzerPin); // Stop any ongoing alarm sound
}

void AlarmManager::beep(int note, int duration) {
    tone(_buzzerPin, note, duration);
    delay(duration); // Duration of the tone
}

