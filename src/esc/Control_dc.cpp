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


        // void controlDC1(int lake1)
        // {
        //     if (lake1 == 0)
        //     {
        //         digitalWrite(MF, HIGH);
        //         digitalWrite(RULO_PIN, LOW);
        //     }
        //     else if (lake1 == 1)
        //     {
        //         digitalWrite(MF, LOW);
        //         digitalWrite(DIR, HIGH);

        //         for (int i = 0; i < (homeSteps - buoclui); i++)
        //         {
        //             unsigned long currentMicros = micros();
        //             if (currentMicros - previousMicros >= interval)
        //             {
        //                 digitalWrite(RULO_PIN, HIGH);
        //                 esc.writeMicroseconds(speedBLDC);
        //                 digitalWrite(PUL, HIGH);
        //                 previousMicros = currentMicros;
        //             }
        //             else
        //             {
        //                 digitalWrite(RULO_PIN, LOW);
        //                 digitalWrite(PUL, LOW);
        //             }
        //         }
        //         digitalWrite(DIR, LOW);
        //         for (int i = 0; i < homeSteps; i++)
        //         {
        //             unsigned long currentMicros = micros();
        //             if (currentMicros - previousMicros >= interval)
        //             {
        //                 digitalWrite(RULO_PIN, HIGH);
        //                 esc.writeMicroseconds(speedBLDC);
        //                 digitalWrite(PUL, HIGH);
        //                 previousMicros = currentMicros;
        //             }
        //             else
        //             {
        //                 digitalWrite(RULO_PIN, LOW);
        //                 digitalWrite(PUL, LOW);
        //             }
        //         }
        //     }
        // }

        // void controlDC2(int lake2)
        // {
          
        //     if (lake2 == 0)
        //     {
        //         digitalWrite(MF, HIGH);
        //         digitalWrite(RULO_PIN, LOW);
        //     }
        //     if (lake2 == 2)
        //     {
        //         digitalWrite(MF, LOW);
        //         digitalWrite(DIR, LOW);
        //         for (int i = 0; i < homeSteps ; i++)
        //         {
        //             unsigned long currentMicros = micros();
        //             if (currentMicros - previousMicros >= interval)
        //             {
        //                 digitalWrite(RULO_PIN, HIGH);
        //                 esc.writeMicroseconds(speedBLDC);
        //                 digitalWrite(PUL, HIGH);
        //                 previousMicros = currentMicros;
        //             }
        //             else
        //             {
        //                 digitalWrite(RULO_PIN, LOW);
        //                 digitalWrite(PUL, LOW);
        //             }
        //         }
        //         digitalWrite(DIR, HIGH);
        //         for (int i = 0; i < (homeSteps - buoclui); i++)
        //         {
        //             unsigned long currentMicros = micros();
        //             if (currentMicros - previousMicros >= interval)
        //             {
        //                 digitalWrite(RULO_PIN, HIGH);
        //                 esc.writeMicroseconds(speedBLDC);
        //                 digitalWrite(PUL, HIGH);
        //                 previousMicros = currentMicros;
        //             }
        //             else
        //             {
        //                 digitalWrite(RULO_PIN, LOW);
        //                 digitalWrite(PUL, LOW);
        //             }
        //         }
        //     }
        // }
    }

}
