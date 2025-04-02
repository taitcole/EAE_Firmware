#include "fan.h"

int setFanSpeed(int fanSwitch, int temp){
    int fanSpeed = 1000;

    if(fanSwitch == 0){
        fanSpeed = 0;
    }else{
        if(temp >= 80){
            fanSpeed = MAX_FAN_SPEED;
        }else if(temp < 80 && temp >= 60){
            fanSpeed = 2000;
        }else if(temp < 60 && temp >= 40){
            fanSpeed = 1600;
        }else if(temp < 40 && temp >= 10){
            fanSpeed = 1200;
        }else{  
            fanSpeed = MIN_FAN_SPEED;
        }
    }
    return fanSpeed;
}
