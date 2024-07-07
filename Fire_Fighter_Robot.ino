#include "AFMotor.h"
#include <SoftwareSerial.h>
#define RxD A4
#define TxD A5
#define Flame A2
const int sensorMin = 0;   // sensor minimum
const int sensorMax = 1023;  // sensor maximum
AF_DCMotor motorR (2);
AF_DCMotor motorL (1);
AF_DCMotor Fan (4);
int cmd;
int sensorReading;
int range, oldrange = 0;
SoftwareSerial blueToothSerial(RxD, TxD);

void setup() {
Serial.begin(9600);
Serial.setTimeout(5);
blueToothSerial.begin(9600);
blueToothSerial.flush();
Serial.write("Ready");
}

void loop() {
  sensorReading = analogRead(Flame);
  range = map(sensorReading, sensorMin, sensorMax, 0, 4);
  if(range==0 && range != oldrange)
  {
    Fan.setSpeed(254);
    Fan.run(FORWARD);
    Serial.println("**Close Fire**"); //A Fire closer than 0.5 meter away.
    oldrange = range;
    
  }
  else if (range > 0 && range < 3 && range != oldrange)
  {
    Fan.setSpeed(0);
    Fan.run(RELEASE);
    Serial.println("**Distant Fire**"); //A Fire between 0.5 - 1meter away.
    oldrange = range;

  }
  else if (range == 3 && range != oldrange)
  {
    Fan.setSpeed(0);
    Fan.run(RELEASE);	
    Serial.println("No Fire"); //NO Fire detected
    oldrange = range;

  }

  if (blueToothSerial.available() > 0)
  {
    cmd = blueToothSerial.read();
  }
  if (cmd == 'F')
  {
    delay(30);
    Serial.write("Forward");
    motorR.setSpeed(140);
    motorL.setSpeed(140);
    motorR.run(FORWARD);
    motorL.run(FORWARD);
  }

  else if (cmd == 'B')
  { 
  delay(30);
  Serial.write("Back");
  motorR.setSpeed(140);
  motorL.setSpeed(140);
  motorR.run(BACKWARD);
  motorL.run(BACKWARD);
 }
  else if (cmd == 'R')
  {
     delay(30);
  Serial.write("Right");
  motorR.setSpeed(140);
  motorL.setSpeed(140);
  motorR.run(BACKWARD);
  motorL.run(FORWARD);
  }
  else if (cmd == 'L')
  {
     delay(30);
  Serial.write("Left");
  motorR.setSpeed(140);
  motorL.setSpeed(140);
  motorL.run(BACKWARD);
  motorR.run(FORWARD);
  }
   else if (cmd == 'S')
  {
     delay(30);
  Serial.write("Stop");
  motorR.setSpeed(0);
  motorL.setSpeed(0);
  motorL.run(RELEASE);
  motorR.run(RELEASE);
  }
  else
  {}
if (Serial.available() > 0)

  {
    cmd = Serial.read();
  }
  if (cmd == 'F' )
  {
    delay(30);
    motorR.setSpeed(240);//0-255
    motorL.setSpeed(230);
    motorR.run(FORWARD);
    motorL.run(FORWARD);
  }

  else if (cmd == 'B')
  {
    delay(30);
    motorR.setSpeed(240);
    motorL.setSpeed(240);
    motorR.run(BACKWARD);
    motorL.run(BACKWARD);

  }
  else if (cmd == 'R')
  {
    delay(30);
    motorR.setSpeed(240);
    motorL.setSpeed(240);
    motorR.run(BACKWARD);
    motorL.run(FORWARD);
  }
  else if (cmd == 'L')
  {
    delay(30);
    motorR.setSpeed(240);
    motorL.setSpeed(240);
    motorL.run(BACKWARD);
    motorR.run(FORWARD);
  }
  else if (cmd == 'S')
  {
    motorR.setSpeed(0);
    motorL.setSpeed(0);
    motorL.run(RELEASE);
    motorR.run(RELEASE);
  }
  else
  {}

}

  
  
