/*
  PID.h - Library for a simple PID controller
  Created by Simon Moeri, October 6, 2023.
  Released into the public domain.
*/

#include "PID.h"

PID::PID(){
    this->kp = 1;
    this->ki = 0;
    this->kd = 0;
    this->controller_Type = true;
}


PID::PID(float proportional_Constant=1, float integral_Constant=0, float derivative_Constant=0, bool boolean_Controller=true){
    this->kp = proportional_Constant;
    this->ki = integral_Constant;
    this->kd = derivative_Constant;
    this->controller_Type = boolean_Controller;
}

void PID::set_constants(float proportional_Constant=1, float integral_Constant=0, float derivative_Constant=0, bool boolean_Controller=true){
    this->kp = proportional_Constant;
    this->ki = integral_Constant;
    this->kd = derivative_Constant;
    this->controller_Type = boolean_Controller;
}

unsigned long PID::determine_time(){
    return 0;
}

void PID::begin(float setpoint){
    this->setpoint = setpoint;
    this->timepoint = this->determine_time();
}

void PID::set_setpoint(float setpoint){
    this->setpoint = setpoint;
}

float PID::calculate(float measured_Value){
    unsigned long current_timepoint = this->determine_time();
    unsigned long time_passed = (current_timepoint - this->timepoint);
    float current_error = this->setpoint - measured_Value;
    float P = this->kp*current_error;
    float I = this->ki*((this->error*(time_passed))+((current_error-this->error)*(time_passed)/2));
    float D = this->kd*((current_error-this->error)/(time_passed));
    float sum = P + I + D;
    this->timepoint = current_timepoint;
    this->error = current_error;
    return sum;
}

float PID::calculate_controller_output_float(float measured_Value){
    float output = this->calculate(measured_Value);
    return output;
}

bool PID::calculate_controller_output_bool(float measured_Value){
    bool output_state = false;
    float output = this->calculate(measured_Value);
    if(output >= 0){
        output_state = true;
    }
    else{
        output_state = false;
    }
    return output_state;
}