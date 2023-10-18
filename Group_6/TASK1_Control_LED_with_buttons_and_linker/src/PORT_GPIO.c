/******************************************************************************
 * Project Name: FRESHER ASSIGNMENT
 * File Name: PORT_GPIO.c
 *
 * Description: Implementation of the PORT_GPIO module
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

 /**
  *   @file       GPIO_Type.h
  *   @version    V0.1
  *   @brief      V0.1 PORT_GPIO Driver
  *   @addtogroup PORT_GPIO_driver
  */

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "GPIO_Type.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief  xxxxxxxx1
 */

/******************************************************************************
 *  EXTERN
 *****************************************************************************/


/******************************************************************************
 *  LOCAL TYPEDEFS
 *****************************************************************************/
/**
* @brief  Template TestType1 brief.
*/

/******************************************************************************
 *  LOCAL CONSTANTS
 *****************************************************************************/


/******************************************************************************
 *  LOCAL VARIABLES
 *****************************************************************************/
/**
 * @brief  test brief1
 */
static PORT_T *Port[5] = {PORTA,PORTB,PORTC,PORTD,PORTE};
static GPIO_Type *Gpio[5] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOD};

/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/
/**
 * @brief  test brief2
 */

/******************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *****************************************************************************/

/******************************************************************************
 *  LOCAL FUNCTION
 ******************************************************************************/
/**
 *   @brief      This funciton config GPIO_Pin
 *
 *   @param[in]  Port_t             port
 *   @param[in]  Pin_t              pin
 *   @param[in]  Enable_Disable     pull
 *   @param[in]  Pull_select        pulls
 *   @param[in]  Enable_Disable     passive_filter
 *   @param[in]  Muxing_mode        mux
 *   @param[in]  Interrupt_config   interrupt
 *   @param[in]  Direction          input_output
 *
 *   @return     Void               None
 *
 *   @note       None.
 *
*/
void Config_GPIO_Pin(Port_t port,
Pin_t pin,
Enable_Disable pull,
Pull_select pulls,
Enable_Disable passive_filter,
Muxing_mode mux,
Interrupt_config interrupt,
Direction input_output)
{
    Port[port]->PORT_PCR[pin].Fields.PE=pull;
    Port[port]->PORT_PCR[pin].Fields.PFE=passive_filter;
    Port[port]->PORT_PCR[pin].Fields.PS=pulls;
    Port[port]->PORT_PCR[pin].Fields.IRQC=interrupt;
    Port[port]->PORT_PCR[pin].Fields.MUX=mux;
    Gpio[port]->GPIO_PDDR |= (uint32_t)input_output<<pin;
}

