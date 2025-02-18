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
                    //    main::action::mode = main::action::RUN;
                    }
                    else
                    {
                        // main::action::mode= main::action::STOP;
                    }
                }

                if (mainTopic == "SECCOMMAND")
                {
                    Serial.println("Main topic is 'SECCOMMAND'");
                    int sensorValue = value.toInt();
                    Serial.print("SECCOMMAND Value: ");
                    Serial.println(sensorValue);
                }
                if (mainTopic == "SELEC_COMMAND")
                {
                    Serial.println("Main topic is 'SELEC_COMMAND'");
                    int sensorValue = value.toInt();
                    Serial.print("SECCOMMAND Value: ");
                    Serial.println(sensorValue);
                }
                else
                {
                    Serial.println(" not topic ");
                }
            }
            main::data::inputString = "";
            main::data::stringComplete = false;
        }

    }
}
