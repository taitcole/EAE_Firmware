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
#include "pump.h"

/** 
 * @brief Sets the pumps speed as 80 L/min or off 
 *        depending on the status of the pump and system
 * @param pumpSwitch is the current status of the pump
 */
int setPumpSpeed(int pumpSwitch){
    if(pumpSwitch == 0){
        return PUMP_OFF;
    }else{
        return PUMP_ON;
    }
}