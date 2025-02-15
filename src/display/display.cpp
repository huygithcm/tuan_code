#include "lib.h"
namespace main
{
    namespace display
    {
        LiquidCrystal_I2C lcd(0x27, 20, 4);

        char MENU[4][20] = 
        {
            "TIME    :          ",  
            "ON TIME :          ",
            "OFF TIME:          ",
            "WEIGHT  :          ",
        };
        void setupLCD()
        {
            lcd.init();
            lcd.backlight();
            lcd.setCursor(0, 0);
            lcd.print("Setting up...");
            lcd.setCursor(0, 1);
            lcd.print("Waiting for done!");
            lcd.setCursor(0, 2);
            lcd.print("Starting...");
            Serial.println("LCD Setup Complete");
        }
        void displayLCD()
        {
            lcd.clear();
            for (int i = 0; i < 4; ++i)
            {
                lcd.setCursor(0, i);
                lcd.print(MENU[i]);
            }
        }
    }
}