#include "Wire.h"
#include <MPU6050_light.h>
MPU6050 mpu(Wire);
#define LEDPIN 3
unsigned long timer = 0;
int min_angle,max_angle,brightness,z_angle;

void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");

}

void loop() {
  mpu.update();
  z_angle = mpu.getAngleZ();
  if((millis()-timer)>10){ // print data every 10ms
  Serial.print("\tZ : ");
  Serial.println(z_angle);
  timer = millis();  
  }

  // set the minimum and maximum angle for the LED brightness
  min_angle = 0;
  max_angle = 90;

  //map the distance to a value between 0 and 255
  brightness = map(z_angle, min_angle, max_angle, 0, 255);

  //limit the brightness to a value between 0 and 255
  brightness = constrain(brightness, 0, 255);
  // limit z-angle to a value between 0 and 90
  z_angle=constrain(z_angle, min_angle, max_angle);

  //LED brightness depending on distance from obstacle
  analogWrite(LEDPIN, brightness);

}
