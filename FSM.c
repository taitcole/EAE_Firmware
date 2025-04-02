#include "FSM.h"
#include "CANBUS.h"

void stateMachine(systemState currentState){
    switch(currentState){
        case STATE_INIT:
            initCAN();  
            currentState = STATE_RUNNING;
            break;  
        case STATE_RUNNING:
            if(error == true){
                currentState = STATE_SHUTDOWN
            }else if(ignition == off){
                currentState = STATE_IGNITION_OFF;
            }else if(iterations = max){
                currentState = STATE_COMPLETE;
            }else{
                currentState = STATE_RUNNING;
            }
            break;
        case STATE_IGNITION_OFF:
            currentState = STATE_INIT;
            break;
        case STATE_SHUTDOWN:
            while(error == true);
            currentState = STATE_INIT;
            break;  
        case STATE_COMPLETE:
            break;
    }
}