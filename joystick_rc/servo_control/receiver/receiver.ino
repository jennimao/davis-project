/* 
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 7
   4 - CSN to Arduino pin 8
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   */

#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)
#include <Servo.h>
#include <SoftwareSerial.h> // Allows print

// (Create an instance of a radio, specifying the CE and CS pins. )
RF24 myRadio (7,8); // "myRadio" is the identifier you will use in following methods
byte addresses[][6] = {"1Node"}; // Create address for 1 pipe.
double joystickValue;  // Data that will be received from the transmitter


int servo1_pin = 3;
int servo2_pin = 5;
int angle = 0;
int pos1 = 0;
int pos2 = 0;

int upperbound1 = 95; 
int lowerbound1 = 22; 

int upperbound2 = 168; 
int lowerbound2 = 95; 

int initial_position1 = upperbound1;
int initial_position2 = lowerbound2;
Servo servo1;
Servo servo2;
int x_key = A1;
int y_key = A0;


void setup()
{
  Serial.begin(9600);
  delay(1000);

  myRadio.begin();  // Start up the physical nRF24L01 Radio
  myRadio.setChannel(108);  // Above most Wifi Channels
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.openReadingPipe(1, addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
  myRadio.startListening();

  servo1.attach (servo1_pin ) ;
  servo1.write (initial_position1);

  servo2.attach (servo2_pin ) ;
  servo2.write (initial_position2); 

}

void loop()
{
  if ( myRadio.available()) // Check for incoming data from transmitter
  {
    while (myRadio.available())  // While there is data ready
    {
      myRadio.read( &joystickValue, sizeof(joystickValue) ); // Get the data payload (You must have defined that already!)
    }
    // DO something with the data, like print it
   //   Serial.print("Data received = ");
   Serial.print(millis());
   Serial.print("    ");
    Serial.println(joystickValue);
  }

  if (joystickValue > 1000) {
    if (initial_position1 >= lowerbound1 && initial_position1 <= upperbound1 && initial_position2 >= lowerbound2 && initial_position2 <= upperbound2)
    {
      initial_position1 = initial_position1 - 5;
      servo1.write (initial_position1);

      initial_position2 = initial_position2 + 5;
      servo2.write (initial_position2);
    }
  }

  if (joystickValue < 20) {
    if (initial_position1 >= (lowerbound1-2) && initial_position1 <= (upperbound1-2) && initial_position2 >= (lowerbound2+2) && initial_position2 <= (upperbound2+2))
    {
      initial_position1 = initial_position1 + 5;
      servo1.write (initial_position1);

      initial_position2 = initial_position2 - 5;
      servo2.write (initial_position2);
    }
  }

  delay(100);
  
  
  }
