/*
 * @brief SCD5510xA display driver
 *
 * @note Created on: 07/06/2015
 *
 *
===============================================================================
 Name        : disp_SCD5510xA.h
 Author      : $(superaga)
 Version     : 0.1
 Copyright   : $(gpl)
 Description : SCD5510xA display driver
===============================================================================
*/

//#include "ssp_13xx.h"

#ifndef DISP_SCD5510XA_H_
#define DISP_SCD5510XA_H_

/*****************************************************************************
 * Constant and macro definitions
 ****************************************************************************/
#define flipByte(x) 		__RBIT(x)			/* reverse bit order in byte */

/* SSP PERIPHERAL */
#define SSP_MODE			1					/* 1: Master, 0: Slave */
#define SSP_DATA_BITS       SSP_BITS_8			/* 8 bits/frame */
#define LPC_SSP           	LPC_SSP0			/* define peripheral ssp number 0 */
#define SSP_IRQ           	SSP0_IRQn			/* define ssp 0 interrupt */
#define SSPIRQHANDLER     	SSP0_IRQHandler		/* define ssp 0 peripheral handler

#define POLLING_MODE        0					/* 1: Interrupt mode, 0: Polling mode */
#if POLLING_MODE
#define INTERRUPT_MODE      0
#else
#define INTERRUPT_MODE      1
#endif

/* DISPLAY COMMANDS */
#define DISPLAY_BRIGHTNESS_OPCODE	0xF0
#define DISPLAY_LAMP_TEST			0xF8
#define DISPLAY_POWER_DOWN			0xFF
#define DISPLAY_CLEAR				0xC0

/** Define display brightness available values */
typedef enum DISPLAY_BRIGHTNESS_VALUES {
	LEVEL_100 = 0,	/* LEVEL 100% */
	LEVEL_53,		/* LEVEL 53 % */
	LEVEL_40,		/* LEVEL 40 % */
	LEVEL_27,		/* LEVEL 27 % */
	LEVEL_20,		/* LEVEL 20 % */
	LEVEL_13,		/* LEVEL 13 % */
	LEVEL_6,		/* LEVEL 6.6% */
} DISPLAY_BRIGHTNESS_VALUES_T;

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
//static 	SSP_ConfigFormat	ssp_format;			/* define a SSP configuration struct */


/*****************************************************************************
 * Public functions prototype
 ****************************************************************************/

/**
 * @brief	Initialize SSP peripheral for communicate with display
 * @return	Nothing
 * @note	Initialize SSP as: 	mode: MASTER,
 * 								frame format: SPI,
 * 								frame length: 8 BIT,
 * 								clock phase: 0,
 * 								clock polarity: 0
 */
void displayInit(void);

/**
 * @brief	Set brightness of display
 * @param	display value level should be:
 * 					- LEVEL_100				:LEVEL 100%
 * 					- LEVEL_53				:LEVEL 53 %
 * 					- LEVEL_40				:LEVEL 40 %
 * 					- LEVEL_27				:LEVEL 27 %
 * 					- LEVEL_20				:LEVEL 20 %
 * 					- LEVEL_13				:LEVEL 13 %
 * 					- LEVEL_6				:LEVEL 6.6%
 * @return	Nothing
 * @note	Default setting for brightness is 100%
 */
void displaySetBrightness(DISPLAY_BRIGHTNESS_VALUES_T level);

/**
 * @brief	Turn on all leds of display
 * @return	Nothing
 * @note	This will set all of the leds to a 53% brightness, and is cleared by loading
 * 			new brightness level (displaySetBrightness)
 */
void displayTest(void);

/**
 * @brief	Power down reduce current down to 50uA, display brightness is set to 0%
 * @return	Nothing
 * @note	Display will be reactivated by loading a new brightness level
 */
void displayPowerDown(void);

/**
 * @brief	Clear address register, RAM and display
 * @return	Nothing
 * @note	Character address register will be set to character 0
 */
void displayClear(void);

#endif /* DISP_SCD5510XA_H_ */
