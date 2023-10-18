/******************************************************************************
 * Project Name: FRESHER  FRESHER ASSIGNMENT
 * File Name: GPIO_Type.h
 *
 * Description: Implementation of the GPIO
 *              Target systems:           S32K144
 *              Derivatives:              ARM cortex M4	
 *              Compiler:                 S32DS
 *
 *****************************************************************************/
/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#ifndef GPIO_TYPE_H
#define GPIO_TYPE_H
#include <stdint.h>
#include "PORT_Type.h"
#include "General.h"
/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define GPIO_BASE_ADDRESS 0x400FF000
#define GPIOA ((GPIO_Type*)(GPIO_BASE_ADDRESS))
#define GPIOB ((GPIO_Type*)(GPIO_BASE_ADDRESS+0x40))
#define GPIOC ((GPIO_Type*)(GPIO_BASE_ADDRESS+0x80))
#define GPIOD ((GPIO_Type*)(GPIO_BASE_ADDRESS+0xC0))
#define GPIOE ((GPIO_Type*)(GPIO_BASE_ADDRESS+0x100))
/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
typedef enum{
	Pin0,Pin1,Pin2,Pin3,Pin4,Pin5,Pin6,Pin7,
	Pin8,Pin9,Pin10,Pin11,Pin12,Pin13,Pin14,Pin15,
	Pin16,Pin17,Pin18,Pin19,Pin20,Pin21,Pin22,Pin23,
	Pin24,Pin25,Pin26,Pin27,Pin28,Pin29,Pin30,Pin31
}Pin_t; // GPIO pin
typedef enum{
	pullDown,
	pullUp
}Pull_select; // use for setting pullup/pulldown for input
typedef enum{
	GPIO_Mode = 1,
	Alternative2,
	Alternative3,
	Alternative4,
	Alternative5,
	Alternative6,
	Alternative7,
}Muxing_mode; // use for config muxing mode
typedef enum{
	DMA_rising =1,
	DMA_falling,
	DMA_either,
	logic0 = 8,
	rising,
	falling,
	either,
	logic1
}Interrupt_config; // use for config GPIO interrupt 
typedef enum{
	input,
	output
}Direction; // use for select direction in GPIO mode
typedef	struct GPIO_Type{
	volatile uint32_t GPIO_PDOR; // Port Data Output Register
	volatile uint32_t GPIO_PSOR; // Port Set Output Register
	volatile uint32_t GPIO_PCOR; // Port Clear Output Register 
	volatile uint32_t GPIO_PTOR; // Port Toggle Output Register
	volatile uint32_t GPIO_PDIR; // Port Data Input Register
	volatile uint32_t GPIO_PDDR; // Port Data Direction Register 
	volatile uint32_t GPIO_PIDR; // Port Input Disable Register
}GPIO_Type;
/******************************************************************************
 *  FUNCTION PROTOTYPES
 *****************************************************************************/
void Config_GPIO_Pin(Port_t port,
Pin_t pin,
Enable_Disable pull,
Pull_select pulls,
Enable_Disable passive_filter,
Muxing_mode mux,
Interrupt_config interrupt,
Direction input_output);
#endif
/*---------------------- End of File ----------------------------------------*/