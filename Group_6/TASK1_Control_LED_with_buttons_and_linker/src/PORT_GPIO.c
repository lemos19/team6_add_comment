#include "GPIO_Type.h"
static PORT_T *Port[5] = {PORTA,PORTB,PORTC,PORTD,PORTE};
static GPIO_Type *Gpio[5] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOD};
void Config_GPIO_Pin(Port_t port,
Pin_t pin,
Enable_Disable pull,
Pull_select pulls,
Enable_Disable passive_filter,
Muxing_mode mux,
Interrupt_config interrupt,
Direction input_output)
{
    Port[port]->PORT_PCR[pin].Fields.PE=pull;
    Port[port]->PORT_PCR[pin].Fields.PFE=passive_filter;
    Port[port]->PORT_PCR[pin].Fields.PS=pulls;
    Port[port]->PORT_PCR[pin].Fields.IRQC=interrupt;
    Port[port]->PORT_PCR[pin].Fields.MUX=mux;
    Gpio[port]->GPIO_PDDR |= (uint32_t)input_output<<pin;
}

