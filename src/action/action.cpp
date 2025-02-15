#include "lib.h"
namespace main
{
    namespace action
    {

        unsigned long previousMillis = 0;
        unsigned long currentMillis = 0;
        void setup()
        {
            Serial.begin(115200);
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
            main::control_dc::setup();
            main::control_dc::setupBLDC();
            main::load_cell::setupLoadCell();
            main::time::setupds1307();
            currentMillis = millis();
        }
        void loop()
        {
            currentMillis = millis();
            if (currentMillis - previousMillis > 1000)
            {
                main::load_cell::readLoadCell();
                main::time::readTime();
                main::display::displayLCD();
                previousMillis = currentMillis;
            }

        }

    }

}