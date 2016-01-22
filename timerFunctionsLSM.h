/*
 * timerFunctionsLSM.h
 *
 *  Created on: 28-12-2015
 *      Author: Mateusz
 */

#ifndef TIMERFUNCTIONSLSM_H_
#define TIMERFUNCTIONSLSM_H_

#include <stdint.h>
#include <DAVE3.h>

extern volatile unsigned int indexI2CreadByte;
extern uint8_t addressTimer;
extern uint8_t subAddressTimer;
extern uint16_t DataReceive2;


extern volatile unsigned int indexI2CwriteByte;
extern uint8_t addressTimerWrite;
extern uint8_t subAddressTimerWrite;
extern uint8_t dataWrite;

extern volatile unsigned int indexI2CreadBytes;
extern uint8_t addressTimerI2CReadBytes;
extern uint8_t subAddressTimerI2CReadBytes;
extern uint16_t accelerationXYZ[6];



void timerHandlerI2CreadByte(void *T);
void timerHandlerI2CreadBytes(void *T);
void timerHandlerI2CwriteByte(void *T);


#endif /* TIMERFUNCTIONSLSM_H_ */
