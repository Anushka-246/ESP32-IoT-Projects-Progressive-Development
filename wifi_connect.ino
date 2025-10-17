#include <WiFi.h> 

// Replace with your WI FI network credentials

const char* ssid = "YOUR_WiFi_SSID";
const char* password = "YOUR_WiFi_PASSWORD";

// Variables for non-blocking Wi-Fi reconnect

unsigned long previousMillis = 0;
const long interval = 10000; // check every 10 seconds

void setup() {
  Serial.begin(115200);

  // Start Wi-Fi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi... ");
}

void loop() {
  // Non-blocking reconnect check
  unsigned long currentMillis = millis();

  if (WiFi.status() != WL_CONNECTED && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    Serial.println("\nWi-Fi disconnected. Attempting to reconnect...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
  }

  // print connection status & IP address
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Wi-Fi Connected !  IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.print(".");
  }

  // Your main code can run here without blocking
  // For example, sensor reading, GPIO control, etc.

  delay(500); // small delay for Serial readability
}
