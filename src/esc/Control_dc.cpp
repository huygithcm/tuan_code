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
            if (main::control_dc::stepper.currentPosition() == -200) {
                main::control_dc::stepper.moveTo(-50); // Di chuyển đến vị trí 2000 bước
            }
            if (main::control_dc::stepper.currentPosition() == -50) {
                main::control_dc::stepper.moveTo(-200); // Di chuyển đến vị trí 2000 bước
            }
        }
        void control_step_motor_a2()
        {
            if (main::control_dc::stepper.currentPosition() == -70) {
                main::control_dc::stepper.moveTo(-100); // Di chuyển đến vị trí 2000 bước
            }
            if (main::control_dc::stepper.currentPosition() == -100) {
                main::control_dc::stepper.moveTo(-70); // Di chuyển đến vị trí 2000 bước
            }
        }
        void setupBLDC()
        {
            esc.attach(ESC_PIN);
            esc.writeMicroseconds(SETUP_BLDC);
            delay(2000);
            // esc.writeMicroseconds(1600);
            digitalWrite(MF, LOW);
        }
        void setup()
        {
            stepper.setMaxSpeed(7000);
            stepper.setAcceleration(5000);
            // Di chuyển về home từ từ
            Serial.println("Homing...");
            stepper.setSpeed(500);  // Hướng về công tắc home

            while (digitalRead(CTHT2) != LOW) {
                stepper.runSpeed(); // Chạy với tốc độ cố định
            }
            stepper.setCurrentPosition(0);  // Đặt vị trí hiện tại là home (0)
            // stepper.move(-55); // Di chuyển đến vị trí 2000 bước
            Serial.println("Home set!");
            stepper.moveTo(-50); // Di chuyển đến vị trí 2000 bước
            stepper.runToPosition();
           
            Serial.println("Setup home done!");
            main::display::lcd.setCursor(0, 3);
            main::display::lcd.print("Setup home done!");
        }
    }

}
