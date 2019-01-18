#include <ESP8266WiFi.h>

/*
   Roadmap
   - setup http server
   - IR library
   - test local
   - Alexa and IFTTT
     - Get External IP
     -
   - optimize (remove sleeps, better the code)
   - try on ESP01
   - Bugs - To-Do
      - lostWifiCallBack
      - configModeCallBack
*/
// WEMOS users may need to adjust pins for compatability
const int pinr1 = 14;                                         // Receiving pin
const int pins1 = 4;                                          // Transmitting preset 1
const int pins2 = 5;                                          // Transmitting preset 2
const int pins3 = 12;                                         // Transmitting preset 3
const int pins4 = 13;                                         // Transmitting preset 4
const int configpin = 10;                                     // Reset Pin

const int ledpin = BUILTIN_LED;                               // Built in LED defined for WEMOS people
// define your default values here, if there are different values in config.json, they are overwritten.
char host_name[20];
char passcode[20];
char port_str[6] = "80";
// Repeat the port as a int
int port = 80;
char user_id[60];
char fingerprint[60] = "8D 83 C3 5F 0A 09 84 AE B4 64 63 23 8F 05 9E 4D 5E 08 60 06";

void setup() {
  // Initialize serial
  Serial.begin(115200);

  // set led pin as output
  pinMode(ledpin, OUTPUT);

  Serial.println("");
  Serial.println("ESP8266 IR Controller");
  pinMode(configpin, INPUT_PULLUP);
  Serial.print("Config pin GPIO");
  Serial.print(configpin);
  Serial.print(" set to: ");
  Serial.println(digitalRead(configpin));
  if (!wifi_setup(digitalRead(configpin) == LOW)) {
    Serial.print("Returning from Config menu. Please reboot with Config button unpressed");
    return;
  }

  if (strlen(host_name) > 0) {
    WiFi.hostname(host_name);
    Serial.println("Wifi hostname set: ");
    Serial.println(host_name);
  } else {
    WiFi.hostname().toCharArray(host_name, 20);
    Serial.println("Wifi hostname set: ");
    Serial.println(toCharArray(host_name, 20));
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  wifi_set_sleep_type(LIGHT_SLEEP_T);

  digitalWrite(ledpin, LOW);

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("URL to send commands: http://" + String(host_name) + ".local:" + port_str);
  //ntp_setup();
  ntp2_setup();
  enableMDNSServices();

}

void loop() {
  //ntp_loop();
  ntp2_loop();
}

