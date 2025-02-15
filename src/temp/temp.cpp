#include "lib.h"
namespace main
{
    namespace temp
    {
    //     SHT31 sht;
    //     const int DELAY_TEMP = 10000;
    //     SemaphoreHandle_t interruptSemaphore;
    //     void interruptHandler()
    //     {
    //         /**
    //          * Give semaphore in the interrupt handler
    //          * https://www.freertos.org/a00124.html
    //          */

    //         xSemaphoreGiveFromISR(interruptSemaphore, NULL);
    //     }
    //     /*
    //      * Led task.
    //      */
    //     void task_temp(void *pvParameters)
    //     {
    //         (void)pvParameters;
    //         for (;;)
    //         {
    //             digitalWrite(TRIAC_GATE, LOW);
    //             vTaskDelay(pdMS_TO_TICKS(DELAY_TEMP));
    //             digitalWrite(TRIAC_GATE, HIGH);
    //         }
    //     }
    //     /**
    //      * @brief Initializes the SHT30 sensor
    //      *
    //      * This function initializes the SHT30 sensor by calling the begin() function.
    //      * This function should be called once at the beginning of the program.
    //      */
    //     void setup()
    //     {
        
    //         sht.begin();

    //         pinMode(ZERO_CROSS, INPUT);
    //         pinMode(TRIAC_GATE, OUTPUT);
    //         // Create task for Arduino led
    //         xTaskCreate(task_temp, // Task function
    //                     "TEM_CONTROL",   // Task name
    //                     1024,    // Stack size
    //                     NULL,
    //                     0, // Priority
    //                     NULL);

    //         /**
    //          * Create a binary semaphore.
    //          * https://www.freertos.org/xSemaphoreCreateBinary.html
    //          */
    //         interruptSemaphore = xSemaphoreCreateBinary();
    //         if (interruptSemaphore != NULL)
    //         {
    //             // Attach interrupt for Arduino digital pin
    //             attachInterrupt(digitalPinToInterrupt(ZERO_CROSS), interruptHandler, HIGH);
    //         }
    //     }
        /**
         * @brief Reads temperature and humidity from the SHT30 sensor
         *
         * This function reads the temperature and humidity values from the SHT30 sensor
         * and prints them to the serial monitor. The temperature and humidity are printed
         * with one decimal point precision. The function introduces a delay of 1000 milliseconds
         * between consecutive readings.
         */

        void read_temp_sht30()
        {
            sht.read();
            Serial.print("Temperature:");
            Serial.print(sht.getTemperature(), 1);
            Serial.print("\t");
            Serial.print("Humidity:");
            Serial.println(sht.getHumidity(), 1);
            delay(1000);
        }
    }
}