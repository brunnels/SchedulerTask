#ifndef TaskScheduler_h
#define TaskScheduler_h

#include "Arduino.h"
#include "Tasks.h"

class TaskScheduler
{
    public:
      TaskScheduler(void);
      void sleepThenToggle(unsigned long sleepPeriod, unsigned long runFor, uint8_t pin, uint8_t startingValue);
      void update();
      void every(unsigned long waitFor,void (*callback)(void));
      void write(uint8_t pin, uint8_t startingValue,unsigned long timeout);
      void start();
      void stop();
    private:
      Tasks tasks;
      
};
#endif
