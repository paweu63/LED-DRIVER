#include <EEPROM.h>

#define RED 9
#define GREEN 10
#define BLUE 11
#define BUTTON_DEBOUNCE_TIME 50
#define BUTTON_PIN A0
#define ENCODER_PIN_A 3
#define ENCODER_PIN_B 4
#define INCREMENT_INTERVAL 50

//Button variables
unsigned long lastDebounceTime = 0;
int lastButtonValue = 0;
int buttonState = 0;


//Encoder variables
volatile int encoderCounter = 0;
int lastEncoderPinA = 0;

//LED variables
int R,G,B = 0;

//Memory variables
int data;
int lastIncrementTime = 0;

//state machine variables
int currentMode;


void setRGB(int r, int g, int b) {
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}

void set_Diode(int r, int g, int b) {
  setRGB(r, g, b); //Potem to wymienic na obsluge diody
}

int readButton() {
  int reading = analogRead(BUTTON_PIN);
  int buttonValue = 0;

  if (reading >= 850) {
    buttonValue = 1;
  } else if (reading >= 550) {
    buttonValue = 2;
  } else if (reading >= 200) {
    buttonValue = 3;
  }
  

  if (buttonValue != lastButtonValue) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > BUTTON_DEBOUNCE_TIME) {
    if (buttonValue != buttonState) {
      buttonState = buttonValue;
      if (buttonState != 0) {
        return buttonState;
      }
    }
  }

  lastButtonValue = buttonValue;
  return 0;
}



void LED_change_program() {
  int step = 1;
  while(step != 4) {
    if(readButton() == 3) step++;
    int step_change = encoderCounter;
    encoderCounter = 0;
    switch(step) {
      case 1:
      //set_Diode(255,0,0);
      Display(1);
      R=R+step_change;
      R = constrain(R, 0, 255);

      break;
      
      case 2:
      //set_Diode(0,255,0);
      Display(2);
      G=G+step_change;
      G = constrain(G, 0, 255);
      
      break;

      case 3:
      //set_Diode(0,0,255);
      Display(3);
      B=B+step_change;
      B = constrain(B, 0, 255);
      
      break;
    }
    setRGB(R,G,B);
  }

}

void handleEncoder() {
  int encoderPinB = digitalRead(ENCODER_PIN_B);
  if (digitalRead(ENCODER_PIN_A) != lastEncoderPinA) {
    if (encoderPinB != digitalRead(ENCODER_PIN_A)) {
      encoderCounter++;
    } else {
      encoderCounter--;
    }
  }
  lastEncoderPinA = digitalRead(ENCODER_PIN_A);
}

void Display(int i)
{
  switch(i)
  {
  case 1://1
  digitalWrite(8,HIGH);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,HIGH);//D
  digitalWrite(A4,HIGH);//E
  digitalWrite(12,HIGH);//F
  digitalWrite(13,HIGH);//G
  break;
  case 2://2
  digitalWrite(8,LOW);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,HIGH);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,HIGH);//F
  digitalWrite(13,LOW);//G
  break;
  case 3://3
  digitalWrite(8,LOW);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,HIGH);//E
  digitalWrite(12,HIGH);//F
  digitalWrite(13,LOW);//G
  break;
  case 4://4
  digitalWrite(8,HIGH);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,HIGH);//D
  digitalWrite(A4,HIGH);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  break;
  case 5://5
  digitalWrite(8,LOW);//A
  digitalWrite(A1,HIGH);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,HIGH);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  break;
  case 6://6
  digitalWrite(8,LOW);//A
  digitalWrite(A1,HIGH);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,LOW);//E
  digitalWrite(12,LOW);//F
  digitalWrite(13,LOW);//G
  break;
  case 7://7
  digitalWrite(8,LOW);//A
  digitalWrite(A1,LOW);//B
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,HIGH);//D
  digitalWrite(A4,HIGH);//E
  digitalWrite(12,HIGH);//F
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
  digitalWrite(A2,LOW);//C
  digitalWrite(A3,LOW);//D
  digitalWrite(A4,HIGH);//E
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


void Memory_set() {

}

void Memory_read() {

}

void setup() {
  //LED 
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  //Encoder pins
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), handleEncoder, CHANGE);
  

  //Seg_Display
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



  //Memory
  data = 0;
  
  //State machine
  currentMode = 0;
}

void loop() {
  int buttonPress = readButton();
    if (buttonPress == 1) {
      currentMode = 1;
    } else if (buttonPress == 2) {
      currentMode = 2;
    } else if (buttonPress == 3) {
      currentMode = 3;
    } else currentMode = 0;

  switch (currentMode) {
    case 1:
          data++;
      Display(data);
      break;

    case 2:
      R = EEPROM.read(0);
      G = EEPROM.read(1);
      B = EEPROM.read(2);
      setRGB(R, G, B);
      break;
    
    case 3:
      // Tryb zmiany kolorów
      LED_change_program();
      
      break;
      
    case 0:
    default:
      setRGB(0, 0, 0);
      Display(0);
      break;
  }
  
}