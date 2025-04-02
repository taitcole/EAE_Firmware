#include "fsm.h"
#include "canbus.h"
#include "plcController.h"
#include "pid.h"
#include "tempSensor.h"
#include "statistics.h"
#include "fan.h"
#include "pump.h"
#include <stdbool.h>

static systemState currentState;
struct systemStats stats;
static int currentTemp;
static PIDController pid;

int fanStatus = 0;
int pumpStatus = 0;
int fanSpeed = 0;
int pumpSpeed = 0;
int fluidLevel = 200;
int levelSwitch = 1;
int ignitionSwitch = 0;
bool ignitionOff = false;

void checkSwitch(int iteration, bool advance){
    if(((iteration + 1) % 5) == 0 && advance == false){
        ignitionSwitch = 0;
    }else{
        advance = false;
        ignitionSwitch = 1;
    }
}

void startPLC(int temperature){
    fanStatus = 1;
    pumpStatus = 1;
    ignitionSwitch = 1;
    levelSwitch = 1;
    fanSpeed = setFanSpeed(fanStatus, temperature);
    pumpSpeed = setPumpSpeed(pumpStatus);
}


void stopPLC(int temperature){
    fanStatus = 0;
    pumpStatus = 0;
    ignitionSwitch = 0;
    levelSwitch = 0;
    fanSpeed = setFanSpeed(fanStatus, temperature);
    pumpSpeed = setPumpSpeed(pumpStatus);
}

systemState getState(){
    return currentState;
}

void tempChange(int fanSpeed, int *temperature){
    // printf("FAN SPEED: %d", fanSpeed);
    switch(fanSpeed){
        case MAX_FAN_SPEED:
            *temperature -= 5;
            break;
        case HIGH_FAN_SPEED:
            *temperature -= 3;
            break;
        case MEDIUM_FAN_SPEED:
            *temperature += 5;
            break;
        case MIN_FAN_SPEED:
            *temperature += 10;
            break;
    }

}

void systemRunning(int *temperature, int setPoint){

    fluidLevel -= 10;
    CANMessage message;
    float compPID = computePID(&pid, setPoint, *temperature);
    // printf("\n\nTEST PID: %f TEMP: %d SET: %d\n\n", compPID, *temperature, setPoint);
    fanSpeed = setFanSpeed(fanStatus, compPID);

    message.id = CHANGE_FAN_SPEED;
    message.RTR = 0;
    message.IDE = 0;
    message.DLC = FAN_SPEED_DATA_SIZE;
    memcpy(message.data, &fanSpeed, sizeof(fanSpeed));
    message.CRC = 0;
    
    pumpSpeed = setPumpSpeed(pumpStatus);
}

void initFSM(){
    ignitionOff = false;
    currentState = STATE_INIT;
}

void stateMachine(int *temperature, int iterations, int setPoint){

    switch(currentState){
        case STATE_INIT:
            // initCAN(); 
            initPID(&pid);
            startPLC(*temperature); 
            if(ignitionOff){
                printf("\n\nIgnition Switch has been turned on.\n\n");
                ignitionOff = false;
            }
            currentState = STATE_RUNNING;
            break;  
        case STATE_RUNNING:
            if(safeOperations(*temperature, fluidLevel) == false){
                *temperature = 70;
                stopPLC(*temperature);
                currentTemp = *temperature;
                if(fluidLevel <= 100){
                    printf("\n\n\n\n\n\nAlerting Operator. System has been shut down due to a low reservoir level. Please take action.\n\n");
                }else{
                    printf("\n\n\n\n\n\nAlerting Operator. System has been shut down due to high temperatures. Please take action.\n");    
                }
                // currentTemp = temperature;
                currentState = STATE_SHUTDOWN;
            }else if(ignitionSwitch == false){
                printf("\n\n\n\n\n\nIgnition Switch has been shut off.\n\n");
                *temperature = 70;
                stopPLC(*temperature);
                currentState = STATE_IGNITION_OFF;
            }else if(iterations == 20){
                printf("\n\n\n\n\n\nSimulation is complete.\n");
                *temperature = 70;
                stopPLC(*temperature);
                currentState = STATE_COMPLETE;
            }else{
                systemRunning(temperature, setPoint);
                tempChange(fanSpeed, temperature);
                currentState = STATE_RUNNING;
            }
            break;
        case STATE_IGNITION_OFF:
            ignitionOff = true;
            currentState = STATE_INIT;
            break;
        case STATE_SHUTDOWN:
            // stopPLC();
            if(fluidLevel <= 100){
                for(int j = 0; j < 3; j++){
                    printf("\nRefilling the reservoir...");
                    sleep(0.5);
                }
                printf("\n\nReservoir is full.\n");
                fluidLevel = 200;
            }else{
                while(currentTemp > 70){
                    printf("\n\nTemperature is cooling: %d C\n", currentTemp);
                    currentTemp -= 10;
                    sleep(1);
                }
                *temperature = 70;
            }
            printf("\nRestarting the system.\n\n\n\n\n");
            currentState = STATE_INIT;
            break;  
        case STATE_COMPLETE:
            break;
    }

    if(currentState != STATE_INIT && currentState != STATE_COMPLETE){
        stats.temperature = *temperature;
        stats.fanStatus = fanStatus;
        stats.fanSpeed = fanSpeed;
        stats.pumpStatus = pumpStatus;
        stats.pumpSpeed = pumpSpeed;
        stats.fluidLevel = fluidLevel;
        stats.levelSwitch = levelSwitch;
        stats.ignitionSwitch = ignitionSwitch;

        printStatistics(&stats, iterations);
        sleep(3);
    }
}