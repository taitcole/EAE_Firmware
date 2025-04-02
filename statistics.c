#include "statistics.h"

char *status[] = {"Off", "On"};

int intLength(int integer){
    char temp[5];
    return sprintf(temp, "%d", integer);
}

void printStatistics(struct systemStats *stats, int iteration){

    int fanSpeedLength = intLength(stats->fanSpeed);
    int temperatureLength = intLength(stats->temperature);
    int extraSpaceFanSpeed = 5 - fanSpeedLength;
    int extraSpaceTemp = 9 - temperatureLength;
    int fixSpace = (temperatureLength == 2) ? ((fanSpeedLength == 4) ? 1 : 0) : ((fanSpeedLength == 4) ? 1 : 0);

    printf("\n\n\n----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                   Cooling System Statistics                                                          \n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %11s | %10s | %9s | %11s | %10s | %15s | %18s | %15s | %9s |", "Temperature", "Fan Status", "Fan Speed", "Pump Status", "Pump Speed", "Reservoir Level", "Fluid Level Switch", "Ignition Switch", "Iteration");
    printf("\n----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %d C%*s | %-10s | %d RPM%*s | %-11s | %d L/min%*s | %d L%*s | %-18s | %-15s | %-9d |", stats->temperature, extraSpaceTemp, EXTRA_SPACE, status[stats->fanStatus], stats->fanSpeed, extraSpaceFanSpeed, EXTRA_SPACE, status[stats->pumpStatus], stats->pumpSpeed, 3 - fixSpace, EXTRA_SPACE, stats->fluidLevel, 10, EXTRA_SPACE, status[stats->levelSwitch], status[stats->ignitionSwitch], iteration + 1);
    printf("\n----------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

