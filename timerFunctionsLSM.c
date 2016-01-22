/*
 * timerFunctionsLSM.c
 *
 *  Created on: 28-12-2015
 *      Author: Mateusz
 */
#include "timerFunctionsLSM.h"
#include "timerFunctions.h"
#include "LSM9DS1_drivers.h"

volatile unsigned int indexI2CreadByte = 0;
uint8_t addressTimer = 0;
uint8_t subAddressTimer = 0;
uint16_t DataReceive2 = 0x0000;

volatile unsigned int indexI2CreadBytes = 0;
uint8_t addressTimerI2CReadBytes = 0;
uint8_t subAddressTimerI2CReadBytes = 0;

volatile unsigned int indexI2CwriteByte = 0;
uint8_t addressTimerWrite = 0;
uint8_t subAddressTimerWrite = 0;
uint8_t dataWrite = 0;

uint16_t accelerationXYZ[6] = {0, 0, 0, 0, 0, 0};

void timerHandlerI2CreadByte(void *T)
{
	//I2C001_DataType data1,data2,data3,data4,data5, data6, data7;


	//int timeout = LSM9DS1_COMMUNICATION_TIMEOUT;

	uint8_t data; // `data` will store the register data

	//wyslanie warunku startowego
	if(0 == indexI2CreadByte)
	{
		I2C001_DataType data1;
		data1.Data1.TDF_Type = I2C_TDF_MStart;
		data1.Data1.Data = ((addressTimer<<1) | I2C_WRITE);
		while(!I2C001_WriteData(&I2C001_Handle0,&data1));
		indexI2CreadByte++;
	}
	else if(1 == indexI2CreadByte)
	{
		I2C001_DataType data3;
		data3.Data1.TDF_Type = I2C_TDF_MTxData;
		data3.Data1.Data = subAddressTimer;
		while(!I2C001_WriteData(&I2C001_Handle0,&data3));
		indexI2CreadByte++;
	}
	else if(2 == indexI2CreadByte)
	{
		I2C001_DataType data5;
		data5.Data1.TDF_Type = I2C_TDF_MRStart;
		data5.Data1.Data = ((addressTimer<<1) | I2C_READ);
		while(!I2C001_WriteData(&I2C001_Handle0,&data5));
		indexI2CreadByte++;
	}
	else if(3 == indexI2CreadByte)
	{
		I2C001_DataType data6;
		data6.Data1.TDF_Type = I2C_TDF_MRxAck1;
		data6.Data1.Data = ubyteFF;
		while(!I2C001_WriteData(&I2C001_Handle0,&data6));
		indexI2CreadByte++;
	}
	else if(4 == indexI2CreadByte)
	{
		I2C001_DataType data7;
		data7.Data1.TDF_Type = I2C_TDF_MStop;
		data7.Data1.Data = ubyteFF;
		while(!I2C001_WriteData(&I2C001_Handle0,&data7));
		indexI2CreadByte++;
	}
	else if(5 == indexI2CreadByte)
	{
		while(!I2C001_ReadData(&I2C001_Handle0,&DataReceive2))
		{
			;
		}
		indexI2CreadByte++;
	}
}

void timerHandlerI2CreadBytes(void *T)
{
	while(1){
	if(0 == indexI2CreadBytes)
	{
		I2C001_DataType data1;
		data1.Data1.TDF_Type = I2C_TDF_MStart;
		data1.Data1.Data = ((addressTimerI2CReadBytes<<1) | I2C_WRITE);
		while(!I2C001_WriteData(&I2C001_Handle0,&data1));
		indexI2CreadBytes++;
	}
	else if(1 == indexI2CreadBytes)
	{
		I2C001_DataType data2;
		data2.Data1.TDF_Type = I2C_TDF_MTxData;
		data2.Data1.Data = (subAddressTimerI2CReadBytes);
		while(!I2C001_WriteData(&I2C001_Handle0,&data2));
		indexI2CreadBytes++;
	}
	else if(2 == indexI2CreadBytes)
	{
		I2C001_DataType data3;
		data3.Data1.TDF_Type = I2C_TDF_MRStart;
		data3.Data1.Data = ((addressTimerI2CReadBytes<<1) | I2C_READ);
		while(!I2C001_WriteData(&I2C001_Handle0,&data3));
		indexI2CreadBytes++;
	}
	else if(3 == indexI2CreadBytes)
	{
		I2C001_DataType data4;
		/*for(int i = 0; i < 6; i++)
		{
			if(i !=5)
			{*/
				/*data4.Data1.TDF_Type = I2C_TDF_MRxAck0;
			}
			else
			{*/
				data4.Data1.TDF_Type = I2C_TDF_MRxAck1;
			//}
			data4.Data1.Data = ubyteFF;
			while(!I2C001_WriteData(&I2C001_Handle0,&data4))
			{
				;
			}

			while(!I2C001_ReadData(&I2C001_Handle0,&accelerationXYZ[indexAccel]))
			{
				;
			}
		//}
		indexI2CreadBytes++;
	}
	else if(4 == indexI2CreadBytes)
	{
		I2C001_DataType data5;
		data5.Data1.TDF_Type = I2C_TDF_MStop;
		data5.Data1.Data = ubyteFF;
		while(!I2C001_WriteData(&I2C001_Handle0,&data5));
		indexI2CreadBytes++;
	}
	else if(indexI2CreadBytes == 5)
	{
		break;
	}
	}
}


void timerHandlerI2CwriteByte(void *T)
{
	if(0 == indexI2CwriteByte)
	{
		I2C001_DataType data1;
		data1.Data1.TDF_Type = I2C_TDF_MStart;
		data1.Data1.Data = ((addressTimerWrite<<1) | I2C_WRITE);
		while(!I2C001_WriteData(&I2C001_Handle0,&data1));
		indexI2CwriteByte++;
	}
	else if(1 == indexI2CwriteByte)
	{
		I2C001_DataType data2;
		data2.Data1.TDF_Type = I2C_TDF_MTxData;
		data2.Data1.Data = subAddressTimerWrite;
		while(!I2C001_WriteData(&I2C001_Handle0,&data2));
		indexI2CwriteByte++;
	}
	else if(2 == indexI2CwriteByte)
	{
		I2C001_DataType data3;
		data3.Data1.TDF_Type = I2C_TDF_MTxData;
		data3.Data1.Data = dataWrite;
		while(!I2C001_WriteData(&I2C001_Handle0,&data3));
		indexI2CwriteByte++;
	}
	else if(3 == indexI2CwriteByte)
	{
		I2C001_DataType data4;
		data4.Data1.TDF_Type = I2C_TDF_MStop;
		data4.Data1.Data = ubyteFF;
		while(!I2C001_WriteData(&I2C001_Handle0,&data4));
		indexI2CwriteByte++;
	}
}
