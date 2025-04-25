#include "Enkoder.h"
#include "Arduino.h"

float counter = 0;
unsigned long OstatnistanA = 0;


void Enkoder()
{
   if(millis() - OstatnistanA > 5)
    {   

        if(digitalRead(7) == 1)
        {
           if(counter < 255) counter++;
        }

        if(digitalRead(7) == 0)
        {
           if(counter > -255) counter--;
        }
       OstatnistanA = millis();
     }  
     
}