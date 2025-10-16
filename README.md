# ESP32-IoT-Projects-Progressive-Development
A curated collection of beginner-friendly ESP32 projects covering sensors, Wi-Fi, GPIO, PWM/servo, I2C devices, and non-blocking programming. Designed as a progressive learning path for practical IoT applications.

### 📁 Projects Overview

- **dht11_wifi.ino**: Read DHT11 temperature & humidity and connect to Wi-Fi
- **wifi_reconnect.ino**: Auto-reconnect ESP32 to Wi-Fi if disconnected
- **non_blocking_dht11_wifi.ino**: Handle sensor reading and Wi-Fi connection using `millis()` (non-blocking)
- **gpio_control.ino**: Control LEDs, relays, and buttons
- **analog_input.ino**: Read analog sensors like potentiometers or photoresistors
- **servo_control.ino**: Control servo motor using PWM
- **oled_display.ino**: Display sensor readings on an I2C OLED screen
- **mqtt_publish.ino**: Publish sensor data to an MQTT broker

---

## ⚡ Features

- Clean, modular example sketches  
- Covers essential ESP32 concepts for IoT  
- Demonstrates both blocking (`delay()`) and non-blocking (`millis()`) code  
- Includes basic Wi-Fi handling and GPIO control  

---

## 📝 Requirements

- **Board:** ESP32 Dev Board  
- **Libraries:**  
  - `WiFi.h` (built-in)  
  - `DHT sensor library` by Adafruit  
  - `Adafruit Unified Sensor`  
  - `Adafruit GFX` and `Adafruit SSD1306` (for OLED examples)  
  - `PubSubClient` (for MQTT example)

---

## 🚀 Usage

1. Open the desired `.ino` file in Arduino IDE  
2. Install required libraries  
3. Connect ESP32 to PC and upload  
4. Monitor Serial for outputs or interact with devices

---

## 📌 Notes

- Projects are progressive: start with DHT11 + Wi-Fi, then learn non-blocking code, GPIO, and sensors  
- Each file is self-contained and can be uploaded individually  
- Ideal for learners to grasp ESP32 fundamentals before moving to advanced projects 
