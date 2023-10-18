#ifndef SCG_H
#define SCG_H
#include <stdint.h>
#include "General.h"
#define SCG_BASE_ADDRESS 0x40064000
typedef union{
	uint32_t Register;
	struct{
		uint32_t DIVSLOW : 4;
		uint32_t DIVBUS : 4;
		uint32_t Reserved : 8;
		uint32_t DIVCORE : 4;
		uint32_t Reserved1 : 4;
		uint32_t SCS : 4;
		uint32_t Reserved2 : 4;
	}Fields;
}CCR_t;
typedef union 
{
	uint32_t Register;
	struct {
		uint32_t Div1 : 3;
		uint32_t Reserved : 5;
		uint32_t Div2 : 3;
		uint32_t Reserved0 : 21;
	}Fields;
}DIV_t;
typedef enum{
	SOSCDIV2_CLK = 1,
	SIRCDIV2_CLK = 2,
	FIRCDIV2_CLK = 3,
	SPLLDIV2_CLK = 6
}Source_div2_t;
typedef enum{
	SOSCDIV1_CLK = 1,
	SIRCDIV1_CLK = 2,
	FIRCDIV1_CLK = 3,
	SPLLDIV1_CLK = 6
}Source_div1_t;
typedef enum{
	FIRC,
	SIRC,
	SOSC,
	SPLL
}Clock_Source_t;
typedef enum{
	Div_By_1= 1,
	Div_By_2,
	Div_By_4,
	Div_By_8,
	Div_By_16,
	Div_By_32,
	Div_By_64
}Divide_Options;
typedef enum{
	Div1,
	Div2,
	Div3,
	Div4,
	Div5,
	Div6,
	Div7,
	Div8,
}PreDiv_SPLL;
typedef enum{
	Multi16,
	Multi17,
	Multi18,
	Multi19,
	Multi20,
	Multi21,
	Multi22,
	Multi23,
	Multi24,
	Multi25,
	Multi26,
	Multi27,
	Multi28,
	Multi29,
	Multi30,
	Multi31,
	Multi32,
	Multi33,
	Multi34,
	Multi35,
	Multi36,
	Multi37,
	Multi38,
	Multi39,
	Multi40,
	Multi41,
	Multi42,
	Multi43,
	Multi44,
	Multi45,
	Multi46,
	Multi47,
}Multiply_SPLL;
typedef union{
	uint32_t Register;
	struct{
		uint32_t SOURCE : 1;
		uint32_t Reserved : 7;
		uint32_t PREDIV : 3;
		uint32_t Reserved1 : 5;
		uint32_t MULT : 5;
		uint32_t Reserved2 : 11;
	}Fields;
}SPLL_cf;
typedef struct{
	volatile uint32_t SCG_VERID;
	volatile uint32_t SCG_PARAM;
	uint32_t Reserved[2];
	volatile CCR_t SCG_CSR;
	volatile CCR_t SCG_RCCR;
	volatile CCR_t SCG_VCCR;
	volatile CCR_t SCG_HCCR;
	volatile uint32_t SCG_CLKOUTCNFG;
	uint32_t Reserved1[55];
	volatile uint32_t SCG_SOSCCSR;
	volatile DIV_t SCG_SOSCDIV;
	volatile uint32_t SCG_SOSCCFG;
	uint32_t Reserved2[61];
	volatile uint32_t SCG_SIRCCSR;
	volatile DIV_t SCG_SIRCDIV;
	volatile uint32_t SCG_SIRCCFG;
	uint32_t Reserved3[61];
	volatile uint32_t SCG_FIRCCSR;
	volatile DIV_t SCG_FIRCDIV;
	volatile uint32_t SCG_FIRCCFG;
	uint32_t Reserved4[189];
	volatile uint32_t SCG_SPLLCSR;
	volatile DIV_t SCG_SPLLDIV;
	volatile SPLL_cf SCG_SPLLCFG;
}SCG_Type;
void SCG_Asyn_Peripheral_Sources(Source_div2_t,Divide_Options);
void Config_SOSC_CLK(void);
void Config_SPLL_CLK(Clock_Source_t,PreDiv_SPLL,Multiply_SPLL);
void Config_RCCR(Clock_Source_t,uint8_t,uint8_t,uint8_t);
#define SCG ((SCG_Type*)(SCG_BASE_ADDRESS))
#endif
