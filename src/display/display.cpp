#include "lib.h"
namespace main
{
    namespace display
    {
        LiquidCrystal_I2C lcd(0x27, 20, 4);
        void setupLCD()
        {
            lcd.init();
            lcd.backlight();
            lcd.setCursor(0, 0);
            lcd.print("Setting up...");
            lcd.setCursor(0, 1);
            lcd.print("Waiting for done!");
        }
        void displayLCD()
        {
            lcd.setCursor(0, 0);
            lcd.print("Time: ");
            if (main::time::thoiGian.hour < 10) lcd.print("0");
            lcd.print(main::time::thoiGian.hour);
            lcd.print(":");
            if (main::time::thoiGian.minute < 10) lcd.print("0");
            lcd.print(main::time::thoiGian.minute);
            lcd.print(":");
            if (main::time::thoiGian.second < 10) lcd.print("0");
            lcd.print(main::time::thoiGian.second);
            lcd.setCursor(0, 1);
            lcd.print(" On: ");
            if (main::data::hourOn1 < 10) lcd.print("0");
            lcd.print(main::data::hourOn1);
            lcd.print(":");
            if (main::data::minuteOn1 < 10) lcd.print("0");
            lcd.print(main::data::minuteOn1);
            lcd.setCursor(0, 2);
            lcd.print(" Off: ");
            if (main::data::hourOff1 < 10) lcd.print("0");
            lcd.print(main::data::hourOff1);
            lcd.print(":");
            if (main::data::minuteOff1 < 10) lcd.print("0");
            lcd.print(main::data::minuteOff1);
            lcd.setCursor(0, 3);
            lcd.print("Weight: ");
            lcd.print(main::load_cell::new_weight_kg, 2);
            lcd.print(" kg");
        }
    }
}