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
#define PUL 10
#define DIR 11
#define CTHT2 3
#define CTHT1 25
#define MF 12
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

#define ADDRESS_EEPROM_OFFSET 0
#define ADDRESS_EEPROM_READING_OFFSET 0

namespace main
{
    namespace action
    {
        // extern unsigned long previousMillis;
        extern uint8_t now_seconds, last_seconds;
        enum state
        {
            RUN,
            STOP,
            WAIT
        };

        extern state mode;
        void setup();
        void loop();
    }
    namespace control_dc
    {
        extern Servo esc;
        void setup();
        void setupBLDC();

    }
    namespace display
    {
        extern LiquidCrystal_I2C lcd;
        extern char MENU[4][20];
        void setupLCD();
        void displayLCD();

    }
    namespace load_cell
    {
        extern HX711 scale;
        void calibrateLoadCell();
        void setupLoadCell();
        void readLoadCell();

    }
    namespace data
    {
        extern String inputString;
        extern  bool stringComplete;
        void getData();
        void setup();
        void serialEvent();
       
    }
    namespace time
    {
        extern RTC_DS1307 rtc;
        typedef struct
        {
            uint8_t hour;
            uint8_t min;
            uint8_t sec;
        } time;
        extern DateTime now;
        extern time thoiGian;
        void readTime();
        void setupds1307();
        void setTime(byte hr, byte min, byte sec);
        void printTime();
    }
}