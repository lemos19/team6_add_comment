#ifndef GENERAL_H
#define GENERAL_H
#define SET_BIT(reg, offset) ((reg) | (1U << (offset))) 
#define CLEAR_BIT(reg, offset) ((reg) & ~(1U << (offset))) 
#define GET_STATE(reg, offset) ( (( (reg) >> (offset) )&1U) ) 
#define TOGGLE_BIT(reg, offset) ((reg) ^ (1U << (offset)))
#define CLEAR_CONTIGUOUS(reg, m, offset) ( (reg) & ~(((1<<(m))-1U)<<(offset)) ) 
#define SET_CONTIGUOUS(reg, m, offset) ( (reg) | (((1U<<(m))-1U)<<(offset)) ) 
#define SET_VALUE_CONTIGUOUS(reg, m, offset, v) ( ((reg)&(~(((1U<<(m))-1U)<<(offset)))) | ((((1U<<(m))-1U)&(v))<<(offset)) ) 
#define GET_CONTIGUOUS(reg, m, offset) (  ((reg)>>(offset)) & ((1U<<(m))-1U)  ) 
typedef enum{
	Disable=0,
	Enable=1
}Enable_Disable;
typedef enum
{
	Normal,
	Time_setting,
	Alarm_setting
} Mode_t;
#endif
