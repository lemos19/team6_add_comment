#include "PCC_Type.h"
#include "General.h"
void PCC_LPIT_ClockSource(Source source){
	PCC->PCC_LPIT.Fields.PCS = source;
	PCC->PCC_LPIT.Fields.CGC = Enable;
}
void PCC_LPUART_ClockSource(LPUART_Chanel ch,Source source){
	switch (ch){
	case CHN0:
		PCC->PCC_LPUART0.Fields.PCS = source;
		PCC->PCC_LPUART0.Fields.CGC = Enable;
		break;
	case CHN1:
		PCC->PCC_LPUART1.Fields.PCS = source;
		PCC->PCC_LPUART1.Fields.CGC = Enable;
		break;
	case CHN2:
		PCC->PCC_LPUART2.Fields.PCS = source;
		PCC->PCC_LPUART2.Fields.CGC = Enable;
		break;
	}
}
void PCC_LPSPI_ClockSource(LPSPI_Chanel chanel,Source source){
	switch (chanel){
	case LPSPI_Chanel0:
		PCC->PCC_LPSPI0.Fields.PCS = source;
		PCC->PCC_LPSPI0.Fields.CGC = Enable;
		break;
	case LPSPI_Chanel1:
		PCC->PCC_LPSPI1.Fields.PCS = source;
		PCC->PCC_LPSPI1.Fields.CGC = Enable;
		break;
	case LPSPI_Chanel2:
		PCC->PCC_LPSPI2.Fields.PCS = source;
		PCC->PCC_LPSPI2.Fields.CGC = Enable;
		break;
	}
}
