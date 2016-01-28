#include "Arduino.h"
#include "Tasks.h"

Tasks::Tasks(void){
  sleepForEventType=NONE;
  deactivate();
}

void Tasks::update(void){
  if(sleepForEventType==NONE)
    return;
    
  unsigned long now;
  now=millis();
  //wait for the sleep time to over.
  //once the sleep time over change the flag by calling activate().
  if (now - lastEventTime >= sleepForPeriod)
  {
    switch (sleepForEventType)
    {
      case SCHEDULE:
        performPreActivation();
        activate();
        break;
      case WITH_TIMEOUT:
        int pinCurrentState = digitalRead(pin);
        if(pinCurrentState==pinState){
          uint8_t tmpPinState = ! pinCurrentState;
          digitalWrite(pin, tmpPinState);
          stop();
        }
        break;
    }
    lastEventTime = now;
  }

  //when the runFor period happen, it check whether sleep time over by checking the flag.
  //if sleep time over then perform the task.
  if (now - runForEventTime >= runForPeriod)
  {
    switch(runForEventType){
       case TOGGLE:
        if(canActivate()){
          uint8_t tmpPinState = ! pinState;
          digitalWrite(pin, tmpPinState);
          deactivate();
        }
        break;
      case CALLBACK:
        if(canActivate()){
          (*callbackFunc)();
          deactivate();
        }
        break;
    }
    runForEventTime=now;
  }
}

void Tasks::begin(uint8_t pinNumber, uint8_t startingState){
  pin=pinNumber;
  pinState=startingState;
  lastEventTime = millis();
}

void Tasks::sleep(unsigned long period){
  sleepForEventType=SCHEDULE;
  sleepForPeriod = period;
  lastEventTime = millis();
}

void Tasks::thenTogglePin(unsigned long period){
  runForEventType=TOGGLE;
  runForPeriod = period;
  runForEventTime=millis();
}

void Tasks::thenCallback(void (*callback)(void)){
  runForEventType=CALLBACK;
  callbackFunc=callback;
  runForPeriod=1;
  runForEventTime=millis();
}

void Tasks::writeWithTimeout(unsigned long timeout){
  digitalWrite(pin, pinState);
  sleepForPeriod = timeout;
  sleepForEventType = WITH_TIMEOUT;
  lastEventTime = millis();
}

void Tasks::start(void){
  isStopped=false;
  sleepForEventType=NONE;
}
void Tasks::stop(void){
  isStopped=true;
  sleepForEventType=NONE;
}

bool Tasks::canActivate(){
  if(schedulReached==1)
    return true;
  else
    return false;
}

void Tasks::activate(){
  schedulReached=1;
}

void Tasks::deactivate(){
  schedulReached=0;
}

void Tasks::performPreActivation(){
  runForEventTime=millis();
  if(pin>0){
    digitalWrite(pin,pinState);
  }
}

