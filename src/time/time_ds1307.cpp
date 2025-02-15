#include "lib.h"
namespace main
{
    namespace time
    {
        RTC_DS1307 rtc;
        time thoiGian;
        void readTime()
        {
            // Đọc giờ từ DS1307
            DateTime now = rtc.now();
            // thoiGian.hour = now.hour();
            // thoiGian.minute = now.minute();
            // thoiGian.second = now.second();
            Serial.print(now.hour(), DEC);
            Serial.print(':');
            Serial.print(now.minute(), DEC);
            Serial.print(':');
            Serial.print(now.second(), DEC);
            Serial.println();
            // Serial.print("Time: ");
            // Serial.print(thoiGian.hour);
            // Serial.print(":");
            // Serial.print(thoiGian.minute);
            // Serial.print(":");
            // Serial.println(thoiGian.second);
        }
        void caculateOFF2()
        {
            //     // Tính toán giờ tắt cho hồ 1
            //     int currentHour = thoiGian.hour;
            //     int currentMinute = thoiGian.minute;
            //     if (main::data::lake1 == 1 && currentHour == main::data::hourOn1 && currentMinute >= main::data::minuteOn1 && currentMinute < main::data::minuteOff1 && main::data::emergency == 1 && main::data::stateLake1 == 1)
            //     {
            //         // Serial.println("H  1 ho t  ng");
            //         control_dc::controlDC1(main::data::lake1);
            //     }
            //     else
            //     {
            //         // Serial.println("H  1 t t");
            //         control_dc::controlDC1(0);
            //         main::control_dc::esc.writeMicroseconds(1000);
            //     }
            //     // Tính toán giờ tắt cho hồ 2
            //     if (main::data::lake2 == 2 && currentHour == main::data::hourOn2 && currentMinute >= main::data::minuteOn2 && currentMinute < main::data::minuteOff2 && main::data::emergency == 1 && main::data::stateLake2 == 1)
            //     {
            //         // Serial.println("H  2 ho t  ng");
            //         control_dc::controlDC2(main::data::lake2);
            //     }
            //     else
            //     {
            //         Serial.println("H  2 t t");
            //         control_dc::controlDC2(0);
            //         main::control_dc::esc.writeMicroseconds(1000);
            //     }
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
