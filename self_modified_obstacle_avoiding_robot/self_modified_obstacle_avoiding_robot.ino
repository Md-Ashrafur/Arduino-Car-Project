#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

//our L298N control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

//sensor pins
#define trig_pin A4 //analog input 1
#define echo_pin A5 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup(){

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(9); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
    delay(0);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=380;
  }
  return cm;
}

void moveStop(){
   analogWrite(RightMotorForward, 110);
  analogWrite(LeftMotorForward, 110);
  analogWrite(RightMotorBackward, 140);
  analogWrite(LeftMotorBackward, 140);
  delay(100);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    analogWrite(LeftMotorForward, 150);
    analogWrite(RightMotorForward, 150);
  
    analogWrite(LeftMotorBackward, 100);
    analogWrite(RightMotorBackward, 100); 
  }
}

void moveBackward(){

  goesForward=false;

  analogWrite(LeftMotorBackward, 170);
  analogWrite(RightMotorBackward, 170);
  
  analogWrite(LeftMotorForward, 100);
  analogWrite(RightMotorForward, 100);
 
}

void turnRight(){

  analogWrite(LeftMotorForward, 170);
  analogWrite(RightMotorBackward, 120);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(250);  
}

void turnLeft(){

  analogWrite(LeftMotorBackward, 120);
  analogWrite(RightMotorForward, 170);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(250);
  
}

 
