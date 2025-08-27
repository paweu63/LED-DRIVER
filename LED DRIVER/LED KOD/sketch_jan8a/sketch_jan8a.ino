////////////////////////////OBSŁUGA PRZYCISKU/////////////////////////
int przycisk(int b) {
  ///  //5V---1023(od 850 do 1023) BUTTON 1 //////////1
  ///  //3,4V---695 (od 550 do 850) BUTTON 2 /////////2
  ///  //2V---409  (od 300 do 550) BUTTON ENKODERA//////3
  if (b <= 1023 && b >= 850) {
    return 1;
  }
  if (b <= 850 && b >= 550) {
    return 2;
  }
  if (b <= 550 && b >= 300) {

     return 3;
  }
  return 0;


}
void dioda(int c)
{
  if(c==1)
  {
    digitalWrite(0, HIGH);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);

  }
  if(c==2)
  {
    digitalWrite(0, LOW);
    digitalWrite(1, HIGH);
    digitalWrite(2, LOW);

  }
   if(c==3)
  {
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);

  }
  else
  {
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    
  }
}

void setup() {
 
  /////////////////////////PINY///////////////////////////////
  pinMode(A0, INPUT);///button
  pinMode(0, OUTPUT);//R
  pinMode(1, OUTPUT);//G
  pinMode(2, OUTPUT);//B

  /////////////////////na start dla diody///////
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  ////////////////Serial_Monitor/////////////////////////////
  //Serial.begin(9600);
}

void loop() {
  unsigned int WhatButton = przycisk(analogRead(0));//////////////////drgania stykow ????////////////
  //Serial.println(WhatButton);

  if(WhatButton == 3 )
  {
    dioda(1);
    Serial.println("do enkodera wlazlem");
  }

  if(WhatButton == 2 )
  {

     Serial.println("zapis pamieci");

  }

  if(WhatButton == 1 )
  {

     Serial.println("zmiana komorki pamieci");

  }

}
