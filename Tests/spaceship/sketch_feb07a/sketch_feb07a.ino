#include <Servo.h>

Servo servoX; 



void setup() {
  // put your setup code here, to run once:
  servoX.attach(9);                                                                                                                                                                                                       
}

void loop() {
  // put your main code here, to run repeatedly:
  servoX.write(20);
}
