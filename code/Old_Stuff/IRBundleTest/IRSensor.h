// ensure this library description is only included once
#ifndef IRSensor_h
#define IRSensor_h

#include "Arduino.h"

// library interface description
class IRSensor
{
  // User-accessible "public" interface
  public:
    IRSensor(unsigned long*, int); // Constructor
    void Setup(void);
    bool Read(void);

  // Fields
  private: 
    const int POINTS = 100;
    const int threshold = 50; 
    unsigned long *scoreRef;
    int inPin;
};

#endif