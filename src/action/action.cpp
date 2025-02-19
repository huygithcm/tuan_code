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

            // digitalWrite(MF, LOW);
            digitalWrite(TRIAC_GATE_PIN, LOW);
            main::display::setupLCD();
            main::control_dc::setup();
            main::control_dc::setupBLDC();
            main::load_cell::setupLoadCell();
            main::time::setupds1307();
            main::data::setup();
            
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
                String dataToSend = "WEIGHT/" + String(main::load_cell::weight_sen);
                Serial2.println(dataToSend);
                last_seconds = now_seconds;
                
                if (action::mode == WAIT && main::time::time_on_1.hour == main::time::now.hour() && main::time::time_on_1.min == main::time::now.minute() && main::time::time_on_1.sec  == main::time::now.second())
                {
                    Serial.println("TOI THOI GIAN BAT 1");
                    action::mode = RUN;
                    
                }
                if (action::mode == WAIT && main::time::time_on_2.hour == main::time::now.hour() && main::time::time_on_2.min == main::time::now.minute() && main::time::time_on_2.sec  == main::time::now.second())
                {
                    Serial.println("TOI THOI GIAN BAT 2");
                    action::mode = RUN;
                }

                if(action::mode == INPROCESS_2 && main::time::time_off_1.hour == main::time::now.hour() && main::time::time_off_1.min == main::time::now.minute() && main::time::time_off_1.sec  == main::time::now.second())
                {
                
                    if( main::control_dc::run_state_a1 == control_dc::RUN_STATE::IN_PCSS && main::control_dc::run_state_a2 == control_dc::RUN_STATE::WAIT)
                    {
                        main::control_dc::stepper.moveTo(POS_A2_0);
                        main::control_dc::run_state_a1 = control_dc::RUN_STATE::WAIT;
                        main::control_dc::run_state_a2 = control_dc::RUN_STATE::IN_PCSS;
                        main::time::cacula_time_off(main::time::time_delay.hour, main::time::time_delay.min, main::time::time_delay.sec, 2);
                        Serial.println("BAT DAU CHU TRINH 3");
                        action::mode = INPROCESS_3;
                    }

                    if( main::control_dc::run_state_a1 == control_dc::RUN_STATE::IN_PCSS && main::control_dc::run_state_a2 == control_dc::RUN_STATE::STOP)
                    {
                        main::control_dc::stepper.moveTo(POS_HOME);
                        main::control_dc::run_state_a1 = control_dc::RUN_STATE::WAIT;
                        main::control_dc::run_state_a2 = control_dc::RUN_STATE::STOP;
                        Serial.println("TAT CHU TRINH 1");
                        action::mode = WAIT;
                    }

                    if( main::control_dc::run_state_a1 == control_dc::RUN_STATE::STOP && main::control_dc::run_state_a2 == control_dc::RUN_STATE::IN_PCSS)
                    {
                        main::control_dc::stepper.moveTo(POS_HOME);
                        main::control_dc::run_state_a1 = control_dc::RUN_STATE::STOP;
                        main::control_dc::run_state_a2 = control_dc::RUN_STATE::WAIT;
                        Serial.println("TAT CHU TRINH 2");
                        action::mode = WAIT;
                    }
                }

                if(action::mode == INPROCESS_3 && main::time::time_off_2.hour == main::time::now.hour() && main::time::time_off_2.min == main::time::now.minute() && main::time::time_off_2.sec  == main::time::now.second())
                {
                    main::control_dc::run_state_a1 = control_dc::RUN_STATE::WAIT;
                    main::control_dc::run_state_a2 = control_dc::RUN_STATE::WAIT;
                    action::mode = WAIT;
                    Serial.println("TAT CHU TRINH 3");
                }
            }
            if(action::mode == RUN)
            {
                if(main::control_dc::run_state_a1 == control_dc::RUN_STATE::WAIT || main::control_dc::run_state_a2 == control_dc::RUN_STATE::WAIT)
                {
                    action::mode = INPROCESS_1;
                    Serial.println("BAT DAU CHU TRINH 1");
                }
                if(main::control_dc::run_state_a1 == control_dc::RUN_STATE::STOP && main::control_dc::run_state_a2 == control_dc::RUN_STATE::STOP)
                {
                    action::mode = WAIT;
                    Serial.println("MAY DANG TAT");
                }
            }
            if(action::mode == INPROCESS_1)
            {
                if(main::control_dc::run_state_a1 == control_dc::RUN_STATE::WAIT && main::control_dc::run_state_a2 == control_dc::RUN_STATE::STOP)
                {
                    main::time::cacula_time_off(main::time::time_delay.hour, main::time::time_delay.min, main::time::time_delay.sec, 1);
                    main::control_dc::stepper.moveTo(POS_A1_0);
                    main::control_dc::run_state_a1 = control_dc::RUN_STATE::IN_PCSS;
                    main::control_dc::run_state_a2 = control_dc::RUN_STATE::STOP;
                    action::mode = INPROCESS_2;
                    Serial.println("CHON MODE CHI CHO AN AO 1");
                }
                if(main::control_dc::run_state_a1 == control_dc::RUN_STATE::STOP && main::control_dc::run_state_a2 == control_dc::RUN_STATE::WAIT)
                {
                    main::time::cacula_time_off(main::time::time_delay.hour, main::time::time_delay.min, main::time::time_delay.sec, 1);
                    main::control_dc::stepper.moveTo(POS_A2_0);
                    main::control_dc::run_state_a1 = control_dc::RUN_STATE::STOP;
                    main::control_dc::run_state_a2 = control_dc::RUN_STATE::IN_PCSS;
                    action::mode = INPROCESS_2;
                    Serial.println("CHON MODE CHI CHO AN AO 2");
                }
                if(main::control_dc::run_state_a1 == control_dc::RUN_STATE::WAIT && main::control_dc::run_state_a2 == control_dc::RUN_STATE::WAIT)
                {
                    main::time::cacula_time_off(main::time::time_delay.hour, main::time::time_delay.min, main::time::time_delay.sec, 1);
                    main::control_dc::stepper.moveTo(POS_A1_0);
                    main::control_dc::run_state_a1 = control_dc::RUN_STATE::IN_PCSS;
                    main::control_dc::run_state_a2 = control_dc::RUN_STATE::WAIT;
                    action::mode = INPROCESS_2;
                    Serial.println("CHON MODE CHI CHO AN CA HAI AO NHA NI :v");
                }
            }

            if(action::mode == INPROCESS_2)
            {
                    main::control_dc::control_step_motor_a1();
                    main::control_dc::control_step_motor_a2();
                    main::control_dc::esc.writeMicroseconds(SPEED_BLDC);
                  
            }
            if(action::mode == INPROCESS_3)
            {
                    main::control_dc::control_step_motor_a1();
                    main::control_dc::control_step_motor_a2();
                    main::control_dc::esc.writeMicroseconds(SPEED_BLDC);
               
            }
            if (main::data::stringComplete)
            {
                main::data::getData();
            }
        }

    }

}