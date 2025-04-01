#ifndef CANBUS_H
#define CANBUS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct{
    uint32_t id;
    uint8_t RTR;
    uint8_t IDE;
    uint8_t DLC;
    uint8_t data[8];
} CanMessage;

void CAN_RX();

void CAN_TX(CanMessage *message);

void initCAN();

#endif