#ifndef FSM_H
#define FSM_H

typedef enum{
    STATE_INIT,
    STATE_RUNNING,
    STATE_IGNITION_OFF,
    STATE_SHUTDOWN,
    STATE_COMPLETE
} systemState;

void stateMachine(int currentState);

#endif