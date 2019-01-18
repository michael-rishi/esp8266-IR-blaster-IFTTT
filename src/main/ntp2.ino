#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
int period = 10000;
unsigned long time_now = 0;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionaly you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 21600000);

void ntp2_setup() {
  // Assuming at this stage that Wifi is connected
  timeClient.begin();
}

void ntp2_loop() {
  if (millis() > time_now + period) {
    time_now = millis();
    timeClient.update();
    Serial.println(timeClient.getFormattedTime());
  }
}
