/*
 * Created by Vasilakis Michalis // 12-12-2014 ver.2
 * Project: Control RC Car via Bluetooth with Android Smartphone
 * More information at www.ardumotive.com
 */
 
//L293 Connection   
  const int motorA1  = 5;  // Pin  2 of L293
  const int motorA2  = 6;  // Pin  7 of L293
  const int motorB1  = 10; // Pin 10 of L293
  const int motorB2  = 9;  // Pin 14 of L293
//Leds connected to Arduino UNO Pin 12
  const int lights  = 12;
//Buzzer / Speaker to Arduino UNO Pin 3
  const int buzzer = 3 ;   
//Bluetooth (HC-06 JY-MCU) State pin on pin 2 of Arduino
  const int BTState = 2;
//Calculate Battery Level
  const float maxBattery = 8.0;// Change value to your max battery voltage level! 
  int perVolt;                 // Percentage variable 
  float voltage = 0.0;         // Read battery voltage
  int level;
// Use it to make a delay... without delay() function!
  long previousMillis = -1000*10;// -1000*10=-10sec. to read the first value. If you use 0 then you will take the first value after 10sec.  
  long interval = 1000*10;       // interval at which to read battery voltage, change it if you want! (10*1000=10sec)
  unsigned long currentMillis;   //unsigned long currentMillis;
//Useful Variables
  int i=0;
  int j=0;
  int state;
  int vSpeed=200;     // Default speed, from 0 to 255
  int vSpeed2;     // For movinng right or left

void setup() {
    // Set pins as outputs:
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(lights, OUTPUT); 
    pinMode(BTState, INPUT);    
    // Initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}
 
void loop() {
  //Stop car when connection lost or bluetooth disconnected
//     if(digitalRead(BTState)==LOW) { state='S'; }

  //Save income data to variable 'state'
    if(Serial.available() > 0){     
      state = Serial.read();   
    }
  
  //Change speed if state is equal from 0 to 4. Values must be from 0 to 255 (PWM)
    if (state == '0'){
      vSpeed=0;}
    else if (state == '1'){
      vSpeed=100;}
    else if (state == '2'){
      vSpeed=180;}
    else if (state == '3'){
      vSpeed=200;}
    else if (state == '4'){
      vSpeed=255;}

      vSpeed2 =vSpeed/2.5;
 	  
  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward!
    if (state == 'F') {
    	analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
        analogWrite(motorB1, 0);      analogWrite(motorB2, vSpeed); 
    }
  /**********************Forward Left************************/
  //If state is equal with letter 'G', car will go forward left
    else if (state == 'G') {
    	analogWrite(motorA1, vSpeed2); analogWrite(motorA2, 0);   //"vSpeed/2" reduing half for rotate left 
        analogWrite(motorB1, 0);    analogWrite(motorB2, vSpeed); 
    }
  /**********************Forward Right************************/
  //If state is equal with letter 'I', car will go forward right
    else if (state == 'I') {
      	analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);      analogWrite(motorB2, vSpeed2); //"vSpeed/2" reduing half for rotate right 
    }
  /***********************Backward****************************/
  //If state is equal with letter 'B', car will go backward
    else if (state == 'B') {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, vSpeed);   analogWrite(motorB2, 0); 
    }
  /**********************Backward Left************************/
  //If state is equal with letter 'H', car will go backward left
    else if (state == 'H') {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed2);   //"vSpeed2" reduing half for rotate left 
        analogWrite(motorB1, vSpeed); analogWrite(motorB2, 0); 
    }
  /**********************Backward Right************************/
  //If state is equal with letter 'J', car will go backward right
    else if (state == 'J') {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, vSpeed2);   analogWrite(motorB2, 0);   //"vSpeed2" reduing half for rotate right
    }
  /***************************Left*****************************/
  //If state is equal with letter 'L', wheels will turn left
    else if (state == 'L') {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0); analogWrite(motorB2, 200); 
    }
  /***************************Right*****************************/
  //If state is equal with letter 'R', wheels will turn right
    else if (state == 'R') {
    	analogWrite(motorA1, 200);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 0); 		
    }


/****************************Pagla Dance****************************/

//If state is equal with letter 'X' or 'x' rotating ultra right turning 
    else if (state == 'V' || state == 'v'){
        
        analogWrite(motorA1, 0);   analogWrite(motorA2, 240); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 240);
         
         delay(750);
      
     
      state='n';  
    }


/**********************ultra left turn***************************/
  //If state is equal with letter 'V' or 'v', ultra left turn
    else if (state == 'X' || state =='x' ){

     analogWrite(motorA1, 240);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, 240);   analogWrite(motorB2, 0);
         
         delay(7500);
     
      state='n';  
    }

   

    




    
  /************************First Forward*****************************/
  //If state is equal with letter 'W', Forward with full speed
    else if (state == 'W' || state == 'w'  ) {
     analogWrite(motorA1, 250); analogWrite(motorA2, 0);
        analogWrite(motorB1, 0);      analogWrite(motorB2, 250);
        delay(850);
      state='n';
    }




     /***********************Imidiately Stop / Break **********************8******/


 else if (state == 'U' || state =='u'){
        
        analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 0);
      
     
      state='n';  
    }


    
  
  /************************Stop*****************************/
  //If state is equal with letter 'S', stop the car
    else if (state == 'S'){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
    }

    
  /***********************Battery*****************************/
  //Read battery voltage every 10sec.
    currentMillis = millis();
    if(currentMillis - (previousMillis) > (interval)) {
       previousMillis = currentMillis; 
       //Read voltage from analog pin A0 and make calibration:
       voltage = (analogRead(A0)*5.015 / 1024.0)*11.132;
       //Calculate percentage...
       perVolt = (voltage*100)/ maxBattery;
       if      (perVolt<=75)               { level=0; }
       else if (perVolt>75 && perVolt<=80) { level=1; }    //        Battery level
       else if (perVolt>80 && perVolt<=85) { level=2; }    //Min ------------------------   Max
       else if (perVolt>85 && perVolt<=90) { level=3; }    //    | 0 | 1 | 2 | 3 | 4 | 5 | >
       else if (perVolt>90 && perVolt<=95) { level=4; }    //    ------------------------
       else if (perVolt>95)                { level=5; }   
       Serial.println(level);    
    }
    
}
