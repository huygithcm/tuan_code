#include "lib.h"
namespace main
{
    namespace control_dc
    {
        /**
         * @brief Khai báo các chân cho mô tơ bước
         *
         */
        Servo esc;
        int homeSteps = 50;
        unsigned long previousMicros = 0;
        unsigned long currentMicros = 0;
        const long interval = 7000;
        uint8_t ao_cho_an = 1;
        uint8_t stepvalue = 0;

        void control_step_motor()
        {
            Serial.println(ao_cho_an);
            
            if (ao_cho_an == 1)
            {
                
                if (digitalRead(CTHT2) != LOW &&  stepvalue < 50)
                {
                    digitalWrite(DIR, LOW);
                    digitalWrite(PUL, !digitalRead(PUL)); 
                }
                else
                {
                    digitalWrite(DIR, HIGH);
                    digitalWrite(PUL, !digitalRead(PUL));
                }
            }

            if (ao_cho_an == 2)
            {

                if (digitalRead(CTHT1) != LOW)
                {
                    digitalWrite(DIR, LOW);
                    digitalWrite(PUL, !digitalRead(PUL));
                }
                else
                {
                    digitalWrite(DIR, HIGH);
                    digitalWrite(PUL, !digitalRead(PUL));
                }
            }
        }

        void setupBLDC()
        {
            esc.attach(ESC_PIN);
            esc.writeMicroseconds(SETUP_BLDC);
            delay(2000);
        }
        void setup()
        {

            digitalWrite(DIR, HIGH);
            while (digitalRead(CTHT2) != LOW)
            {
                digitalWrite(PUL, HIGH);
                delayMicroseconds(7000);
                digitalWrite(PUL, LOW);
                delayMicroseconds(7000);
            }
            // quay về nhà yêu dấu
            digitalWrite(DIR, LOW);
            for (long i = 0; i < homeSteps; i++)
            {
                digitalWrite(PUL, HIGH);
                delayMicroseconds(7000);
                digitalWrite(PUL, LOW);
                delayMicroseconds(7000);
            }
            Serial.println("Setup home done!");
            main::display::lcd.setCursor(0, 3);
            main::display::lcd.print("Setup home done!");
        }
    }

}
