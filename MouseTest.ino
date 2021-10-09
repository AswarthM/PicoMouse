#include <Mouse.h>

#define encoderDT 2
#define encoderCLK 3 // Interrupt
#define encoderSW 4

int previousDT;
int previousCLK;
int previousSW;

int actualSW;

int multiplier = 10;

void setup()
{
Serial.begin(9600);
Mouse.begin();
delay(5000);
pinMode(encoderDT, INPUT_PULLUP);
pinMode(encoderCLK, INPUT_PULLUP);
pinMode(encoderSW, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(encoderCLK), doEncoder, CHANGE);
previousDT = digitalRead(encoderDT);
previousCLK = digitalRead(encoderCLK);
previousSW = digitalRead(encoderSW);
}

int encoderPos = 0;
int previousEncoderPos = 0;

void loop()
{
actualSW = digitalRead(encoderSW); // Without debouncing

if (actualSW != previousSW)
{
Serial.print("SW= ");
Serial.println(actualSW);
previousSW = actualSW;
}

if(encoderPos > previousEncoderPos)
{
moveup();
Serial.print(actualSW);
Serial.print(" ");
Serial.print(encoderPos);
Serial.println(" CW");
}

if(encoderPos < previousEncoderPos)
{
movedown();
Serial.print(actualSW);
Serial.print(" ");
Serial.print(encoderPos);
Serial.println(" CCW");
}

previousEncoderPos = encoderPos;

// delay(1000);
delay(40);
}

void doEncoder()
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

void moveup(){
  if(actualSW==0)
  Mouse.move(0, 1 * multiplier, 0);
  else
  Mouse.move(1 * multiplier, 0, 0);
  }

void movedown(){
  if(actualSW==0)
  Mouse.move(0, -1 * multiplier, 0);
  else
  Mouse.move(-1 * multiplier, 0, 0);
  }
