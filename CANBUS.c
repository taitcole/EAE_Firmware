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
#include "canbus.h"

CANMessage messagesBuffer[20];

int head;
int tail;
int messages;

/** 
 * @brief Initiation of CAN bus module
 */
void initCAN(){
    head = 0;
    tail = 0;
    messages = 0;
}

/** 
 * @brief Transmitter for CAN bus message 
 * @param message is the message being transmitted by the CAN bus
 */
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

/** 
 * @brief Receiver for CAN bus message 
 * @param message is the message being received by the CAN bus
 */
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

/** 
 * @brief RCR calculation for transmitting message
 * @param message is the message being transmitted by the CAN bus
 */
uint16_t calculateCRC(CANMessage *message){
    return 0;
}

/** 
 * @brief RCR checking for receiving message
 * @param message is the message being received by the CAN bus
 */
bool checkCRC(CANMessage *message){
    return true;
}


