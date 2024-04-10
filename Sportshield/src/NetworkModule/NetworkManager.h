#ifndef NetworkManager_h
#define NetworkManager_h

#include <Arduino.h>
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

class NetworkManager {
public:
    NetworkManager(const char* apn, const char* user, const char* pass, Stream &modemStream); // Constructor
    void begin(); // Initializes the network module and connects to the GSM network
    bool sendNotification(String url, String message); // Sends a notification to the specified URL
    bool updateCoordinates(String url, float latitude, float longitude, float batteryLevel); // Sends the GPS coordinates and battery level to the specified URL
    
private:
    TinyGsm modem; // GSM modem
    TinyGsmClient client; // GSM client for HTTP requests
    HttpClient http; // HTTP client
    const char* _apn; // APN for GSM network
    const char* _user; // User for GSM network
    const char* _pass; // Password for GSM network
};

#endif
