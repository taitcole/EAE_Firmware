#include "tempSensor.h"

int convertVoltageToTemp(float voltage){

    int temp;
    
    if(voltage >= 4.771){
        temp = -20;
    }else if(voltage >= 4.642){
        temp = -10;
    }else if(voltage >= 4.438){
        temp = 0;
    }else if(voltage >= 4.141){
        temp = 10;
    }else if(voltage >= 3.751){
        temp = 20;
    }else if(voltage >= 3.325){
        temp = 30;
    }else if(voltage >= 2.838){
        temp = 40;
    }else if(voltage >= 1.915){
        temp = 60;
    }else if(voltage >= 1.212){
        temp = 80;
    }else if(voltage >= 0.749){
        temp = 100;
    }else if(voltage >= 0.465){
        temp = 120;
    }else if(voltage >= 0.295){
        temp = 140;
    }else{
        temp = 160;
    }

    return temp;
}

