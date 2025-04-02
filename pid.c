/*
 * Epiroc Combined Challenge - Question 7 Coding
 * Author: Cole Tait
 *
 *****************
 *** IMPORTANT ***
 *****************
 * This program can be ran through the "make run" command 
 * inside of the MSYS2 MINGW64 Shell. 
 * 
 * Also increasing the size of the shell to fit the entire table
 * is recommended for the best visual experience of the system.
 */
#include "pid.h"

/** 
 * @brief Initiation of PID loop module
 */
void initPID(PIDController *pid){
    pid->kp = PID_KP;
    pid->ki = PID_KI;
    pid->kd = PID_KD;
    pid->integral = 0.0f;
    pid->prevError = 0.0f;
}

/** 
 * @brief Computes the PID of the systems temperature to speed up or slow down fans 
 * @param pid is a pointer to the pid struct to maintain memory
 * @param setPoint is the desired temperature of the system
 * @param currentTemp is the current temperature of the system
 */
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