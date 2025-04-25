#include "Enkoder.h"
#include "ColorLed.h"
#include "Button.h"
#include "Dioda.h"
#include "Arduino.h"

float R,G,B;

void kolorLed()
{
  int c=1;
  counter=0;
  while(c!=4)
  {
    ////////////////////////////Enkoder////////////////////
    if(c==1)
    {
      R=R+counter;
      if(R < 0)
      {
        R=0;
      }
      analogWrite(9, R);
      counter=0;
    }
     if(c==2)
    {
      G=G+counter;
      if(G < 0)
      {
        G=0;
      }
      analogWrite(10, G);
      counter=0;
    }
     if(c==3)
    {
      B=B+counter;
      if(B < 0)
      {
        B=0;
      }
      analogWrite(5, B);
      counter=0;
    }
    
   if(przycisk() == 3)
   {
      c++;
      counter=0;
   }
      dioda(c);




  }

  dioda(0);

}