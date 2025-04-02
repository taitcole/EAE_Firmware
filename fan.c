#include "fan.h"

int setFanSpeed(int fanSwitch, float pid){
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
