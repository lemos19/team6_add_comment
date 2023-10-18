/******************************************************************************
|------------------------------------------------------------------------------
|   FILE DESCRIPTION                                                           
|------------------------------------------------------------------------------
|    File Name:   <main>.<c>
|    Course:      EMB - Class 3                                                  
|    Date:        01-10-2023
|    Description: Source file for task 1, team 6
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
#include "string.h"
#include <math.h>
#include <stdio.h>
/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define CLEAR_FLAG_LPIT_CHANEL(chanel) LPIT->MSR.Fields.TIF##chanel = 1;
#define ENABLE_LPIT_CHANEL(chanel) LPIT->TCTRL##chanel.Fields.T_EN = Enable;
#define DISABLE_LPIT_CHANEL(chanel) LPIT->TCTRL##chanel.Fields.T_EN = Disable;
#define TOGGLE_STATUS_LPIT_CHANEL0 LPIT->TCTRL0.Fields.T_EN ^= 1;
#define STATUS_LPIT_CHANEL0 LPIT->TCTRL0.Fields.T_EN
#define FLAG_FROM_PTC(pin) PORTC->PORT_PCR[pin].Fields.ISF == 1
#define CLEAR_FLAG_PTC(pin) PORTC->PORT_PCR[pin].Fields.ISF = 1;
typedef enum
{
	Red_led = 15,
	Green_led = 16,
	Blu_led = 0
} LED;
/******************************************************************************
 *  VARIABLES
 *****************************************************************************/
static char buffer[10];
static int8_t buffer_index = 0;
static LED switch_led = Red_led;
uint8_t counter = 10;
static char messageHello[] = "\nhello world!!\n";
static char messageUpdateCounter[30];
static uint32_t timeValue = 125000;
uint8_t sendCommand = 0;
/******************************************************************************
 *  FUNCTION PROTOTYPES
 *****************************************************************************/
void PORTC_IRQHandler(void);
void LPUART1_RxTx_IRQHandler(void);
void LPIT0_Ch0_IRQHandler(void);
void LPIT0_Ch1_IRQHandler(void);
void LPIT0_Ch2_IRQHandler(void);
void Blink_Led_Function(void);
/******************************************************************************
 *  attribute to memmory section 
 *****************************************************************************/
void Blink_Led_Function() __attribute__((section(".flash_blinkled")));
uint8_t counter __attribute__((section(".new_data")));
uint8_t sendCommand __attribute__((section(".new_data")));
/******************************************************************************
 *  FUNCTION DECLARATION
 *****************************************************************************/
void Blink_Led_Function(void){
	switch (switch_led)
	{
	case Red_led:
		GPIOD->GPIO_PSOR = 0x18001; 
		GPIOD->GPIO_PCOR = (1u << Red_led);
		break;
	case Green_led:
		GPIOD->GPIO_PSOR = 0x18001; 
		GPIOD->GPIO_PCOR = (1u << Green_led);
		break;
	case Blu_led:
		GPIOD->GPIO_PSOR = 0x18001; 
		GPIOD->GPIO_PCOR = (1u << Blu_led);
		break;
	}
}

int main(void)
{
	initializeGPIOandSystick();
	Config_SOSC_CLK();					  // 8Mhz
	Config_SPLL_CLK(SOSC, Div1, Multi20); // 80Mhz
	Config_RCCR(SPLL, 0 /*div core by 1*/, 1 /*div bus by 2*/, 2 /*div slow by 3*/);
	SCG_Asyn_Peripheral_Sources(SOSCDIV2_CLK, Div_By_64); // 125000 Hz
	SCG_Asyn_Peripheral_Sources(FIRCDIV2_CLK, Div_By_1);  // 48Mhz

	Config_LPIT_Chanel(
		LPIT_Chanel0,
		SOSCDIV2_CLK, /*chose clock source*/
		Enable,		  /*enable interrupt*/
		timeValue	  /*reset value*/
	);
	Config_LPIT_Chanel(LPIT_Chanel1, SOSCDIV2_CLK, Enable, 92800);

	Config_LPUART_Chanel(
		CHN1,
		FIRCDIV2_CLK,
		500, /*baurate = baud clock /(oversameling*500)----baurate: 9600|baud clock: 48Mh|oversameling: 10*/
		ratio10,
		One_Stop_Bit,
		_8BitData,
		Disable /*disable parity bit*/
	);

	Enable_LPUART_Interrupts(CHN1, Receiver_Interrupt);
	NVIC_Config_Interrup_Modul(Lpuart1, Enable);
	Enable_LPUART_Pin(Chn1_Tx_PTC7);
	Enable_LPUART_Pin(Chn1_Rx_PTC6);
	Enable_ReceiveData_Chanel(CHN1);

	Send_Message(&messageHello[0]);
	ENABLE_LPIT_CHANEL(0)
	ENABLE_LPIT_CHANEL(1)
	while (1)
	{
		Blink_Led_Function();
		if (sendCommand)
		{
			sendCommand = Disable;
			sprintf(messageUpdateCounter, "Counter value: %d\n", counter);
			Send_Message(&messageUpdateCounter[0]);
		}
	}
}
void LPIT0_Ch0_IRQHandler(void)
{
	CLEAR_FLAG_LPIT_CHANEL(0)
	if (switch_led == Red_led)
	{
		switch_led = Green_led;
	}
	else if (switch_led == Green_led)
	{
		switch_led = Blu_led;
	}
	else
	{
		switch_led = Red_led;
	}
}
void LPIT0_Ch1_IRQHandler(void)
{
	CLEAR_FLAG_LPIT_CHANEL(1)
	sendCommand = Enable;
}
void PORTC_IRQHandler(void)
{
	if (FLAG_FROM_PTC(12))
	{
		CLEAR_FLAG_PTC(12)
		counter++;
		timeValue += 12500;
		LPIT->TVAL0 = timeValue;
	}
	else if (FLAG_FROM_PTC(13))
	{
		CLEAR_FLAG_PTC(13)
		if (STATUS_LPIT_CHANEL0 == Disable)
		{
			if (counter!=1)
			{
				counter--;
				timeValue -= 12500;
				LPIT->TVAL0 = timeValue;
			}
		}
		TOGGLE_STATUS_LPIT_CHANEL0
	}
}

void LPUART1_RxTx_IRQHandler(void)
{
	buffer[buffer_index] = (uint8_t)ReceiveData(CHN1);
	if (buffer[buffer_index] == '.')
	{
		buffer[buffer_index] = '\0';
		if (!(strcmp("SW2", buffer)))
		{
			GPIOD->GPIO_PSOR = 0x18001; 
			GPIOD->GPIO_PCOR = (1u << Red_led);
		}
		else if (!(strcmp("SW3", buffer)))
		{
			GPIOD->GPIO_PSOR = 0x18001; 
			GPIOD->GPIO_PCOR = (1u << Red_led);
		}
		buffer_index = -1;
	}
	buffer_index++;
}
/******************************************************************************
*                           End of File                                       *
******************************************************************************/