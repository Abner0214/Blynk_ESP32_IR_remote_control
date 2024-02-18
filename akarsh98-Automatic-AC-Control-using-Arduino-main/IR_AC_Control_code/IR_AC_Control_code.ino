/* rawSend.ino Example sketch for IRLib2
 *  Illustrates how to send a code Using raw timings which were captured
 *  from the "rawRecv.ino" sample sketch.  Load that sketch and
 *  capture the values. They will print in the serial monitor. Then you
 *  cut and paste that output into the appropriate section below.
 */
#include <IRLibSendBase.h>  //We need the base code
#include <IRLib_HashRaw.h>  //Only use raw sender
// #include "DHT.h"

// #define DHT_PIN 34  // Analog Pin sensor is connected to
// #define DHT_TYPE DHT11

// DHT dht(DHT_PIN, DHT_TYPE);

IRsendRaw mySender;

void setup() {
  Serial.begin(9600);
  delay(2000);
  while (!Serial)
    ;  //delay for Leonardo
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
}
/* Cut and paste the output from "rawRecv.ino" below here. It will 
 * consist of a #define RAW_DATA_LEN statement and an array definition
 * beginning with "uint16_t rawData[RAW_DATA_LEN]= {…" and concludes
 * with "…,1000};"
 */
#define RAW_DATA_LEN 100
uint16_t rawDataOff[RAW_DATA_LEN] = {
  5926, 7454, 498, 3466, 498, 3466, 522, 3442,
  526, 3438, 498, 3466, 498, 1470, 498, 1498,
  498, 3438, 502, 1494, 498, 1474, 494, 1474,
  498, 1494, 498, 1474, 498, 3466, 498, 3466,
  498, 1470, 498, 1470, 498, 3466, 498, 3466,
  522, 3442, 498, 1498, 498, 1470, 498, 3466,
  498, 1470, 498, 3466, 522, 1446, 498, 1498,
  498, 1470, 498, 3466, 498, 3466, 498, 1470,
  498, 3466, 498, 3466, 498, 1470, 502, 3462,
  498, 1498, 498, 3466, 498, 1470, 498, 1470,
  502, 1470, 498, 1494, 502, 3462, 498, 1474,
  498, 3462, 502, 1470, 522, 3442, 498, 3466,
  498, 3466, 498, 1000
};

#define RAW_DATA_LEN 100
uint16_t rawDataOn[RAW_DATA_LEN] = {
  5902, 7478, 502, 3466, 498, 3466, 494, 3466,
  502, 3466, 498, 3462, 502, 1470, 498, 1470,
  498, 3466, 498, 1470, 498, 1498, 498, 1470,
  498, 1470, 498, 1498, 498, 3466, 498, 3466,
  498, 1470, 498, 1470, 498, 3466, 498, 3466,
  498, 1474, 498, 1494, 498, 1474, 498, 3466,
  498, 1470, 498, 3466, 498, 1470, 498, 1498,
  498, 3466, 498, 3466, 498, 3466, 494, 1474,
  498, 3466, 498, 3466, 494, 1474, 498, 3466,
  498, 1470, 498, 3466, 498, 1498, 498, 1470,
  498, 1470, 498, 1474, 498, 3462, 526, 1470,
  498, 3466, 498, 1470, 498, 3466, 498, 3466,
  498, 3466, 498, 1000
};


#define FAN_SWITCH_RAW_DATA_LEN 68
uint16_t FAN_SWITCH_rawData[RAW_DATA_LEN]={
	9030, 4466, 594, 558, 574, 558, 578, 558, 
	574, 558, 578, 1662, 578, 1662, 578, 558, 
	574, 558, 574, 1666, 578, 1662, 578, 1666, 
	574, 1666, 574, 558, 578, 554, 578, 1662, 
	578, 1662, 582, 554, 578, 554, 578, 558, 
	578, 1662, 578, 554, 578, 554, 578, 558, 
	578, 1662, 578, 1662, 578, 1662, 578, 1662, 
	582, 554, 602, 1638, 578, 1662, 578, 1662, 
	578, 554, 582, 1000};


/*
 * Cut-and-paste into the area above.
 */

void loop() {

  // DHT.read11(dht_apin);
  // float t = dht.readTemperature();
  // Serial.print("temperature = ");
  // Serial.print(t);
  // Serial.println(" C");
  // int temp = 30;/////////////////////////////////////////////////////
  // if (temp > 29) {
  //   mySender.send(rawDataOn, RAW_DATA_LEN, 36);  //Pass the buffer,length, optionally frequency
  //   Serial.println(F("AC Switched On"));
  // } else if (temp < 26) {
  //   mySender.send(rawDataOff, RAW_DATA_LEN, 36);  //Pass the buffer,length, optionally frequency
  //   Serial.println(F("AC Switched Off"));
  // }

  mySender.send(FAN_SWITCH_rawData, FAN_SWITCH_RAW_DATA_LEN, 38);  //Pass the buffer,length, optionally frequency
  Serial.println(F("Fan Switched On"));

  delay(3000);
}
