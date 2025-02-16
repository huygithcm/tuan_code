#include "lib.h"
namespace main
{
    namespace action
    {

        uint8_t now_seconds = 0, last_seconds = 0, previousMillis = 0, currentMillis = 0;
        state mode = WAIT;
        void setup()
        {
            Serial.begin(9600);

            pinMode(PUL, OUTPUT);
            pinMode(DIR, OUTPUT);
            pinMode(MF, OUTPUT);
            pinMode(CTHT2, INPUT_PULLUP);
            pinMode(CTHT1, INPUT_PULLUP);
            pinMode(RULO_PIN, OUTPUT);
            pinMode(ESC_PIN, OUTPUT);
            pinMode(ZERO_CROSS_PIN, INPUT);
            pinMode(TRIAC_GATE_PIN, OUTPUT);
            pinMode(BUTTON_PIN, INPUT_PULLUP);

            digitalWrite(MF, LOW);
            digitalWrite(TRIAC_GATE_PIN, LOW);

            main::display::setupLCD();

            // main::control_dc::setup();
            // main::control_dc::setupBLDC();
            main::load_cell::setupLoadCell();
            main::time::setupds1307();
            main::data::setup();
        }
        void loop()
        {
            main::time::readTime();
            if (Serial2.available() > 0)
            {
                main::data::serialEvent();
            }
            if (now_seconds != last_seconds)
            {
                main::display::displayLCD();
                main::time::printTime();
                main::load_cell::readLoadCell();
                last_seconds = now_seconds;
            }
            if (main::data::stringComplete)
            {
                main::data::getData();
            }
        }

    }

}