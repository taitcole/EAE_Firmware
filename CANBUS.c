#include "CANBUS.h"

CanMessage messagesBuffer[5];

int tail = 0;

// Transmit CAN Message
void CAN_TX(CanMessage *message){

    message = &messagesBuffer[tail];

    // Circular queue
    tail = (tail + 1) % 5;

    // message->id = id;
    // message->RTR = RTR;
    // message->IDE = IDE;
    // message->DLC = DLC;
    // message->data[]

    

}

