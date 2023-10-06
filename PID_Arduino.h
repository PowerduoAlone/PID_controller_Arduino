/*
  PID_Arduino.h - Library to implement a simple PID controller on an Arduino
  Created by Simon Moeri, October 6, 2023.
  Released into the public domain.
*/
#ifndef PID_ARDUINO_H
#define PID_ARDUINO_H
#include "PID.h"
#include "Arduino.h"

class PID_arduino : public PID
{
    public:
        long unsigned determine_time(){
            return millis();
        }
};
#endif