#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 2     // esp32 GPIO2 connected to DHT11 Data pin
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "YOUR_WiFi_NAME";
const char* password = "YOUR_WiFi_PASSWORD";

unsigned long previousMillis = 0;
const long wifiCheckInterval = 10000;  // Check WiFi every 10 seconds

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to WiFi
  connectToWiFi();
}

void loop() {
  // ------- Check WiFi Status -------
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= wifiCheckInterval) {
    previousMillis = currentMillis;
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi DISCONNECTED! Reconnecting...");
      connectToWiFi();
    }
  }

  // ------- Read DHT11 Sensor -------
  float humidity = dht.readHumidity();  // in %
  float temperatureC = dht.readTemperature();  // Temperature in Celcius
  float temperatureF = dht.readTemperature(true);  // Temperature in Fahrenheit 

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("Failed to read from DHT11!");
    delay(2000);
    return;
  }

  // ------ Print Sensor Data ------
  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("Temperature in C: ");
  Serial.println(temperatureC);

  Serial.print("Temperature in F: ");
  Serial.println(temperatureF);

  Serial.println("----------------------");

  delay(5000);
}

// ------- WiFi Connection Function -------
void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < 20) { // 20 * 500ms = 10 seconds
    Serial.print(".");
    delay(500);
    timeout++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi connection FAILED! Will retry...");
  }
}
