/*
 * Bluetooth.h
 *
 *  Created on: 27-12-2015
 *      Author: Mateusz
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <DAVE3.h>			//Declarations from DAVE3 Code Generation (includes SFR declaration)
#include <string.h>

#define MAX_READ_DATA 70
#define OUT_OF_INIT 7

extern char checkAnswersBt[8][7];
extern char commandsInitBt[8][100];
extern unsigned char readData[MAX_READ_DATA];
extern char copiedData[MAX_READ_DATA];
extern unsigned char dataToSend[100];
extern unsigned char dataToReceive[100];

extern int chosenSensor;

//extern char lk[4];

extern int lengthReceive;
extern int statusRxFifoFilling;
extern int howManyRead;
extern int stageOfInitialization;
extern int lastStageOfInitialization;
extern int statusSent;

extern uint32_t k;
extern uint32_t z;
extern uint32_t l;
extern uint32_t m;

extern handle_t TimerIdReceive;
extern uint32_t StatusReceive;

extern handle_t TimerIDSetConnection;
extern uint32_t statusSetConnection;
extern char turnOnSendingReceiving;
extern char sendStatus;
extern char readStatus;

extern handle_t receiveID;
extern handle_t transmitID;

extern uint32_t receiveStatus;
extern uint32_t transmitStatus;

extern handle_t emergencySentID;
extern handle_t emergencyReadID;

extern uint32_t emergencySentStatus;
extern uint32_t emergencyReadStatus;

extern handle_t TimerId;
extern uint32_t Status;

extern char initStatus;

void initVariables(void);

//timery przy inicjalizacji
void timerHandler(void *T);
void timerReceiveHandler(void *T);
//timery przy inicjalizacji

//do wyslania 7 komendy
void timerHandlerConnectionSet(void *T);
void timerReceiveHandler1(void *T);
//do wyslania 7 komendy

void emergencySentHandler(void *T);
void emergencyReadHandler(void *T);

//handlery do wysylania i odbierania wiadomosci z bluetooth w stream mode
void receive(void *T);
void transmit(void *T);

void transmitToSensor(void *T); //wysylanie do czujnika
//handlery do wysylania i odbierania wiadomosci z bluetooth w stream mode

void sendBluetooth(char *command1, char *answer);
int checkFunction(char answer[]);
void emptyReadData(void);
int checkStatusCts(void);
void copyCheckAnswers(void);
void copyCommands(void);
void initCommandsAndAnswers(void);
void initFlowControl(void);
void askAboutSending(void);
void stopAskingAboutSending(void);
int statusRtsFlowControl(void);
int connectStatus(void);
void send(char* command1, int length);
void read(void);
void copyData(void);
void blueToothHandle(void);
char compareStrings(const char *string);

void turnOnLeftDiode(void);
void turnOffLeftDiode(void);

void turnOnRightDiode(void);
void turnOffRightDiode(void);
void checkStream(void);

/*void makeTimer(uint32_t period, SYSTM001_TimerType TimerType, SYSTM001_TimerCallBackPtr TimerCallBack, void *pCallBackArgPtr, uint32_t *status, handle_t *timerID);
void removeTimer(uint32_t *status, handle_t *timerID);*/
void manageConnection(void);

#endif /* BLUETOOTH_H_ */
