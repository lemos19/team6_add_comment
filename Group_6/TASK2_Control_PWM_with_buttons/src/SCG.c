#include "SCG_Type.h"
void SCG_Asyn_Peripheral_Sources(Source_div2_t source,Divide_Options div){
    if (source == FIRCDIV2_CLK){
        SCG->SCG_FIRCDIV.Fields.Div2 = div;
    }
    else if (source == SOSCDIV2_CLK){
        SCG->SCG_SOSCDIV.Fields.Div2 = div;
    }
    else if (source == SIRCDIV2_CLK){
        SCG->SCG_SIRCDIV.Fields.Div2 = div;
    }
    else{
        SCG->SCG_SPLLDIV.Fields.Div2 = div;
    }
}
void Config_SOSC_CLK(void){
    SCG->SCG_SOSCCSR = CLEAR_BIT(SCG->SCG_SOSCCSR,0);
    SCG->SCG_SOSCCFG = SET_BIT(SCG->SCG_SOSCCFG,2)|SET_BIT(SCG->SCG_SOSCCFG,3)|SET_BIT(SCG->SCG_SOSCCFG,5);
    SCG->SCG_SOSCCSR = SET_BIT(SCG->SCG_SOSCCSR,0);
    while (!(GET_STATE(SCG->SCG_SOSCCSR,24))){}
}
void Config_SPLL_CLK(Clock_Source_t Sosc_Firc,PreDiv_SPLL div,Multiply_SPLL mul){
    SCG->SCG_SPLLCSR = CLEAR_BIT(SCG->SCG_SPLLCSR,0);
    if (Sosc_Firc == SOSC){
        SCG->SCG_SPLLCFG.Fields.SOURCE = 0;
    }
    else if (Sosc_Firc == FIRC){
        SCG->SCG_SPLLCFG.Fields.SOURCE = 1;
    }
    else{}
    SCG->SCG_SPLLCFG.Fields.PREDIV = div;
    SCG->SCG_SPLLCFG.Fields.MULT = mul;
    SCG->SCG_SPLLCSR = SET_BIT(SCG->SCG_SPLLCSR,0);
    while (!(GET_STATE(SCG->SCG_SPLLCSR,24))){}
}
void Config_RCCR(Clock_Source_t source,uint8_t divCore1_16_minus1,uint8_t divBus1_16_minus1,uint8_t divSlow1_8_minus1){
    CCR_t tempRCCR;
    tempRCCR.Register = 0;
    if (source == FIRC){
        tempRCCR.Fields.SCS = 3;
    }
    else if (source == SIRC){
        tempRCCR.Fields.SCS = 2;
    }
    else if (source == SOSC){
        tempRCCR.Fields.SCS = 1;
    }
    else if (source == SPLL){
        tempRCCR.Fields.SCS = 6;
    }
    tempRCCR.Fields.DIVCORE = divCore1_16_minus1;
    tempRCCR.Fields.DIVBUS = divBus1_16_minus1;
    tempRCCR.Fields.DIVSLOW = divSlow1_8_minus1;
    SCG->SCG_RCCR.Register = tempRCCR.Register;
    while (!(SCG->SCG_CSR.Register==SCG->SCG_RCCR.Register)){} 
}

