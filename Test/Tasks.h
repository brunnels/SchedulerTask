#ifndef Tasks_h
#define Tasks_h

#include <inttypes.h>

#define NONE 0
#define SCHEDULE 1
#define TOGGLE 2
#define CALLBACK 3
#define WITH_TIMEOUT 4
class Tasks
{
public:
  Tasks(void);
  void update(void);
  void begin(uint8_t pinNumber, uint8_t startingState);
  void thenTogglePin(unsigned long period);
  void thenCallback(void (*callback)(void));
  void writeWithTimeout(unsigned long timeout);
  void sleep(unsigned long period);
  void start(void);
  void stop(void);
private:
  int8_t runForEventType;
  unsigned long runForPeriod;
  uint8_t schedulReached=0;
  unsigned long runForEventTime;
  unsigned long sleepForPeriod;
  int8_t sleepForEventType;
  uint8_t pin;
  uint8_t pinState;
  unsigned long lastEventTime;
  void (*callbackFunc)(void);
  bool isStopped;
  
  bool canActivate();
  void activate();
  void deactivate();
  void performPreActivation();
};

#endif
