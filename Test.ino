#include "TaskScheduler.h"

TaskScheduler t1;
TaskScheduler t2;
TaskScheduler t3;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  
  t1.sleepThenToggle(4000,1000,13,HIGH);
  t2.every(2000,readSensor);
  t3.write(12,HIGH,4000);
}

void readSensor(){
  Serial.println("Reading sensors...");
}

void loop() {
  t1.update();
  t2.update();
  t3.update();
}
