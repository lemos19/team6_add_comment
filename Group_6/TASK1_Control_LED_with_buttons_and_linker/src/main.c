/******************************************************************************
 * Project Name: Control LED with buttons
 * File Name: main.c
 *
 * Description: Implementation of the <module>
 *              Target systems:           S32K144
 *              Derivatives:              ARM M4f
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "MacroAndFuntion.h"
#include "LPIT_Type.h"
#include "LPUART.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief  Clear flag LPIT.
 */
#define CLEAR_FLAG_LPIT_CHANEL(chanel) LPIT->MSR.Fields.TIF##chanel = 1;
/**
 * @brief  Enable LPIT Channel.
 */
#define ENABLE_LPIT_CHANEL(chanel) LPIT->TCTRL##chanel.Fields.T_EN = Enable;
/**
 * @brief  Disable LPIT Channel.
 */
#define DISABLE_LPIT_CHANEL(chanel) LPIT->TCTRL##chanel.Fields.T_EN = Disable;
/**
 * @brief  Toggle status LPIT.
 */
#define TOGGLE_STATUS_LPIT_CHANEL0 LPIT->TCTRL0.Fields.T_EN ^= 1;
/**
 * @brief  Check status LPIT.
 */
#define STATUS_LPIT_CHANEL0 LPIT->TCTRL0.Fields.T_EN
/**
 * @brief  Check Flag from PTC.
 */
#define FLAG_FROM_PTC(pin) PORTC->PORT_PCR[pin].Fields.ISF == 1
/**
 * @brief  Clear Flag form PTC.
 */
#define CLEAR_FLAG_PTC(pin) PORTC->PORT_PCR[pin].Fields.ISF = 1;

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
/*!
 * Pins definitions
 * ===================================================
 *
 * Pin number        | Function
 * ----------------- |------------------
 * PTD15             | GPIO [RED LED]
 * PTD16             | GPIO [GREEN LED]
 * PTD0              | GPIO [BLUE LED]
 */
typedef enum
{
	Red_led = 15,
	Green_led = 16,
	Blue_led = 0
} LED;
/******************************************************************************
 *  LOCAL VARIABLES
 *****************************************************************************/
static char buffer[10]; /*Buffer store string to need send UART*/
static int8_t buffer_index = 0;
static LED switch_led = Red_led;				  /* led status */
static uint8_t counter = 10;					  /* counter variable value */
static char messageHello[] = "\nhello world!!\n"; /* Message when UART connection is successful */
static char messageUpdateCounter[30];			  /* Buffer store string to need send UART */
static uint32_t timeValue = 125000;				  /* Channel 0 timeout period */
static uint8_t sendCommand = 0;
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
/**
 *   @brief      This funciton shall be used to control LED flashing
 *
 *   @arg        Red_led       15
 *   @arg        Green_led     16
 * 	 @arg        Blue_led      0
 *
 */
void Blink_Led_Function(void)
{
	switch (switch_led)
	{
	case Red_led:
		GPIOD->GPIO_PSOR = 0x18001; /* Turn off all LED */
		GPIOD->GPIO_PCOR = (1u << Red_led);		/* Turn on Led Red */
		break;
	case Green_led:
		GPIOD->GPIO_PSOR = 0x18001;
		GPIOD->GPIO_PCOR = (1u << Green_led);	/* Turn on Led Green */
		break;
	case Blue_led:
		GPIOD->GPIO_PSOR = 0x18001;
		GPIOD->GPIO_PCOR = (1u << Blue_led);	/* Turn on Led Blue */
		break;
	}
}

/**
 *   @brief      This function is used to control LED flashing
 *
 *   @note       This function only occurs when there is an interrupt from LPIT Channel 0
 *
 */
void LPIT0_Ch0_IRQHandler(void)
{
	CLEAR_FLAG_LPIT_CHANEL(0)
	if (switch_led == Red_led)
	{
		switch_led = Green_led;
	}
	else if (switch_led == Green_led)
	{
		switch_led = Blue_led;
	}
	else
	{
		switch_led = Red_led;
	}
}

/**
 *   @brief      This function is used to send UART
 *
 *
 *   @note       This function only occurs when there is an interrupt from LPIT Channel 1
 *
 */
void LPIT0_Ch1_IRQHandler(void)
{
	CLEAR_FLAG_LPIT_CHANEL(1)		/* Clear flag interrupt Lpit */
	sendCommand = Enable;
}

/**
 *   @brief      This function is used to control the frequency of LPIT
 *
 *
 *   @note       This function only occurs when there is an interrupt from PORTC
 *
 */
void PORTC_IRQHandler(void)
{
	if (FLAG_FROM_PTC(12)) /* Check Flag form PTC12 */
	{
		CLEAR_FLAG_PTC(12) /* Clear flag from interrupt PTC12 */
		counter++;
		timeValue += 12500;
		LPIT->TVAL0 = timeValue;
	}
	else if (FLAG_FROM_PTC(13)) /* Check Flag form PTC13 */
	{
		CLEAR_FLAG_PTC(13)					/* Clear flag from interrupt PTC13 */
		if (STATUS_LPIT_CHANEL0 == Disable) /* Check status LPIT channel 0 */
		{
			if (counter != 1) /* Check variable counter */
			{
				counter--;
				timeValue -= 12500;
				LPIT->TVAL0 = timeValue;
			}
		}
		TOGGLE_STATUS_LPIT_CHANEL0 /* Toggle status LPIT */
	}
}

int main(void)
{
	initializeGPIOandSystick();							  /* Configure ports */
	Config_SOSC_CLK();									  /* Initialize system oscilator for 8 MHz xtal */
	Config_SPLL_CLK(SOSC, Div1, Multi20);				  /* STATUS_LPIT_CHANEL0 SPLL to 80 MHz with 8 MHz SOSC */
	Config_RCCR(SPLL, 0u, 1u, 2u);						  /* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */
	SCG_Asyn_Peripheral_Sources(SOSCDIV2_CLK, Div_By_64); /* Initialize SOSCDIV2 125000Hz */
	SCG_Asyn_Peripheral_Sources(FIRCDIV2_CLK, Div_By_1);  /* Initialize FIRCDIV2 48MHz */

	Config_LPIT_Chanel(
		LPIT_Chanel0,	/* select LPIT channel 0 */
		SOSCDIV2_CLK, 	/* chose clock source SOSC */
		Enable,		    /* enable interrupt */
		timeValue	    /* reset value */
	);

	Config_LPIT_Chanel(
		LPIT_Chanel1,	/* select LPIT channel 1 */
		SOSCDIV2_CLK, 	/* chose clock source SOSC */
		Enable,		    /* enable interrupt */
		92800	    	/* reset value */
	);

	Config_LPUART_Chanel(
		CHN1,
		FIRCDIV2_CLK,	/* chose clock source FIRC */
		500, 			/* baurate = baud clock /(oversameling*500)----baurate: 9600|baud clock: 48Mh|oversameling: 10 */
		ratio10,		/* oversameling */
		One_Stop_Bit,	/* 1 bit stop */
		_8BitData,		/* bit data */
		Disable 		/*disable parity bit */
	);
	Enable_LPUART_Pin(Chn1_Tx_PTC7);		/* Config pin PTC6 as pin Tx */
	Enable_LPUART_Pin(Chn1_Rx_PTC6);		/* Config pin PTC6 as pin RX */

	Send_Message(&messageHello[0]);			/* Transmit "hello world" string when successfully connecting UART*/
	ENABLE_LPIT_CHANEL(0)					/* Enable LPIT channel 0 */
	ENABLE_LPIT_CHANEL(1)					/* Enable LPIT channel 1 */
	while (1)
	{
		Blink_Led_Function();	
		if (sendCommand)		/* check */
		{
			sendCommand = Disable;
			sprintf(messageUpdateCounter, "Counter value: %d\n", counter); 	/* The sprintf() function is used to create strings from primitive data types */
			Send_Message(&messageUpdateCounter[0]);							/* Transmit string via UART */
		}
	}
}
/*---------------------- End of File ----------------------------------------*/