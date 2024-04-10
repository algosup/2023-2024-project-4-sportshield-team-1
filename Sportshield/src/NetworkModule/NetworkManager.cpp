#include "NetworkManager.h"

NetworkManager::NetworkManager(const char* apn, const char* user, const char* pass, Stream &modemStream) 
    : modem(modemStream), client(modem), http(client, serverName, serverPort), _apn(apn), _user(user), _pass(pass) {
}

void NetworkManager::begin() {
    // Initialize modem
    modem.restart();
    // Wait for network to connect
    while (!modem.waitForNetwork()) {
        delay(1000);
    }
    // Connect to GPRS
    modem.gprsConnect(_apn, _user, _pass);
}

bool NetworkManager::sendNotification(String url, String message) {
    http.beginRequest();
    http.post(url);
    http.sendHeader("Content-Type", "application/json");
    http.sendHeader("Content-Length", message.length());
    http.beginBody();
    http.print(message);
    http.endRequest();
    
    int statusCode = http.responseStatusCode();
    http.stop();
    return statusCode == 200;
}

bool NetworkManager::updateCoordinates(String url, float latitude, float longitude, float batteryLevel) {
    String payload = "{\"latitude\":\"" + String(latitude, 6) + "\",\"longitude\":\"" + String(longitude, 6) + "\",\"battery\":\"" + String(batteryLevel) + "\"}";
    return sendNotification(url, payload);
}
