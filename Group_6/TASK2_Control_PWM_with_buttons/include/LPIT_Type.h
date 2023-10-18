#ifndef LPIT_h
#define LPIT_h
#include <stdint.h>
#include "General.h"
#include "PCC_Type.h"
#define LPIT_BASE_ADD 0x40037000
typedef union {
	uint32_t Resigter;
	struct {
		uint32_t M_CEN : 1;
		uint32_t SW_RST : 1;
		uint32_t DOZE_EN : 1;
		uint32_t DBG_EN : 1;
		uint32_t Reserved : 28;
	}Fields;
}MCR_t;

typedef union {
	uint32_t Resigter;
	struct {
		uint32_t TIF0 : 1;
		uint32_t TIF1 : 1;
		uint32_t TIF2 : 1;
		uint32_t TIF3 : 1;
		uint32_t Reserved : 28;
	}Fields;
}MSR_t;

typedef union {
	uint32_t Resigter;
	struct {
		uint32_t TIE0 : 1;
		uint32_t TIE1 : 1;
		uint32_t TIE2 : 1;
		uint32_t TIE3 : 1;
		uint32_t Reserved : 28;
	}Fields;
}MIER_t;

typedef union {
	uint32_t Resigter;
	struct {
		uint32_t SET_T_EN_0 : 1;
		uint32_t SET_T_EN_1 : 1;
		uint32_t SET_T_EN_2 : 1;
		uint32_t SET_T_EN_3 : 1;
		uint32_t Reserved : 28;
	}Fields;
}SETTEN_t;

typedef union {
	uint32_t Resigter;
	struct {
		uint32_t CLR_T_EN_0 : 1;
		uint32_t CLR_T_EN_1 : 1;
		uint32_t CLR_T_EN_2 : 1;
		uint32_t CLR_T_EN_3 : 1;
		uint32_t Reserved : 28;
	}Fields;
}CLRTEN_t;

typedef union{
	uint32_t Register;
	struct{
		uint32_t T_EN : 1;
		uint32_t CHAIN : 1 ;
		uint32_t MODE : 2;
		uint32_t Reserved : 12;
		uint32_t TSOT : 1;
		uint32_t TSOI : 1;
		uint32_t TROT : 1;
		uint32_t Reserved1 : 4;
		uint32_t TRG_SRC : 1;
		uint32_t TRG_SEL : 4;
		uint32_t Reserved2 : 4;
	}Fields;
}TCTRL_t;

typedef struct LPIT_Type{
	volatile uint32_t VERID;
	volatile uint32_t PARAM;
	volatile MCR_t MCR;
	volatile MSR_t MSR;
	volatile MIER_t MIER;
	volatile SETTEN_t SETTEN;
	volatile CLRTEN_t CLRTEN;
	uint32_t Reserved;
	volatile uint32_t TVAL0;
	volatile uint32_t CVAL0;
	volatile TCTRL_t TCTRL0;
	uint32_t Reserved1;
	volatile uint32_t TVAL1;
	volatile uint32_t CVAL1;
	volatile TCTRL_t TCTRL1;
	uint32_t Reserved2;
	volatile uint32_t TVAL2;
	volatile uint32_t CVAL2;
	volatile TCTRL_t TCTRL2;
	uint32_t Reserved3;
	volatile uint32_t TVAL3;
	volatile uint32_t CVAL3;
	volatile TCTRL_t TCTRL3;
}LPIT_Type;
typedef enum{
	LPIT_Chanel0,
	LPIT_Chanel1,
	LPIT_Chanel2,
	LPIT_Chanel3
}LPIT_Chanel;

void Config_LPIT_Chanel(LPIT_Chanel chanel,
Source_div2_t clock_sorce,
Enable_Disable interrupt,
uint32_t timeValue);
void LPIT_Set_Clear_Chanel(LPIT_Chanel chanel,Enable_Disable e_d);
#define LPIT ((LPIT_Type*)(LPIT_BASE_ADD))
#endif
