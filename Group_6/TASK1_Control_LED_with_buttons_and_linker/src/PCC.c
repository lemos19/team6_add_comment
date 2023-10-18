/******************************************************************************
 * Project Name: FRESHER ASSIGNMENT
 * File Name: PCC.c
 *
 * Description: Implementation of the PCC module
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

 /**
  *   @file       PCC_Type.h
  *   @version    V0.1
  *   @brief      V0.1 PCC Driver
  *   @addtogroup PCC_driver
  */

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "PCC_Type.h"
#include "General.h"

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
 *   @brief      This funciton shall be invoked to set up Baudrate of Controller
 *
 *   @param[in]  xxx1       xxxxxxxx    
 *   @param[in]  xxx2       xxxxxxxx
 *   @arg        XXX1       xxxxxxxx
 *   @arg        XXX2       xxxxxxxx  
 *
 *   @return     YYY/void   xxxxxxxx
 *   @retval     yyy1       xxxxxxxx
 *   @retval     yyy2       xxxxxxxx
 *
 *   @note       This function will be called by Can_Init and Can_SetBaudrate.
 *
*/

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
 /**
  *   @brief      This initializes the global variable - l_CanConfig_ptr with
  *                   the valid configuration pointer.
  *                   Also sets the CAN driver Status as INITIALIZED.
  *
  *   @param[in]  xxx1       xxxxxxxx
  *   @param[in]  xxx2       xxxxxxxx
  *   @arg        XXX21      xxxxxxxx
  *   @arg        XXX22      xxxxxxxx
  *
  *   @return     YYY/void   xxxxxxxx
  *   @retval     yyy1       xxxxxxxx
  *   @retval     yyy2       xxxxxxxx
  *
  *   @note       Driver should be in Un-Initialization.
  *
 */
void PCC_LPIT_ClockSource(Source source){
	PCC->PCC_LPIT.Fields.PCS = source;
	PCC->PCC_LPIT.Fields.CGC = Enable;
}

/**
 *   @brief      Select clock source for LPUART
 *               The valid configuration variable.
 *
 *   @param[in]  LPUART_Chanel      ch
 *   @param[in]  Source				source
 *
 *   @return	 Void				None
 *   @retval     yyy1				xxxxxxxx
 *   @retval     yyy2				xxxxxxxx
 *
 *   @note       None
 *
*/
void PCC_LPUART_ClockSource(LPUART_Chanel ch,Source source){
	switch (ch){
	case CHN0:
		PCC->PCC_LPUART0.Fields.PCS = source;
		PCC->PCC_LPUART0.Fields.CGC = Enable;
		break;
	case CHN1:
		PCC->PCC_LPUART1.Fields.PCS = source;
		PCC->PCC_LPUART1.Fields.CGC = Enable;
		break;
	case CHN2:
		PCC->PCC_LPUART2.Fields.PCS = source;
		PCC->PCC_LPUART2.Fields.CGC = Enable;
		break;
	}
}

/**
 *   @brief      Select clock source for LPUART
 *               The valid configuration variable.
 *
 *   @param[in]  LPSPI_Chanel		chanel
 *   @param[in]  Source				source
 *
 *   @return     Void				None
 *   @retval     yyy1       xxxxxxxx
 *   @retval     yyy2       xxxxxxxx
 *
 *   @note       None.
 *
*/
void PCC_LPSPI_ClockSource(LPSPI_Chanel chanel,Source source){
	switch (chanel){
	case LPSPI_Chanel0:
		PCC->PCC_LPSPI0.Fields.PCS = source;
		PCC->PCC_LPSPI0.Fields.CGC = Enable;
		break;
	case LPSPI_Chanel1:
		PCC->PCC_LPSPI1.Fields.PCS = source;
		PCC->PCC_LPSPI1.Fields.CGC = Enable;
		break;
	case LPSPI_Chanel2:
		PCC->PCC_LPSPI2.Fields.PCS = source;
		PCC->PCC_LPSPI2.Fields.CGC = Enable;
		break;
	}
}
