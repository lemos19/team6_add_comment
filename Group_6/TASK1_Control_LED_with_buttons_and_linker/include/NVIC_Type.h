#ifndef NVIC_TYPE_H
#define NVIC_TYPE_H
#define NVIC_BASE_ADD 0xE000E100
#include <stdint.h>
#include "General.h"
typedef enum{
	LPIT0=48,LPIT1,LPIT2,LPIT3,
	PortA=59,PortB,PortC,PortD,PortE,
	Lpuart0=31,Lpuart1=33,Lpuart2=35,
	Lpspi0=26,Lpspi1,Lpspi2
}Modul;

void NVIC_Config_Interrup_Modul(Modul,Enable_Disable);
typedef struct NVIC_Type
	{
		volatile uint32_t ISER[8];
		volatile uint32_t res1[24];
		volatile uint32_t ICER[8];
		volatile uint32_t res2[24];
		volatile uint32_t ISPR[8];
		volatile uint32_t res3[24];
		volatile uint32_t ICPR[8];
		volatile uint32_t res4[24];
		volatile uint32_t IABR[8];
		volatile uint32_t res5[56];
		volatile uint32_t IPR[60];
		volatile uint32_t res6[644];
		volatile uint32_t STIR;
	}NVIC_Type;
#define NVIC ((NVIC_Type*)(NVIC_BASE_ADD))
#endif
