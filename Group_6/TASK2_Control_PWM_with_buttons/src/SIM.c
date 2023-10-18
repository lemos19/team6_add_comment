#include "SIM_Type.h"
void Clkout_config(Clkoutsource source,Clkoutdiv_t div){
	SIM->CHIPCTL.Fields.CLKOUTEN = Disable;
    SIM->CHIPCTL.Fields.CLKOUTSEL=  source; 
    SIM->CHIPCTL.Fields.CLKOUTDIV= div;
    SIM->CHIPCTL.Fields.CLKOUTEN = Enable; 
}
