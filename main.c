#include "FSM.h"
// #include "CANBUS.h"
#include "plcController.h"
#include "pid.h"
#include "tempSensor.h"
#include "statistics.h"
#include "fan.h"
#include "pump.h"

#include <windows.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


int main(){

    bool advance = false;
    int temperature = 0;
    // int fanStatus = 0;
    // int pumpStatus = 0;
    // int fanSpeed = 0;
    // int pumpSpeed = 0;
    // int fluidLevel = 200;
    // int levelSwitch = 1;

    initFSM();

    int i = 0;

    srand(time(NULL));

    struct systemStats stats;

    while(getState() != STATE_COMPLETE){
        float voltage = generateRandomVoltage();
        temperature = convertVoltageToTemp(voltage);
        stateMachine(temperature, i);

        if(getState() == STATE_RUNNING){
            i++;    
        }
    }

    return 0;
}