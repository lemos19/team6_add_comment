#include "FTM_type.h"
#include "PCC_Type.h"
static FTM_type* FTM[8]={FTM0,FTM1,FTM2,FTM3,FTM4,FTM5,FTM6,FTM7};
void FTM_init(Ftm_modul_t modul,Source_div1_t source,preScale_fmt_t div,uint32_t modulo){
    switch (modul)
    {
    case FTM_0:
    	PCC->PCC_FTM0.Fields.PCS = source;
        PCC->PCC_FTM0.Fields.CGC = Enable;
        break;
    case FTM_1:
        PCC->PCC_FTM1.Fields.PCS = source;
        PCC->PCC_FTM1.Fields.CGC = Enable;
        break;
    case FTM_2:
        PCC->PCC_FTM2.Fields.PCS = source;
        PCC->PCC_FTM2.Fields.CGC = Enable;
        break;
    case FTM_3:
        PCC->PCC_FTM3.Fields.PCS = source;
        PCC->PCC_FTM3.Fields.CGC = Enable;
        break;
    case FTM_4:
        PCC->PCC_FTM4.Fields.PCS = source;
        PCC->PCC_FTM4.Fields.CGC = Enable;
        break;
    case FTM_5:
        PCC->PCC_FTM5.Fields.PCS = source;
        PCC->PCC_FTM5.Fields.CGC = Enable;
        break;
    case FTM_6:
        PCC->PCC_FTM6.Fields.PCS = source;
        PCC->PCC_FTM6.Fields.CGC = Enable;
        break;
    case FTM_7:
        PCC->PCC_FTM7.Fields.PCS = source;
        PCC->PCC_FTM7.Fields.CGC = Enable;
        break;
    }
    FTM[modul]->MODE.Fields.WPDIS = Enable;
    FTM[modul]->SC.Fields.PS = div;
    FTM[modul]->SC.Fields.PWMEN0 = Enable;
    FTM[modul]->SC.Fields.PWMEN1 = Enable;
    FTM[modul]->MOD = modulo;
    //turn on chanel 1 PWM
    FTM[modul]->CnSC_And_CnV[1].CnSC = SET_BIT(FTM[modul]->CnSC_And_CnV[1].CnSC,3)|SET_BIT(FTM[modul]->CnSC_And_CnV[1].CnSC,5);
    FTM[modul]->CnSC_And_CnV[1].CnV = 31250;/* FTM0 ch1 compare value = 75% modulo*/
}
void Start_counter_FTM0(void){
    FTM0->SC.Fields.CLKS = 3;
}
void Disable_counter_FTM0(void){
    FTM0->SC.Fields.CLKS = 0;
}
