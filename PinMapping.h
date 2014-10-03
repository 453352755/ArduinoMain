//pin connections 
#ifndef PinMapping_h
//analog pin A0-A5 
//digital pin 13

//sharp IR sensor: long, range 20-150
//sharp IR sensor: short, range 10-80
//short sensor signal pin -> arduino  
#define frontSensorLPin A5
#define frontSensorCPin A1
#define frontSensorRPin A4
#define LSensorFrontPin A3
#define RSensorFrontPin A2


//ultrasonic sensor urm37: range 4-300
//servo attached to ultrasonic control signal 
//urm37 pin5 -> servo signal (yellow)
//urm37 pin1 -> 5V
//urm37 pin2 -> GND
//urm37 pin8 -> arduino
//urm37 pin9 -> arduino
#define URPWM  13
#define URTRIG  11
//#define ultra_pin
//#define ultra_pin

//pololu wheel encoders
//left motor A output (yellow) ->
//left motor B output (white) ->
//right motor A output (yellow) ->
//right motor B output (white) ->

//#define motorLA_pin
//#define motorLB-pin
//#define motorRA_pin 
//#define motorRB_pin

#define enLeftPin 5
#define enRightPin 3

#endif

