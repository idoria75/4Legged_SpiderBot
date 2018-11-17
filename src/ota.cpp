#include "ota.h"

uint Ota::port = 5222;

Ota::Ota() {
  Serial.println("Start of OTA");

  ArduinoOTA.setPort(port);

  ArduinoOTA.onStart([=]() { Serial.println("Starting OTA..."); });
  ArduinoOTA.onEnd([=]() { Serial.println("End of OTA..."); });
  ArduinoOTA.onProgress([=](unsigned int progress, unsigned int total) {
    Serial.print("Progress: ");
    Serial.print(progress / (total / 100));
    Serial.println("\%");
  });
  ArduinoOTA.onError(
      [=](ota_error_t error) { Serial.println("Error on OTA..."); });
  ArduinoOTA.begin();
}

void Ota::handle() {
  ArduinoOTA.handle();
}

Ota& Ota::self() {
  static Ota self;
  return self;
}

Ota::~Ota() {}