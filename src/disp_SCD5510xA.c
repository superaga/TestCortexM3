/*
 * @brief SCD5510xA display driver
 *
 * @note Created on: 07/06/2015
 *
 *
===============================================================================
 Name        : disp_SCD5510xA.c
 Author      : $(superaga)
 Version     : 0.1
 Copyright   : $(gpl)
 Description : SCD5510xA display driver
===============================================================================
*/

#include "disp_SCD5510xA.h"

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize SSP peripheral for communication with display */
void displayInit(void)
{
	/* SSP INITIALIZATION */
	Chip_SSP_Init(LPC_SSP);		/* Default init: SSP_MODE_MASTER, SSP_BITS_8, SSP_FRAMEFORMAT_SPI, SSP_CLOCK_CPHHA0_CPOL0 */
	Chip_Clock_SetSSP0ClockDiv(18);		/* */

	/* define peripherals options */
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI;
	ssp_format.bits = SSP_DATA_BITS;
	ssp_format.clockMode = SSP_CLOCK_MODE0;

	/* set parameters to peripherals SSP0 */
	Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);

	/* Set the SSP operating modes, master or slave */
	Chip_SSP_SetMaster(LPC_SSP, SSP_MODE_TEST);

	/* Enable SSP operation */
	Chip_SSP_Enable(LPC_SSP);

}

/* Set display brightness */
void displaySetBrightness(DISPLAY_BRIGHTNESS_VALUES_T level)
{
	Chip_SSP_SendFrame(LPC_SSP, LPC_SSP, flipByte(DISPLAY_BRIGHTNESS_OPCODE|level));
}


/* Lights on all display leds @ 53% */
void displayTest(void)
{
	Chip_SSP_SendFrame(LPC_SSP, flipByte(DISPLAY_LAMP_TEST));
}

/* Power down display */
void displayPowerDown(void)
{
	Chip_SSP_SendFrame(LPC_SSP, flipByte(DISPLAY_POWER_DOWN));
}

/* Reset display register and clear display */
void displayClear(void)
{
	Chip_SSP_SendFrame(LPC_SSP, flipByte(DISPLAY_CLEAR));
}

