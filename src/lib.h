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
#define ESC_PIN 7
#define PUL 10 // chân step
#define DIR 11 // chân hướng
#define CTHT2 3  
#define CTHT1 25 
#define MF 12 // chân enable
#define DT_PIN 65
#define SCK_PIN 64  
#define BUTTON_PIN 22
#define speedBLDC 1200
#define SETUP_BLDC 1000
#define LOADCELL_DOUT_PIN 65
#define LOADCELL_SCK_PIN 64  
#define BUTTON_PIN 22
#define RULO_PIN 6
#define TRIAC_GATE_PIN 8                 
#define ZERO_CROSS_PIN 19
   

namespace main
{
    namespace action
    {
        extern unsigned long previousMillis;
        extern unsigned long currentMillis;
        void setup();
        void loop();
    }
    namespace control_dc
    {
        extern Servo esc;
        extern int homeSteps;
        extern int buoclui;
        void setup();
        void setupBLDC();
        void setHomeDC();
        void controlDC1(int lake1);
        void controlDC2(int lake2);

    }
    namespace display
    {
        extern LiquidCrystal_I2C lcd;
        void setupLCD();
        void displayLCD();

    }
    namespace load_cell
    {
        extern HX711 scale;
        extern float calibration_factor;
        extern float tare_weight;
        extern unsigned long buttonPressStart;
        extern bool buttonPressed;
        extern float weight_kg;
        extern float new_weight_kg;
        void calibrateLoadCell();
        void setupLoadCell();
        void readLoadCell();

    }
    namespace data
    {
        extern int lake1;
        extern int lake2;
        extern int hourOn1, minuteOn1;
        extern int hourOff1, minuteOff1;
        extern int hourOn2, minuteOn2;
        extern int hourOff2, minuteOff2;
        extern float kg, temp;
        extern int emergency;
        extern int stateLake1;
        extern int stateLake2;
        void receiveSerialData();
        float readEEPROMFloat(int address);
        void writeEEPROMFloat(int address, float value);
    }
    namespace time
    {
        extern RTC_DS1307 rtc;
        typedef struct
        {
            uint8_t hour;
            uint8_t minute;
            uint8_t second;
        } time;
        extern time thoiGian;
        extern int startHour1, startMinute1;
        extern int endHour1, endMinute1;
        extern int startHour2, startMinute2;
        extern int endHour2, endMinute2;
        void readTime();
        void caculateOFF2();
        void setupds1307();
        void setTime(byte hr, byte min, byte sec);
    }
    namespace temp
    {
        extern SHT31 sht;
      
        void setup();
        void main();
        void read_temp_sht30();
        void temp_control(int temp);

    }
}