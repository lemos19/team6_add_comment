/******************************************************************************
 * Project Name: FRESHER ASSIGNMENT
 * File Name: LPUART.c
 *
 * Description: Implementation of the NVIC module
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

 /**
  *   @file       LPUART_Type.h
  *   @version    V0.1
  *   @brief      V0.1 LPUART Driver
  *   @addtogroup LPUART_driver
  */

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "LPUART.h"
#include "PORT_Type.h"
#include "PCC_Type.h"
#include "General.h"
#include "string.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/


/******************************************************************************
 *  EXTERN
 *****************************************************************************/


/******************************************************************************
 *  LOCAL TYPEDEFS
 *****************************************************************************/


/******************************************************************************
 *  LOCAL CONSTANTS
 *****************************************************************************/


/******************************************************************************
 *  LOCAL VARIABLES
 *****************************************************************************/
/**
 * @brief  this is pointer to call LPUART channel
 */
static LPUART_Type* CHANEL[3] = { LPUART0,LPUART1,LPUART2 };
/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/


/******************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *****************************************************************************/

/******************************************************************************
 *  LOCAL FUNCTION
 ******************************************************************************/

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/

/**
 *   @brief      This funciton to send message by UART
 *
 *   @param[in]  char				mess
 *
 *   @return     Void               None
 *
 *   @note       Init LPUART before call this function.
 *
*/
void Send_Message(char* mess){
    Enable_TransmitData_Chanel(CHN1);
	while ((*mess)!='\0'){
		TransmitData(CHN1,(*mess));
        mess++;
	}
	Disable_TransmitData_Chanel(CHN1);
}

/**
 *   @brief      This funciton config LPUART channel module
 *
 *   @param[in]  LPUART_Chanel          Chanel
 *   @param[in]  Source                 source
 *   @param[in]  uint16_t               baud_rate_modulo_divisor
 *   @param[in]  Oversampling_Ratio		oversampling_ratio
 *   @param[in]  StopBit_Num		    numS
 *   @param[in]  Character_Num		    numD
 *   @param[in]  Enable_Disable		    parity
 *
 *   @return     Void                   None
 *
 *   @note       Enable PCC_LPUART before call this function.
 *
*/
void Config_LPUART_Chanel(LPUART_Chanel Chanel,
Source source,
uint16_t baud_rate_modulo_divisor,
Oversampling_Ratio oversampling_ratio,
StopBit_Num numS,
Character_Num numD,
Enable_Disable parity){
    PCC_LPUART_ClockSource(Chanel,source);
    CHANEL[Chanel]->BAUD.Fields.SBR = baud_rate_modulo_divisor;
    CHANEL[Chanel]->BAUD.Fields.OSR = oversampling_ratio;
    CHANEL[Chanel]->BAUD.Fields.SBNS = numS;
    CHANEL[Chanel]->CTRL.Fields.M = numD;
    CHANEL[Chanel]->CTRL.Fields.PE = parity;
}

/**
 *   @brief      This funciton to enable LPUART Interrupt module
 *
 *   @param[in]  LPUART_Chanel				ch
 *   @param[in]  LPUART_Interrupts		    in
 *
 *   @return     Void                       None
 *
 *   @note       Init NVIC interrupt before call this function.
 *
*/
void Enable_LPUART_Interrupts(LPUART_Chanel ch,LPUART_Interrupts in){
    if (in == Overrun_Interrupt){
       CHANEL[ch]->CTRL.Fields.ORIE = Enable;
    }
    else if (in == Noise_Error_Interrupt){
        CHANEL[ch]->CTRL.Fields.NEIE = Enable;
    }
    else if (in == Framing_Error_Interrupt){
        CHANEL[ch]->CTRL.Fields.FEIE = Enable;
    }
    else if (in == Parity_Error_Interrupt){
        CHANEL[ch]->CTRL.Fields.PEIE = Enable;
    }
    else if (in == Transmit_Interrupt){
        CHANEL[ch]->CTRL.Fields.TIE = Enable;
    }
    else if (in == Transmission_Complete_Interrupt){
        CHANEL[ch]->CTRL.Fields.TCIE = Enable;
    }
    else if (in == Receiver_Interrupt){
        CHANEL[ch]->CTRL.Fields.RIE = Enable;
    }
    else if (in == Idle_Line_Interrupt){
        CHANEL[ch]->CTRL.Fields.ILIE = Enable;
    }
    else{}
}

/**
 *   @brief      This funciton enable transmit bit channel
 *
 *   @param[in]  LPUART_Chanel      chanel
 *
 *   @return     Void               None
 *
 *   @note       This function is called in Send_Message function.
 *
*/
void Enable_TransmitData_Chanel(LPUART_Chanel chanel){
    CHANEL[chanel]->CTRL.Fields.TE= Enable;
}

/**
 *   @brief      This funciton disable transmit bit channel
 *
 *   @param[in]  LPUART_Chanel      chanel
 *
 *   @return     Void               None
 *
 *   @note        This function is called in Send_Message function.
 *
*/
void Disable_TransmitData_Chanel(LPUART_Chanel chanel){
    CHANEL[chanel]->CTRL.Fields.TE= Disable;
}

/**
 *   @brief      This funciton enable receive bit channel
 *
 *   @param[in]  LPUART_Chanel      chanel
 *
 *   @return     Void               None
 *
 *   @note       None.
 *
*/
void Enable_ReceiveData_Chanel(LPUART_Chanel chanel){
    CHANEL[chanel]->CTRL.Fields.RE=Enable;
}

/**
 *   @brief      This funciton disable receive bit channel
 *
 *   @param[in]  LPUART_Chanel      chanel
 *
 *   @return     Void               None
 *
 *   @note       None.
 *
*/
void Disable_ReceiveData_Chanel(LPUART_Chanel chanel){
    CHANEL[chanel]->CTRL.Fields.RE=Disable;
}

/**
 *   @brief      This funciton transmit data by LPUART
 *
 *   @param[in]  LPUART_Chanel      chanel
 *   @param[in]  uint16_t           data
 *
 *   @return     Void               None
 *
 *   @note       This is called in Send_Message function.
 *
*/
void TransmitData(LPUART_Chanel chanel,uint16_t data){
    while (!(GET_STATE(CHANEL[chanel]->STAT,23))){}
    CHANEL[chanel]->DATA.Fields.data = data;
}

/**
 *   @brief      This funciton receive data by LPUART
 *
 *   @param[in]  LPUART_Chanel      chanel
 *
 *   @return     uint16_t           ReceiData
 *
 *   @note       None.
 *
*/
uint16_t ReceiveData(LPUART_Chanel chanel){
    return CHANEL[chanel]->DATA.Fields.data;
}

/**
 *   @brief      This funciton config GPIO pin mode (MUX)
 *
 *   @param[in]  Chanel_Mode_Pin    Chnn_mode_pin
 *
 *   @return     Void               None
 *
 *   @note       None.
 *
*/
void Enable_LPUART_Pin(Chanel_Mode_Pin Chnn_mode_pin){
    switch (Chnn_mode_pin){
    case Chn0_CTS_PTC8:
        PCC->PCC_PORTC |= 1<<30;
        PORTC->PORT_PCR[8].Fields.MUX = 6;
        break;
    case Chn0_CTS_PTA0:
        PCC->PCC_PORTA |= 1<<30;
        PORTA->PORT_PCR[0].Fields.MUX = 6;
        break;
    case Chn0_Rx_PTA2:
        PCC->PCC_PORTA |= 1<<30;
        PORTA->PORT_PCR[2].Fields.MUX = 6;
        break;    
    case Chn0_Rx_PTB0:
        PCC->PCC_PORTB |= 1<<30;
        PORTB->PORT_PCR[0].Fields.MUX = 2;
        break;    
    case Chn0_Rx_PTC2:
        PCC->PCC_PORTC |= 1<<30;
        PORTC->PORT_PCR[2].Fields.MUX = 4;
        break;    
    case Chn0_Tx_PTA3:
        PCC->PCC_PORTA |= 1<<30;
        PORTA->PORT_PCR[3].Fields.MUX = 6;
        break;    
    case Chn0_Tx_PTB1:
        PCC->PCC_PORTB |= 1<<30;
        PORTB->PORT_PCR[1].Fields.MUX = 2;
        break;    
    case Chn0_Tx_PTC3:
        PCC->PCC_PORTC |= 1<<30;
        PORTC->PORT_PCR[3].Fields.MUX = 4;
        break;    
    case Chn1_CTS_PTA6:
        PCC->PCC_PORTA |= 1<<30;
        PORTA->PORT_PCR[6].Fields.MUX = 6;
        break;    
    case Chn1_CTS_PTE2:
        PCC->PCC_PORTE |= 1<<30;
        PORTE->PORT_PCR[2].Fields.MUX = 6;
        break;    
    case Chn1_CTS_PTE15:
        PCC->PCC_PORTE |= 1<<30;
        PORTE->PORT_PCR[15].Fields.MUX = 2;
        break;    
    case Chn1_Rx_PTC6:
        PCC->PCC_PORTC |= 1<<30;
        PORTC->PORT_PCR[6].Fields.MUX = 2;
        break;    
    case Chn1_Rx_PTC8:
        PCC->PCC_PORTC |= 1<<30;
        PORTC->PORT_PCR[8].Fields.MUX = 2;
        break;    
    case Chn1_Rx_PTD13:
        PCC->PCC_PORTD |= 1<<30;
        PORTD->PORT_PCR[13].Fields.MUX = 3;
        break;    
    case Chn1_Tx_PTC9:
        PCC->PCC_PORTC |= 1<<30;
        PORTC->PORT_PCR[9].Fields.MUX = 2;
        break;    
    case Chn1_Tx_PTC7:
        PCC->PCC_PORTC |= 1<<30;
        PORTC->PORT_PCR[7].Fields.MUX = 2;
        break;    
    case Chn1_Tx_PTD14:
        PCC->PCC_PORTD |= 1<<30;
        PORTD->PORT_PCR[14].Fields.MUX = 3;
        break;    
    case Chn2_CTS_PTE9:
        PCC->PCC_PORTE |= 1<<30;
        PORTE->PORT_PCR[9].Fields.MUX = 3;
        break;    
    case Chn2_CTS_PTD11:
        PCC->PCC_PORTD |= 1<<30;
        PORTD->PORT_PCR[11].Fields.MUX = 6;
        break;    
    case Chn2_CTS_PTC12:
        PCC->PCC_PORTC |= 1<<30;
        PORTC->PORT_PCR[12].Fields.MUX = 4;
        break;    
    case Chn2_Rx_PTD6:
        PCC->PCC_PORTD |= 1<<30;
        PORTD->PORT_PCR[6].Fields.MUX = 2;
        break;    
    case Chn2_Rx_PTD17:
        PCC->PCC_PORTD |= 1<<30;
        PORTD->PORT_PCR[17].Fields.MUX = 3;
        break;    
    case Chn2_Rx_PTA8:
        PCC->PCC_PORTA |= 1<<30;
        PORTA->PORT_PCR[8].Fields.MUX = 2;
        break;    
    case Chn2_Tx_PTD7:
        PCC->PCC_PORTD |= 1<<30;
        PORTD->PORT_PCR[7].Fields.MUX = 2;
        break;    
    case Chn2_Tx_PTE12:
        PCC->PCC_PORTE |= 1<<30;
        PORTE->PORT_PCR[12].Fields.MUX = 3;
        break;        
    case Chn2_Tx_PTA9:
        PCC->PCC_PORTA |= 1<<30;
        PORTA->PORT_PCR[9].Fields.MUX = 2;
        break;    
    }
}
    
