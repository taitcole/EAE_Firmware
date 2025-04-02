#include "pid.h"

void initPID(PIDController *pid){
    pid->kp = PID_KP;
    pid->ki = PID_KI;
    pid->kd = PID_KD;
    pid->integral = 0.0f;
    pid->prevError = 0.0f;
}

float computePID(PIDController *pid, float setPoint, float currentTemp){
    
    float computePID;
    float error = setPoint - currentTemp;
    pid->integral += error;
    float derivative = error - pid->prevError;

    computePID = (pid->kp*error) + (pid->ki*pid->integral) + (pid->kd*derivative);
    pid->prevError = error;

    return computePID;
}