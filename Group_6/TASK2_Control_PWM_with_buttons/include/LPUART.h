#ifndef LPUART_H
#define LPUART_H
#include <stdint.h>
#include "General.h"
#include "PCC_Type.h"
#define LPUART0_BASE_ADD 0x4006A000
#define LPUART1_BASE_ADD 0x4006B000
#define LPUART2_BASE_ADD 0x4006C000
//muxing value s32k144
typedef enum{
    Chn0_CTS_PTC8 ,
    Chn0_CTS_PTA0 ,
    Chn0_Rx_PTA2 ,
    Chn0_Rx_PTB0 ,
    Chn0_Rx_PTC2 ,
    Chn0_Tx_PTA3 ,
    Chn0_Tx_PTB1 ,
    Chn0_Tx_PTC3 ,
    Chn1_CTS_PTA6 ,
    Chn1_CTS_PTE2 ,
    Chn1_CTS_PTE15 ,
    Chn1_Rx_PTC6 ,
    Chn1_Rx_PTC8 ,
    Chn1_Rx_PTD13 ,
    Chn1_Tx_PTC9 ,
    Chn1_Tx_PTC7 ,
    Chn1_Tx_PTD14 ,
    Chn2_CTS_PTE9 ,
    Chn2_CTS_PTD11 ,
    Chn2_CTS_PTC12 ,
    Chn2_Rx_PTD6 ,
    Chn2_Rx_PTD17 ,
    Chn2_Rx_PTA8 ,
    Chn2_Tx_PTD7 ,
    Chn2_Tx_PTE12 ,
    Chn2_Tx_PTA9 
}Chanel_Mode_Pin;
typedef enum{
    One_Stop_Bit,
    Two_Stop_Bit
}StopBit_Num;
typedef enum{
    ratio4_BOTHEDGE = 3,
    ratio5_BOTHEDGE,
    ratio6_BOTHEDGE,
    ratio7_BOTHEDGE,
    ratio8,
    ratio9,
    ratio10,
    ratio11,
    ratio12,
    ratio13,
    ratio14,
    ratio15,
    ratio16,
    ratio17,
    ratio18,
    ratio19,
    ratio20,
    ratio21,
    ratio22,
    ratio23,
    ratio24,
    ratio25,
    ratio26,
    ratio27,
    ratio28,
    ratio29,
    ratio30,
    ratio31,
    ratio32
}Oversampling_Ratio;
typedef union{
    uint32_t Register;
    struct {
       uint32_t PT : 1;
       uint32_t PE : 1;
       uint32_t ILT : 1;
       uint32_t WAKE : 1;
       uint32_t M : 1;
       uint32_t RSRC : 1;
       uint32_t DOZEEN :1; 
       uint32_t LOOPS : 1;
       uint32_t IDLECFG :3 ;
       uint32_t M7 :1 ;
       uint32_t Reserved: 2;
       uint32_t MA2IE : 1;
       uint32_t MA1IE : 1;
       uint32_t SBK : 1;
       uint32_t RWU : 1;
       uint32_t RE : 1;
       uint32_t TE : 1;
       uint32_t ILIE : 1;
       uint32_t RIE : 1;
       uint32_t TCIE : 1;
       uint32_t TIE : 1;
       uint32_t PEIE : 1;
       uint32_t FEIE : 1;
       uint32_t NEIE : 1;
       uint32_t ORIE : 1;
       uint32_t TXINV : 1;
       uint32_t TXDIR : 1;
       uint32_t R9T8 : 1;
       uint32_t R8T9 : 1;
    }Fields;
}CTRL_t;
typedef union
{
    uint32_t Register;
    struct{
        uint32_t SBR : 13;
        uint32_t SBNS : 1;
        uint32_t RXEDGIE : 1;
        uint32_t LBKDIE : 1;
        uint32_t RESYNCDIS : 1;
        uint32_t BOTHEDGE : 1;
        uint32_t MATCFG : 2;
        uint32_t RIDMAE : 1;
        uint32_t RDMAE : 1;
        uint32_t Reserved :1;
        uint32_t TDMAE : 1;
        uint32_t OSR : 5;
        uint32_t M10 : 1;
        uint32_t MAEN2 : 1;
        uint32_t MAEN1 : 1;
    }Fields;
}BAUD_t;
typedef union{
    uint32_t Register;
    struct {
        uint32_t data : 10;
        uint32_t Reserved :1;
        uint32_t IDLINE : 1;
        uint32_t RXEMPT : 1;
        uint32_t FRETSC : 1;
        uint32_t PARITYE : 1;
        uint32_t NOISY : 1;
        uint32_t Reserved0 : 16;
    }Fields;
}DATA_t;
typedef enum{
    _8BitData,
    _9BitData
}Character_Num;
typedef enum{
    Overrun_Interrupt,
    Noise_Error_Interrupt,
    Framing_Error_Interrupt,
    Parity_Error_Interrupt,
    Transmit_Interrupt,
    Transmission_Complete_Interrupt,
    Receiver_Interrupt,
    Idle_Line_Interrupt 
}LPUART_Interrupts;
typedef struct{
    volatile uint32_t VERID;
    volatile uint32_t PARAM;
    volatile uint32_t GLOBAL;
    volatile uint32_t PINCFG;
    volatile BAUD_t BAUD;
    volatile uint32_t STAT;
    volatile CTRL_t CTRL;
    volatile DATA_t DATA;
    volatile uint32_t MATCH;
    volatile uint32_t MODIR;
    volatile uint32_t FIFO;
    volatile uint32_t WATER;
}LPUART_Type;

#define LPUART0 ((LPUART_Type*)(LPUART0_BASE_ADD))
#define LPUART1 ((LPUART_Type*)(LPUART1_BASE_ADD))
#define LPUART2 ((LPUART_Type*)(LPUART2_BASE_ADD))
void Config_LPUART_Chanel(LPUART_Chanel Chanel,
Source_div2_t source,
uint16_t baud_rate_modulo_divisor,
Oversampling_Ratio oversampling_ratio,
StopBit_Num numS,
Character_Num numD,
Enable_Disable parity);
void Enable_LPUART_Interrupts(LPUART_Chanel,LPUART_Interrupts);
void Enable_LPUART_Pin(Chanel_Mode_Pin Chnn_mode_pin);
void TransmitData(LPUART_Chanel,uint16_t);
uint16_t ReceiveData(LPUART_Chanel);
void Enable_TransmitData_Chanel(LPUART_Chanel);
void Disable_TransmitData_Chanel(LPUART_Chanel);
void Enable_ReceiveData_Chanel(LPUART_Chanel);
void Disable_ReceiveData_Chanel(LPUART_Chanel);
void Send_Message(char*);
void Send_CurrentMode_Message(Mode_t);
#endif
