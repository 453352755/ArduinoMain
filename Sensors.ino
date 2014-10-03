float distFrontL;
float distFrontR;
float distFrontC;
float distL;
float distR; 
//float distRBack;
float URdist;
  
  
void getSensorReading()
{
  //get sensor reading
  Serial.print("pscanner:");
  distFrontL = frontSensorL.distance();
  distFrontC = frontSensorC.distance();
  distFrontR = frontSensorR.distance();
  distL = LSensor.distance();
  distR = RSensor.distance();

  Serial.print(distFrontL);
  Serial.print(",");
  
  Serial.print(distFrontC);
  Serial.print(",");

  Serial.print(distFrontR);
  Serial.print(",");

  Serial.print(distL);
  Serial.print(",");

  Serial.println(distR);
  //Serial.print(",");
  //Serial.print("Right Back: "); 
  //URreading();
}

float IR(int pin){
  int cnt = 0;
  float sum;
  //float predis = 0;
  while(cnt<10){
    float raw=analogRead(pin);
    float voltFromRaw=map(raw, 0, 1023, 0, 5000);
    float reading = 27.728*pow(voltFromRaw/1000, -1.2045);
    sum = sum + reading;
    cnt++;
  }
  sum /= 10;
  cnt = 0;
  
  while (cnt<20){
    float raw=analogRead(pin);
    float voltFromRaw=map(raw, 0, 1023, 0, 5000);
    float reading = 27.728*pow(voltFromRaw/1000, -1.2045);
    
    if(reading > sum * 0.9 && reading < sum * 1.1){
      sum += reading;
      cnt++;
    }
  }
  return sum/20;
}
  

float URreading(){                              // a low pull on pin COMP/TRIG  triggering a sensor reading
    digitalWrite(URTRIG, LOW);
    digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses
     
    unsigned long DistanceMeasured=pulseIn(URPWM,LOW);
     
    if(DistanceMeasured>25000){              // the reading is invalid if more than 500cm.
      //Serial.print("Invalid");   
   }
    else{
      URdist=DistanceMeasured/50;           // every 50us low level stands for 1cm
   }
  //Serial.print("Ultrasonic Distance=");
  //Serial.println(URdist);
  //Serial.println("cm");
  return URdist;
}
