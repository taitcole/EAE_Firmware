#ifndef FSM_H
#define FSM_H
#include <stdbool.h>

typedef enum{
    STATE_INIT,
    STATE_RUNNING,
    STATE_IGNITION_OFF,
    STATE_SHUTDOWN,
    STATE_COMPLETE
} systemState;

systemState getState();

void initFSM();
void checkSwitch(int iteration, bool advance);
void stopPLC(int temperature);
void startPLC();
void systemRunning(int temperature);

void stateMachine(int temperature, int iterations);

#endif