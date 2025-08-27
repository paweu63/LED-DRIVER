#include <EEPROM.h>
int counter = 0;
unsigned long OstatnistanA = 0;
int R,G,B;
int data=1;
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
           if(counter > 0) counter--;
        }
       OstatnistanA = millis();
     }  
}

void Display(int i)
{
  switch(i)
  {
  case 1://1
  digitalWrite(8,HIGH);//A
  digitalWrite(A1,HIGH);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,HIGH);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,HIGH);//G

  case 2://2
  digitalWrite(8,LOW);//A
  digitalWrite(A1,HIGH);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,HIGH);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  case 3://3
  digitalWrite(8,LOW);//A
  digitalWrite(A1,HIGH);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  case 4://4
  digitalWrite(8,HIGH);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,HIGH);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  case 5://5
  digitalWrite(8,LOW);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,HIGH);//F
  digitalWrite(13,LOW);//G
  case 6://6
  digitalWrite(8,LOW);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,HIGH);//F
  digitalWrite(13,LOW);//G
  case 7://7
  digitalWrite(8,LOW);//A
  digitalWrite(A1,HIGH);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,HIGH);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,HIGH);//G
  case 8://8
  digitalWrite(8,LOW);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  case 9://9
  digitalWrite(8,LOW);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  default:
  digitalWrite(8,HIGH);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,HIGH);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  break;
  }
}
void kolorLed()
{
  int c=1;

  while(c!=4)
  {
    ////////////////////////////Enkoder////////////////////
    if(c==1)
    {
      Enkoder();
      R=counter;
      analogWrite(9, R);
    }
     if(c==2)
    {
      G=counter;
      analogWrite(10, G);

    }
     if(c==3)
    {

      B=counter;
      analogWrite(11, B);

    }
    unsigned int WhatButton = przycisk();

   if(WhatButton == 3)
   {
      c++;
      counter=0;
   }
      dioda(c);
      WhatButton = 0;



  }

  dioda(0);

}

int przycisk() {
  int b = analogRead(0);

  delay(150);
  ///  //5V---1023(od 850 do 1023) BUTTON 1 //////////1
  ///  //3,4V---695 (od 550 do 850) BUTTON 2 /////////2
  ///  //2V---409  (od 300 do 550) BUTTON ENKODERA//////3
  if (b <= 1023 && b >= 850) {
    return 1;
    delay(20);
    return 0;
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
void dioda(int c)
{
  if(c==1)
  {
    digitalWrite(0, LOW);
    digitalWrite(1, HIGH);
    digitalWrite(2, LOW);

  }
  if(c==2)
  {
    digitalWrite(0, HIGH);
    digitalWrite(1, LOW);
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
  ////////////////////////Wyswietlacz////////////////////////
  pinMode(8,OUTPUT); //A
  pinMode(A1,OUTPUT);//B
  pinMode(A2,OUTPUT);//C
  pinMode(A3,OUTPUT);//D
  pinMode(A4,OUTPUT);//E
  pinMode(12,OUTPUT);//F
  pinMode(13,OUTPUT);//G



  ////////////////////////Dioda//////////////////////////////
  pinMode(A0, INPUT);///button
  pinMode(0, OUTPUT);//R
  pinMode(1, OUTPUT);//G
  pinMode(2, OUTPUT);//B`
  ////////////////PINY PASKA LED/////////////////////////////
  pinMode(9, OUTPUT);//R
  pinMode(10, OUTPUT);//G
  pinMode(11, OUTPUT);//B
  ////////////////PINY Enkodera/////////////////////////////
  pinMode(6, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), Enkoder, LOW);
  pinMode(7, INPUT);
  /////////////////////na start dla diody///////
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  ////////////////Serial_Monitor/////////////////////////////
 // Serial.begin(9600);
 ///////////////////PAMIEC//////////////////////////////////
 EEPROM.write(1, R);
 EEPROM.write(2, G);
 EEPROM.write(3, B);
}

void loop() {

  unsigned int WhatButton = przycisk();

  if(WhatButton == 3 )//enko
  {
    kolorLed();
  }

  if(WhatButton == 2 )
  {
    EEPROM.update(data+2, R);
    EEPROM.update(data+3, G);
    EEPROM.update(data+4, B);
    // Serial.println("zapis pamieci");

  }

  if(WhatButton == 1 )
  {
    data++;
    Display(data);
    if(data > 9)
    {
      data=0;
    }
     //Serial.println("zmiana komorki pamieci");

  }
  analogWrite(9,R);
  analogWrite(10,G);
  analogWrite(11,B);
}
