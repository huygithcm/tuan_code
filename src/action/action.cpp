#include "lib.h"
namespace main
{
    namespace action
    {

        uint8_t now_seconds = 0, last_seconds = 0, currentMillis = 0;
        state mode = WAIT;
        unsigned long previousMillis = 0;
        bool state_step;

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
            main::control_dc::setup();
            main::control_dc::setupBLDC();
            main::load_cell::setupLoadCell();
            main::time::setupds1307();
            main::data::setup();
            // previousMillis = millis();
            // state_step = true;
        }
        void loop()
        {
            main::time::readTime();
            main::control_dc::stepper.run(); // Không chặn chương trình, vẫn cho phép chạy các lệnh khác
            if (Serial2.available() > 0)
            {
                main::data::serialEvent();
            }
            if (now_seconds != last_seconds)
            {
                main::display::displayLCD();
                main::time::printTime();
                main::load_cell::readLoadCell();
                long position = main::control_dc::stepper.currentPosition();
                Serial.println(position);
                if(position >= -50)
                {   
                    main::control_dc::stepper.moveTo(-5); // Di chuyển đến vị trí 2000 bước
                }
                if(position == -5)
                {   
                    main::control_dc::stepper.moveTo(-50); // Di chuyển đến vị trí 2000 bước
                }

                last_seconds = now_seconds;
            }
            if (main::data::stringComplete)
            {
                main::data::getData();
            }
        }

    }

}