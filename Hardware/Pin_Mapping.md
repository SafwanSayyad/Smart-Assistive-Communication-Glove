System Architecture:

Communication: ESP-NOW (Peer-to-Peer, No Router Required).
Transmitter: ESP8266 + 3 Flex Sensors.
Receiver: ESP8266 + OLED + Buzzer + Blynk IoT Cloud

Pin Mapping - Transmitter (Glove):

COMPONENT         | ESP8266 PIN | FUNCTION
------------------|-------------|-------------------------
Flex Sensor 1     | A0          | Index: "Need Water" 
Flex Sensor 2     | A1          | Middle: "Need Help" 
Flex Sensor 3     | A2          | Ring:"Need Food" 
Battery (+)       | Vin / 5V    | Power Supply 
Battery (-)       | GND         | Common Ground

Pin Mapping - Receiver:

COMPONENT         | ESP8266 PIN | FUNCTION
------------------|-------------|-------------------------
OLED Display SDA  | D2 (GPIO 4) | I2C Data Communication 
OLED Display SCL  | D1 (GPIO 5) | I2C Clock Signal
Buzzer            | D5 (GPIO 14)| Emergency Alert Audio 
Blynk App         | Wi-Fi       | Remote Monitoring 
