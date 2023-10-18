/******************************************************************************
 * Project Name: FRESHER ASSIGNMENT
 * File Name: FTM_type.h
 *
 * Description: Implementation of the Flexible timer modul
 *              Target systems:           S32K144
 *              Derivatives:              ARM cortex M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/
#ifndef FTM_H
#define FTM_H
/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include <stdint.h>
/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define FTM0_BASE_ADDRESS 0x40038000
#define FTM1_BASE_ADDRESS 0x40039000
#define FTM2_BASE_ADDRESS 0x4003A000
#define FTM3_BASE_ADDRESS 0x40026000
#define FTM4_BASE_ADDRESS 0x4006E000
#define FTM5_BASE_ADDRESS 0x4006F000
#define FTM6_BASE_ADDRESS 0x40070000
#define FTM7_BASE_ADDRESS 0x40071000
/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
typedef struct // this struct for memory layout of FTM 
{
    volatile uint32_t SC;
    volatile uint32_t CNT;
    volatile uint32_t MOD;
    volatile uint32_t C0SC;
    volatile uint32_t C0V;
    volatile uint32_t C1SC;
    volatile uint32_t C1V;
    volatile uint32_t C2SC;
    volatile uint32_t C2V;
    volatile uint32_t C3SC;
    volatile uint32_t C3V;
    volatile uint32_t C4SC;
    volatile uint32_t C4V;
    volatile uint32_t C5SC;
    volatile uint32_t C5V;
    volatile uint32_t C6SC;
    volatile uint32_t C6V;
    volatile uint32_t C7SC;
    volatile uint32_t C7V;
    volatile uint32_t CNTIN;
    volatile uint32_t STATUS;
    volatile uint32_t MODE;
    volatile uint32_t SYNC;
    volatile uint32_t OUTINIT;
    volatile uint32_t OUTMASK;
    volatile uint32_t COMBINE;
    volatile uint32_t DEADTIME;
    volatile uint32_t EXTTRIG;
    volatile uint32_t POL;
    volatile uint32_t FMS;
    volatile uint32_t FILTER;
    volatile uint32_t FLTCTRL;
    volatile uint32_t QDCTRL;
    volatile uint32_t CONF;
    volatile uint32_t FLTPOL;
    volatile uint32_t SYNCONF;
    volatile uint32_t INVCTRL;
    volatile uint32_t SWOCTRL;
    volatile uint32_t PWMLOAD;
    volatile uint32_t HCR;
    volatile uint32_t PAIR0DEADTIME;
    uint32_t Reserved0 ;
    volatile uint32_t PAIR1DEADTIME;
    uint32_t Reserved1 ;
    volatile uint32_t PAIR2DEADTIME;
    uint32_t Reserved2 ;
    volatile uint32_t PAIR3DEADTIME;
    uint32_t Reserved3[81] ;
    volatile uint32_t MOD_MIRROR;
    volatile uint32_t CnV_MIRROR[8];
}FTM_type; 
#endif
/*---------------------- End of File ----------------------------------------*/