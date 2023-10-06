#include <PID.h>
#include <PID_Arduino.h>

#include "PID.h"
#include "PID_Arduino.h"

enum solder_state{
  inactive,
  preheat,
  soak,
  reflow,
  plateau,
  cooling
};

solder_state state = inactive;
PID_arduino controller(1,0.1,0.2,true);
bool Heater = false;
float temp = 25;


void setup() {
  controller.begin(25);
}

void loop() {

  Heater = controller.calculate_controller_output_bool(temp);

}

/*
preheating zone: rise max 3°C/s, 150°C in about 90s
soak zone: stay at 150° C for about 90s
reflow zone: rise approx. 2°C/s, to 245°C
"plateau zone": hold 245°C for about 40-80s
cooling zone: decrease with max -4°C/s to avoid thermal stress
*/