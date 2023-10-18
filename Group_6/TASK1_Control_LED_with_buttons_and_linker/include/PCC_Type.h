#ifndef PCC_TYPE_H
#define PCC_TYPE_H
// Peripheral Clock Controller
#include <stdint.h>
#include "SCG_Type.h"
#define PCC_BASE_ADDRESS 0x40065000
typedef enum{
	CHN0,
	CHN1,
	CHN2
}LPUART_Chanel;
typedef enum{
    LPSPI_Chanel0,
    LPSPI_Chanel1,
    LPSPI_Chanel2,
}LPSPI_Chanel;
typedef union{
	uint32_t Resigter;
	struct{
		uint32_t Reserved : 24;
		uint32_t PCS :3;
		uint32_t Reserved0 : 3;
		uint32_t CGC :1;
		uint32_t Reserved1 : 1;
	}Fields;
}LPIT_T;
typedef struct PCC_Type{
	volatile uint32_t PCC_FTFC;
	volatile uint32_t PCC_DMAMUX;
	volatile uint32_t PCC_Reserved[2];
	volatile uint32_t PCC_FlexCAN0;
	volatile uint32_t PCC_FlexCAN1;
	volatile uint32_t PCC_FTM3;
	volatile uint32_t PCC_ADC1;
	volatile uint32_t PCC_Reserved1[3];
	volatile uint32_t PCC_FlexCAN2;
	volatile LPIT_T PCC_LPSPI0;
	volatile LPIT_T PCC_LPSPI1;
	volatile LPIT_T PCC_LPSPI2;
	volatile uint32_t PCC_Reserved2[2];
	volatile uint32_t PCC_PDB1;
	volatile uint32_t PCC_CRC;
	volatile uint32_t PCC_Reserved3[3];
	volatile uint32_t PCC_PDB0;
	volatile LPIT_T PCC_LPIT;
	volatile uint32_t PCC_FTM0;
	volatile uint32_t PCC_FTM1;
	volatile uint32_t PCC_FTM2;
	volatile uint32_t PCC_ADC0;
	volatile uint32_t PCC_Reserved4[1];
	volatile uint32_t PCC_RTC;
	volatile uint32_t PCC_Reserved5[2];
	volatile uint32_t PCC_LPTMR0;
	volatile uint32_t PCC_Reserved6[8];
	volatile uint32_t PCC_PORTA; 
	volatile uint32_t PCC_PORTB; 
	volatile uint32_t PCC_PORTC; //ennable clock
	volatile uint32_t PCC_PORTD; //ennable clock
	volatile uint32_t PCC_PORTE; 
	volatile uint32_t PCC_Reserved7[6];
	volatile uint32_t PCC_SAI0;
	volatile uint32_t PCC_SAI1;
	volatile uint32_t PCC_Reserved8[4];
	volatile uint32_t PCC_FlexIO;
	volatile uint32_t PCC_Reserved10[6];
	volatile uint32_t PCC_EWM;
	volatile uint32_t PCC_Reserved11[4];
	volatile uint32_t PCC_LPI2C0;
	volatile uint32_t PCC_LPI2C1;
	volatile uint32_t PCC_Reserved12[2];
	volatile LPIT_T PCC_LPUART0;
	volatile LPIT_T PCC_LPUART1;
	volatile LPIT_T PCC_LPUART2;
	volatile uint32_t PCC_Reserved13;
	volatile uint32_t PCC_FTM4;
	volatile uint32_t PCC_FTM5;
	volatile uint32_t PCC_FTM6;
	volatile uint32_t PCC_FTM7;
	volatile uint32_t PCC_Reserved14;
	volatile uint32_t PCC_CMP0;
	volatile uint32_t PCC_Reserved15[2];
	volatile uint32_t PCC_QSPI;
	volatile uint32_t PCC_Reserved16[2];
	volatile uint32_t PCC_ENET;
}PCC_Type;
void PCC_LPSPI_ClockSource(LPSPI_Chanel,Source);
void PCC_LPIT_ClockSource(Source);
void PCC_LPUART_ClockSource(LPUART_Chanel,Source);
#define PCC ((PCC_Type*)(PCC_BASE_ADDRESS+0x80))
#endif
