#include "lib.h"
/**
 * @brief Setup function
 *
 * This function is the setup function for the program and is
 * called once at the beginning of the program. It calls the
 * main::action::setup() function, which is responsible for
 * initializing the serial communication, setting up the DC motor,
 * setting up the BLDC motor, and performing other tasks.
 */
void setup()
{
    main::action::setup();
}
/**
 * @brief Main loop
 *
 * This function is the main loop of the program and is called
 * repeatedly. It calls the main::action::loop() function, which
 * is responsible for controlling the DC motor and performing other
 * tasks.
 */
void loop()
{
    main::action::loop();
}