/******************************************************************************
 * Project Name: FRESHER  ASSIGNMENT
 * File Name: SIM_Type.h
 *
 * Description: Implementation of the <module>
 *              Target systems:           S32K<xxx>
 *              Derivatives:              ARM<xxx>
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/**
 *   @file       template.h
 *   @version    V0.1
 *   @brief      <version> <module> Driver
 *   @addtogroup <module>_driver
 */

#ifndef SIM_H
#define SIM_H
/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include <stdint.h>
#include "General.h"



/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief   Peripheral SIM base address.
 */
#define SIM_BASE_ADD 0x40048000
/**
 * @brief   Peripheral SIM base pointer
 */
#define SIM ((Sim_t*)(SIM_BASE_ADD))


/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
/**
* @brief  Fields of Chip Control register.
*/
typedef union 
{
    uint32_t Register;
    struct 
    {
        uint32_t ADC_INTERLEAVE_EN : 4;
        uint32_t CLKOUTSEL :4 ;
        uint32_t CLKOUTDIV : 3;
        uint32_t CLKOUTEN : 1;
        uint32_t TRACECLK_SEL : 1;
        uint32_t PDB_BB_SEL : 1;
        uint32_t Reserved0 : 2;
        uint32_t ADC_SUPPLY : 3;
        uint32_t ADC_SUPPLYEN : 1;
        uint32_t SRAMU_RETEN : 1 ;
        uint32_t SRAML_RETEN : 1;
        uint32_t Reserved1 : 10;
    }Fields;
}CHIPCTL_t;

/**
* @brief  Configure prescale clockout .
*/
typedef enum{
    clkout_div1,
    clkout_div2,
    clkout_div3,
    clkout_div4,
    clkout_div5,
    clkout_div6,
    clkout_div7,
    clkout_div8
}Clkoutdiv_t;

/**
* @brief  Choose clock source pin CLKOUT
*/
typedef enum{
    clkout_Scgclkout,
    clkout_Soscdiv2=2,
    clkout_Sircdiv2=4,
    clkout_Fircdiv2=6,
    clkout_Hclk,
    clkout_Splldiv2,
    clkout_Busclk,
    clkout_Lpo128k,
    clkout_Lpo=12,
    clkout_Rtc=14
}Clkoutsource;

/**
* @brief  SIM - Register Layout Typedef.
*/
typedef struct 
{
	uint32_t Reserved;
    volatile CHIPCTL_t CHIPCTL;
    uint32_t Reserved0;
    volatile uint32_t FTMOPT0;
    volatile uint32_t LPOCLKS;
    uint32_t Reserved1;
    volatile uint32_t ADCOPT;
    volatile uint32_t FTMOPT1;
    volatile uint32_t MISCTRL0;
    volatile uint32_t SDID;
    uint32_t Reserved2[6];
    volatile uint32_t PLATCGC;
    uint32_t Reserved3[2];
    volatile uint32_t FCFG1;
    uint32_t Reserved4;
    volatile uint32_t UIDH;
    volatile uint32_t UIDMH;
    volatile uint32_t UIDML;
    volatile uint32_t UIDL;
    uint32_t Reserved5;
    volatile uint32_t CLKDIV4;
    volatile uint32_t MISCTRL1;
}Sim_t;
/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
void Clkout_config(Clkoutsource,Clkoutdiv_t);
#endif
