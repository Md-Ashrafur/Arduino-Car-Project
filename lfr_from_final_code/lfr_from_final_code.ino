int Sensor1 = A0;
int Sensor2 = A1;
int Sensor3 = A2;
int Sensor4 = A3;
void setup() {
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);
  pinMode(Sensor4, INPUT);
  pinMode(6, OUTPUT); //For motor 1
  pinMode(7, OUTPUT); //For motor 1
  pinMode(9, OUTPUT); // For motor 2
  pinMode(10, OUTPUT); //For motor 2
  Serial.begin(9600);
}
void forward() { //Move Forward
  analogWrite(5, 80);
  analogWrite(6, 0);
  analogWrite(9, 70);
  analogWrite(10, 0);
}
void backward() { // Move Backward
  analogWrite(5, 0);
  analogWrite(6, 80);
  analogWrite(9, 0);
  analogWrite(10, 70);
}
void rightSide() { // Move Right Side
  analogWrite(5, 80);
  analogWrite(6, 0);
  analogWrite(9, 0);
  analogWrite(10, 0);
}
void leftSide() { // Move left Side
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(9, 80);
  analogWrite(10, 0);
}
void stopCar() { // Stop the car
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(9, 0);
  analogWrite(10, 0);
}
void loop() {
  int SensorValue1 = analogRead(Sensor1);
  int SensorValue2 = analogRead(Sensor2);
  int SensorValue3 = analogRead(Sensor3);
  int SensorValue4 = analogRead(Sensor4);
  Serial.print("SensorValue1: ");
  Serial.println(SensorValue1);
  Serial.print("SensorValue2: ");
  Serial.println(SensorValue2);
  Serial.print("SensorValue3: ");
  Serial.println(SensorValue3);
  Serial.print("SensorValue4: ");
  Serial.println(SensorValue4);

  if (  SensorValue1 < 400 && SensorValue2 < 400 )
  {
    forward() ;
  }
  else if (SensorValue3 < 400 && SensorValue2 < 400) {
    rightSide();

  }


  else if (SensorValue4 < 400 && SensorValue2 < 400 ) {
    leftSide();
  }
  else if (SensorValue1 > 400 && SensorValue2 > 400 ) {
    backward();
  }


}
