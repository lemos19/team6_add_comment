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


/******************************************************************************
 *  EXTERN
 *****************************************************************************/


/******************************************************************************
 *  LOCAL TYPEDEFS
 *****************************************************************************/


/******************************************************************************
 *  LOCAL CONSTANTS
 *****************************************************************************/


/******************************************************************************
 *  LOCAL VARIABLES
 *****************************************************************************/


/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/


/******************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *****************************************************************************/

/******************************************************************************
 *  LOCAL FUNCTION
 ******************************************************************************/

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/

 /**
  *   @brief      Select clock source for LPIT
  *				  The valid configuration variable.
  *
  *   @param[in]  Source		source
  *
  *   @return     Void			None
  *
  *   @note       None.
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
 *   @param[in]  LPUART_Chanel		ch
 *   @param[in]  Source				source
 *
 *   @return	 Void				None
 *
 *   @note       None.
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
 *   @brief      Select clock source for LPSPI
 *               The valid configuration variable.
 *
 *   @param[in]  LPSPI_Chanel		chanel
 *   @param[in]  Source				source
 *
 *   @return     Void				None
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
