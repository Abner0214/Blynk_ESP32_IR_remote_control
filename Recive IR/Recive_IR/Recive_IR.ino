#include <Arduino.h>
#include <IRremote.h>

const int irPin = 4;  // Change according to your GPIO connection

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK); // Initialize the receiver and enable feedback LED
  Serial.println("IR Receiver Initialized");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println("Received IR signal:");
    
    // Print raw data
    for (int i = 0; i < IrReceiver.decodedIRData.rawDataPtr->rawlen; i++) {
      Serial.print(IrReceiver.decodedIRData.rawDataPtr->rawbuf[i] * MICROS_PER_TICK);
      Serial.print(",");
    }
    Serial.println();

    IrReceiver.resume(); // Receive the next value
  }

  delay(1000);
}
