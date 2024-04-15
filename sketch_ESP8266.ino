// Include Libraries
#include <espnow.h>
#include <ESP8266WiFi.h>

// Define a data structure
typedef struct struct_message {
  char a[32];
  bool button_clicked;
  bool entered_boolean_value;
} struct_message;

// Create a structured object
struct_message myData;

// Callback function executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println("Data received:");

  // Print received values
  Serial.print("Character Value: ");
  Serial.println(myData.a);
  Serial.print("Button Clicked: ");
  Serial.println(myData.button_clicked ? "True" : "False");
  Serial.print("Entered Boolean Value: ");
  Serial.println(myData.entered_boolean_value ? "True" : "False");
  Serial.println();
}

void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
  
  // Set ESP8266 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing to do in the loop for this receiver code
}
