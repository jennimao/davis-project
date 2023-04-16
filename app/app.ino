#include <Servo.h>
#include <SoftwareSerial.h> // Allows communication with Bluetooth

Servo servo1; // create servo object to control a servo
Servo servo2; // create servo object to control a servo
unsigned long progress;
long angle;
boolean up;

int data = 0; // create integer variable for data that comes in through bluetooth


SoftwareSerial mySerial(0, 1); // RX, TX

unsigned long MOVING_TIME = 3000; // moving time is 3 seconds
unsigned long moveStartTime;



 


 

void setup() {
servo1.attach(3); // attaches the String1 on pin 3 to the servo object
servo2.attach(5); // attaches the String2 on pin 5 to the servo object



// Open communication with bluetooth and wait for port to open:
Serial.begin(57600);


Serial.println("Initiated");

// set the data rate for the SoftwareSerial port
mySerial.begin(9600);
mySerial.println("Hello, world?");
servo1.write(75);
servo2.write(115);
up = false;

}

void loop() {



if (mySerial.available() ) // if recieve data
{

   data = mySerial.read(); // define data as the num recieved from BT
   Serial.println(data);
   if (data == 1)
   { MOVING_TIME = 3000;}

   if (data == 2)
   { MOVING_TIME = 2000;}
   
   if (data == 3)
   { MOVING_TIME = 1000;}
 
   if (data == 4 && not up)
   {
    moveStartTime = millis(); // start moving
    while (progress <= MOVING_TIME) {
    progress = millis() - moveStartTime;
    long angle = map(progress, 0, MOVING_TIME, 0, 90);
    servo1.write(75 + angle);
    servo2.write(115 - angle);
  }
  up = true;
  progress = 0;
   }
   
   if (data == 5 && up)
   {
    moveStartTime = millis(); // start moving
    while (progress <= MOVING_TIME) {
    progress = millis() - moveStartTime;
    long angle = map(progress, 0, MOVING_TIME, 90, 0);
    servo1.write(75 + angle);
    servo2.write(115 - angle);
  }
  progress = 0;
  up= false;
   }
   
}}
