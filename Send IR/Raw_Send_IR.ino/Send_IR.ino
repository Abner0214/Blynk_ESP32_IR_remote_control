#include <IRremoteESP8266.h>
#include <IRsend.h>

#define IR_LED_PIN 2  // Change this to the GPIO pin you've connected the IR LED to

#define FAN_SWITCH_RAW_DATA_LEN 68
uint16_t FAN_SWITCH_rawData[FAN_SWITCH_RAW_DATA_LEN] = {
  9030, 4466, 594, 558, 574, 558, 578, 558,
  574, 558, 578, 1662, 578, 1662, 578, 558,
  574, 558, 574, 1666, 578, 1662, 578, 1666,
  574, 1666, 574, 558, 578, 554, 578, 1662,
  578, 1662, 582, 554, 578, 554, 578, 558,
  578, 1662, 578, 554, 578, 554, 578, 558,
  578, 1662, 578, 1662, 578, 1662, 578, 1662,
  582, 554, 602, 1638, 578, 1662, 578, 1662,
  578, 554, 582, 1000
};

IRsend irsend(IR_LED_PIN);

void setup() {
  Serial.begin(115200);
  irsend.begin();
  Serial.println("irSender is ready");
}


int send_cnt = 0;
void loop() {
  ++send_cnt;
  Serial.print(" ===||-----------------> ");
  Serial.println(send_cnt);
  irsend.sendRaw(FAN_SWITCH_rawData, FAN_SWITCH_RAW_DATA_LEN, 38);  // Replace with your IR remote's frequency if different
  Serial.println("IR Signal Sent");
  delay(3000);                              // Adjust the delay as needed
}
