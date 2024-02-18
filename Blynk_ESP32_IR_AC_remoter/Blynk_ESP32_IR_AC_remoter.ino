#define BLYNK_TEMPLATE_ID "TMPL6FbQuBtzp"
#define BLYNK_TEMPLATE_NAME "AC IR remoter"
#define BLYNK_AUTH_TOKEN "TY_KsPR1f2rggjYTKoRCIxaLWSE1vh7N"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <IRremoteESP8266.h>
#include <ir_Gree.h>
#include <DHT.h>

#define DHTPIN 2     // Change the pin according to your setup
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


// Replace with your network credentials
const char* ssid = "LONG_MAX";
const char* password = "00000000";

// Replace with your unique Blynk Auth Token

char auth[] = "TY_KsPR1f2rggjYTKoRCIxaLWSE1vh7N";

const uint16_t kIrLedPin = 4;  // The GPIO pin number where IR emitter is connected
IRGreeAC ac(kIrLedPin);  // Replace with your AC brand

BlynkTimer timer;

bool acIsOn = false;
// This function will be called every time device connected to Virtual Pin V2
BLYNK_WRITE(V2) {
  int pinValue = param.asInt(); // Assigning incoming value from pin V2 to a variable

  if (pinValue == 1) {
    ac.begin();
    ac.on();
    acIsOn = true;
    Serial.println("Turn on AC");
    ac.send();
  } else {
    ac.begin();
    ac.off();
    acIsOn = false;
    Serial.println("Turn off AC");
    ac.send();
  }
}


// This function will be called every time device connected to Virtual Pin V4
BLYNK_WRITE(V4) {
  int temperature = param.asInt(); // Assigning incoming value from pin V4 to a variable

  if (temperature >= 16 && temperature <= 30) {
    ac.begin();
    ac.setTemp(temperature);
    if (acIsOn) {
      ac.on();
    }
    Serial.print("AC temperature: ");
    Serial.println(temperature);
    ac.send();
  }
}


// This function will be called every time device connected to Virtual Pin V3
BLYNK_WRITE(V3) {
  int mode = param.asInt(); // Assigning incoming value from pin V3 to a variable

  ac.begin();
  switch (mode+1) {
    case 0:
      ac.setMode(kGreeCool);
      Serial.println("AC mode: Cool");
      break;
    case 1:
      ac.setMode(kGreeHeat);
      Serial.println("AC mode: Heat");
      break;
    case 2:
      ac.setMode(kGreeDry);
      Serial.println("AC mode: Dry");
      break;
    case 3:
      ac.setMode(kGreeFan);
      Serial.println("AC mode: Fan");
      break;
    case 4:
      ac.setMode(kGreeAuto);
      Serial.println("AC mode: Auto");
      break;
    default:
      Serial.println("Invalid mode");
      return;
  }
  ac.send();
}

void sendSensorData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // By default, the temperature is in Celsius

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, temperature);
  Serial.print("temperature: ");
  Serial.println(temperature);
  Blynk.virtualWrite(V1, humidity);
  Serial.print("humidity: ");
  Serial.println(humidity);
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
  ac.begin();  // Modify as needed for your AC
  Serial.println("AC ready!!");
  dht.begin();
  Serial.println("DHT11 ready!!");
  timer.setInterval(2000L, sendSensorData); // Set the interval to 2 seconds (2000 milliseconds)
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
