#ifndef PLCCONTROLLER_H
#define PLCCONTROLLER_H
// #include "tempSensor.h"
#include <windows.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


// void checkSwitch(int iteration, bool advance);

bool safeOperations(int currentTemp, int fluidLevel);

// void stopPLC();

// void startPLC();

// float generateRandomVoltage();

#endif
