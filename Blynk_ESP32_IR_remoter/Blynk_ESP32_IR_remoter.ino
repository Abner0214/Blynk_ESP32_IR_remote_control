// *** MAIN SETTINGS ***
// Replace this block with correct template settings.
// You can find it for every template here:
//
//   https://blynk.cloud/dashboard/templates

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "DHT.h"
#define DHT_PIN 4
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

#define BLYNK_TEMPLATE_ID "TMPL6Py1k1g9B"
#define BLYNK_TEMPLATE_NAME "LED ESP32"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

#include "BlynkEdgent.h"

#define IR_LED_PIN 2  // Change this to the GPIO pin you've connected the IR LED to
//			| PWOER |
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
//			| Oscillation |
#define FAN_OSC_RAW_DATA_LEN 68
uint16_t FAN_OSC_rawData[FAN_OSC_RAW_DATA_LEN] = {
  9030, 4482, 578, 554, 578, 554, 578, 554,
  582, 554, 578, 1658, 582, 1658, 582, 554,
  578, 554, 578, 1662, 578, 1662, 602, 1638,
  578, 1658, 582, 554, 578, 554, 578, 1662,
  578, 1662, 606, 1634, 578, 554, 606, 1634,
  582, 554, 578, 554, 578, 554, 582, 554,
  578, 1662, 578, 554, 578, 1662, 582, 554,
  578, 1662, 578, 1662, 578, 1662, 578, 1662,
  578, 554, 578, 1000
};
//			| Fan speed up |
#define FAN_SPEED_UP_RAW_DATA_LEN 68
uint16_t FAN_SPEED_UP_rawData[FAN_SPEED_UP_RAW_DATA_LEN] = {
  9034, 4482, 578, 554, 578, 558, 578, 554,
  578, 558, 578, 1662, 578, 1662, 578, 558,
  578, 554, 578, 1662, 578, 1662, 578, 1662,
  578, 1666, 578, 554, 578, 558, 578, 1662,
  578, 1662, 582, 554, 578, 1662, 578, 1662,
  578, 558, 578, 554, 578, 558, 578, 554,
  578, 1662, 578, 1662, 578, 558, 578, 554,
  578, 1662, 578, 1666, 574, 1666, 578, 1662,
  578, 558, 578, 1000
};
//			| Fan speed down |
#define FAN_SPEED_DOWN_RAW_DATA_LEN 68
uint16_t FAN_SPEED_DOWN_rawData[FAN_SPEED_DOWN_RAW_DATA_LEN] = {
  9014, 4482, 578, 554, 578, 558, 578, 554,
  578, 554, 578, 1662, 582, 1662, 578, 554,
  578, 554, 578, 1666, 578, 1658, 582, 1662,
  578, 1662, 578, 554, 578, 554, 582, 1662,
  578, 1662, 578, 1662, 578, 1662, 578, 1662,
  582, 554, 578, 554, 606, 526, 582, 554,
  578, 1662, 578, 554, 582, 554, 578, 554,
  578, 1662, 578, 1662, 582, 1658, 582, 1658,
  582, 554, 578, 1000
};

IRsend irsend(IR_LED_PIN);

// V0 is a datastream used to transfer and store LED switch state.
// Evey time you use the LED switch in the app, this function
// will listen and update the state on device
// Power
BLYNK_WRITE(V0) {
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:
  int value = param.asInt();

  if (value == 1) {
    Serial.print("value = ");
    Serial.println(value);
    irsend.sendRaw(FAN_SWITCH_rawData, FAN_SWITCH_RAW_DATA_LEN, 38);  // Replace with your IR remote's frequency if different
    Serial.println("IR Signal Sent (Power on)");
    delay(100);
  } else {
    Serial.print("value = ");
    Serial.println(value);
    irsend.sendRaw(FAN_SWITCH_rawData, FAN_SWITCH_RAW_DATA_LEN, 38);  // Replace with your IR remote's frequency if different
    Serial.println("IR Signal Sent (Power off)");
    delay(100);
  }
}
// Oscillation
BLYNK_WRITE(V4) {
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:
  int value = param.asInt();

  if (value == 1) {
    Serial.print("value = ");
    Serial.println(value);
    irsend.sendRaw(FAN_OSC_rawData, FAN_OSC_RAW_DATA_LEN, 38);  // Replace with your IR remote's frequency if different
    Serial.println("IR Signal Sent (Oscillation on)");
    delay(100);
  } else {
    Serial.print("value = ");
    Serial.println(value);
    irsend.sendRaw(FAN_OSC_rawData, FAN_OSC_RAW_DATA_LEN, 38);  // Replace with your IR remote's frequency if different
    Serial.println("IR Signal Sent (Oscillation off)");
    delay(100);
  }
}
// Fan speed
BLYNK_WRITE(V3) {
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:
  int value = param.asInt();
  
  if (value > 0) {  // Fan speed +
    Serial.print("value = ");
    Serial.println(value);
    for (int i = 0;  i < value;  ++i) {
      irsend.sendRaw(FAN_SPEED_UP_rawData, FAN_SPEED_UP_RAW_DATA_LEN, 38);  // Replace with your IR remote's frequency if different
      Serial.println("IR Signal Sent (Fan speed up)");
      delay(100);
    }
    Serial.print("Fan speed +");
    Serial.println(value);
  } else if (value > 0) {  // Fan speed -
    Serial.print("value = ");
    Serial.println(value);
    for (int i = 0;  i < value;  ++i) {
      irsend.sendRaw(FAN_SPEED_DOWN_rawData, FAN_SPEED_DOWN_RAW_DATA_LEN, 38);  // Replace with your IR remote's frequency if different
      Serial.println("IR Signal Sent (Fan speed down)");
      delay(100);
    }
    Serial.print("Fan speed ");
    Serial.println(value);
  }
}

void setup() {
  // Debug console. Make sure you have the same baud rate selected in your serial monitor
  Serial.begin(115200);
  delay(100);
  BlynkEdgent.begin();
  Serial.println("Blynk is ready");
  irsend.begin();
  Serial.println("irSender is ready");
}

int loop_cnt = 0;
void loop() {
  ++loop_cnt;
  Serial.print("+++++++ NEW LOOP +++++++: ");
  Serial.println(loop_cnt);
  // Blynk
  BlynkEdgent.run();
  delay(10);
  // dht11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // check read
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor.");
    delay(2000);
    return;
  }
  Blynk.virtualWrite(V1, t);
  Serial.print("Temperature: ");
  Serial.println(t);
  Blynk.virtualWrite(V2, h);
  Serial.print("Humidity: ");
  Serial.println(h);

  delay(2000);
}