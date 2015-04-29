/*
===============================================================================
 Name        : Test.c
 Author      : $(superaga)
 Version     : 0.1
 Copyright   : $(gpl)
 Description : SCD5510X display test program
===============================================================================
*/

#include "Test.h"


#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

/*****************************************************************************
 * MACRO *
 ****************************************************************************/

//#define flipByte(x) __REV(__RBIT(x))			/* reverse bit in byte */
#define flipByte(x) __RBIT(x)			/* reverse bit in byte */

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

#define SSP_MODE_TEST       1	/* 1: Master, 0: Slave */

#define POLLING_MODE        0	/* 1: Interrupt mode, 0: Polling mode */
#if POLLING_MODE
#define INTERRUPT_MODE      0
#else
#define INTERRUPT_MODE      1
#endif

//#define BUFFER_SIZE							(0x08) // 8 bit frame buffer
#define SSP_DATA_BITS                       (SSP_BITS_8)	/*!< 8 bits/frame */

#define LPC_SSP           LPC_SSP0
#define SSP_IRQ           SSP0_IRQn
#define SSPIRQHANDLER     SSP0_IRQHandler

static 	SSP_ConfigFormat	ssp_format;


int main(void) {

#if defined (__USE_LPCOPEN)
#if !defined(NO_BOARD_LIB)

    SystemCoreClockUpdate();			/* Read clock settings and update SystemCoreClock variable
    									 * Set up and initialize all required blocks and
    									 * functions related to the board hardware */
    Board_Init();
#endif
#endif


	/* SSP initialization */
	Board_SSP_Init(LPC_SSP);			/* enable */
	Chip_SSP_Init(LPC_SSP);
	Chip_Clock_SetSSP0ClockDiv(18);

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

	Chip_SSP_SendFrame(LPC_SSP, flipByte(0xB0));

	//Chip_SSP_SendFrame(LPC_SSP, 0b00001101);	// load address 0
	//_delay_ms(1);
	Chip_SSP_SendFrame(LPC_SSP, 0b01110000);  // load D letter
	//_delay_ms(1);
	Chip_SSP_SendFrame(LPC_SSP, 0b11001100);
	//_delay_ms(1);
	Chip_SSP_SendFrame(LPC_SSP, 0b10101010);
	//_delay_ms(1);
	Chip_SSP_SendFrame(LPC_SSP, 0b10011110);
	//_delay_ms(1);
	Chip_SSP_SendFrame(LPC_SSP, 0b01110001);





    return 0 ;
}
