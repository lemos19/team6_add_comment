#ifndef PORT_TYPE_H
#define PORT_TYPE_H
// Port Control and Interrupts (PORT)
#include <stdint.h>
typedef enum {
	Port_A,
	Port_B,
	Port_C,
	Port_D,
	Port_E
}Port_t;
typedef union{
	uint32_t Register;
	struct 
	{
		uint32_t PS : 1;
		uint32_t PE : 1 ;
		uint32_t reserved0 : 2;
		uint32_t PFE : 1;
		uint32_t reserved1 : 1;
		uint32_t DSE : 1;
		uint32_t reserved2 : 1;
		uint32_t MUX : 3;
		uint32_t reserved3 : 4;
		uint32_t LK : 1;
		uint32_t IRQC : 4;
		uint32_t reserved4 : 4;
		uint32_t ISF : 1;
		uint32_t reserved5 : 7;
	}Fields;
}Port_PCR;
#define PORTA_ADDRESS 0x40049000
#define PORTB_ADDRESS 0x4004A000
#define PORTC_ADDRESS 0x4004B000
#define PORTD_ADDRESS 0x4004C000
#define PORTE_ADDRESS 0x4004D000
typedef	struct PORT_T{
	volatile Port_PCR PORT_PCR[32]; // config 32pin (muxing to GPIO -- 001 bit 8 to 10) 
	volatile uint32_t PORT_GPCLR; 
	volatile uint32_t PORT_GPCHR;
	volatile uint32_t PORT_GICLR;
	volatile uint32_t PORT_GICHR;
	volatile uint32_t PORT_Reserved2Bytes[4];
	volatile uint32_t PORT_ISFR;
	volatile uint32_t PORT_Reserved4Bytes[7];
	volatile uint32_t PORT_DFER;
	volatile uint32_t PORT_DFCR;
	volatile uint32_t PORT_DFWR;
}PORT_T;
void PORTC_IRQHandler(void);
#define PORTA ((PORT_T*)(PORTA_ADDRESS))
#define PORTB ((PORT_T*)(PORTB_ADDRESS))
#define PORTC ((PORT_T*)(PORTC_ADDRESS))
#define PORTD ((PORT_T*)(PORTD_ADDRESS))
#define PORTE ((PORT_T*)(PORTE_ADDRESS))

#endif
