/******************************************************************************
 * Project Name: FRESHER ASSIGNMENT
 * File Name: FTM.c
 *
 * Description: Implementation of the FTM module
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

 /**
  *   @file       FTM_Type.h
  *   @version    V0.1
  *   @brief      V0.1 FTM Driver
  *   @addtogroup FTM_driver
  */

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "FTM_type.h"
#include "PCC_Type.h"

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

 /**
  * @brief  this is pointer to call FTM channel
  */
static FTM_type* FTM[8]={FTM0,FTM1,FTM2,FTM3,FTM4,FTM5,FTM6,FTM7};

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
  *   @brief      This is config for FTM module
  *               The valid configuration variable.
  *
  *   @param[in]  Ftm_modul_t           modul
  *   @param[in]  Source_div1_t         source
  *   @param[in]  preScale_fmt_t        div
  *   @param[in]  uint32_t              modulo      
  *
  *   @return     Void                  None  
  *
  *   @note       None.
  *
 */
void FTM_init(Ftm_modul_t modul,Source_div1_t source,preScale_fmt_t div,uint32_t modulo){
    switch (modul)
    {
    case FTM_0:
    	PCC->PCC_FTM0.Fields.PCS = source;
        PCC->PCC_FTM0.Fields.CGC = Enable;
        break;
    case FTM_1:
        PCC->PCC_FTM1.Fields.PCS = source;
        PCC->PCC_FTM1.Fields.CGC = Enable;
        break;
    case FTM_2:
        PCC->PCC_FTM2.Fields.PCS = source;
        PCC->PCC_FTM2.Fields.CGC = Enable;
        break;
    case FTM_3:
        PCC->PCC_FTM3.Fields.PCS = source;
        PCC->PCC_FTM3.Fields.CGC = Enable;
        break;
    case FTM_4:
        PCC->PCC_FTM4.Fields.PCS = source;
        PCC->PCC_FTM4.Fields.CGC = Enable;
        break;
    case FTM_5:
        PCC->PCC_FTM5.Fields.PCS = source;
        PCC->PCC_FTM5.Fields.CGC = Enable;
        break;
    case FTM_6:
        PCC->PCC_FTM6.Fields.PCS = source;
        PCC->PCC_FTM6.Fields.CGC = Enable;
        break;
    case FTM_7:
        PCC->PCC_FTM7.Fields.PCS = source;
        PCC->PCC_FTM7.Fields.CGC = Enable;
        break;
    }
    FTM[modul]->MODE.Fields.WPDIS = Enable;
    FTM[modul]->SC.Fields.PS = div;
    FTM[modul]->SC.Fields.PWMEN0 = Enable;
    FTM[modul]->SC.Fields.PWMEN1 = Enable;
    FTM[modul]->MOD = modulo;
    //turn on chanel 1 PWM
    FTM[modul]->CnSC_And_CnV[1].CnSC = SET_BIT(FTM[modul]->CnSC_And_CnV[1].CnSC,3)|SET_BIT(FTM[modul]->CnSC_And_CnV[1].CnSC,5);
    FTM[modul]->CnSC_And_CnV[1].CnV = 31250;/* FTM0 ch1 compare value = 75% modulo*/
}

/**
 *   @brief      This function is start counter FTM0
 *               The valid configuration variable.
 *
 *   @return     Void                  None
 *
 *   @note       Call this function after init FTM.
 *
*/
void Start_counter_FTM0(void){
    FTM0->SC.Fields.CLKS = 3;
}

/**
 *   @brief      This function is stop counter FTM0
 *               The valid configuration variable.
 *
 *   @return     Void                  None
 *
 *   @note       None.
 *
*/
void Disable_counter_FTM0(void){
    FTM0->SC.Fields.CLKS = 0;
}
