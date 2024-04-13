void setup() {
  Serial.begin(115200); // Initialize serial communication with baud rate 115200
}

void loop() {
  if (Serial.available()) {
    String receivedMessage = Serial.readStringUntil('\n'); // Read the incoming message
    Serial.print("Received Message: "); 
    Serial.println(receivedMessage); // Print the received message
  }
}
