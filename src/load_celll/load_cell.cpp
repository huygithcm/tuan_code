#include "lib.h"
namespace main
{
    namespace load_cell
    {

        HX711 scale;
        float calibration_factor;   
        float weight_g_known = 10000;
        long reading_offset = -330299;
        long offset = -930182;

        void calibrateLoadCell()
        {
            if (scale.is_ready())
            {
                Serial.println("Đang hiệu chuẩn Offset...");
                scale.tare(); // Tự động đặt Offset
                Serial.print("Offset: ");
                Serial.println(scale.get_offset()); // Hiển thị giá trị Offset tìm được

                Serial.println("Tare... remove any weights from the scale.");
                delay(5000);
                scale.tare();
                Serial.println("Tare done...");
                Serial.print("Place a known weight on the scale...");
                delay(5000);
                long reading = scale.get_units(10);
                Serial.print("Result: ");
                Serial.println(reading);
            }
            else
            {
                Serial.println("HX711 not found.");
            }
            delay(1000);
        }
        void setupLoadCell()
        {
            scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
            calibration_factor = reading_offset / weight_g_known;
            scale.set_scale(calibration_factor);
            scale.set_offset(offset); 
   
        }
        void readLoadCell()
        {
            Serial.print("Khối lượng: ");
            float weight_kg = scale.get_units(5);
            if (weight_kg < 0)
            {
                weight_kg = 0;
            }
            Serial.println(weight_kg);
            main::display::lcd.setCursor(0, 0);
            main::display::lcd.print("Weight: ");
            main::display::lcd.print(weight_kg, 2);
            main::display::lcd.print(" kg");
       
        }
    }
}