#include "lib.h"
namespace main
{
    namespace time
    {
        RTC_DS1307 rtc;

        time time_on_1, time_on_2, time_off_1, time_off_2, time_off_3, time_delay;
        DateTime now;

        void readTime()
        {
            // Đọc giờ từ DS1307
            now = rtc.now();
            main::action::now_seconds = now.second();
            snprintf(main::display::MENU[0], sizeof(main::display::MENU[0]), "TIME    :  %02d:%02d:%02d", now.hour(), now.minute(), now.second());
        }
        void printTime()
        {
            Serial.print(now.hour(), DEC);
            Serial.print(':');
            Serial.print(now.minute(), DEC);
            Serial.print(':');
            Serial.print(now.second(), DEC);
            Serial.println();
        }

        void cacula_time_off(uint8_t hou, uint8_t min, uint8_t sec, int set_timer)
        {
            if (set_timer == 1)
            {
                DateTime time_on(now + TimeSpan(0, hou, min, sec));
                time_off_1.hour = time_on.hour();
                time_off_1.min = time_on.minute();
                time_off_1.sec = time_on.second();
                Serial.print("TIME OFF 1 : ");
                Serial.print(time_off_1.hour);
                Serial.print(':');
                Serial.print(time_off_1.min);
                Serial.print(':');
                Serial.print(time_off_1.sec);
                Serial.println();
            }
            if (set_timer == 2)
            {
                DateTime time_on(now + TimeSpan(0, hou, min, sec));
                time_off_2.hour = time_on.hour();
                time_off_2.min = time_on.minute();
                time_off_2.sec = time_on.second();
                Serial.print("TIME OFF 2 : ");
                Serial.print(time_off_2.hour);
                Serial.print(':');
                Serial.print(time_off_2.min);
                Serial.print(':');
                Serial.print(time_off_2.sec);
                Serial.println();
            }
           
        }
        void cacula_time_off_2(uint8_t hou, uint8_t min, uint8_t sec)
        {

            DateTime time_on(now + TimeSpan(0, hou, min, sec));
            time_off_2.hour = time_on.hour();
            time_off_2.min = time_on.minute();
            time_off_2.sec = time_on.second();
            Serial.print("thoi gian bat tiep theo: ");
            Serial.print(time_off_2.hour);
            Serial.print(':');
            Serial.print(time_off_2.min);
            Serial.print(':');
            Serial.print(time_off_2.sec);
            Serial.println();
            // snprintf(display::run_mode[2], 20, "CYCLE:  %02d:%02d:%02d   ", time_on.hour(), time_on.minute(), time_on.second());
        }
        void setupds1307()
        {

#ifndef ESP8266
            while (!Serial)
                ; // wait for serial port to connect. Needed for native USB
#endif

            if (!rtc.begin())
            {
                Serial.println("Couldn't find RTC");
                Serial.flush();
                while (1)
                    delay(10);
            }

            if (!rtc.isrunning())
            {
                Serial.println("RTC is NOT running, let's set the time!");
                // When time needs to be set on a new device, or after a power loss, the
                // following line sets the RTC to the date & time this sketch was compiled
                rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
                // This line sets the RTC with an explicit date & time, for example to set
                // January 21, 2014 at 3am you would call:
                // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
            }
            rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }

        int bcd2dec(byte num)
        {
            return ((num / 16 * 10) + (num % 16));
        }
        /* Chuyển từ Decimal sang BCD */
        int dec2bcd(byte num)
        {
            return ((num / 10 * 16) + (num % 10));
        }
        void setTime(byte hr, byte min, byte sec)
        {
            /* Địa chỉ của DS1307 */
            const byte DS1307 = 0x68;
            Wire.beginTransmission(DS1307);
            Wire.write(byte(0x00)); // đặt lại pointer
            Wire.write(dec2bcd(sec));
            Wire.write(dec2bcd(min));
            Wire.write(dec2bcd(hr));
            Wire.endTransmission();
        }

    }
}
