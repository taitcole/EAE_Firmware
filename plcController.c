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
#include "plcController.h"
#include "tempSensor.h"
#include "statistics.h"
#include "fan.h"
#include "pump.h"
#include "fsm.h"
// int temperature = 0;
// int fanStatus = 0;
// int pumpStatus = 0;
// int fanSpeed = 0;
// int pumpSpeed = 0;
// int fluidLevel = 200;
// int ignitionSwitch = 0;
// int levelSwitch = 1;
// bool advance = false;

/** 
 * @brief Checks level and temperature sensors for faulty conditions
 * @param temperature is the current temperature in degrees celsius
 * @param fluidLevel is the reservoir fluid level in litres
 */
bool safeOperations(int temperature, int fluidLevel){

    bool isSafe = true;

    if(temperature > 120 || fluidLevel < 100){
        isSafe = false;
    }else{
        isSafe = true;
    }

    // Minimum reservoir capacity 
    if(fluidLevel <= 100){
        isSafe = false;
    }

    return isSafe;
}

// void checkSwitch(int iteration, bool advance){
//     if(((iteration + 1) % 5) == 0 && advance == false){
//         ignitionSwitch = 0;
//     }else{
//         advance = false;
//         ignitionSwitch = 1;
//     }
// }

// void stopPLC(){
//     fanStatus = 0;
//     pumpStatus = 0;
//     ignitionSwitch = 0;
//     levelSwitch = 0;
//     fanSpeed = setFanSpeed(fanStatus, temperature);
//     pumpSpeed = setPumpSpeed(pumpStatus);
// }

// void startPLC(){
//     fanStatus = 1;
//     pumpStatus = 1;
//     ignitionSwitch = 1;
//     levelSwitch = 1;
// }

// Generate some random DC Voltage between 0-5 V that would 
// be seen as a PLC input from the temperature sensor
// float generateRandomVoltage(){
//     int randomVoltage = rand() % 5 ;
//     return randomVoltage;
// }



// int main(){

//     startPLC();
//     int i = 0;
//     bool ignitionOff = false;
//     srand(time(NULL));

//     while(1){
//         float voltage = generateRandomVoltage();
//         checkSwitch(i, advance); 
//         temperature = convertVoltageToTemp(voltage);
//         bool isSafe = safeOperations(temperature, fluidLevel);

//         if(ignitionSwitch == 1 && i < 20 && isSafe == true){
//             fluidLevel -= 10;
//             fanSpeed = setFanSpeed(fanStatus, temperature);
//             pumpSpeed = setPumpSpeed(pumpStatus);
//             i++;
//         }else{
//             if(isSafe == false){
//                 stopPLC();
//                 fanSpeed = setFanSpeed(fanStatus, temperature);
//                 pumpSpeed = setPumpSpeed(pumpStatus);    

//                 if(fluidLevel <= 100){
//                     printf("\n\n\n\n\n\nAlerting Operator. System has been shut down due to a low reservoir level. Please take action.\n\n");
//                 }else{
//                     printf("\n\n\n\n\n\nAlerting Operator. System has been shut down due to high temperatures. Please take action.\n");    
//                 }
//                 // sleep(1); 
                    
//             }else if(i < 20 && isSafe == true){
//                 printf("\n\n\n\n\n\nIgnition Switch has been shut off.\n\n");
//                 stopPLC();
//                 // sleep(2);
//                 fanSpeed = setFanSpeed(fanStatus, temperature);
//                 pumpSpeed = setPumpSpeed(pumpStatus);
//                 ignitionOff = true;
//             }else{
//                 printf("\n\n\n\n\n\nSimulation is complete.\n");
//                 break;
//             }
//         }
//         // sleep(1);
//         struct systemStats stats = {temperature, fanStatus, fanSpeed, pumpStatus, pumpSpeed, fluidLevel, levelSwitch, ignitionSwitch};
//         printStatistics(&stats, i-1);

//         if(ignitionOff == true){
//             advance = true;
//             startPLC();
//             printf("\n\nIgnition Switch has been turned back on.\n\n");
//             // sleep(1);
//             ignitionOff = false;
//         }else{
//             if(!isSafe){
//                 if(fluidLevel <= 100){
//                     for(int j = 0; j < 3; j++){
//                         printf("\nRefilling the reservoir...");
//                         sleep(0.5);
//                     }
//                     printf("\n\nReservoir is full.\n");
//                     fluidLevel = 200;
//                 }

//                 printf("\nRestarting the system.\n\n\n\n\n");
//                 startPLC();    
//                 // sleep(1);
//             }
//         }
//         sleep(3);
//     }
//     return 0;

// }