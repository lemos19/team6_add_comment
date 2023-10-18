#ifndef LPSPI_H
#define LPSPI_H
#include <stdint.h>
#include "General.h"
#include "PCC_Type.h"
#define Framesz8_minus1 uint8_t
#define SCKDivider_plus2 uint8_t
#define LPSPI0_BASE_ADD 0x4002C000
#define LPSPI1_BASE_ADD 0x4002D000
#define LPSPI2_BASE_ADD 0x4002E000
typedef enum{
    LPSPI0_PCS0_PTB0,LPSPI0_PCS0_PTB5,
    LPSPI0_SCK_PTB2,LPSPI0_SCK_PTE0,LPSPI0_SCK_PTD15,
    LPSPI0_SIN_PTE1,LPSPI0_SIN_PTB3,LPSPI0_SIN_PTD16,
    LPSPI0_SOUT_PTE2,LPSPI0_SOUT_PTB4,LPSPI0_SOUT_PTB1,

    LPSPI1_PCS0_PTD3,LPSPI1_PCS0_PTE1,
    LPSPI1_SCK_PTD0,LPSPI1_SCK_PTB14,
    LPSPI1_SIN_PTB15,LPSPI1_SIN_PTD1,
    LPSPI1_SOUT_PTD2,LPSPI1_SOUT_PTB16,LPSPI1_SOUT_PTE0,

    LPSPI2_PCS0_PTA9,LPSPI2_PCS0_PTC14,LPSPI2_PCS0_PTE11,
    LPSPI2_SCK_PTE15,LPSPI2_SCK_PTC15,
    LPSPI2_SIN_PTE16,LPSPI2_SIN_PTC0,
    LPSPI2_SOUT_PTA8,LPSPI2_SOUT_PTC1
}LPSPT_Chanel_Mode_Pin;
typedef union{
    uint32_t Register;
    struct {
        uint32_t FRAMESZ : 12;
        uint32_t Reserved : 4;
        uint32_t WIDTH : 2;
        uint32_t TXMSK : 1;
        uint32_t RXMSK : 1;
        uint32_t CONTC : 1;
        uint32_t CONT : 1;
        uint32_t BYSW : 1;
        uint32_t LSBF : 1;
        uint32_t PCS : 2; 
        uint32_t Reserved1 :1;
        uint32_t PRESCALE : 3;
        uint32_t CPHA : 1;
        uint32_t CPOL : 1;
    }Fields;   
}TCR_t;

typedef union{
    uint32_t Register;
    struct {
       uint32_t SCKDIV : 8;
       uint32_t DBT : 8;
       uint32_t PCSSCK : 8;
       uint32_t SCKPCS : 8;
    }Fields;
}LPSPI_CCR_t;
typedef enum{
    Divide_by_1,
    Divide_by_2,
    Divide_by_4,
    Divide_by_8,
    Divide_by_16,
    Divide_by_32,
    Divide_by_64,
    Divide_by_128
}PRESCALE_devide;
typedef enum{
    inactive_state_SCK_low,
    inactive_state_SCK_high
}CPOL;
typedef enum{
    captured,
    changed
}CPHA;
typedef enum{
    LPSPI_PCS0,
    LPSPI_PCS1,
    LPSPI_PCS2,
    LPSPI_PCS3,
}Peripheral_chip_select;
typedef enum{
    Slave,
    Master
}LPSPI_mode;
typedef union{
    uint32_t Register;
    struct {
       uint32_t MASTER : 1;
       uint32_t SAMPLE : 1;
       uint32_t AUTOPCS: 1;
       uint32_t NOSTALL :1; 
       uint32_t Reserved : 4;
       uint32_t PCSPOL : 4;
       uint32_t Reserved1 : 4;
       uint32_t MATCFG : 3;
       uint32_t Reserved2 : 5;
       uint32_t PINCFG : 2;
       uint32_t OUTCFG : 1;
       uint32_t PCSCFG : 1;
       uint32_t Reserved3 : 4;
    }Fields;
}CFGR1_t;
typedef enum{
    Transmit_Data_Interrupt,
    Receive_Data_Interrupt,
    Word_Complete_Interrupt,
    Frame_Complete_Interrupt,
    Transfer_Complete_Interrupt,
    Transmit_Error_Interrupt,
    Receive_Error_Interrupt,
    Data_Match_Interrupt 
}LPSPI_Interrupt;
typedef union{
    uint32_t Register;
    struct{
        uint32_t TDIE : 1;
        uint32_t RDIE : 1;
        uint32_t Reserved : 6;
        uint32_t WCIE : 1;
        uint32_t FCIE : 1;
        uint32_t TCIE : 1;
        uint32_t TEIE : 1;
        uint32_t REIE : 1;
        uint32_t DMIE : 1;
        uint32_t Reserved1 : 18;
    }Fields;
}LPSPI_IER_t;
typedef struct {
    volatile uint32_t VERID;
    volatile uint32_t PARAM;
    volatile uint32_t Reserved[2];
    volatile uint32_t CR;
    volatile uint32_t SR;
    volatile LPSPI_IER_t IER;
    volatile uint32_t DER;
    volatile uint32_t CFGR0;
    volatile CFGR1_t CFGR1;
    volatile uint32_t Reserved1[2];
    volatile uint32_t DMR0;
    volatile uint32_t DMR1;
    volatile uint32_t Reserved2[2];
    volatile LPSPI_CCR_t CCR;
    volatile uint32_t Reserved3[5];
    volatile uint32_t FCR;
    volatile uint32_t FSR;
    volatile TCR_t TCR;
    volatile uint32_t TDR;
    volatile uint32_t Reserved4[2];
    volatile uint32_t RSR;
    volatile uint32_t RDR;
}LPSPI_Type;
void Config_LPSPI_Chanel(LPSPI_Chanel,
Source_div2_t,
PRESCALE_devide,
CPOL,
CPHA,
uint8_t,
Peripheral_chip_select,
uint8_t,
LPSPI_mode);
void Enable_LPSPI_Pin(LPSPT_Chanel_Mode_Pin);
void Config_LPSPI_Interrupt(LPSPI_Chanel,LPSPI_Interrupt);
#define LPSPI0 ((LPSPI_Type*)(LPSPI0_BASE_ADD))
#define LPSPI1 ((LPSPI_Type*)(LPSPI1_BASE_ADD))
#define LPSPI2 ((LPSPI_Type*)(LPSPI2_BASE_ADD))
#endif
