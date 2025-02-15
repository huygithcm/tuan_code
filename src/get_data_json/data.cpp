#include "lib.h"
namespace main
{
    namespace data
    {
        int lake1 = 0;
        int lake2 = 0;
        int hourOn1, minuteOn1;
        int hourOff1, minuteOff1;
        int hourOn2, minuteOn2;
        int hourOff2, minuteOff2;
        float kg, temp;
        int emergency = 1;
        int stateLake1;
        int stateLake2;

        void receiveSerialData()
        {
            if (Serial2.available())
            {
                String data = Serial2.readStringUntil('\n');
                Serial.println(data);
                StaticJsonDocument<2048> doc;
                DeserializationError error = deserializeJson(doc, data);
                if (error)
                {
                    Serial.print(F("deserializeJson() failed: "));
                    Serial.println(error.c_str());
                    return;
                }
                lake1 = doc["lake1"];
                lake2 = doc["lake2"];
                hourOn1 = doc["hourOn1"];
                minuteOn1 = doc["minuteOn1"];
                hourOff1 = doc["hourOff1"];
                minuteOff1 = doc["minuteOff1"];
                hourOn2 = doc["hourOn2"];
                minuteOn2 = doc["minuteOn2"];
                hourOff2 = doc["hourOff2"];
                minuteOff2 = doc["minuteOff2"];
                emergency = doc["emergency"];
                stateLake1 = doc["stateLake1"];
                stateLake2 = doc["stateLake2"];

            }
        }
        float readEEPROMFloat(int address)
        {
            float value;
            byte *p = (byte *)&value;
            for (int i = 0; i < sizeof(float); i++)
            {
                *p++ = EEPROM.read(address + i);
            }
            return value;
        }


        void writeEEPROMFloat(int address, float value)
        {
            byte *p = (byte *)&value;
            for (int i = 0; i < sizeof(float); i++)
            {
                EEPROM.write(address + i, *p++);
            }
        }
        // xTaskCreatePinnedToCore(mqttTask, "MQTT Task", 4096, NULL, 1, NULL, 1);

    }
}