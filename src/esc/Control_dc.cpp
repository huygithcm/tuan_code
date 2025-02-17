#include "lib.h"
namespace main
{
    namespace control_dc
    {

        Servo esc, pul_step;

        AccelStepper stepper(AccelStepper::DRIVER, PUL, DIR);
        unsigned long previousMicros = 0;
        unsigned long currentMicros = 0;
        const long interval = 7000;
        uint8_t ao_cho_an = 1;
        uint8_t homeSteps = 50;
        uint8_t save_step = 0;
        bool direction = false;

        void control_step_motor_a1()
        {

            if (digitalRead(CTHT2) == LOW)
            {
                digitalWrite(DIR, LOW);
            }
            else if (digitalRead(CTHT2) != LOW)
            {
                digitalWrite(DIR, HIGH);
            }

            // Serial.print("Dang chay: ");
            // Serial.println(save_step);
        }
        void control_step_motor_a2()
        {

            digitalWrite(MF, LOW);
            if (digitalRead(CTHT2) == LOW)
            {
                digitalWrite(DIR, LOW);
            }
            else if (digitalRead(CTHT2) != LOW)
            {
                digitalWrite(DIR, HIGH);
            }
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
            // esc.writeMicroseconds(1600);
        }
        void setup()
        {
            stepper.setMaxSpeed(2000);
            stepper.setAcceleration(1500);
            // stepper.setMaxSpeed(500);
            // stepper.setAcceleration(200);
            
            // Di chuyển về home từ từ
            Serial.println("Homing...");
            stepper.setSpeed(300);  // Hướng về công tắc home
            while (digitalRead(CTHT2) != LOW) {
                stepper.runSpeed(); // Chạy với tốc độ cố định
            }
            
            stepper.setCurrentPosition(0);  // Đặt vị trí hiện tại là home (0)
            Serial.println("Home set!");
            stepper.moveTo(-70); // Di chuyển đến vị trí 2000 bước
            // digitalWrite(MF, HIGH);
            // pul_step.attach(PUL);
            // pul_step.writeMicroseconds(5000);
            // digitalWrite(MF, LOW);
            // digitalWrite(DIR, HIGH);

            // while (digitalRead(CTHT2) != LOW)
            // {
            //     digitalWrite(DIR, HIGH);

            //     // digitalWrite(MF, HIGH);
            // }
            // digitalWrite(DIR, LOW);
            // delay(1000);
            // digitalWrite(MF, HIGH);
            // pul_step.writeMicroseconds(0);
            // digitalWrite(DIR, HIGH);
            // quay về nhà yêu dấu
            // digitalWrite(DIR, HIGH);
            // for (long i = 0; i < homeSteps; i++)
            // {
            //     digitalWrite(PUL, HIGH);
            //     delayMicroseconds(7000);
            //     digitalWrite(PUL, LOW);
            //     delayMicroseconds(7000);
            // }
            Serial.println("Setup home done!");
            main::display::lcd.setCursor(0, 3);
            main::display::lcd.print("Setup home done!");
        }
    }

}
