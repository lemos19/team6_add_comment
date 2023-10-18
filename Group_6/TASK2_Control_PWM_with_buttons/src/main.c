/******************************************************************************
 * Project Name: Task2_Control_PWM_with_buttons
 * File Name: main.c
 *
 * Description: Implementation of the PWM and buttons
 *              Target systems:           S32K144
 *              Derivatives:              ARM M4F
 *              Compiler:                 S32DS
 *
 *****************************************************************************/


/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "MacroAndFuntion.h"
#include "LPUART.h"
#include <string.h>
#include "FTM_type.h"
#include <stdio.h>
/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define FLAG_FROM_PTC(pin) 				PORTC->PORT_PCR[pin].Fields.ISF == 1
#define CLEAR_FLAG_PTC(pin) 			PORTC->PORT_PCR[pin].Fields.ISF = 1;
#define PCC_CGC_BIT 30	
/******************************************************************************
 *  VARIABLES
 *****************************************************************************/
int Duti_cricle = 125; 
uint8_t SendMessage_Command = Disable; //status for UART
static char message[30]; 	/*buffer store string need to send through UART*/
static char arr[] = "hello world!!\n"; 
/******************************************************************************
 *  FUNCTION PROTOTYPES
 *****************************************************************************/
void PORTC_IRQHandler(void);

int main(void)
{
	/*!
	 * Initialization:
	 * =======================
	 */
	initializeGPIOandSystick();			/*Initialize GPIO*/
	Config_SOSC_CLK();					/* Initialize system oscillator for 8 MHz xtal */
	Config_SPLL_CLK(SOSC, Div1, Multi20); /* Initialize SPLL to 80 MHz with 8 MHz SOSC */
	Config_RCCR(SPLL, 0, 1 , 2); 		/*Initialize run mode with 80 Mhz core, 40Mhz bus ,20 Mhz Flash*/
	SCG_Asyn_Peripheral_Sources(FIRCDIV2_CLK, Div_By_1); /**/
	SCG->SCG_SOSCDIV.Fields.Div1 = Div_By_1; /*SOSCDIV1 divide by 1*/

	/**
	 * FTM0, Channel 1 in PWM Mode:
	 * ==================================================
	 */
	FTM_init
	(
		FTM_0,     /*Using flex timer 0 */
		SOSCDIV1_CLK, /*Using SOSCDIV1 for source clock*/
		Div_16,  /*Prescale = 16*/
		249 		/* modulo value --- clockout = clockin/(pre scale*modulo) */
	);
	FTM0->CnSC_And_CnV[1].CnV = Duti_cricle; /*FTM counter value = duty cycle*/
	PORTD->PORT_PCR[16].Fields.MUX = 2; /*Configure PTC16 is FTM0_CH1*/
	Start_counter_FTM0(); /*Start the FTM0_CH1*/

	/**
	 * Configure LPUART1
	 * ==================================================
	 */
	Config_LPUART_Chanel
	(
		CHN1,			/*Using UART1*/
		FIRCDIV2_CLK,	/*FIRCDIV 2 is used as source clock for UART1*/
		500, 			/*baurate = baud clock /(oversameling*500)----baurate: 9600|baud clock: 48Mh|oversameling: 10*/
		ratio10,		/*Over sampling ratio is 10*/
		One_Stop_Bit,	/*1 bit stop*/
		_8BitData,		/*Using 8 bit data*/
		Disable 		/*disable parity bit*/
	);

	/**
	 * Configure Pin for UART
	 * ==================================================
	 */
	Enable_LPUART_Pin(Chn1_Tx_PTC7); // PTC7 is used TX
	Enable_LPUART_Pin(Chn1_Rx_PTC6); // PTC6 is used RX

	Send_Message(&arr[0]); 

	/*infiniti loop*/
	while (1)
	{
		/**
		*@brief This will continue check the condition then send string through UART1 
		*/
		if (SendMessage_Command) 
		{
			SendMessage_Command = Disable; //clear status
			sprintf(message, "Counter value: %d\n", Duti_cricle/25);  // convert string to send
			Send_Message(&message[0]); // send string
		}
	}
}


void PORTC_IRQHandler(void)
{
	SendMessage_Command = Enable; //set status
	/**
	*@brief If interrupt PORTC occur it will check flag of each pin then clear that flag, also contrain 0% < duty cycle <100%
	*/
	if (FLAG_FROM_PTC(12))
	{
		CLEAR_FLAG_PTC(12)
		if (Duti_cricle < 250)
		{
			Duti_cricle += 25; //increase duty cycle 10%
			FTM0->CnSC_And_CnV[1].CnV = Duti_cricle;
		}
	}
	else if (FLAG_FROM_PTC(13))
	{
		CLEAR_FLAG_PTC(13)
		if (Duti_cricle > 0)
		{
			Duti_cricle -= 25;// decrease duty cycle 10%
			FTM0->CnSC_And_CnV[1].CnV = Duti_cricle;
		}
	}
	else if (FLAG_FROM_PTC(15))
	{
		CLEAR_FLAG_PTC(15)
		/**
		* @brief This will change frequency of FTM by change prescale value
		*/
		if (FTM0->SC.Fields.PS == Div_16)
		{
			FTM0->SC.Fields.PS = Div_8;
		}
		else
		{
			FTM0->SC.Fields.PS = Div_16;
		}
		Duti_cricle = 125;
		FTM0->CnSC_And_CnV[1].CnV = Duti_cricle;
	}
}

/******************************************************************************
*                           End of File                                       *
******************************************************************************/
