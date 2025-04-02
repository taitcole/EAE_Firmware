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
#include "canbus.h"
#include "plcController.h"
#include "pid.h"
#include "tempSensor.h"
#include "statistics.h"
#include "fan.h"
#include "pump.h"
#include <stdbool.h>
#define MAX_ITERATIONS 20

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

/** 
 * @brief Simulation function for turning the ignition switch off every 5 iterations
 * @param iteration is the current functional iteration of the system simulation
 * @param advance checks whether the ignition switch was just turned off
 */
void checkSwitch(int iteration, bool advance){
    if(((iteration + 1) % 5) == 0 && advance == false){
        ignitionSwitch = 0;
    }else{
        advance = false;
        ignitionSwitch = 1;
    }
}

/** 
 * @brief Turns on all components after safety of system is restored
 * @param temperature is used to set fan speed of initial state temperature
 */
void startPLC(int temperature){
    fanStatus = 1;
    pumpStatus = 1;
    ignitionSwitch = 1;
    levelSwitch = 1;
    fanSpeed = newFanSpeed(fanStatus, temperature);
    pumpSpeed = setPumpSpeed(pumpStatus);
}

/** 
 * @brief Turns off all components of the system was safety check returns faulty
 * @param temperature is used to set fan speed of initial state temperature
 */
void stopPLC(int temperature){
    fanStatus = 0;
    pumpStatus = 0;
    ignitionSwitch = 0;
    levelSwitch = 0;
    fanSpeed = newFanSpeed(fanStatus, temperature);
    pumpSpeed = setPumpSpeed(pumpStatus);
}

/** 
 * @brief Returns the current state of the FSM
 */
systemState getState(){
    return currentState;
}

/** 
 * @brief Adjusts temperature of system based on fan speed (for simulation purposes)
 * @param fanSpeed is used to set temperature of the system
 * @param temperature is a pointer to temperature that gets updated every iteration
 */
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

/** 
 * @brief Ensures operation of the entire cooling system and CAN bus in the running state
 * @param temperature is the current temperature of the system
 * @param setPoint is the desired temperature used in the pid loop
 */
void systemRunning(int *temperature, int setPoint){

    fluidLevel -= 10;
    CANMessage message;
    float compPID = computePID(&pid, setPoint, *temperature);
    int newSpeed = newFanSpeed(fanStatus, compPID);

    message.id = CHANGE_FAN_SPEED;
    message.RTR = 0;
    message.IDE = 0;
    message.DLC = FAN_SPEED_DATA_SIZE;
    memcpy(message.data, &newSpeed, sizeof(newSpeed));
    message.CRC = 0;
    
    fanSpeed = setFanSpeed(&message);
    pumpSpeed = setPumpSpeed(pumpStatus);
}

/** 
 * @brief Initiates state machine
 */
void initFSM(){
    ignitionOff = false;
    currentState = STATE_INIT;
}

/** 
 * @brief State machine that runs the entire process of the system from start to end
 * @param temperature is the current temperature of the system
 * @param setPoint is the desired temperature of the system
 */
void stateMachine(int *temperature, int iterations, int setPoint){

    switch(currentState){
        case STATE_INIT:
            initCAN(); 
            initPID(&pid);
            if(iterations == 0){
                startPLC(10);
            }else{
                startPLC(*temperature); 
            }
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
                currentState = STATE_SHUTDOWN;
            }else if(ignitionSwitch == false){
                printf("\n\n\n\n\n\nIgnition Switch has been shut off.\n\n");
                *temperature = 70;
                stopPLC(*temperature);
                currentState = STATE_IGNITION_OFF;
            }else if(iterations == MAX_ITERATIONS){
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