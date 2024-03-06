// *** MAIN SETTINGS ***
#define BLYNK_TEMPLATE_ID "TMPL6Py1k1g9B"
#define BLYNK_TEMPLATE_NAME "LED ESP32"  // copy from Blynk's template
#define BLYNK_AUTH_TOKEN "v65kZep5AZyblGds4balWknDIH1dv8wk"
//
//   https://blynk.cloud/dashboard/templates

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <DHT.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

#define IR_LED_PIN 4  // Change this to the GPIO pin you've connected the IR LED to

// Replace with your network credentials
const char* ssid = "LONG_MAX";
const char* password = "00000000";
// Replace with your unique Blynk Auth Token
char auth[] = "v65kZep5AZyblGds4balWknDIH1dv8wk";

BlynkTimer timer;

// The IR raw data of my fan
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
  } else if (value < 0) {  // Fan speed -
    Serial.print("value = ");
    Serial.println(value);
    value *= -1;
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
  // Debug console
  Serial.begin(115200);
  delay(100);

  // Connect to Wi-Fi
  int try_times = 0;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    ++try_times;
    Serial.print("Try to connect Wifi: ");
    Serial.println(try_times);
  }
  Serial.println("\n Wifi successfully connected!");

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  Serial.println("Blynk ready!!");
  // Initialize AC object
  irsend.begin();
  Serial.println("irSender is ready");

  dht.begin();
  Serial.println("DHT11 ready!!");
  
  timer.setInterval(2000L, sendSensorData); // Set the interval to 2 seconds (2000 milliseconds)  
}

void sendSensorData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // By default, the temperature is in Celsius

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, temperature);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Blynk.virtualWrite(V2, humidity);
  Serial.print("Humidity: ");
  Serial.println(humidity);
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}