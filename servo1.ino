#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2; 

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(8);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val); 
  myservo2.write(val); // sets the servo position according to the scaled value
  // delay(2000);       // waits for the servo to get there
  // myservo.write(180); 
  //myservo2.write(0); 
  // delay(2000); 
}
