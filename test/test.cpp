#include "Arduino.h"
#include "Wire.h"
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <SPI.h>
#include "HX711.h"
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <SHT31.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Bắt đầu xóa toàn bộ EEPROM...");
    
    for (int i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0xFF); // Ghi giá trị 255 (0xFF) vào tất cả các ô nhớ
    }

    Serial.println("Xóa xong toàn bộ EEPROM!");
}

void loop() {
    // Không cần làm gì trong loop
}
