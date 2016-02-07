/*
 * Bluetooth.c
 *
 *  Created on: 27-12-2015
 *      Author: Mateusz
 */

#include "Bluetooth.h"
#include "timerFunctions.h"
#include "LSM9DS1_drivers.h"

#define TURN_ON 1
#define TURN_OFF 0

#define START_ASKING 0
#define STOP_ASKING 1

#define INITIAL_STATE 0

char lk[20];

char checkAnswersBt[8][7];
char commandsInitBt[8][100];
unsigned char readData[MAX_READ_DATA];
char copiedData[MAX_READ_DATA];
unsigned char dataToSend[100];
unsigned char dataToReceive[100];

int lengthReceive;
int statusRxFifoFilling;
int howManyRead;
int lastStageOfInitializationBt;
int stageOfInitializationBt;
int statusSent;

uint32_t k;
uint32_t z;
uint32_t l;
uint32_t m;

handle_t TimerIdReceive;
uint32_t StatusReceive;

handle_t TimerIDSetConnection;
uint32_t statusSetConnection;
char turnOnSendingReceiving;
char sendStatus;
char readStatus;

handle_t receiveID;
handle_t transmitID;

uint32_t receiveStatus;
uint32_t transmitStatus;

handle_t emergencySentID;
handle_t emergencyReadID;

uint32_t emergencySentStatus;
uint32_t emergencyReadStatus;

handle_t TimerId;
uint32_t Status;

int chosenSensor;

char initStatus;

void initVariables(void)
{
	lengthReceive = 0;
	statusRxFifoFilling = 0;
	howManyRead = 0;
	stageOfInitializationBt = 0;
	lastStageOfInitializationBt = 0;
	statusSent = 0;

	initStatus  = 0;

	k = 0;
	z = 0;
	l = 0;
	m = 0;

	handle_t TimerIdReceive = 0;
	uint32_t StatusReceive = SYSTM001_ERROR;

	handle_t TimerIDSetConnection = 0;
	uint32_t statusSetConnection = SYSTM001_ERROR;
	char turnOnSendingReceiving = 0;
	char sendStatus = 0;
	char readStatus = 0;

	handle_t receiveID = 0;
	handle_t transmitID = 0;

	uint32_t receiveStatus = SYSTM001_ERROR;
	uint32_t transmitStatus = SYSTM001_ERROR;

	handle_t emergencySentID = 0;
	handle_t emergencyReadID = 0;

	uint32_t emergencySentStatus = SYSTM001_ERROR;
	uint32_t emergencyReadStatus = SYSTM001_ERROR;

	handle_t TimerId = 0;
	uint32_t Status = SYSTM001_ERROR;

	chosenSensor = -1; //neither of sensors were chosen
}

void timerHandler(void *T)
{
	char *command1 = commandsInitBt[stageOfInitializationBt];
	volatile int length = strlen(command1);

	send(command1, length);

	while((UART001_GetFlagStatus(&UART001_Handle0,UART001_TRANSFER_STATUS_BUSY_FLAG )==UART001_SET))
	{
		int h = 0;
	}
	l++;
	//potem trzeba poprosic od przes³anie odpowiedzi przez RTS
	askAboutSending();
	TimerIdReceive = SYSTM001_CreateTimer(200,SYSTM001_ONE_SHOT,timerReceiveHandler,NULL);
	if(TimerIdReceive != 0)
	{
		StatusReceive = SYSTM001_StartTimer(TimerIdReceive);
	}
}

void sendBluetooth(char *command1, char *answer)
{

}


int checkFunction(char answer[])
{
	lengthReceive = strlen(answer);
	if(strcmp(answer, (char*)readData) == 0)
	{
		return 0;
	}

	return 1;
}

void emptyReadData(void)
{
	volatile int j = 0;

	for(j = 0; j < MAX_READ_DATA; j++)
	{
		readData[j] = '\0';
	}
}

void askAboutSending(void)
{
	IO004_SetOutputValue(IO004_Handle2, START_ASKING);
}

void stopAskingAboutSending(void)
{
	IO004_SetOutputValue(IO004_Handle2, STOP_ASKING);
}

int statusRtsFlowControl(void)
{
	return IO004_ReadPin(IO004_Handle2);
}

int checkStatusCts(void)
{
	return IO004_ReadPin(IO004_Handle3);
}

void copyCheckAnswers(void)
{
	strcpy(checkAnswersBt[0], "ROK\r\n");
	strcpy(checkAnswersBt[1], "OK\r\n");
	strcpy(checkAnswersBt[2], "OK\r\n");
	strcpy(checkAnswersBt[3], "OK\r\n");
	strcpy(checkAnswersBt[4], "OK\r\n");
	strcpy(checkAnswersBt[5], "OK\r\n");
	strcpy(checkAnswersBt[6], "OK\r\n");
	strcpy(checkAnswersBt[7], "OK\r\n");
}

void copyCommands(void)
{
	strcpy(commandsInitBt[0], "AT+JRES\r\n");
	strcpy(commandsInitBt[1], "AT+JSEC=4,1,04,1111,0,0\r\n");
	strcpy(commandsInitBt[2], "AT+JSLN=07,Chmura1\r\n");
	strcpy(commandsInitBt[3], "AT+JRLS=32,13,0000110100001000800000805F9B34FB,Serial port 1,01,C20200\r\n");
	strcpy(commandsInitBt[4], "AT+JAAC=1\r\n");
	strcpy(commandsInitBt[5], "AT+JDIS=3\r\n");
	strcpy(commandsInitBt[6], "AT+JGPC=FFFD,0000,0000,0000,FFFD\r\n");
	strcpy(commandsInitBt[7], "AT+JSCR\r\n");
}

void initCommandsAndAnswers(void)
{
	copyCheckAnswers();
	copyCommands();
}

void initFlowControl(void)
{
	stopAskingAboutSending();
}


void timerReceiveHandler(void *T)
{
	//askAboutSending();
	m++;

	read();

	if(!checkFunction(checkAnswersBt[stageOfInitializationBt]))
	{
		stageOfInitializationBt++;
	}
	statusSent = 1;
}

int connectStatus(void)
{
	return IO004_ReadPin(IO004_Handle4);
}

void timerHandlerConnectionSet(void *T)
{
	char *command1 = commandsInitBt[lastStageOfInitializationBt];
	volatile int length = strlen(command1);

	send(command1, length);

	while((UART001_GetFlagStatus(&UART001_Handle0,UART001_TRANSFER_STATUS_BUSY_FLAG )==UART001_SET))
	{
		int h = 0;
	}
	l++;
	//potem trzeba poprosic od przes³anie odpowiedzi przez RTS
	askAboutSending();
	TimerIdReceive = SYSTM001_CreateTimer(200,SYSTM001_ONE_SHOT,timerReceiveHandler1,NULL);

	if(TimerIdReceive != 0)
	{
		StatusReceive = SYSTM001_StartTimer(TimerIdReceive);
	}
}


void timerReceiveHandler1(void *T)
{
	//askAboutSending();
	m++;

	read();

	if(!checkFunction(checkAnswersBt[lastStageOfInitializationBt]))
	{
		lastStageOfInitializationBt++;
	}

	statusSent = 1;
}

void receive(void *T)
{
	if(sendStatus == 0)
	{
		askAboutSending();
		readStatus = 1;
		read();
		readStatus = 0;
	}
}

void transmit(void *T)
{
	char kommando[20]/* = "DupaMateusz"*/;
	/*lk[0] = 'O';
	lk[1] = 'K';
	lk[2] = 'C';
	lk[3] = 'H';
	lk[4] = 'O';
	lk[5] = 'S';
	lk[6] = 'E';
	lk[7] = 'N';
	lk[8] = '\0';*/

	if(lk[0] != '\0')
	{
		int licznik = 0;
		for(licznik = 0; licznik < strlen(lk); licznik++)
		{
			kommando[licznik] = lk[licznik];
		}
		kommando[licznik] = '\0';

		int len = strlen(kommando);

		if(readStatus == 0)
		{
			sendStatus = 1;
			send(kommando, len);
			sendStatus = 0;
		}
	}

}


void transmitToSensor(void *T)
{
	char kommando[20]/* = "DupaMateusz"*/;


	if(lk[0] != '\0')
	{
		int licznik = 0;
		for(licznik = 0; licznik < strlen(lk); licznik++)
		{
			kommando[licznik] = lk[licznik];
		}
		kommando[licznik] = '\0';

		int len = strlen(kommando);

		if(readStatus == 0)
		{
			sendStatus = 1;
			send(kommando, len);
			sendStatus = 0;
		}
	}

}

void read(void)
{
	emptyReadData();
	if(((UART001_GetFlagStatus(&UART001_Handle0,UART001_FIFO_STD_RECV_BUF_FLAG)) == UART001_SET))
	{

		IO004_TogglePin(IO004_Handle1);

		statusRxFifoFilling = USIC_GetRxFIFOFillingLevel(UART001_0_USIC_CH);
		howManyRead =  UART001_ReadDataBytes(&UART001_Handle0, readData, statusRxFifoFilling);

		if(strcmp(readData, "LSM9DS1") == 0)
		{
			chosenSensor = 1;
		}
		else if(strcmp(readData, "TEMP_SENSOR") == 0)
		{
			chosenSensor = 2;
		}

		UART001_ClearFlag(&UART001_Handle0,UART001_FIFO_STD_RECV_BUF_FLAG);

		while(!USIC_ubIsRxFIFOempty(UART001_0_USIC_CH))
		{
			USIC_FlushRxFIFO(UART001_0_USIC_CH);
		}

		copyData();
		stopAskingAboutSending();
	}
}




void send(char* command1, int length)
{
	if(!statusRtsFlowControl())
	{
		stopAskingAboutSending();
	}

	/*char *command1 = commandsInitBt[i];
	volatile int length = strlen(command1);*/

	USIC_CH_TypeDef* UartRegs = UART001_Handle0.UartRegs;
	uint32_t WriteCount = 0;

	while(length)
	{
		/*while(checkStatusCts())
		{
			int h = 0;
		};*/

		if(!(USIC_CH_TCSR_TDV_Msk & UartRegs->TCSR))
		{
			while(checkStatusCts())
			{
				;
			}
			char c = command1[WriteCount];

			UartRegs->TBUF[0] = c;
			length--;
			WriteCount++;

			k = SYSTM001_GetTime();
		}

		if(UART001_GetFlagStatus(&UART001_Handle0,UART001_TRANS_BUFFER_IND_FLAG) == UART001_SET)
		{
			//po wyczyszczeniu flagi powinno sie przeslac
			UART001_ClearFlag(&UART001_Handle0,UART001_TRANS_BUFFER_IND_FLAG);
		}
	}
}

void copyData(void)
{
	volatile int i = 0;

	if(readData[0] != '\0')
	{
		for(i = 0; i < MAX_READ_DATA; i++)
		{
			if(readData[i] == '\0') //jak koniec tablicy
			{                       //to kopiuje znak konca linii i wychodze z petli
				copiedData[i] = readData[i];
				break;
			}

			copiedData[i] = readData[i];
		}
	}
}

void blueToothHandle(void)
{
	if(copiedData[0] == '+')
	{
		if(compareStrings("+RDII\r\n"))
		{
			turnOnLeftDiode();
		}
	}
}

char compareStrings(const char *string)
{
	if(strcmp((const char *)copiedData, string) == 0)
	{
		return 1;
	}

	return 0;
}

void turnOnLeftDiode(void)
{
	IO004_SetOutputValue(IO004_Handle0, TURN_ON);
}

void turnOffLeftDiode(void)
{
	IO004_SetOutputValue(IO004_Handle0, TURN_OFF);
}

void turnOnRightDiode(void)
{
	IO004_SetOutputValue(IO004_Handle1, TURN_ON);
}

void turnOffRightDiode(void)
{
	IO004_SetOutputValue(IO004_Handle1, TURN_OFF);
}

void checkStream(void)
{

	//sprawdzenie na to czy mamy event roz³¹czenia
	if(strstr((const char *)copiedData, "+RDII") != NULL)
	{
		turnOnRightDiode();

		//zastopowanie odbioru i transmisji danych
		removeTimer(&receiveStatus, &receiveID);
		removeTimer(&transmitStatus, &transmitID);
		//zastopowanie odbioru i transmisji danych

		//wlaczenie ponownej inicjalizacji
		makeTimer(500, SYSTM001_PERIODIC, timerHandler, NULL, &Status, &TimerId);

		stageOfInitializationBt = INITIAL_STATE;
		//wy³¹czenie mozliwosci wysy³u odbioru
		turnOnSendingReceiving = TURN_OFF;
		//wy³¹czenie mozliwosci wysy³u odbioru

		initStatus = 0;
		//wyresetowanie bufora danych
		for(int h = 0; h < MAX_READ_DATA; h++)
		{
			copiedData[h] = '\0';
		}
		//wyresetowanie bufora danych
	}

}

void emergencySentHandler(void *T)
{
	int len = strlen(dataToSend);
	send(dataToSend, len);
}
void emergencyReadHandler(void *T);

/*void makeTimer(uint32_t period, SYSTM001_TimerType TimerType, SYSTM001_TimerCallBackPtr TimerCallBack, void *pCallBackArgPtr, uint32_t *status, handle_t *timerID)
{
	*timerID = SYSTM001_CreateTimer(period,TimerType,TimerCallBack,NULL);

	if(*timerID != 0)
	{
		*status = SYSTM001_StartTimer(*timerID);
	}
}


void removeTimer(uint32_t *status, handle_t *timerID)
{
	if(*timerID != 0)
	{
		*status = SYSTM001_StopTimer(*timerID);

		if(*status == DAVEApp_SUCCESS)
		{
			SYSTM001_DeleteTimer(*timerID);
			*timerID = 0;
		}
	}
}*/


void manageConnection(void)
{
	k = SYSTM001_GetTime();
	k = SYSTM001_GetSysTickCount(100);
	z++;
	if(statusSent == 1) //jak statusSent jest rowny jeden to inicjalizujemy modul po kolei zwiêkszaj¹c stageOfInitializationBt
	{					//a¿ do stageOfInitializationBt == 6
		removeTimer(&StatusReceive, &TimerIdReceive);

		statusSent = 0;
	}

	if(stageOfInitializationBt == OUT_OF_INIT) //tutaj stageOfInitializationBt == 7 czyli mamy doczynienia z ostatnim etapem inicjalizacji
	{
		removeTimer(&Status, &TimerId); //usuniecie timera odpowiedzialnego za wysylanie w celu inicjalizacji

		stageOfInitializationBt++; //zwiekszenie licznika inicjalizacji w celu wyslania ostatniej komendy w ostatnim kroku
	}

	if(((stageOfInitializationBt - 1) == OUT_OF_INIT)) //wyslanie ostaniej ostaniej komendy
	{
		lastStageOfInitializationBt = OUT_OF_INIT;

		makeTimer(500, SYSTM001_PERIODIC, timerHandlerConnectionSet, NULL, &statusSetConnection, &TimerIDSetConnection); //wys³anie ostaniej komendy

		if(TimerIDSetConnection != 0)
		{
			stageOfInitializationBt++;
		}
	}
	else if(lastStageOfInitializationBt == (OUT_OF_INIT + 1))
	{
		removeTimer(&statusSetConnection, &TimerIDSetConnection);//usuniecie timera o odpowiedzialnego za wyslanie ostaniej komendy

		if(statusSetConnection == DAVEApp_SUCCESS)
		{
			removeTimer(&StatusReceive, &TimerIdReceive);

			lastStageOfInitializationBt++;
			turnOnSendingReceiving = 1;
		}
	}

	if(turnOnSendingReceiving == 1)
	{
		//deklaracja do odbioru

		makeTimer(500, SYSTM001_PERIODIC, receive, NULL, &receiveStatus, &receiveID);

		//deklaracja do wysylania
		makeTimer(1500, SYSTM001_PERIODIC, transmit, NULL, &transmitStatus, &transmitID);

		initStatus = 1;
		turnOnSendingReceiving = 0;

	}

	//blueToothHandle();

	//check stream, if disconnection occured
	checkStream();
	//check stream, if disconnection occured

	if(chosenSensor == 1)
	{
		//zastopowanie odbioru i transmisji danych
		removeTimer(&receiveStatus, &receiveID);
		removeTimer(&transmitStatus, &transmitID);
		//zastopowanie odbioru i transmisji danych
	}
	else if(chosenSensor == 2)
	{
		//zastopowanie odbioru i transmisji danych
		removeTimer(&receiveStatus, &receiveID);
		removeTimer(&transmitStatus, &transmitID);
		//zastopowanie odbioru i transmisji danych
		//cos tam

		//elo melo
	}
}

