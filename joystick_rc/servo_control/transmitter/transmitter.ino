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


// (Create an instance of a radio, specifying the CE and CS pins. )
RF24 myRadio (7, 8); // "myRadio" is the identifier you will use in following methods
byte addresses[][6] = {"1Node"}; // Create address for 1 pipe.
double dataTransmitted;  // Data that will be Transmitted from the transmitter
int y_key = A0;
// Scale
//HX711 scale;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  
  // Setup RF24 Radio
  myRadio.begin();  // Start up the physical nRF24L01 Radio
  myRadio.setChannel(108);  // Above most Wifi Channels
  myRadio.setPALevel(RF24_PA_MIN);
 // myRadio.setDataRate(RF24_250KBPS); 
  myRadio.openWritingPipe( addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
  pinMode (y_key, INPUT) ;
 
  delay(1000);
}

void loop()
{
 
  dataTransmitted = double(analogRead(y_key));// you will get this from the imu dat

myRadio.write(&dataTransmitted,sizeof(dataTransmitted)); //  Transmit the data


  
//  Serial.print(millis());
// Serial.print("    ");
// Serial.print(F("Data Transmitted = "));
Serial.println(dataTransmitted);
  delay(100);

}
