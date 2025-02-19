#include "lib.h"
namespace main
{
    namespace data
    {
        volatile bool dataReady = false;
        String inputString = "";     // a String to hold incoming data
        bool stringComplete = false; // whether the string is complete
        void setup()
        {
            Serial2.begin(9600);
            inputString.reserve(200);
        }
        void serialEvent()
        {
            while (Serial2.available())
            {
                // get the new byte:
                char inChar = (char)Serial2.read();
                // add it to the inputString:
                inputString += inChar;
                // if the incoming character is a newline, set a flag so the main loop can
                // do something about it:
                if (inChar == '\n')
                {
                    stringComplete = true;
                }
            }
        }
        void getData()
        {
            Serial.println(main::data::inputString);
            int separator = main::data::inputString.indexOf('/');
            if (separator != -1)
            {                                                                       // Nếu có dấu '/'
                String mainTopic = main::data::inputString.substring(0, separator); // Lấy topic chính
                String value = main::data::inputString.substring(separator + 1);    // Lấy giá trị sau '/'
                if (mainTopic == "ONOFF")
                {
                    Serial.println("Main topic is 'ONOFF'");
                    int valuedata = value.toInt();
                    Serial.print("ONOFF Value: ");
                    Serial.println(valuedata);

                    if (valuedata == 1)
                    {
                        main::action::mode = main::action::WAIT;
                    }
                    else if (valuedata == 0)
                    {
                        main::action::mode = main::action::STOP;
                    }
                }
                if (mainTopic == "CALI_ZERO")
                {
                    Serial.println("Main topic is 'CALI_ZERO'");
                    int valuedata = value.toInt();
                    Serial.print("CALI_ZERO Value: ");
                    Serial.println(valuedata);

                    if (valuedata == 1)
                    {
                        main::load_cell::scale.tare();
                    }
                    else if (valuedata == 0)
                    {
                     
                    }
                }

                if (mainTopic == "SECCOMMAND")
                {
                    Serial.println("Main topic is 'SECCOMMAND'");
                    int sensorValue = value.toInt();
                    Serial.print("SECCOMMAND Value: ");
                    Serial.println(sensorValue);
                    main::time::time_delay.hour = sensorValue / 3600;
                    main::time::time_delay.min = (sensorValue % 3600) / 60;
                    main::time::time_delay.sec = sensorValue % 60;

                    Serial.print("Time on 2: ");
                    Serial.print(main::time::time_delay.hour);
                    Serial.print(":");
                    Serial.print(main::time::time_delay.min);
                    Serial.print(":");
                    Serial.println(main::time::time_delay.sec);
                }
                if (mainTopic == "SELEC_COMMAND")
                {
                    Serial.println("Main topic is 'SELEC_COMMAND'");
                    int sensorValue = value.toInt();
                    Serial.print("SECCOMMAND Value: ");
                    Serial.println(sensorValue);
                    if (sensorValue == 1)
                    {
                        main::control_dc::run_state_a1 = main::control_dc::WAIT;
                        main::control_dc::run_state_a2 = main::control_dc::STOP;
                        Serial.print("CHON MODE CHO AN AO: AO 1 ");
                    }
                    else if (sensorValue == 2)
                    {
                        main::control_dc::run_state_a1 = main::control_dc::STOP;
                        main::control_dc::run_state_a2 = main::control_dc::WAIT;
                        Serial.print("CHON MODE CHO AN AO: AO 2 ");
                    }
                    else if (sensorValue == 3)
                    {
                        main::control_dc::run_state_a1 = main::control_dc::WAIT;
                        main::control_dc::run_state_a2 = main::control_dc::WAIT;
                        Serial.print("CHON MODE CHO AN CA 2 AO ");
                    }
                }
                if (mainTopic == "TIME_FEED_1")
                {
                    Serial.println("Main topic is 'SECCOMMAND'");
                    long sensorValue = value.toInt();
                    Serial.print("TIME_FEED_1 Value: ");
                    Serial.println(sensorValue);
                    main::time::time_on_1.hour = sensorValue / 3600;
                    main::time::time_on_1.min = (sensorValue % 3600) / 60;
                    main::time::time_on_1.sec = sensorValue % 60;
                    Serial.print("Time on 1: ");
                    Serial.print(main::time::time_on_1.hour);
                    Serial.print(":");
                    Serial.print(main::time::time_on_1.min);
                    Serial.print(":");
                    Serial.println(main::time::time_on_1.sec);
                    snprintf(main::display::MENU[1], sizeof(main::display::MENU[0]), "ON TIME 1: %02d:%02d:%02d", main::time::time_on_1.hour, main::time::time_on_1.min, main::time::time_on_1.sec);
                }
                if (mainTopic == "TIME_FEED_2")
                {
                    Serial.println("Main topic is 'SECCOMMAND'");
                    long sensorValue = value.toInt();
                    Serial.print("TIME_FEED_2 Value: ");
                    Serial.println(sensorValue);

                    main::time::time_on_2.hour = sensorValue / 3600;
                    main::time::time_on_2.min = (sensorValue % 3600) / 60;
                    main::time::time_on_2.sec = sensorValue % 60;

                    Serial.print("Time on 2: ");
                    Serial.print(main::time::time_on_2.hour);
                    Serial.print(":");
                    Serial.print(main::time::time_on_2.min);
                    Serial.print(":");
                    Serial.println(main::time::time_on_2.sec);
                    snprintf(main::display::MENU[1], sizeof(main::display::MENU[0]), "ON TIME 2: %02d:%02d:%02d", main::time::time_on_2.hour, main::time::time_on_2.min, main::time::time_on_2.sec);
                }
                if (mainTopic == "TIME_SET")
                {
                    Serial.println("Main topic is 'TIME_SET'");
                    long sensorValue = value.toInt();
                    Serial.print("TIME_SET Value: ");
                    Serial.println(sensorValue);

                    uint8_t hour_set = sensorValue / 3600;
                    uint8_t min_set  = (sensorValue % 3600) / 60;
                    uint8_t sec_set = sensorValue % 60;
                    main::time::setTime(hour_set, min_set, sec_set);
                }
            }
            else
            {
                Serial.println(" not topic ");
            }
            main::data::inputString = "";
            main::data::stringComplete = false;
        }
    }

}
