#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  // Bluetooth device name
  SerialBT.begin("Jacob's Radio Device"); 
  // Initialize Serial2 for communication with Arduino Mega
  Serial2.begin(9600); 
}

void loop() {
  if (SerialBT.available()) {
    char receivedChar = SerialBT.read();
    // Send the received character to the Arduino Mega via Serial2
    Serial2.write(receivedChar); 
  }
  delay(20);
}
