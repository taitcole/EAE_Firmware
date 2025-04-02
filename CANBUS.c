#include "canbus.h"


CANMessage messagesBuffer[20];

int head;
int tail;
int messages;

// Transmit CAN Message
void CAN_TX(CANMessage *message){

    if(message->DLC > 8){
        printf("\nError. Cannot send more than 8 bytes of data.\n");
        return;
    }

    if(messages > 20){
        printf("\nError. Too many messages on CAN bus at the moment.\n");
        return;
    }

    message->CRC = calculateCRC(&message);

    message = &messagesBuffer[tail];

    // Circular queue
    tail = tail % 20;
    tail++;
    messages++;

}

void CAN_RX(CANMessage *message){

    bool errorCheck = false;
    
    if(!checkCRC(&message->CRC)){
        printf("\nError. Message was corrupted. Discarding.\n");
    }else if(messages == 0){
        printf("\nError. No messages on the CAN bus at this time.\n"); 
    }else{
        printf("");
    }

    head = head % 5;
    messages--;

}

uint16_t calculateCRC(CANMessage *message){
    return 0;
}

bool checkCRC(CANMessage *message){
    return true;
}

void initCAN(){
    head = 0;
    tail = 0;
    messages = 0;
}

