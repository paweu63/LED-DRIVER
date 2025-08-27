#include <IRremote.hpp>
#include <EEPROM.h>

float counter = 0;
unsigned long OstatnistanA = 0;
float R,G,B;
int data;
int time;
int lastR, lastG, lastB;
int data_poczatkowa;


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
  break;
  case 2://2
  digitalWrite(8,LOW);//A
  digitalWrite(A1,HIGH);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,HIGH);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  break;
  case 3://3
  digitalWrite(8,LOW);//A
  digitalWrite(A1,HIGH);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  break;
  case 4://4
  digitalWrite(8,HIGH);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,HIGH);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  break;
  case 5://5
  digitalWrite(8,LOW);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,HIGH);//F
  digitalWrite(13,LOW);//G
  break;
  case 6://6
  digitalWrite(8,LOW);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,HIGH);//F
  digitalWrite(13,LOW);//G
  break;
  case 7://7
  digitalWrite(8,LOW);//A
  digitalWrite(A1,HIGH);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,HIGH);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,HIGH);//G
  break;
  case 8://8
  digitalWrite(8,LOW);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  break;
  case 9://9
  digitalWrite(8,LOW);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  break;
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
  digitalWrite(8,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
  digitalWrite(A4,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);



  ////////////////////////Dioda//////////////////////////////
  pinMode(A0, INPUT);///button
  pinMode(0, OUTPUT);//R
  pinMode(1, OUTPUT);//G
  pinMode(2, OUTPUT);//B`
  ////////////////PINY PASKA LED/////////////////////////////
  pinMode(9, OUTPUT);//R
  pinMode(10, OUTPUT);//G
  pinMode(5, OUTPUT);//B
  ////////////////PINY Enkodera/////////////////////////////
  pinMode(6, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), Enkoder, LOW);
  pinMode(7, INPUT);
  /////////////////////na start dla diody///////
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  ////////////////Serial_Monitor/////////////////////////////
  //Serial.begin(9600);
 ///////////////////PAMIEC//////////////////////////////////
 data=0;
 Display(data);
 R=EEPROM.read(27);
 G=EEPROM.read(28);
 B=EEPROM.read(29);
 //////////////////////////IR//////////////////////////////////
IrReceiver.begin(A5);
}

void loop() {
   if (IrReceiver.decode()) {
      switch(IrReceiver.decodedIRData.decodedRawData)
      {
        case 0xF30CFF00: //1
        R=EEPROM.read(0);
        G=EEPROM.read(1);
        B=EEPROM.read(2);
        break;
        case 0xE718FF00: //2
        R=EEPROM.read(3);
        G=EEPROM.read(4);
        B=EEPROM.read(5);
        break;
        case 0xA15EFF00: //3
        R=EEPROM.read(6);
        G=EEPROM.read(7);
        B=EEPROM.read(8);
        break;
        case 0xF708FF00: //4
        R=EEPROM.read(9);
        G=EEPROM.read(10);
        B=EEPROM.read(11);
        break;
        case 0xE31CFF00: //5
        R=EEPROM.read(12);
        G=EEPROM.read(13);
        B=EEPROM.read(14);
        break;
        case 0xA55AFF00: //6
        R=EEPROM.read(15);
        G=EEPROM.read(16);
        B=EEPROM.read(17);
        break;
        case 0xBD42FF00: //7
        R=EEPROM.read(18);
        G=EEPROM.read(19);
        B=EEPROM.read(20);
        break;
        case 0xAD52FF00: //8
        R=EEPROM.read(21);
        G=EEPROM.read(22);
        B=EEPROM.read(23);
        break;
        case 0xB54AFF00: //9
        R=EEPROM.read(24);
        G=EEPROM.read(25);
        B=EEPROM.read(26);
        break;
        
      }
      IrReceiver.resume();
  }

  unsigned int WhatButton = przycisk();
  data_poczatkowa=(data-1)*3;
 
  if(WhatButton == 3 )//enko
  {
    delay(200);
    kolorLed();
  }

  if(WhatButton == 2 )
  {
    delay(200);
    if(data != 0)
    {
    EEPROM.update(data_poczatkowa,R);
    EEPROM.update(data_poczatkowa+1,G);
    EEPROM.update(data_poczatkowa+2,B);
    }
  }

  if(WhatButton == 1 )
  { 

    delay(100);
    WhatButton=przycisk();
    if(WhatButton==1)
    {
      R=EEPROM.read(data_poczatkowa);
      G=EEPROM.read(data_poczatkowa+1);
      B=EEPROM.read(data_poczatkowa+2);

    }
    if(WhatButton==0)
    {
    data++;
    Display(data);
    if(data > 9)
    {
      data=0;
    }
    }

  }
  if(lastR != R ||  lastG != G || lastB !=B)
  {
  analogWrite(9,R);
  analogWrite(10,G);
  analogWrite(5,B);
  }
  EEPROM.update(27, R);
  EEPROM.update(28, G);
  EEPROM.update(29, B);



  lastR=R;
  lastG=G;
  lastB=B;

  R=(R/(0.1*counter+1));
  G=(G/(0.1*counter+1));
  B=(B/(0.1*counter+1));

  if(R < 0) R=0;
  if(G < 0) G=0;
  if(B < 0) B=0;
  if(R > 255) R = 255;
  if(G > 255) G = 255;
  if(B > 255) B = 255;
  counter=0;

}

