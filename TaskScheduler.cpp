#include "TaskScheduler.h"

TaskScheduler::TaskScheduler(){
  
}


void TaskScheduler::sleepThenToggle(unsigned long sleepPeriod, unsigned long runFor,uint8_t pin, uint8_t startingValue){
  tasks.begin(pin,startingValue);
  tasks.sleep(sleepPeriod);
  tasks.thenTogglePin(runFor);
}

void TaskScheduler::write(uint8_t pin, uint8_t startingValue,unsigned long timeout){
  tasks.begin(pin, startingValue);
  tasks.writeWithTimeout(timeout);
}

void TaskScheduler::every(unsigned long waitFor,void (*callback)(void)){
  tasks.sleep(waitFor);
  tasks.thenCallback(callback);
}

void TaskScheduler::update(){
  tasks.update();
}

void TaskScheduler::start(){
  tasks.start();
}
void TaskScheduler::stop(){
  tasks.stop();
}

