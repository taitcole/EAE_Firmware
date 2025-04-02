#ifndef STATISTICS_H
#define STATISTICS_H
#define EXTRA_SPACE " "
#include <stdio.h>
// char *status[] = {"Off", "On"};

struct systemStats{
    int temperature;
    int fanStatus;
    int fanSpeed;
    int pumpStatus;
    int pumpSpeed;
    int fluidLevel;
    int levelSwitch;
    int ignitionSwitch;
};

void formatHeader();

int intLength(int integer);

void printStatistics(struct systemStats *stats, int iteration);

#endif