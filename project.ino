void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String received_data = Serial.readStringUntil('\n');
    // Do something with the received data
    Serial.println("Received: " + received_data);
  }
}
