#define BLYNK_TEMPLATE_ID "TMPL3nb_xi7ZI"
#define BLYNK_TEMPLATE_NAME "Smart Glove"
#define BLYNK_AUTH_TOKEN "twDigfESGIBgI9VbZd-uoKC8t5g0o_vT"
#include <WiFi.h>
#include <esp_now.h>
#include <BlynkSimpleEsp32.h>




char ssid[] = "xyz", pass[] = "IOT123456";

// Flex sensor pins
int flex1 = 34;  
int flex2 = 35;  
int flex3 = 32; 
int BUZZER= 25;

// Replace with your ESP8266 receiver MAC address
const uint8_t receiverMac[6] = {0xC4, 0x5B, 0xBE, 0x62, 0xE2, 0x35};
 

void setup() {
  Serial.begin(115200);

  // Connect Blynk (internet side)
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Init ESP-NOW (direct WiFi comms)
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed!");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) == ESP_OK) {
    Serial.println("ESP32 Sender ready");
  } else {
    Serial.println("Failed to add peer");
  }
}

void loop() {
  Blynk.run();

  // Read flex sensors
  int v0 = analogRead(flex1);
  int v1 = analogRead(flex2);
  int v2 = analogRead(flex3);

  // Print flex values to Serial Monitor
  Serial.print("Flex1: "); Serial.print(v0);
  Serial.print(" | Flex2: "); Serial.print(v1);
  Serial.print(" | Flex3: "); Serial.println(v2);

  // Decide message
  String msg = "Idle...";
  if (v0 > 550) { msg = "I NEED WATER"; Blynk.virtualWrite(V0, msg); }
  else if (v1 > 100) { msg = "I NEED HELP"; Blynk.virtualWrite(V1, msg); }
  else if (v2 > 545) { msg = "I NEED FOOD"; Blynk.virtualWrite(V2, msg); }
else { msg = "IDLE..."; Blynk.virtualWrite(V3, msg); }


  // Send message to ESP8266 receiver
  esp_now_send(receiverMac, (uint8_t*) msg.c_str(), msg.length());

  // Also log what was sent
  Serial.println("Sent: " + msg);
  Serial.println("----------------------");

  delay(500);
}
