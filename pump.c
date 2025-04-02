#include "pump.h"

int setPumpSpeed(int pumpSwitch){
    int pumpSpeed = 0;

    if(pumpSwitch == 0){
        pumpSpeed = 0;
    }else{
        pumpSpeed = 80;
    }
    return pumpSpeed;
}