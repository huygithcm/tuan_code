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
        RUN_STATE run_state_a1 = WAIT;
        RUN_STATE run_state_a2 = WAIT;

        // tới giờ -
        void control_step_motor_a1()
        {
            if (run_state_a1 == IN_PCSS)
            {
                if (main::control_dc::stepper.currentPosition() == POS_A1_1)
                {
                    main::control_dc::stepper.moveTo(POS_A1_0); // Di chuyển đến vị trí 2000 bước
                    Serial.println("POS_A1_0");
                  
                }
                if (main::control_dc::stepper.currentPosition() == POS_A1_0)
                {
                    main::control_dc::stepper.moveTo(POS_A1_1); // Di chuyển đến vị trí 2000 bước
                    Serial.println("POS_A1_1");
                 
                }
            }
        }
        void control_step_motor_a2()
        {
            if (run_state_a2 == IN_PCSS)
            {
                if (main::control_dc::stepper.currentPosition() == POS_A2_0)
                {
                    main::control_dc::stepper.moveTo(POS_A2_1); // Di chuyển đến vị trí 2000 bước
                    Serial.println("POS_A2_1");
                    delay(1000);
                }
                if (main::control_dc::stepper.currentPosition() == POS_A2_1)
                {
                    main::control_dc::stepper.moveTo(POS_A2_0); // Di chuyển đến vị trí 2000 bước
                    Serial.println("POS_A2_0");
                }
            }
        }
        void setupBLDC()
        {
            esc.attach(ESC_PIN);
            esc.writeMicroseconds(SETUP_BLDC);
            delay(2000);
            // esc.writeMicroseconds(1300);
            digitalWrite(MF, LOW);
        }
        void setup()
        {
            stepper.setMaxSpeed(10000);
            stepper.setAcceleration(2000);

            Serial.println("Homing...");
            stepper.setSpeed(300); // Hướng về công tắc home

            while (digitalRead(CTHT2) != LOW)
            {
                stepper.runSpeed(); // Chạy với tốc độ cố định
            }
            stepper.setCurrentPosition(0); // Đặt vị trí hiện tại là home (0)
            stepper.moveTo(POS_HOME);          // Di chuyển đến vị trí 2000 bước
            stepper.runToPosition();
            Serial.println("Home set!");
            Serial.println("Setup home done!");
            main::display::lcd.setCursor(0, 3);
            main::display::lcd.print("Setup home done!");
        }
    }

}
