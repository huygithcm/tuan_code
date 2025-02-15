#include "lib.h"
namespace main
{
    namespace action
    {

        static unsigned long previousMillis = 0;

        void setup()
        {
            Serial.begin(115200);
            pinMode(RULO_PIN, OUTPUT);
            pinMode(PUL, OUTPUT);
            pinMode(DIR, OUTPUT);
            pinMode(MF, OUTPUT);
            pinMode(CTHT2, INPUT_PULLUP);
            pinMode(CTHT1, INPUT_PULLUP);
            pinMode(RULO_PIN, OUTPUT);
            pinMode(BUTTON_PIN, INPUT_PULLUP);
            pinMode(ESC_PIN, OUTPUT);
            pinMode(ZERO_CROSS_PIN, INPUT);
            pinMode(TRIAC_GATE_PIN, OUTPUT);
            pinMode(BUTTON_PIN, INPUT_PULLUP);
            digitalWrite(MF, LOW);
            digitalWrite(TRIAC_GATE_PIN, LOW);

            main::display::setupLCD();
            main::control_dc::setup();
            main::control_dc::setupBLDC();
            main::load_cell::setupLoadCell();
            main::time::setupds1307();
            // main::temp::setup();
        }
        void loop()
        {
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis >= 1000)
            {
                previousMillis = currentMillis;
                main::load_cell::readLoadCell();
                main::time::readTime();
            }
            // main::load_cell::calibrateLoadCell();
            // unsigned long currentMillis = millis();
            // if (currentMillis - previousMillis >= 1000)
            // {
            //     previousMillis = currentMillis;
            //     main::display::displayLCD();
            // }
            // main::time::readTime();
            // main::data::receiveSerialData();
            // main::time::caculateOFF2();
        }

    }

}