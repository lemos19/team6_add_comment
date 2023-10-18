#ifndef FTM_H
#define FTM_H
#include <stdint.h>
#include "SCG_Type.h"
#define FTM0_BASE_ADDRESS 0x40038000
#define FTM1_BASE_ADDRESS 0x40039000
#define FTM2_BASE_ADDRESS 0x4003A000
#define FTM3_BASE_ADDRESS 0x40026000
#define FTM4_BASE_ADDRESS 0x4006E000
#define FTM5_BASE_ADDRESS 0x4006F000
#define FTM6_BASE_ADDRESS 0x40070000
#define FTM7_BASE_ADDRESS 0x40071000
typedef union 
{
    uint32_t Register;
    struct 
    {
        uint32_t FTMEN : 1;
        uint32_t INIT : 1;
        uint32_t WPDIS : 1;
        uint32_t PWMSYNC : 1;
        uint32_t CAPTEST : 1;
        uint32_t FAULTM : 1;
        uint32_t FAULTIE : 1;
    }Fields;
}Ftm_mode_t;
typedef union 
{
    uint32_t Register;
    struct 
    {
        uint32_t PS : 3;
        uint32_t CLKS : 2;
        uint32_t CPWMS : 1;
        uint32_t RIE : 1;
        uint32_t RF : 1;
        uint32_t TOIE : 1;
        uint32_t TOF : 1;
        uint32_t Reserved : 6;
        uint32_t PWMEN0: 1;
        uint32_t PWMEN1: 1;
        uint32_t PWMEN2: 1;
        uint32_t PWMEN3: 1;
        uint32_t PWMEN4: 1;
        uint32_t PWMEN5: 1;
        uint32_t PWMEN6: 1;
        uint32_t PWMEN7: 1;
        uint32_t FLTPS : 4;
        uint32_t Reserved0 : 4;
    }Fields;  
}Sc_t;

typedef struct 
{
    volatile Sc_t SC;
    volatile uint32_t CNT;
    volatile uint32_t MOD;
    struct 
    {
        volatile uint32_t CnSC;
        volatile uint32_t CnV;
    }CnSC_And_CnV[8];
    volatile uint32_t CNTIN;
    volatile uint32_t STATUS;
    volatile Ftm_mode_t MODE;
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
typedef enum {
    FTM_0,
    FTM_1,
    FTM_2,
    FTM_3,
    FTM_4,
    FTM_5,
    FTM_6,
    FTM_7,
}Ftm_modul_t;
typedef enum {
    Div_1,
    Div_2,
    Div_4,
    Div_8,
    Div_16,
    Div_32,
    Div_64,
    Div_128
}preScale_fmt_t;
#define FTM0 ((FTM_type*)(FTM0_BASE_ADDRESS))
#define FTM1 ((FTM_type*)(FTM1_BASE_ADDRESS))
#define FTM2 ((FTM_type*)(FTM2_BASE_ADDRESS))
#define FTM3 ((FTM_type*)(FTM3_BASE_ADDRESS))
#define FTM4 ((FTM_type*)(FTM4_BASE_ADDRESS))
#define FTM5 ((FTM_type*)(FTM5_BASE_ADDRESS))
#define FTM6 ((FTM_type*)(FTM6_BASE_ADDRESS))
#define FTM7 ((FTM_type*)(FTM7_BASE_ADDRESS))
void FTM_init(Ftm_modul_t,Source_div1_t,preScale_fmt_t, uint32_t);
void Start_counter_FTM0(void);
void Disable_counter_FTM0(void);
#endif