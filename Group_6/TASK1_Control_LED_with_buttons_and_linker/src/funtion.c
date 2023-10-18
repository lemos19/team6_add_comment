#include "MacroAndFuntion.h"
void initializeGPIOandSystick(void){
	// enable Peripheral clock in portC and portD
	PCC->PCC_PORTC = SET_BIT(PCC->PCC_PORTC,30);
	PCC->PCC_PORTD = SET_BIT(PCC->PCC_PORTD,30);
	/* muxing pin to GPIO each pin have 1 resigter (PORT_PCR[pin])
	+PortD: pin 0,15,16 
	+PortC: pin 12,13 */ //filter turn on bit 4
	PORTD->PORT_PCR[0].Fields.MUX=1;
	PORTD->PORT_PCR[15].Fields.MUX=1; 
	PORTD->PORT_PCR[16].Fields.MUX=1;
	
	PORTC->PORT_PCR[12].Fields.MUX=1; PORTC->PORT_PCR[12].Fields.PFE=Enable;
	PORTC->PORT_PCR[13].Fields.MUX=1; PORTC->PORT_PCR[13].Fields.PFE=Enable;
	/* config data direction for pin (PDDR)(1 resigter 32 bit config 32 pin)
	+PortD: pin 0,15,16 out put (bit = 1)
	+PortC: pin 12,13 input     (bit = 0) */
	GPIOD->GPIO_PDDR = SET_BIT(GPIOD->GPIO_PDDR,0)|SET_BIT(GPIOD->GPIO_PDDR,15)|SET_BIT(GPIOD->GPIO_PDDR,16);
	GPIOC->GPIO_PDDR = 0; 
	/* Write bit in to PDOR if we config is output | Read bit by PDIR if we config is input 
		 Each resigter have 32 bit for 32 pin */
	//PDOR 1: led off, 0:led on
	GPIOD->GPIO_PDOR = SET_BIT(GPIOD->GPIO_PDOR,0)|SET_BIT(GPIOD->GPIO_PDOR,15)|SET_BIT(GPIOD->GPIO_PDOR,16);
	// configure rising edge for interrupt sensitive
	PORTC->PORT_PCR[12].Fields.IRQC = 9;//configure rising edge for pin 12
	PORTC->PORT_PCR[13].Fields.IRQC = 11; //configure rising edge for pin 13
	//PORTC->PORT_PCR[12]= SET_VALUE_CONTIGUOUS(PORTC->PORT_PCR[12],4,16,0xC); //configure logic 1 for pin 12
	//PORTC->PORT_PCR[13]= SET_VALUE_CONTIGUOUS(PORTC->PORT_PCR[13],4,16,0xC); //configure logic 1 for pin 13
	//PORTC->PORT_PCR[12]= SET_VALUE_CONTIGUOUS(PORTC->PORT_PCR[12],4,16,0xC); //configure falling edge for pin 12
	//PORTC->PORT_PCR[13]= SET_VALUE_CONTIGUOUS(PORTC->PORT_PCR[13],4,16,0xC); //configure falling edge for pin 13
	// enable PORTC interrupt in NVIC
	// Interrupt ID of PORTC: 61 -> n = 1, bit 29th
	// Skip setting priority for PORTC interrupt since we only use one
	NVIC_Config_Interrup_Modul(PortC,Enable);
	SYST->SYST_CSR = SET_BIT(SYST->SYST_CSR,2);
	SYST->SYST_RVR = (48000000/1000) - 1; 
}
void delayInterrupt_ms(uint32_t ms){
	msCounter = ms;
	SYST->SYST_CSR = SET_BIT(SYST->SYST_CSR,1)|SET_BIT(SYST->SYST_CSR,0); // start counter & enable interrupt
	while(msCounter){}
	SYST->SYST_CVR = 0;
	SYST->SYST_CSR = CLEAR_BIT(SYST->SYST_CSR,1)|CLEAR_BIT(SYST->SYST_CSR,0); //stop counter & disalble interrupt
}
void SysTick_Handler(void){
	msCounter--;
}


