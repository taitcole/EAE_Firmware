#ifndef CANBUS_H
#define CANBUS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

typedef struct{
    uint32_t id;
    uint8_t RTR;
    uint8_t IDE;
    uint8_t DLC;
    uint8_t data[8];
    uint16_t CRC;
} CANMessage;

void CAN_RX(CANMessage *message);

bool checkCRC(CANMessage *message);

uint16_t calculateCRC(CANMessage *message);

void CAN_TX(CANMessage *message);

void initCAN();

#endif