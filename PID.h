/*
  PID.h - Library for a simple PID controller
  Created by Simon Moeri, October 6, 2023.
  Released into the public domain.
*/

#ifndef PID_H
#define PID_H

class PID
{
    public:
        PID(float proportional_Constant, float integral_Constant, float derivative_Constant, bool boolean_Controller);
        ~PID();
        void begin(float setpoint);
        void set_constants(float proportional_Constant, float integral_Constant, float derivative_Constant, bool boolean_Controller);
        void set_setpoint(float setpoint);
        virtual unsigned long determine_time();
        float calculate_controller_output(float measured_Value);

    private:
        float kp = 1.0; //proportional constant
        float ki = 1.0; //integral constant
        float kd = 1.0; //derivative constant
        bool controller_Type = true; //if this is set to TRUE, controller output will be either 0 or 1, otherwise float
        unsigned long timepoint = 0; //storage for the time between calculations
        //unsigned long prev_Timepoint = 0.0;
        float setpoint = 0.0; //desired regulated value
        float measurement = 0.0; //actual measured value
        float error = 0.0; //difference between setpoint and measurement
        //float prev_Error = 0.0;
        //float integral = 0.0;
        float control_Output = 0.0; //in case of boolean controller this will be either 1 or 0 otherwise returns the float
        
};
#endif