#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Gree.h>

const uint16_t kIrLedPin = 4;  // ESP32的GPIO引腳，連接到紅外線發射器
IRsend irsend(kIrLedPin);      // 創建IRsend實例

void setup() {
  irsend.begin();  // 初始化IRsend
  Serial.begin(115200);
}

void loop() {
  // 創建一個 Gree AC 控制物件
  IRGreeAC ac(kIrLedPin);

  ac.begin();  // 初始化 Gree AC 物件
  ac.on();     // 開啟冷氣
  ac.setMode(kGreeCool); // 設定模式為製冷
  ac.setFan(kGreeFanAuto); // 設定風扇速度為自動
  ac.setTemp(24); // 設定溫度為 24 度
  ac.setXFan(false); // 關閉額外的風扇功能
  ac.setLight(false); // 關閉顯示燈

  // 發送信號
  ac.send();

  delay(10000); // 等待 10 秒
}
