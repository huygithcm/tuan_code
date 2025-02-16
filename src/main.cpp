#include "lib.h"
unsigned long previousMillis = 0;
unsigned long nowMillis = 0;
void setup()
{
    main::action::setup();
}
void loop()
{
    main::action::loop();

    if(main::action::mode == main::action::STOP) 
    {
        
    }
    if (main::action::mode == main::action::RUN)
    {
        /* code */
    }
    
    
}