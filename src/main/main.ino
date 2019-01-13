#include <ESP8266WiFi.h>

/*
 * Roadmap
 * - setup http server
 * - IR library
 * - test local
 * - Alexa and IFTTT
 * - optimize (remove sleeps, better the code)
 * - try on ESP01
 */
void setup() {
  // put your setup code here, to run once:
  wifi_setup();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  }
  ntp_setup();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  ntp_loop();
}
