#include <PID.h>
#include <PID_Arduino.h>

#include "PID.h"
#include "PID_Arduino.h"

enum solder_state {
  inactive_state,
  preheat_state,
  soak_state,
  reflow_state,
  plateau_state,
  cooling_state
};

#define time_between_decisions 500  //ms
#define second 1000                 //ms
#define preheat_step float(3) * time_between_decisions / second
#define preheat_limit 150
#define wait_time_soak second / time_between_decisions * 90
#define reflow_step float(2) * time_between_decisions / second
#define reflow_limit 245
#define plateau_time 40  //from 40 to 80 possible
#define wait_time_plateau second / time_between_decisions* plateau_time
#define cooling_step float(-4) * time_between_decisions / second¨
#define cooling_limit 35

solder_state state = preheat_state;
PID_arduino PID_controller(1, 0, 0, true);
bool heater_relais = false;
uint8_t NTC_pin = A0;
uint8_t relais_pin = 2;
uint8_t button_pin = 3;
int NTC_voltage = 0;
float temperature = 24.0;
float desired_temperature = 20.0;

unsigned long run_time = 0;
int time_counter = 0;
bool running = false;
bool handle_state = false;
int counter = 0;

ISR(TIMER1_OVF_vect)
{
  TCNT1 =99820;
  counter +=1;
  if(counter >= 1){
    handle_state = true;
    counter = 0;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(relais_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 =99820;
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();
  PID_controller.begin(desired_temperature);
}

void loop() {
  if (handle_state) {
    //Serial.print("run time is: ");
    Serial.println(millis());
    state_machine(state);
    if (!running) {
      Serial.println("Ready");
    }
    PID_controller.set_setpoint(desired_temperature);
    //Serial.print("Temperature is: ");
    Serial.println(temperature);
    //Serial.print("Desired Temperature is: ");
    Serial.println(desired_temperature);
    //Serial.print("The state of the relais is: ");
    Serial.println(heater_relais, DEC);
    handle_state = false;
  }
  //measure temperature;
  heater_relais = PID_controller.calculate_controller_output_bool(temperature);
  digitalWrite(relais_pin, heater_relais);
}

void state_machine(solder_state state) {
  switch (state) {
    case inactive_state:
      if (digitalRead(button_pin) == 1) {
        state = preheat_state;
        running = true;
      }
      break;
    case preheat_state:
      preheat();
      break;
    case soak_state:
      soak();
      break;
    case reflow_state:
      reflow();
      break;
    case plateau_state:
      plateau();
      break;
    case cooling_state:
      cooling();
      break;
  }
}

void preheat() {
  if (temperature >= preheat_limit) {
    state = soak_state;
  }
  if (desired_temperature < preheat_limit) {
    desired_temperature += preheat_step;
  }
}

void soak() {
  if (time_counter >= wait_time_soak) {
    state = reflow_state;
    time_counter = 0;
  } else {
    time_counter += 1;
  }
}

void reflow() {
  if (temperature >= reflow_limit) {
    state = plateau_state;
  }
  if (desired_temperature < reflow_limit) {
    desired_temperature += reflow_step;
  }
}

void plateau() {
  if (time_counter >= wait_time_plateau) {
    state = cooling_state;
    time_counter = 0;
  } else {
    time_counter += 1;
  }
}

void cooling() {
  if (temperature <= cooling_limit) {
    state = inactive_state;
    running = false;
  }
  if (desired_temperature < cooling_limit) {
    desired_temperature -= reflow_step;
  }
}

/*
preheating zone: rise max 3°C/s, 150°C in about 90s
soak zone: stay at 150° C for about 90s
reflow zone: rise approx. 2°C/s, to 245°C
"plateau zone": hold 245°C for about 40-80s
cooling zone: decrease with max -4°C/s to avoid thermal stress
*/