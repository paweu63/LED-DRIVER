// WYPIERDOLIC DIODE PROSTOWNICZA 


#include <EEPROM.h>

#define RED 9
#define GREEN 10
#define BLUE 11
#define BUTTON_DEBOUNCE_TIME 50
#define BUTTON_PIN A0
#define ENCODER_PIN_A 3
#define ENCODER_PIN_B 4
#define data_change_time 40
#define LONG_PRESS_TIME 2000
#define IR_PIN A5

//Button variables
unsigned long lastDebounceTime = 0;
int lastButtonValue = 0;
int buttonState = 0;
bool buttonHandled = false;

//for LONGPRESS
unsigned long pressStartTime = 0;

//IR
volatile unsigned long irCode = 0;
volatile int bitIndex = 0;
volatile bool codeReady = false;
volatile unsigned long lastChange = 0;
//IR Pilot
int newR;
int newG;
int newB;
static int colorIndex = 0;
bool colorActive = false;

//Encoder variables
volatile int encoderCounter = 0;
int lastEncoderPinA = 0;

//Brightness
float brightnessFactor = 1.0;
bool brightnessMode = true;
const float ENCODER_BRIGHTNESS_STEP = 0.02;
const float IR_BRIGHTNESS_STEP = 0.10;

//LED variables
int R = 0, G = 0, B = 0;
int baseR = 255, baseG = 255, baseB = 255;

//Memory variables
int data;

// --- Functions declarations  ---

// LED
void setRGB(int r, int g, int b);
void set_Diode(int r, int g, int b);
void LED_change_program();
// Button
int readButton();
// Encoder
void handleEncoder();
void handleEncoderBrightness();
// Segment display
void Display(int i);
// EEPROM memory
void Memory_Read();
void Memory_add();
void Memory_change();
// IR
void IR_setup(unsigned long irData);


void setup() {
  //Button
  pinMode(BUTTON_PIN, INPUT);
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
  Display(0);



  //Memory
  data = 0;


  //IR 
  pinMode(IR_PIN, INPUT_PULLUP);
  //Register settings to activate interrups
  PCICR |= (1 << PCIE1);   //Start interrups for PCINT1 (Group of pins A0-A5)
  PCMSK1 |= (1 << PCINT13); // Start interrups for A5 pin (PCINT13)

  
}

void loop() {
  switch (readButton()) {
    case 1:
    Memory_change();
    break;

    case 2:
    Memory_add();
    break;

    case 3:
    LED_change_program();
    break;

    case 4:
    Memory_Read();
    break;

    default:
    break;
  }

  if (codeReady) {
    noInterrupts();
    unsigned long code = irCode;
    codeReady = false;
    interrupts();
    IR_setup(code);
  }
  handleEncoderBrightness();
  Display(data);
  setRGB(R,G,B);
  
}
void setRGB(int r, int g, int b) {
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}

void set_Diode(int r, int g, int b) {
  setRGB(r, g, b); //Potem to wymienic na obsluge diody
}

int readButton() {
  //This can be not nessecary 
  const int samples = 7;
  int values[samples];
  for (int i = 0; i < samples; i++) {
    values[i] = analogRead(BUTTON_PIN);
  
  }
  for (int i = 0; i < samples - 1; i++) {
    for (int j = i + 1; j < samples; j++) {
      if (values[j] < values[i]) {
        int temp = values[i];
        values[i] = values[j];
        values[j] = temp;
      }
    }
  }
  int reading = values[samples / 2];
  int buttonValue = 0;
  //

  
  if (reading >= 850) buttonValue = 1;       // BTN1
  else if (reading >= 550) buttonValue = 2;  // BTN2
  else if (reading >= 300) buttonValue = 3;  // BTN3
  else buttonValue = 0;

  // Debounce + handled
  if (buttonValue != lastButtonValue) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > BUTTON_DEBOUNCE_TIME) {
    if (buttonValue != 0 && !buttonHandled) {
      buttonHandled = true;
      lastButtonValue = buttonValue;
      pressStartTime = millis();
      return buttonValue;
    } else if (buttonValue == 0) {
      buttonHandled = false;
    }
  if((millis() - pressStartTime) > LONG_PRESS_TIME && buttonValue == 1 && buttonHandled)
  {
    return 4;
  }
  }

  lastButtonValue = buttonValue;


  return 0;
}

/*
Function to change led color(Main program blocked), by interrupts from
encoder R,G,B variables are changed, encoder button changes the 
variable to be written
*/ 
void LED_change_program() {
  brightnessMode = false;
  int step = 1;
  encoderCounter = 0;
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
  setColor(R, G, B);
  brightnessMode = true;

}


//Encoder function 
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

void applyBrightness() {
  R = constrain((int)(baseR * brightnessFactor), 0, 255);
  G = constrain((int)(baseG * brightnessFactor), 0, 255);
  B = constrain((int)(baseB * brightnessFactor), 0, 255);
  setRGB(R, G, B);
}

void increaseBrightness() {
  brightnessFactor += IR_BRIGHTNESS_STEP;
  if (brightnessFactor > 1.0) brightnessFactor = 1.0;
  applyBrightness();
}

void decreaseBrightness() {
  brightnessFactor -= IR_BRIGHTNESS_STEP;
  if (brightnessFactor < 0.0) brightnessFactor = 0.0;
  applyBrightness();
}

void setColor(int r, int g, int b) {
  baseR = r;
  baseG = g;
  baseB = b;
  applyBrightness();
}

//Zmiana jasności enkoderem
void handleEncoderBrightness() {
  static int lastEncoderValue = 0;
  int delta = encoderCounter - lastEncoderValue;

  // nic się nie zmieniło → wyjście
  if (delta == 0) return;

  lastEncoderValue = encoderCounter;

if (brightnessMode) {
    brightnessFactor += delta * ENCODER_BRIGHTNESS_STEP;  // czułość regulacji (2% na "krok")
    brightnessFactor = constrain(brightnessFactor, 0.0, 1.0);
    applyBrightness(); // przelicz nowy kolor z bazowego i aktualnym współczynnikiem jasności
  }
}

//Display decoder
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
/*
Function to Read data cell and write to R,G,B variables
*/
 
void Memory_Read() {
  int first_adress = (data-1)*3;
  setColor(
  EEPROM.read(first_adress),
  EEPROM.read(first_adress+1),
  EEPROM.read(first_adress+2)
  );
}
/*
Function to add R,G,B value to memory according to setted data
*/
void Memory_add(){
  int first_adress = (data-1)*3;
  EEPROM.update(first_adress, R);
  EEPROM.update(first_adress+1, G);
  EEPROM.update(first_adress+2, B);
  
}


/*
Function to change memory cell
*/
void Memory_change() {
  data++;
  if(data > 9) data = 0;
}


/*
Decoded IR results
*/
void IR_setup(unsigned long irData) {

  switch(irData){
    case 1145049365://RED
       setColor(255, 0, 0);
       colorIndex = 0;
       colorActive = true;
       brightnessFactor = 1.0;
     break;

    case 1090524245://w prawo
      if (colorActive) 
      { 
        colorIndex++;
        if (colorIndex > 2) colorIndex = 0;
        switch(colorIndex) 
        {
          case 0: R=255; G=0; B=0; break;
          case 1: R=0; G=255; B=0; break;
          case 2: R=0; G=0; B=255; break;
        }
      }
      brightnessFactor = 1.0;
    break;

    case 1409286485://w lewo
       if (colorActive) 
       { 
        colorIndex--;
        if (colorIndex < 0) colorIndex = 2;
        switch(colorIndex) 
        {
          case 0: R=255; G=0; B=0; break;
          case 1: R=0; G=255; B=0; break;
          case 2: R=0; G=0; B=255; break;
        }
      }
      brightnessFactor = 1.0;
    break; 

    case 83906645://1
      setColor(EEPROM.read(0), EEPROM.read(1), EEPROM.read(2));
      colorActive = false;
      brightnessFactor = 1.0;
    break;

    case 20993045://2
      setColor(EEPROM.read(3), EEPROM.read(4), EEPROM.read(5));
      colorActive = false;
      brightnessFactor = 1.0;
    break;

    case 356794385://3
      setColor(EEPROM.read(6), EEPROM.read(7), EEPROM.read(8));
      colorActive = false;
      brightnessFactor = 1.0;
    break;

    case 16798805://4
     setColor(EEPROM.read(9), EEPROM.read(10), EEPROM.read(11));
      colorActive = false;
      brightnessFactor = 1.0;
    break;

    case 88100885://5
      setColor(EEPROM.read(12), EEPROM.read(13), EEPROM.read(14));
      colorActive = false;
      brightnessFactor = 1.0;
    break;

    case 289686545://6
      setColor(EEPROM.read(15), EEPROM.read(16), EEPROM.read(17));
      colorActive = false;
      brightnessFactor = 1.0;
    break;

    case 268715345://7
      setColor(EEPROM.read(18), EEPROM.read(19), EEPROM.read(20));
      colorActive = false;
      brightnessFactor = 1.0;
    break;

    case 272909585://8
     setColor(EEPROM.read(21), EEPROM.read(22), EEPROM.read(23));
      colorActive = false;
      brightnessFactor = 1.0;
    break;

    case 285492305://9
      setColor(EEPROM.read(24), EEPROM.read(25), EEPROM.read(26));
      colorActive = false;
      brightnessFactor = 1.0;
    break;

    case 1141117265://OFF
      setColor(0, 0, 0);
      colorActive = false;
      brightnessFactor = 1.0;
    break;

    case 1094718485://DECREMENT
      decreaseBrightness();
    break;

    case 283985://INCREMENT
    increaseBrightness();
    break;
  }
}


/*
Interrups handler
*/
ISR(PCINT1_vect) { // PCINT for A0-A5
  unsigned long now = micros();
  unsigned long diff = now - lastChange;
  lastChange = now;

  if (diff < 100) return;

  // Transmition start ~9ms
  if (diff > 8000 && diff < 10000) {
    bitIndex = 0;
    irCode = 0;
    return;
  }

  // Bit 1 (~1.7ms)
  if (diff > 1200 && diff < 2000) {
    irCode = (irCode << 1) | 1;
    bitIndex++;
  }
  // Bit 0 (~0.6ms)
  else if (diff > 400 && diff < 900) {
    irCode = (irCode << 1);
    bitIndex++;
  }

  if (bitIndex >= 32) {                                                             
    codeReady = true;
    bitIndex = 0;
  }
}
