/******************************************************************************
|------------------------------------------------------------------------------
|   FILE DESCRIPTION                                                           
|------------------------------------------------------------------------------
|    File Name:   <LPIT_type>.<h>                                                  
|    Date:        05-09-2023
|    Description: Source file for lowpower timer
|------------------------------------------------------------------------------
|
|------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y                                  
|------------------------------------------------------------------------------
| Name: Phan Hoang Chanh 
|------------------------------------------------------------------------------
|               EXECUTION NOTE
|------------------------------------------------------------------------------
| Note: use for s32k144 serial
| ---------------------------------------------------------------------------*/
#ifndef LPIT_h
#define LPIT_h
#include <stdint.h>
#include "General.h"
#include "PCC_Type.h"
/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define LPIT_BASE_ADD 0x40037000
#define LPIT ((LPIT_Type*)(LPIT_BASE_ADD))
/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
typedef union {
	uint32_t Resigter;
	struct {
		uint32_t M_CEN : 1;
		uint32_t SW_RST : 1;
		uint32_t DOZE_EN : 1;
		uint32_t DBG_EN : 1;
		uint32_t Reserved : 28;
	}Fields;
}MCR_t; // define bit fields for MCR register

typedef union {
	uint32_t Resigter;
	struct {
		uint32_t TIF0 : 1;
		uint32_t TIF1 : 1;
		uint32_t TIF2 : 1;
		uint32_t TIF3 : 1;
		uint32_t Reserved : 28;
	}Fields;
}MSR_t; // define bit fields for MSR register

typedef union {
	uint32_t Resigter;
	struct {
		uint32_t TIE0 : 1;
		uint32_t TIE1 : 1;
		uint32_t TIE2 : 1;
		uint32_t TIE3 : 1;
		uint32_t Reserved : 28;
	}Fields;
}MIER_t; // define bit fields for MIER register

typedef union {
	uint32_t Resigter;
	struct {
		uint32_t SET_T_EN_0 : 1;
		uint32_t SET_T_EN_1 : 1;
		uint32_t SET_T_EN_2 : 1;
		uint32_t SET_T_EN_3 : 1;
		uint32_t Reserved : 28;
	}Fields;
}SETTEN_t; // define bit fields for SETTEN register

typedef union {
	uint32_t Resigter;
	struct {
		uint32_t CLR_T_EN_0 : 1;
		uint32_t CLR_T_EN_1 : 1;
		uint32_t CLR_T_EN_2 : 1;
		uint32_t CLR_T_EN_3 : 1;
		uint32_t Reserved : 28;
	}Fields;
}CLRTEN_t; // define bit fields for CLRTEN register

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
}TCTRL_t; // define bit fields for TCTRL register

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
}LPIT_Type; // define memory layout of modul LPIT
typedef enum{
	LPIT_Chanel0,
	LPIT_Chanel1,
	LPIT_Chanel2,
	LPIT_Chanel3
}LPIT_Chanel;

void Config_LPIT_Chanel /* this funtion use for config particulor chanel of modul*/
(
	LPIT_Chanel chanel,
	Source clock_sorce,
	Enable_Disable interrupt,
	uint32_t timeValue
); 
/******************************************************************************
 *  FUNCTION PROTOTYPES
 *****************************************************************************/
void LPIT_Set_Clear_Chanel(LPIT_Chanel chanel,Enable_Disable e_d);
#endif
/*---------------------- End of File ----------------------------------------*/