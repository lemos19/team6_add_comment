#ifndef SYSTICK_H
#define SYSTICK_H

#define SYSTICK_ADD 0xE000E010
#include <stdint.h>
typedef struct SysTick_Type{
	volatile uint32_t SYST_CSR;
	volatile uint32_t SYST_RVR;
	volatile uint32_t SYST_CVR;
	volatile uint32_t SYST_CALIB;
}SysTick_Type;
void SysTick_Handler(void);
#define SYST ((SysTick_Type*)(SYSTICK_ADD))
#endif
