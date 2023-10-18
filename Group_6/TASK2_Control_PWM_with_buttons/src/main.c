/******************************************************************************
|------------------------------------------------------------------------------
|   FILE DESCRIPTION                                                           
|------------------------------------------------------------------------------
|    File Name:   <main>.<c>
|    Course:      EMB - Class 3                                                  
|    Date:        01-10-2023
|    Description: Source file for task 2, team 6
|------------------------------------------------------------------------------
|
|------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y                                  
|------------------------------------------------------------------------------
| Name: Phan Hoang Chanh 
|------------------------------------------------------------------------------
|               EXECUTION NOTE
|------------------------------------------------------------------------------
| Note: use for s32k144 serial
| ---------------------------------------------------------------------------*/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "MacroAndFuntion.h"
#include "LPIT_Type.h"
#include "LPUART.h"
#include <string.h>
#include "LPSPI_Type.h"
#include "ledMax7219.h"
#include "SIM_Type.h"
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
static char buffer[10];
static int8_t buffer_index = 0;
int Duti_cricle = 125;
uint8_t SendMessage_Command = Disable;
static char message[30];
static char arr[] = "hello world!!\n";
/******************************************************************************
 *  FUNCTION PROTOTYPES
 *****************************************************************************/
void PORTC_IRQHandler(void);
void LPUART1_RxTx_IRQHandler(void);
/******************************************************************************
 *  FUNCTION DECLARATION
 *****************************************************************************/

/*
*******************************************************************************
Function name   :   main
Description     :   Init peripherals 
*******************************************************************************
*/
int main(void)
{
	initializeGPIOandSystick();
	Config_SOSC_CLK();					  // 8Mhz
	Config_SPLL_CLK(SOSC, Div1, Multi20); // 80Mhz
	Config_RCCR(SPLL, 0 /*div core by 1*/, 1 /*div bus by 2*/, 2 /*div slow by 3*/);
	SCG_Asyn_Peripheral_Sources(FIRCDIV2_CLK, Div_By_1); // 48Mhz
	SCG_Asyn_Peripheral_Sources(SOSCDIV2_CLK, Div_By_1);

	FlexCAN0init();
	PCC->PCC_PORTE = SET_BIT(PCC->PCC_PORTE,PCC_CGC_BIT);
	PORTE->PORT_PCR[4].Fields.MUX=5;
	PORTE->PORT_PCR[5].Fields.MUX=5;

	SCG->SCG_SOSCDIV.Fields.Div1 = Div_By_1;
	FTM_init
	(
		FTM_0,
		SOSCDIV1_CLK,
		Div_16,
		249 		/* modulo value --- clockout = clockin/(pre scale*modulo) */
	);
	FTM0->CnSC_And_CnV[1].CnV = Duti_cricle; /*duti cricle*/
	PORTD->PORT_PCR[16].Fields.MUX = 2; /*FTM0 chanel 1*/
	Start_counter_FTM0(); 
	
	Config_LPUART_Chanel
	(
		CHN1,
		FIRCDIV2_CLK,
		500, 			/*baurate = baud clock /(oversameling*500)----baurate: 9600|baud clock: 48Mh|oversameling: 10*/
		ratio10,
		One_Stop_Bit,
		_8BitData,
		Disable 		/*disable parity bit*/
	);
	Enable_LPUART_Interrupts(CHN1, Receiver_Interrupt);
	NVIC_Config_Interrup_Modul(Lpuart1, Enable);
	Enable_LPUART_Pin(Chn1_Tx_PTC7);
	Enable_LPUART_Pin(Chn1_Rx_PTC6);
	Enable_ReceiveData_Chanel(CHN1);

	Send_Message(&arr[0]);

	while (1)
	{
		if (SendMessage_Command)  //send command enable every 500ms from interrupt PORTC
		{
			SendMessage_Command = Disable; 
			sprintf(message, "Counter value: %d\n", Duti_cricle/25); 
			Send_Message(&message[0]);
		}
	}
}

void PORTC_IRQHandler(void)
{
	SendMessage_Command = Enable;
	if (FLAG_FROM_PTC(12))
	{
		CLEAR_FLAG_PTC(12)
		if (Duti_cricle < 250)
		{
			Duti_cricle += 25;
			FTM0->CnSC_And_CnV[1].CnV = Duti_cricle;
		}
	}
	else if (FLAG_FROM_PTC(13))
	{
		CLEAR_FLAG_PTC(13)
		if (Duti_cricle > 0)
		{
			Duti_cricle -= 25;
			FTM0->CnSC_And_CnV[1].CnV = Duti_cricle;
		}
	}
	else if (FLAG_FROM_PTC(15))
	{
		CLEAR_FLAG_PTC(15)
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

//this is for test interrupt recive UART 
void LPUART1_RxTx_IRQHandler(void)
{
	buffer[buffer_index] = (uint8_t)ReceiveData(CHN1);
	if (buffer[buffer_index] == '.')
	{
		buffer[buffer_index] = '\0';
		if (!(strcmp("SW2", buffer)))
		{
			/*nothing*/   
		}
		else if (!(strcmp("SW3", buffer)))
		{
			/*nothing*/
		}
		buffer_index = -1;
	}
	buffer_index++;
}
/******************************************************************************
*                           End of File                                       *
******************************************************************************/
