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
#include <AccelStepper.h>
// #include <AFMotor.h>

#define ESC_PIN 7
#define PUL 10
#define DIR 11
#define CTHT2 3
#define CTHT1 25
#define MF 12
#define DT_PIN 65
#define SCK_PIN 64
#define BUTTON_PIN 22
#define SPEED_BLDC 1500
#define OFF_BLDC 1000
#define SETUP_BLDC 1000
#define LOADCELL_DOUT_PIN 65
#define LOADCELL_SCK_PIN 64
#define BUTTON_PIN 22
#define RULO_PIN 6
#define TRIAC_GATE_PIN 8
#define ZERO_CROSS_PIN 19

#define ADDRESS_EEPROM_OFFSET 0
#define ADDRESS_EEPROM_READING_OFFSET 0

#define POS_HOME -300
#define POS_A1_1 -250
#define POS_A1_0 -60

#define POS_A2_1 -800
#define POS_A2_0 -550

namespace main
{
    namespace action
    {
        // extern unsigned long previousMillis;
        extern uint8_t now_seconds, last_seconds;
        enum state
        {
            STOP,
            RUN,
            INPROCESS_1,
            INPROCESS_2,
            INPROCESS_3,
            MODE_2_AO,
            WAIT
        };

        extern state mode;
        void setup();
        void loop();
    }
    namespace control_dc
    {
        
        extern Servo esc;
        extern AccelStepper stepper;
        enum RUN_STATE
        {
            RUN,
            STOP,
            IN_PCSS,
            DONE,
            WAIT
        };
        extern RUN_STATE run_state_a1;
        extern RUN_STATE run_state_a2;
        void setup();
        void setupBLDC();
        void control_step_motor_a1();
        void control_step_motor_a2();

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
        extern  int weight_sen;
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
        extern time time_on_1, time_on_2, time_off_1, time_off_2, time_delay;
        void readTime();
        void setupds1307();
        void setTime(byte hr, byte min, byte sec);
        void cacula_time_off(uint8_t hou, uint8_t min, uint8_t sec, int set_timer);
        void printTime();
    }
}