#include "lib.h"
namespace main
{
    namespace control_dc
    {

        Servo esc;
        unsigned long previousMicros = 0;
        unsigned long currentMicros = 0;
        const long interval = 7000;
        uint8_t ao_cho_an = 1;
        uint8_t homeSteps = 50;
        uint8_t save_step = 0;
        bool direction = false;

        void control_step_motor_a1()
        {
            
                if (digitalRead(CTHT2) != LOW && direction == true) // chạy theo chiều dương.
                {
                    digitalWrite(DIR, LOW);
                    digitalWrite(PUL, !digitalRead(PUL)); 
                    save_step++;
                    if(save_step == homeSteps)
                    {
                        direction = false;
                    }
                }
                if (digitalRead(CTHT2) != LOW && direction == false)
                {
                    digitalWrite(DIR, HIGH);
                    digitalWrite(PUL, !digitalRead(PUL));
                    save_step--;
                    if(save_step == 0)
                    {
                        direction = true;
                    }
                }
                if (digitalRead(CTHT2) == LOW)
                {
                    save_step=0;
                    direction = true;
                }
                // Serial.print("Dang chay: ");
                // Serial.println(save_step);
        }
        void control_step_motor_a2()
        {
          

                // if (digitalRead(CTHT1) == LOW)
                // {
                //     digitalWrite(DIR, LOW);
                //     digitalWrite(PUL, !digitalRead(PUL)); 
                //     stepvalue = 0;
                // }
                // else if (digitalRead(CTHT1) != LOW)
                // {
                //     digitalWrite(DIR, HIGH);
                //     digitalWrite(PUL, !digitalRead(PUL));
                //     stepvalue = 0;
                // }
            
        }
        void setupBLDC()
        {
            esc.attach(ESC_PIN);
            esc.writeMicroseconds(SETUP_BLDC);
            delay(2000);
            esc.writeMicroseconds(1300);
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
