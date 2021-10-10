#include <Mouse.h>

#define encoderDT 2
#define encoderCLK 3 // Interrupt
#define encoderSW 4

int previousDT;
int previousCLK;
int previousSW;


int actualSW;

bool clicked = false;
int multiplier = 10;
int dir = 0;
int encoderPos = 0;
int previousEncoderPos = 0;

void setup()
{
Serial.begin(9600);
Mouse.begin();
delay(5000);

////////rotaryEncoder//////////
pinMode(encoderDT, INPUT_PULLUP);
pinMode(encoderCLK, INPUT_PULLUP);
pinMode(encoderSW, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(encoderCLK), doEncoder, CHANGE);
previousDT = digitalRead(encoderDT);
previousCLK = digitalRead(encoderCLK);
previousSW = digitalRead(encoderSW);
////////rotaryEncoder//////////

}


void loop()
{
  
actualSW = digitalRead(encoderSW); // Without debouncing
if (actualSW == LOW && previousSW == HIGH) //check for click
 {
   clicked = !clicked;
   Serial.print("SW= ");
   Serial.println(actualSW==LOW);
 }
previousSW = digitalRead(encoderSW);


dir = rotaryDir();
if(dir != 0)
  {
    moveMouse();
    Serial.println(dir);
  }
}


//Rotary Encoder Logic
int rotaryDir()
{
  dir = encoderPos - previousEncoderPos;
  previousEncoderPos = encoderPos;
//  if(dir == 1)
//  {
//  moveup();
//  Serial.print(actualSW);
//  Serial.print(" ");
//  Serial.print(encoderPos);
//  Serial.println(" CW");
//  }
//  
//  if(dir == -1)
//  {
//  movedown();
//  Serial.print(actualSW);
//  Serial.print(" ");
//  Serial.print(encoderPos);
//  Serial.println(" CCW");
//  }
  
  
  delay(40);
  return dir;
}

void doEncoder() //rotary encoder interupt
{
int actualCLK = digitalRead(encoderCLK);
int actualEncoderDT = digitalRead(encoderDT);

if ((actualCLK == 1) and (previousCLK == 0))
{
if (actualEncoderDT == 1){
encoderPos--;}
else{
encoderPos++;}
}

if ((actualCLK == 0) and (previousCLK == 1))
{
if (actualEncoderDT == 1){
encoderPos++;}
else{
encoderPos--;}
}

previousCLK = actualCLK;
}

void moveup()
{
  if(clicked)
  Mouse.move(0, 1 * multiplier, 0);
  else
  Mouse.move(1 * multiplier, 0, 0);
}

void movedown()
{
  if(clicked)
  Mouse.move(0, -1 * multiplier, 0);
  else
  Mouse.move(-1 * multiplier, 0, 0);
}

void moveMouse()
{
  if(clicked)
  {
    Mouse.move(0, dir * multiplier, 0);
  }
  if(!clicked)
  {
    Mouse.move(dir * multiplier, 0, 0);
  }
}
