#include <WiFi.h>

// Replace with your Wi-Fi credentials
const char* ssid = "YOUR_WiFi_SSID";
const char* password = "YOUR_WiFi_PASSWORD";

unsigned long previousReconnectAttempt = 0;
const long reconnectInterval = 10000;  // Try reconnect every 10 seconds

bool wifiConnected = false;
bool lastWifiConnected = false;  // Track last connection state
IPAddress lastIP(0,0,0,0);       // To track IP change

// Wi-Fi Event Handler
void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
  switch (event) {

    case ARDUINO_EVENT_WIFI_STA_START:
      Serial.println("[EVENT] WiFi Started");
      break;

    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      Serial.println("[EVENT] Connected to Access Point");
      break;

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.print("[EVENT] Got IP Address: ");
      Serial.println(WiFi.localIP());
      wifiConnected = true;

      // Set persistent to false after first connect
      WiFi.persistent(false);
      break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED: {
      wifiConnected = false;

      // Use correct type for disconnect event
      wifi_event_sta_disconnected_t discInfo = info.wifi_sta_disconnected;

      if (discInfo.reason == WIFI_REASON_AUTH_EXPIRE ||
          discInfo.reason == WIFI_REASON_AUTH_FAIL) {
        Serial.println("[ERROR] Wrong password!");
      } else if (discInfo.reason == WIFI_REASON_NO_AP_FOUND) {
        Serial.println("[ERROR] Access Point not found!");
      } else {
        Serial.print("[WARNING] WiFi disconnected, reason: ");
        Serial.println(discInfo.reason);
      }
      break;
    }

    default:
      Serial.print("[EVENT] Unhandled WiFi Event: ");
      Serial.println(event);
      break;
  }
}

void setup() {
  Serial.begin(115200);

  // Attach Wi-Fi event handler
  WiFi.onEvent(WiFiEvent);

  // Configure Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true); // First connection persistent

  Serial.println("Connecting to WiFi...");
}

void loop() {
  unsigned long currentMillis = millis();

  // Backup check in case event missed
  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
  } else {
    wifiConnected = false;
  }

  // Non-blocking reconnect logic
  if (!wifiConnected && (currentMillis - previousReconnectAttempt >= reconnectInterval)) {
    previousReconnectAttempt = currentMillis;
    Serial.println("[LOOP] Attempting reconnect...");
    WiFi.begin(ssid, password);   // Safer than WiFi.reconnect()
  }

  // Print connection status only on change
  if (wifiConnected != lastWifiConnected) {
    lastWifiConnected = wifiConnected;

    if (wifiConnected) {
      lastIP = WiFi.localIP();  // Update last IP
      Serial.print("[INFO] Wi-Fi Connected | IP: ");
      Serial.println(lastIP);
    } else {
      Serial.println("[INFO] Wi-Fi Disconnected");
    }
  }
}
