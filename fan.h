#ifndef FAN_H
#define FAN_H
#define MAX_FAN_SPEED 2450
#define MIN_FAN_SPEED 600
#define MEDIUM_FAN_SPEED 1600
#define HIGH_FAN_SPEED 2000
#include "canbus.h"

int newFanSpeed(int fanSwitch, float pid);

int setFanSpeed(CANMessage *message);

#endif