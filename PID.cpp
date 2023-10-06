/*
  PID.h - Library for a simple PID controller
  Created by Simon Moeri, October 6, 2023.
  Released into the public domain.
*/

#include "PID.h"

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

float PID::calculate_controller_output(float measured_Value){
    unsigned long current_timepoint = this->determine_time();
    float current_error = this->setpoint - measured_Value;
    float P = this->kp*current_error;
    float I = this->ki*((this->error*(current_timepoint-this->timepoint))+((current_error-this->error)*(current_timepoint-this->timepoint)/2));
    float D = this->kd*((current_error-this->error)/(current_timepoint-this->timepoint));
    float sum = P + I + D;
    this->timepoint = current_timepoint;
    this->error = current_error;
    return sum;
}