#include "Display.h"
#include "Arduino.h"

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