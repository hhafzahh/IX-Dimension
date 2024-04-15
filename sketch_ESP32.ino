// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

// Button Pin Definition
const int buttonPin = 5;  // Button connected to GPIO2 (D4)

// Variables for boolean values
bool button_clicked = false;
bool entered_boolean_value = true;

// MAC Address of receiver (ESP8266) - edit as required
uint8_t receiverAddress[] = {0x44, 0x17, 0x93, 0x0F, 0xCD, 0x78};

// Define a data structure
typedef struct struct_message {
  char a[32];
  bool button_clicked;
  bool entered_boolean_value;
} struct_message;

// Create a structured object
struct_message myData;

// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  
  // Set up Serial Monitor
  Serial.begin(115200);
 
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer (ESP8266 receiver)
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  // Initialize button pin
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {

  // Read button state
  int buttonState = digitalRead(buttonPin);

  // If button is clicked
  if (buttonState == LOW && !button_clicked) {
    button_clicked = true;
    
    // Format structured data
    strcpy(myData.a, "Button Clicked");
    myData.button_clicked = button_clicked;
    myData.entered_boolean_value = entered_boolean_value;
    
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(receiverAddress, (uint8_t *) &myData, sizeof(myData));
     
    if (result == ESP_OK) {
      Serial.println("Sending confirmed");
    }
    else {
      Serial.println("Sending error");
    }
  } else if (buttonState == HIGH && button_clicked) {
    button_clicked = false;
  }
  
  delay(200); // Debounce delay
}
