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
#include "tempSensor.h"

/** 
 * @brief Converts sensor voltages from temperature sensor data sheet 
 *        into their respective temperatures.
 * @param voltage is the sensor voltage 
 */
int convertVoltageToTemp(float voltage){

    if(voltage >= V_TEMP_NEGATIVE_20){
        return -20;
    }else if(voltage >= V_TEMP_NEGATIVE_10){
        return -10;
    }else if(voltage >= V_TEMP_0){
        return 0;
    }else if(voltage >= V_TEMP_10){
        return 10;
    }else if(voltage >= V_TEMP_20){
        return 20;
    }else if(voltage >= V_TEMP_30){
        return 30;
    }else if(voltage >= V_TEMP_40){
        return 40;
    }else if(voltage >= V_TEMP_60){
        return 60;
    }else if(voltage >= V_TEMP_80){
        return 80;
    }else if(voltage >= V_TEMP_100){
        return 100;
    }else if(voltage >= V_TEMP_120){
        return 120;
    }else if(voltage >= V_TEMP_140){
        return 140;
    }else{
        return 160;
    }
}

