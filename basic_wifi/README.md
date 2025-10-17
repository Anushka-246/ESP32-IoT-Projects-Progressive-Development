# Basic Wi-Fi Examples for ESP32

This folder contains example sketches for connecting ESP32 to Wi-Fi with different approaches.

1. **wifi_basic_reconnect.ino**  
   Demonstrates non-blocking Wi-Fi reconnection.

2. **wifi_event_handler_autoreconnect.ino**  
   Uses Wi-Fi events to handle connection status, errors, and automatic reconnection.

---

## Wi-Fi Reconnect Approaches

```mermaid
flowchart TD
    A[Start ESP32] --> B{Check Wi-Fi Connection}
    
    %% Non-blocking loop-based reconnect
    B -->|Disconnected| C[Attempt reconnect in loop every 10s]
    C --> B
    B -->|Connected| D[Continue normal operation]
    
    %% Event-driven reconnect
    E[Wi-Fi Event Triggered] --> F{Event Type?}
    F -->|Connected| G[Store IP, proceed]
    F -->|Disconnected| H[Auto reconnect via event handler]
    F -->|Auth/Timeout Error| I[Handle error, retry reconnect]
