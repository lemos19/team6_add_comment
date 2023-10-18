#include "ledMax7219.h"
#include "LPSPI_Type.h"
#include "MacroAndFuntion.h"
uint16_t Printf_led(Number_Print_t num, Led_add add, Dot_t d)
{
	while (!(GET_STATE(LPSPI0->SR, 0)))
	{
	}
	return (uint16_t)(((add << 8) | num) | (d << 7));
}
void ConfigledMAX7219(void)
{
	while (!(GET_STATE(LPSPI0->SR, 0)))
	{
	}
	LPSPI0->TDR = 0x0C01;
	while (!(GET_STATE(LPSPI0->SR, 0)))
	{
	}
	LPSPI0->TDR = 0x0900;
	while (!(GET_STATE(LPSPI0->SR, 0)))
	{
	}
	LPSPI0->TDR = 0x0A0F;
	while (!(GET_STATE(LPSPI0->SR, 0)))
	{
	}
	LPSPI0->TDR = 0x0B07;

	LPSPI0->TDR = Printf_led(_0, Led_1, no_dot);
	LPSPI0->TDR = Printf_led(_0, Led_2, no_dot);
	LPSPI0->TDR = Printf_led(_0, Led_3, dot);
	LPSPI0->TDR = Printf_led(_0, Led_4, no_dot);
	LPSPI0->TDR = Printf_led(_off, Led_5, no_dot);
	LPSPI0->TDR = Printf_led(_off, Led_6, no_dot);
	LPSPI0->TDR = Printf_led(_off, Led_7, no_dot);
	LPSPI0->TDR = Printf_led(_off, Led_8, no_dot);
}
void StartUPled(void)
{
	// Start up led !!
	LPSPI0->TDR = Printf_led(_rightDown, Led_5, no_dot);
	delayInterrupt_ms(250);
	LPSPI0->TDR = Printf_led(_rightUp, Led_5, no_dot);
	delayInterrupt_ms(200);
	LPSPI0->TDR = Printf_led(_up, Led_5, no_dot);
	delayInterrupt_ms(180);
	LPSPI0->TDR = Printf_led(_up, Led_6, no_dot);
	delayInterrupt_ms(120);
	LPSPI0->TDR = Printf_led(_up, Led_7, no_dot);
	delayInterrupt_ms(100);
	LPSPI0->TDR = Printf_led(_up, Led_8, no_dot);
	delayInterrupt_ms(50);
	LPSPI0->TDR = Printf_led(_leftUp, Led_8, no_dot);
	delayInterrupt_ms(100);
	LPSPI0->TDR = Printf_led(_leftDown, Led_8, no_dot);
	delayInterrupt_ms(120);
	LPSPI0->TDR = Printf_led(_down, Led_8, no_dot);
	delayInterrupt_ms(180);
	LPSPI0->TDR = Printf_led(_down, Led_7, no_dot);
	delayInterrupt_ms(200);
	LPSPI0->TDR = Printf_led(_down, Led_6, no_dot);
	delayInterrupt_ms(250);

	LPSPI0->TDR = Printf_led(_down, Led_5, no_dot);
	delayInterrupt_ms(200);

	LPSPI0->TDR = Printf_led(_mid, Led_8, no_dot);
	LPSPI0->TDR = Printf_led(_off, Led_5, no_dot);
}
