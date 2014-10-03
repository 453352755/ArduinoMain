//SharpIR accurate return distance in double instead of int 
#include <SharpIR.h>
#include <DualVNH5019MotorShield.h>
int aligned = -10;

void autoAlign(){
  if (thereIsAWall()){
    int cnt = 0;
    while((URreading()<4.5 || URreading() >5) && cnt < 100){
      if(URreading()<4.5){
        md.init();
        md.setSpeeds(-100,-100);
        delay(50);
        md.setBrakes(400,400);
        delay(100);
      }else{
        md.init();
        md.setSpeeds(100,100);
        delay(50);
        md.setBrakes(400,400);
        delay(100);
      }
      cnt++;
    }
        
    while(aligned != 1){
      tune();
      if (abs(frontSensorL.distance() - (URreading()+2)) <= 1 && 
          abs(frontSensorR.distance() - (URreading()+2)) <= 1){
        aligned++;
        //Serial.print("aligned = ");
        //Serial.println(aligned);
      }else{
        aligned = -10;
      }
    }
    aligned = -10;
    
    cmdProcessed = 0;
    //oneGridForward();
  }
}

boolean thereIsAWall(){
  if(URreading() < 10){
    if(frontSensorL.distance()<15 && frontSensorL.distance()>4 && frontSensorR.distance()<15 && frontSensorR.distance()>4  )
      return true;
  }
  return false;
}


void tune(){
  double left, right, center;
  center = URreading()+2;
  left =  frontSensorL.distance();
  right = frontSensorR.distance(); 

  //align
  if ((right < center) && (center < left)){
    
    adjustRight();

  }if ((left < center) && (center < right)){
    
    adjustLeft();

  }
  delay(10);
  //serial test
  Serial.print("L:");
  Serial.print(left);
  Serial.print("; C:");
  Serial.print(center);
  Serial.print("; R:");
  Serial.println(right);
	
}

void adjustRight()
{
  //Serial.print("adjust right");
  md.init();
  md.setSpeeds(-100,100);
  delay(100);
  md.setBrakes(400,400);
  delay(100);
}

void adjustLeft()
{
 // Serial.print("adjust left");
  md.init();
  md.setSpeeds(100,-100);
  delay(100);
  md.setBrakes(400,400);
  delay(100);
}
