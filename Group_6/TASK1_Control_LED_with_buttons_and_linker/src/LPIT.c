#include "LPIT_Type.h"
#include "SCG_Type.h"
#include "NVIC_Type.h"
void Config_LPIT_Chanel
(
    LPIT_Chanel chanel,
    Source clock_sorce,
    Enable_Disable interrupt,
    uint32_t timeValue
)
{
    PCC_LPIT_ClockSource(clock_sorce);
    LPIT->MCR.Fields.M_CEN = Enable;
	LPIT->MCR.Fields.DBG_EN = Enable;
    if (chanel == LPIT_Chanel0){
        LPIT->TVAL0 = timeValue;
        LPIT->MIER.Fields.TIE0 = interrupt;
        NVIC_Config_Interrup_Modul(LPIT0,interrupt);
    }
    else if (chanel == LPIT_Chanel1){
        LPIT->TVAL1 = timeValue;
        LPIT->MIER.Fields.TIE1 = interrupt;
        NVIC_Config_Interrup_Modul(LPIT1,interrupt);
    }
    else if (chanel == LPIT_Chanel2){
        LPIT->TVAL2 = timeValue;
        LPIT->MIER.Fields.TIE2 = interrupt;
        NVIC_Config_Interrup_Modul(LPIT2,interrupt);
    }
    else {
        LPIT->TVAL3 = timeValue;
        LPIT->MIER.Fields.TIE3 = interrupt;
        NVIC_Config_Interrup_Modul(LPIT3,interrupt);
    }
}
void LPIT_Set_Clear_Chanel(LPIT_Chanel chanel,Enable_Disable e_d){
    if (chanel== LPIT_Chanel0){
        LPIT->TCTRL0.Fields.T_EN = e_d;
    }
    if (chanel== LPIT_Chanel1){
        LPIT->TCTRL1.Fields.T_EN = e_d;
    }
    if (chanel== LPIT_Chanel2){
        LPIT->TCTRL2.Fields.T_EN = e_d;
    }
    if (chanel== LPIT_Chanel3){
       LPIT->TCTRL3.Fields.T_EN = e_d;
    }
}
