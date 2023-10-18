/******************************************************************************
 * Project Name: FRESHER ASSIGNMENT
 * File Name: LPIT.c
 *
 * Description: Implementation of the LPIT module
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

 /**
  *   @file       LPIT_Type.h
  *   @version    V0.1
  *   @brief      V0.1 LPIT Driver
  *   @addtogroup LPIT_driver
  */

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "LPIT_Type.h"
#include "SCG_Type.h"
#include "NVIC_Type.h"

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

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
 /**
  *   @brief      This initializes the global variable - l_CanConfig_ptr with
  *                   the valid configuration pointer.
  *                   Also sets the CAN driver Status as INITIALIZED.
  *
  *   @param[in]  LPIT_Chanel           chanel
  *   @param[in]  Source                clock_sorce
  *   @param[in]  Enable_Disable        interrupt
  *   @param[in]  uint32_t              timeValue      
  *
  *   @return     Void                  None  
  *
  *   @note       None.
  *
 */
void Config_LPIT_Chanel
(
    LPIT_Chanel chanel,
    Source clock_sorce,
    Enable_Disable interrupt,
    uint32_t timeValue
)
{
    PCC_LPIT_ClockSource(clock_sorce);
    LPIT->MCR.Fields.M_CEN = Enable;
	LPIT->MCR.Fields.DBG_EN = Enable;
    if (chanel == LPIT_Chanel0){
        LPIT->TVAL0 = timeValue;
        LPIT->MIER.Fields.TIE0 = interrupt;
        NVIC_Config_Interrup_Modul(LPIT0,interrupt);
    }
    else if (chanel == LPIT_Chanel1){
        LPIT->TVAL1 = timeValue;
        LPIT->MIER.Fields.TIE1 = interrupt;
        NVIC_Config_Interrup_Modul(LPIT1,interrupt);
    }
    else if (chanel == LPIT_Chanel2){
        LPIT->TVAL2 = timeValue;
        LPIT->MIER.Fields.TIE2 = interrupt;
        NVIC_Config_Interrup_Modul(LPIT2,interrupt);
    }
    else {
        LPIT->TVAL3 = timeValue;
        LPIT->MIER.Fields.TIE3 = interrupt;
        NVIC_Config_Interrup_Modul(LPIT3,interrupt);
    }
}

/**
 *   @brief      This initializes the global variable - l_CanConfig_ptr with
 *                   the valid configuration pointer.
 *                   Also sets the CAN driver Status as INITIALIZED.
 *
 *   @param[in]  LPIT_Chanel            chanel
 *   @param[in]  Enable_Disable         e_d
 *
 *   @return     Void                   None
 *
 *   @note       None.
 *
*/
void LPIT_Set_Clear_Chanel(LPIT_Chanel chanel,Enable_Disable e_d){
    if (chanel== LPIT_Chanel0){
        LPIT->TCTRL0.Fields.T_EN = e_d;
    }
    if (chanel== LPIT_Chanel1){
        LPIT->TCTRL1.Fields.T_EN = e_d;
    }
    if (chanel== LPIT_Chanel2){
        LPIT->TCTRL2.Fields.T_EN = e_d;
    }
    if (chanel== LPIT_Chanel3){
       LPIT->TCTRL3.Fields.T_EN = e_d;
    }
}
