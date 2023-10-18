#ifndef MicroAndFuntion_h
#define MicroAndFuntion_h
// define some interesting things
#include "GPIO_Type.h"
#include "PCC_Type.h"
#include "PORT_Type.h"
#include "NVIC_Type.h"
#include "SysTick.h"
#include "SCG_Type.h"
void initializeGPIOandSystick(void);
void delayInterrupt_ms(uint32_t);
volatile static uint32_t msCounter = 0;
#define SET_BIT(reg, offset) ((reg) | (1U << (offset))) 
#define CLEAR_BIT(reg, offset) ((reg) & ~(1U << (offset))) 
#define GET_STATE(reg, offset) ( (( (reg) >> (offset) )&1U) ) 
#define TOGGLE_BIT(reg, offset) ((reg) ^ (1U << (offset)))
#define CLEAR_CONTIGUOUS(reg, m, offset) ( (reg) & ~(((1<<(m))-1U)<<(offset)) ) 
#define SET_CONTIGUOUS(reg, m, offset) ( (reg) | (((1U<<(m))-1U)<<(offset)) ) 
#define SET_VALUE_CONTIGUOUS(reg, m, offset, v) ( ((reg)&(~(((1U<<(m))-1U)<<(offset)))) | ((((1U<<(m))-1U)&(v))<<(offset)) ) 
#define GET_CONTIGUOUS(reg, m, offset) (  ((reg)>>(offset)) & ((1U<<(m))-1U)  ) 

#endif
