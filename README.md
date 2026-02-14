## Project Overview
This project is an **IoT-based assistive wearable** designed for patients with paralysis, Locked-in Syndrome, or motor neuron diseases. It enables individuals with restricted movement to communicate essential needs—like requesting water or help—using simple finger gestures.

## System Architecture & Connectivity
The system utilizes a **dual-node architecture** connected via the **ESP-NOW protocol**:
* **Transmitter (Glove):** Uses an ESP32/ESP8266 to read flex sensor data and map movements.
* **Receiver (Station):** Processes data to update a local OLED display and trigger a buzzer.
* **Peer-to-Peer:** Communication is internet-independent and does not require a router.

## Tech Stack & Components
### **Hardware**
* **Microcontrollers:** ESP32 and ESP8266.
* **Sensors:** Flex Sensors for gesture detection.
* **Feedback:** OLED Display for local alerts and a Buzzer for emergencies.
* **Power:** Battery-operated.

### **Software**
* **Framework:** Arduino IDE (Embedded C++).
* **Protocol:** ESP-NOW for low-latency transmission.
* **IoT Platform:** **Blynk Application** for remote monitoring.
