#include "LPSPI_Type.h"
#include "PCC_Type.h"
#include "PORT_Type.h"
static LPSPI_Type *Chanel[3] = {LPSPI0, LPSPI1, LPSPI2};
void Config_LPSPI_Chanel
(
    LPSPI_Chanel chanel,  
    Source source,
    PRESCALE_devide div,
    CPOL cpol,
    CPHA cpha,
    Framesz8_minus1 Framesz8_31_minus1,
    Peripheral_chip_select pcs,
    SCKDivider_plus2 SCK_Divider_plus2,
    LPSPI_mode mode
)
{
    TCR_t temp;
    if (mode == Master)
    {
        temp.Register = SET_BIT(temp.Register, 19);
    }
    else
    {
        temp.Register = SET_BIT(temp.Register, 18);
    }
    PCC_LPSPI_ClockSource(chanel, source);
    temp.Fields.PRESCALE = div;
    temp.Fields.CPOL = cpol;
    temp.Fields.CPHA = cpha;
    temp.Fields.FRAMESZ = Framesz8_31_minus1;
    temp.Fields.PCS = pcs;
    Chanel[chanel]->TCR.Register = temp.Register;
    Chanel[chanel]->CCR.Fields.SCKDIV = SCK_Divider_plus2;
    Chanel[chanel]->CR = SET_BIT(Chanel[chanel]->CR, 3);
    Chanel[chanel]->CFGR1.Fields.MASTER = mode;
    Chanel[chanel]->CR = SET_BIT(Chanel[chanel]->CR, 0);
}

void Config_LPSPI_Interrupt(LPSPI_Chanel chanel, LPSPI_Interrupt intr)
{
    switch (intr)
    {
    case Transmit_Data_Interrupt:
        Chanel[chanel]->IER.Fields.TDIE = Enable;
        break;
    case Receive_Data_Interrupt:
        Chanel[chanel]->IER.Fields.RDIE = Enable;
        break;
    case Word_Complete_Interrupt:
        Chanel[chanel]->IER.Fields.WCIE = Enable;
        break;
    case Frame_Complete_Interrupt:
        Chanel[chanel]->IER.Fields.FCIE = Enable;
        break;
    case Transfer_Complete_Interrupt:
        Chanel[chanel]->IER.Fields.TCIE = Enable;
        break;
    case Transmit_Error_Interrupt:
        Chanel[chanel]->IER.Fields.TEIE = Enable;
        break;
    case Receive_Error_Interrupt:
        Chanel[chanel]->IER.Fields.REIE = Enable;
        break;
    case Data_Match_Interrupt:
        Chanel[chanel]->IER.Fields.DMIE = Enable;
        break;
    }
}

void Enable_LPSPI_Pin(LPSPT_Chanel_Mode_Pin c_m_p)
{
    switch (c_m_p)
    {
    case LPSPI0_PCS0_PTB0:
        PCC->PCC_PORTB |= 1 << 30;
        PORTB->PORT_PCR[0].Fields.MUX = 3;
        break;
    case LPSPI0_PCS0_PTB5:
        PCC->PCC_PORTB |= 1 << 30;
        PORTB->PORT_PCR[5].Fields.MUX = 4;
        break;
    case LPSPI0_SCK_PTB2:
        PCC->PCC_PORTB |= 1 << 30;
        PORTB->PORT_PCR[2].Fields.MUX = 3;
        break;
    case LPSPI0_SCK_PTE0:
        PCC->PCC_PORTE |= 1 << 30;
        PORTE->PORT_PCR[0].Fields.MUX = 2;
        break;
    case LPSPI0_SCK_PTD15:
        PCC->PCC_PORTD |= 1 << 30;
        PORTD->PORT_PCR[15].Fields.MUX = 4;
        break;
    case LPSPI0_SIN_PTE1:
        PCC->PCC_PORTE |= 1 << 30;
        PORTE->PORT_PCR[1].Fields.MUX = 2;
        break;
    case LPSPI0_SIN_PTB3:
        PCC->PCC_PORTB |= 1 << 30;
        PORTB->PORT_PCR[3].Fields.MUX = 3;
        break;
    case LPSPI0_SIN_PTD16:
        PCC->PCC_PORTD |= 1 << 30;
        PORTD->PORT_PCR[16].Fields.MUX = 4;
        break;
    case LPSPI0_SOUT_PTE2:
        PCC->PCC_PORTE |= 1 << 30;
        PORTE->PORT_PCR[2].Fields.MUX = 2;
        break;
    case LPSPI0_SOUT_PTB4:
        PCC->PCC_PORTB |= 1 << 30;
        PORTB->PORT_PCR[4].Fields.MUX = 3;
        break;
    case LPSPI0_SOUT_PTB1:
        PCC->PCC_PORTB |= 1 << 30;
        PORTB->PORT_PCR[1].Fields.MUX = 3;
        break;
    case LPSPI1_PCS0_PTD3:
        PCC->PCC_PORTD |= 1 << 30;
        PORTD->PORT_PCR[3].Fields.MUX = 3;
        break;
    case LPSPI1_PCS0_PTE1:
        PCC->PCC_PORTE |= 1 << 30;
        PORTE->PORT_PCR[1].Fields.MUX = 5;
        break;
    case LPSPI1_SCK_PTD0:
        PCC->PCC_PORTD |= 1 << 30;
        PORTD->PORT_PCR[0].Fields.MUX = 3;
        break;
    case LPSPI1_SCK_PTB14:
        PCC->PCC_PORTB |= 1 << 30;
        PORTB->PORT_PCR[14].Fields.MUX = 3;
        break;
    case LPSPI1_SIN_PTB15:
        PCC->PCC_PORTB |= 1 << 30;
        PORTB->PORT_PCR[15].Fields.MUX = 3;
        break;
    case LPSPI1_SIN_PTD1:
        PCC->PCC_PORTD |= 1 << 30;
        PORTD->PORT_PCR[1].Fields.MUX = 3;
        break;
    case LPSPI1_SOUT_PTD2:
        PCC->PCC_PORTD |= 1 << 30;
        PORTD->PORT_PCR[2].Fields.MUX = 3;
        break;
    case LPSPI1_SOUT_PTB16:
        PCC->PCC_PORTB |= 1 << 30;
        PORTB->PORT_PCR[16].Fields.MUX = 3;
        break;
    case LPSPI1_SOUT_PTE0:
        PCC->PCC_PORTE |= 1 << 30;
        PORTE->PORT_PCR[0].Fields.MUX = 5;
        break;
    case LPSPI2_PCS0_PTA9:
        PCC->PCC_PORTA |= 1 << 30;
        PORTA->PORT_PCR[9].Fields.MUX = 3;
        break;
    case LPSPI2_PCS0_PTC14:
        PCC->PCC_PORTC |= 1 << 30;
        PORTC->PORT_PCR[14].Fields.MUX = 3;
        break;
    case LPSPI2_PCS0_PTE11:
        PCC->PCC_PORTE |= 1 << 30;
        PORTE->PORT_PCR[11].Fields.MUX = 2;
        break;
    case LPSPI2_SCK_PTE15:
        PCC->PCC_PORTE |= 1 << 30;
        PORTE->PORT_PCR[15].Fields.MUX = 3;
        break;
    case LPSPI2_SCK_PTC15:
        PCC->PCC_PORTC |= 1 << 30;
        PORTC->PORT_PCR[15].Fields.MUX = 3;
        break;
    case LPSPI2_SIN_PTE16:
        PCC->PCC_PORTE |= 1 << 30;
        PORTE->PORT_PCR[16].Fields.MUX = 3;
        break;
    case LPSPI2_SIN_PTC0:
        PCC->PCC_PORTC |= 1 << 30;
        PORTC->PORT_PCR[0].Fields.MUX = 3;
        break;
    case LPSPI2_SOUT_PTA8:
        PCC->PCC_PORTA |= 1 << 30;
        PORTA->PORT_PCR[8].Fields.MUX = 3;
        break;
    case LPSPI2_SOUT_PTC1:
        PCC->PCC_PORTC |= 1 << 30;
        PORTC->PORT_PCR[1].Fields.MUX = 3;
        break;
    }
}
