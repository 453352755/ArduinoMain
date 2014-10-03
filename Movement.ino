#include <DualVNH5019MotorShield.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#define oneGrid200 287

#define right90 385
#define left90 390

DualVNH5019MotorShield md;

volatile int enLeft;
volatile int enRight;
volatile int leftCompensate;
volatile int neg;
volatile int fastMode = 0;
volatile float factor = 1;
void oneGridForward(){
  goAhead(1);
}

void right(){
  rotate(1);
}

void left(){
  rotate(-1);
}

void right180(){
  rotate(2);
}

void right270(){
  rotate(3);
}


void rotate(int times) {
  neg =  - times / abs(times);
  enLeft = right90 * abs(times);
  
  if (times < 0){
    enLeft = left90 * abs(times);
  }
  
  enRight = enLeft;
  leftCompensate = 0;
  
  setTimerInterrupt();
  attachInterrupt(1, countRight, RISING);
  
  md.init(); 
  md.setSpeeds(200 * neg, -200 * neg);

  while (enLeft--) {
    while (digitalRead(enLeftPin));
    while (!digitalRead(enLeftPin));
  }
  
  detachInterrupt(1);
  detachTimerInterrupt();

  md.setBrakes(400, 400);
  delay(100);
}

void goAhead(int grid) {
  neg = 1;
  enLeft = enRight = oneGrid200 * grid;
  leftCompensate = 0;

  setTimerInterrupt();
  attachInterrupt(1, countRight, RISING);

  md.init(); 
  md.setSpeeds(200, 200);
  
  while (enLeft--) {
    while (digitalRead(enLeftPin)); // change to catch the posedge
    while (!digitalRead(enLeftPin)); // change to catch the posedge
  }

  detachInterrupt(1);
  detachTimerInterrupt();

  md.setBrakes(400, 400);
  delay(100);
}

void countRight() {
  enRight--;
  leftCompensate =  enRight -enLeft;
}

void setTimerInterrupt() {
  // initialize Timer1
  cli();          // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B

  // set compare match register to desired timer count:
  OCR1A = 1513; // scale = 1024, so OCR1A = (xxx * 10^8 / 6.25 / 1024) // 3124
  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);
  sei();          // enable global interrupts
}

void detachTimerInterrupt() {
  cli();
  TIMSK1 = 0;
  sei();
}

ISR(TIMER1_COMPA_vect) {
  if (fastMode == 0){
    md.setM1Speed((200 + leftCompensate) * neg); // need test <---------
    }
  else
    md.setM1Speed((350 + leftCompensate) * neg);
}
