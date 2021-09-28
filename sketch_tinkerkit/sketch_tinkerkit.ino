#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;
Servo hope;

void setup() {
  // Braccio.begin();
  pinMode(3, OUTPUT);
  hope.attach(3);
}

void loop() {
//  Braccio.ServoMovement(20, 0, 0, 0, 0, 0, 0);
//  delay(1000);
//  Braccio.ServoMovement(20, 0, 110, 0, 0, 0, 0);
//  delay(1000);
  hope.write(0);
  delay(250);
  hope.write(180);
  delay(250);
}
