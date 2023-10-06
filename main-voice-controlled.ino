#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 200);
EthernetClient ethClient;
Adafruit_MQTT_Client mqttClient(&ethClient, "io.adafruit.com", 1883, "username", "AIO_KEY");

Adafruit_MQTT_Subscribe lightControl = Adafruit_MQTT_Subscribe(&mqttClient, "username/feeds/light-control");

void setup() {
  Ethernet.begin(mac, ip);
  mqttClient.connect();
  lightControl.setCallback(lightControlCallback);
  mqttClient.subscribe(&lightControl);
}

void loop() {
  mqttClient.processPackets();
}

void lightControlCallback(double x) {
  if (x == 1.0) {
    // Turn on the lights
    digitalWrite(13, HIGH); // Replace 13 with the pin number you are using to control the lights
  } else {
    // Turn off the lights
    digitalWrite(13, LOW); // Replace 13 with the pin number you are using to control the lights
  }
}