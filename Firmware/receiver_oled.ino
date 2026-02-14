#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int buzzer = D5;

String lastMessage = "";   // store received message
bool newMessage = false;   // flag for new data

// Callback: store message only
void onDataRecv(uint8_t *mac, uint8_t *data, uint8_t len) {
  lastMessage = "";
  for (int i = 0; i < len; i++) lastMessage += (char)data[i];
  lastMessage.trim();
  newMessage = true;  // set flag
}

void setup() {
  Serial.begin(115200);

  // Init OLED
  Wire.begin(D2, D1);  // SDA = D2, SCL = D1
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Receiver Ready...");
  display.display();

  // Init buzzer
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  // Init ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(onDataRecv);

  Serial.println("ESP8266 Receiver Ready");
}

void loop() {
  if (newMessage) {
    Serial.println("Recv: " + lastMessage);

    // Show on OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Message:");
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.println(lastMessage);
    display.display();

    // Control buzzer
    digitalWrite(buzzer, (lastMessage == "I NEED HELP") ? HIGH : LOW);

    newMessage = false; // reset flag
  }
}
