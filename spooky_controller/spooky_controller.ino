#include <Servo.h>

/*
      INTERNATIONAL MORSE CODE INFO

* dot is one unit; dash is three units
* space between parts of the same letter is one unit
* space between letters is three units
* space between words is seven units

*/
Servo cameraServo;
const int servoPin = 10;

const int murderPins[6] = {2,3,4,5,6,7};
const int murderSwitches[6] = {A0,A1,A2,A3,A4,A5};

const int pinMorse = 8; 

const int cameraSwitch = 9;

const int unit = 500; // in milliseconds how long a unit is.

const int M[8] = {HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW};
const int U[8] = {HIGH, LOW, HIGH, LOW, HIGH, HIGH, HIGH, LOW};
const int R[8] = {HIGH, LOW, HIGH, HIGH, LOW, LOW, HIGH, LOW};
const int D[8] = {HIGH, HIGH, HIGH, LOW, HIGH, LOW, HIGH, LOW};
const int E[8] = {HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW};


void setup() {
  // put your setup code here, to run once:
  cameraServo.attach(servoPin);
  Serial.begin(9600);
  pinMode(pinMorse, INPUT);
  pinMode(cameraSwitch, INPUT);
  for (int i = 0; i< sizeof(murderPins)/sizeof(murderPins[0]); i++){
    pinMode(murderPins[i], OUTPUT);
    pinMode(murderSwitches[i], INPUT);
  }
}

void murder(){
  // led
  Serial.println("here");
  for (int i = 0; i < sizeof(M)/sizeof(M[0]); i++){
    Serial.print(i);
    Serial.print(" ");
    Serial.print(murderPins[0]);
    Serial.print(" ");
    Serial.println(M[i]);
    digitalWrite(murderPins[0], M[i]);
    digitalWrite(murderPins[1], U[i]);
    digitalWrite(murderPins[2], R[i]);
    digitalWrite(murderPins[3], D[i]);
    digitalWrite(murderPins[4], E[i]);
    digitalWrite(murderPins[5], R[i]);
    delay(unit);
  }
}

void manageCandles(){
  for (int i = 0; i < sizeof(murderPins)/sizeof(murderPins[0]); i++){
    Serial.println(analogRead(murderSwitches[i]));
    
    if (analogRead(murderSwitches[i]) > 512){
      digitalWrite(murderPins[i], HIGH);
    }else{
      digitalWrite(murderPins[i], LOW);
    }
  }
}

void manageCamera(){
  if (analogRead(cameraSwitch) > 512){
    cameraServo.write(90);
  } else {
    cameraServo.write(0);
  }
}
void loop() {
  // if servo high, 90deg if servo low 90 back
  //manageCamera();
  Serial.print(digitalRead(pinMorse));
  if (digitalRead(pinMorse) == HIGH){    
    // if morse, jump to M-U-R-D-E-R
    murder();
    delay(unit*3);
  } else {
    // otherwise, check each pin
    manageCandles();
    delay (100);
  }
}
