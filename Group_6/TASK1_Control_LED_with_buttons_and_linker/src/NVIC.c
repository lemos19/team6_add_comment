#include "NVIC_Type.h"
void NVIC_Config_Interrup_Modul(Modul modul,Enable_Disable enable_disable){
	if (enable_disable == Enable){
		NVIC->ISER[modul/32] = SET_BIT(NVIC->ISER[modul/32],(modul%32));
	}
	else{
		NVIC->ISER[modul/32] = CLEAR_BIT(NVIC->ISER[modul/32],(modul%32));
	}	
}
