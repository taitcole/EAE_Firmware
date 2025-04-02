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
#include "fan.h"
#include "canbus.h"
#include <string.h>

/** 
 * @brief Gets the new fans speed based off of the pid loop 
 *        of the system. Values and ranges were chosen at random.
 * @param fanSwitch is the current status of the fan
 * @param pid is the updated value of the pid loop for fan speed control
 */
int newFanSpeed(int fanSwitch, float pid){
    int fanSpeed = 1000;

    if(fanSwitch == 0){
        fanSpeed = 0;
    }else{
        if(pid >= 60){
            fanSpeed = MAX_FAN_SPEED;
        }else if(pid < 60 && pid >= 20){
            fanSpeed = HIGH_FAN_SPEED;
        }else if(pid < 20 && pid > 1){
            fanSpeed = MEDIUM_FAN_SPEED;
        }else{
            fanSpeed = MIN_FAN_SPEED;
        }
    }
    return fanSpeed;
}

/** 
 * @brief Sets the fans speed based off of the speed given from 
 *        the CAN bus.
 * @param message is the CAN bus message that contains the fan speed 
 */
int setFanSpeed(CANMessage *message){
    int fanSpeed;
    memcpy(&fanSpeed, message->data, sizeof(int));
    return fanSpeed;
}

