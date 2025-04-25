#include "Button.h"
#include "Arduino.h"

int przycisk() {
  int b = analogRead(0);

  delay(150);
  ///  //5V---1023(od 850 do 1023) BUTTON 1 //////////1
  ///  //3,4V---695 (od 550 do 850) BUTTON 2 /////////2
  ///  //2V---409  (od 300 do 550) BUTTON ENKODERA//////3
  if (b <= 1023 && b >= 850) {
    return 1;

  }
  if (b <= 850 && b >= 550) {
    return 2;
    delay(20);
    return 0;
  }
  if (b <= 550 && b >= 300) {

     return 3;
     delay(20);
     return 0;
  }
  else return 0;


}