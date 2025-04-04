#ifndef PID_H
#define PID_H
#define PID_KP 2
#define PID_KI 0.05
#define PID_KD 1.5

typedef struct{
    float kp;
    float ki;
    float kd;
    float integral;
    float prevError;
}PIDController;

void initPID(PIDController *pid);

float computePID(PIDController *pid, float setPoint, float currentTemp);

#endif