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
    float error = currentTemp - setPoint;
    pid->integral += error;
    float derivative = error - pid->prevError;

    computePID = (pid->kp*error) + (pid->ki*pid->integral) + (pid->kd*derivative);

    if(computePID > 100){
        computePID = 100;
    }

    if(computePID < 0){
        computePID = 0;
    }


    pid->prevError = error;

    return computePID;
}