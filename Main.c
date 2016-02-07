/*
 * Main.c
 *
 *  Created on: 27-12-2015
 *      Author: Mateusz
 */





#include <DAVE3.h>			//Declarations from DAVE3 Code Generation (includes SFR declaration)
#include "Bluetooth.h"
#include "LSM9DS1_drivers.h"
#include "LSM9DS1_Registers.h"
#include "LSM9DS1_Types.h"
#include "timerFunctions.h"


#define LSM9DS1_M	0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG	0x6B // Would be 0x6A if SDO_AG is LOW

/*handle_t TimerId;
uint32_t Status;*/
void initBluetooth(void);
void initLSM9DS1(void);

int accelMeasurementsNum;

int main(void)
{
//	status_t status;		// Declaration of return variable for DAVE3 APIs (toggle comment if required)


	DAVE_Init();			// Initialization of DAVE Apps

	initLSM9DS1();
	calibrate(TRUE);

	accel pomiary[100];

	//initBluetooth();
	accelMeasurementsNum = 0;

	while(1)
	{
		if(	accelMeasurementsNum > 99)
		{
			accelMeasurementsNum = 0;
		}

		/*if(initStatus)
		{*/
		readAccel1v1(pomiary);
		/*}*/

		manageConnection();
	}
	return 0;
}

void initBluetooth(void)
{
	initVariables();
	initCommandsAndAnswers();
	initFlowControl();

	makeTimer(500, SYSTM001_PERIODIC, timerHandler, NULL, &Status, &TimerId);
}

void initLSM9DS1(void)
{
	init(IMU_MODE_I2C, LSM9DS1_AG_ADDR(1), LSM9DS1_M_ADDR(1));

	settings.device.commInterface = IMU_MODE_I2C;
	settings.device.mAddress = LSM9DS1_M;
	settings.device.agAddress = LSM9DS1_AG;

	if(!begin())
	{
		int k = 0;
	}
}
