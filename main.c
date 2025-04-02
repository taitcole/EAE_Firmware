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
 *
 * Constraints for simulation of cooling system:
 * 
 * 1. The pump level of the system is either defaulted to 80 L/min
 *    or 0 L/min for "Pump On" & "Pump Off", since the effects of 
 *    the pressure on the system is unknown.
 * 
 * 2. The fan speed was chosen at random to simulate how temperature
 *    affects the changing of the fan speed for increased/decrease cooling.
 * 
 * 3. Iterations only increase when the system is functioning properly 
 *    "functional iterations". If the iterations are repeated, it means
 *    that the system was previously stopped due to one of:
 * 
 *    -The ignition switch
 *    -Low reservoir levels
 *    -Extreme temperatures
 */
#include "fsm.h"
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


int main(int argc, char *argv[]){

    int setPoint;

    if(argc < 2){
        setPoint = 80;
    }else if(argc < 3){
        setPoint = atoi(argv[1]); 
    }else{
        printf("\nToo many arguments. Please provide only setpoint value.\n\n");
        return 1;
    }

    initFSM();
    int i = 0;
    srand(time(NULL));
    int temperature = 70;

    while(getState() != STATE_COMPLETE){
        stateMachine(&temperature, i, setPoint);

        if(getState() == STATE_RUNNING){
            i++;    
        }
    }
    return 0;
}