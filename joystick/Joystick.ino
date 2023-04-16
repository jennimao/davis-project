#include <Servo.h>
#include <SoftwareSerial.h> // Allows print
Servo servo1;
Servo servo2;
int x_key = A1;
int y_key = A0;
int x_pos;
int y_pos;
int servo1_pin = 3;
int servo2_pin = 5;
int angle = 0;
int pos1 = 0;
int pos2 = 0;
int initial_position1 = 75;
int initial_position2 = 115;


void setup ( ) {
  Serial.begin (9600) ;
  servo1.attach (servo1_pin ) ;
  servo2.attach (servo2_pin ) ;
  servo1.write (initial_position1);
  servo2.write (initial_position2);
  pinMode (x_key, INPUT) ;
  pinMode (y_key, INPUT) ;
  Serial.begin(57600);
  Serial.println("Initiated");
}

void loop ( ) {
  x_pos = analogRead (x_key) ;
  y_pos = analogRead (y_key) ;
  Serial.println(y_pos);
  delay(100);


  if (y_pos > 1000) {
    Serial.println("up");

    if (initial_position1 >= 22 && initial_position1 <= 75 && initial_position2 >= 115 && initial_position2 <= 168)
    {
      Serial.println("up1");
      Serial.println(initial_position1);

      initial_position1 = initial_position1 - 1;

      servo1.write (initial_position1 ) ;
      Serial.println("up2");
      Serial.println(initial_position2);

      initial_position2 = initial_position2 + 1;

      servo2.write (initial_position2 ) ;
    }
  }


  if (y_pos < 20) {

    Serial.println("down");
    if (initial_position1 >= 20 && initial_position1 <= 73 && initial_position2 >= 117 && initial_position2 <= 170)
    {
      Serial.println("down1");
      Serial.println(initial_position1);

      initial_position1 = initial_position1 + 1;

      servo1.write ( initial_position1 ) ;

      Serial.println("down2");
      Serial.println(initial_position2);

      initial_position2 = initial_position2 - 1;

      servo2.write (initial_position2 ) ;
    }

  }

}
