    

#include "PinMapping.h"
//#include "Sensors.h"
#include <SharpIR.h>

#include <SharpIRAccurate.h> //return float
//////////////////////////////////

//motor control

////////////////////////////////////
//SharpIRAccurate frontSensorL(frontSensorLPin, 25, 80, 1080);
//SharpIRAccurate frontSensorR(frontSensorRPin, 25, 80, 1080);
SharpIR frontSensorL(frontSensorLPin, 25, 93, 1080);
SharpIR frontSensorC(frontSensorCPin, 25, 93, 1080);
SharpIR frontSensorR(frontSensorRPin, 25, 93, 1080);
SharpIR LSensor(LSensorFrontPin, 25, 93, 1080);
SharpIR RSensor(RSensorFrontPin, 25, 93, 1080);
//SharpIR RSensorFront(RSensorFrontPin, 25, 93, 1080);
//SharpIR RSensorBack(A0, 25, 93, 1080);

int count = 0;
int explore = 1;
uint8_t EnPwmCmd[4]={0x44,0x02,0xbb,0x01};
char command;
int cmdProcessed;

void setup()
{
  Serial.begin(4800); 
  setPins();
  command = '1';
  for(int i=0;i<4;i++){
      Serial.write(EnPwmCmd[i]);
  }
}

void loop()
{
   command = (Serial.read());

    processCommand(command);
   
    if (cmdProcessed > 4){
      autoAlign();
    }
     
    //delay(1000); 
    //command = '1';

}

void processCommand(char command)
{
  
  switch(command){
    case 's': 
      processing();
      explore = 0; 
      break;
    case 'e': 
      explore = 1; 
      break;
    case '0': 
      processing();
      getSensorReading();
      break;
    case '1':
      processing(); 
      oneGridForward();
      getSensorReading();
      break;
    case '2': 
      processing();
      right();
      getSensorReading();
      break;
    case '3': 
      processing();
      left();
      getSensorReading();
      break;
      case '4':
      right180();
      break;
      case '5':
      right270();
      break;
    
    default:break;
  }
}
    
void processing()
{
  if (explore){
    Serial.print("n");  
    Serial.println(command);
  }else{
    Serial.print("p");  
    Serial.println(command);      
  }
  cmdProcessed++;
}

void setPins() 
{
  //encoder
  pinMode(enLeftPin, INPUT);
  pinMode(enRightPin, INPUT);
  //ir sensor
  pinMode(frontSensorLPin, INPUT);
  pinMode(frontSensorRPin, INPUT);
  pinMode(LSensorFrontPin, INPUT);
  //pinMode(LSensorBackPin, INPUT);
  pinMode(RSensorFrontPin, INPUT);
  //pinMode(RSensorBackPin, INPUT);
  //ultra
  pinMode(URTRIG,OUTPUT);                     // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                  // Set to HIGH  
  pinMode(URPWM, INPUT);  
}

