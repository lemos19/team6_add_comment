#include "FlexCAN.h"
#include "PCC_Type.h"

uint32_t RxCODE;      /*< Received message buffer code 			*/
uint32_t RxID;        /*< Received message ID 					*/
uint32_t RxLENGTH;    /*< Recieved message number of data bytes 	*/
uint32_t RxDATA[2];   /*< Received message data (2 words) 		*/
uint32_t RxTIMESTAMP; /*< Received message time*/

void FlexCAN0init(void)
{
#define MSG_BUF_SIZE 4
    uint32_t i;
    PCC->PCC_FlexCAN0 = 1u << CGC_SHIFT;
    CAN0->MCR |= CAN_MCR_MDIS_MASK;
    CAN0->CTRL1.Register &= ~CAN_CTRL1_CLKSRC_MASK;
    CAN0->MCR &= ~CAN_MCR_MDIS_MASK;

    while (!((CAN0->MCR & CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT))
    {
    }
    CAN0->CTRL1.Register = 0;
    CAN0->CTRL1.Fields.PSEG2 = 3;
    CAN0->CTRL1.Fields.PSEG1 = 3;
    CAN0->CTRL1.Fields.PROPSEG = 6;
    CAN0->CTRL1.Fields.RJW = 3;
    CAN0->CTRL1.Fields.SMP = 1;
    for (i = 0; i < 128; i++)
    {
        CAN0->RAMn[i] = 0;
    }
    for (i = 0; i < 16; i++)
    {
        CAN0->RXIMRn[i] = 0xFFFFFFFF;
    }
    CAN0->RXMGMASK = 0x1FFFFFFF;

    CAN0->RAMn[4 * MSG_BUF_SIZE + 0] = 0x04000000; /* Msg Buf 4, word 0: Enable for reception 	*/
                                                   /* EDL,BRS,ESI=0: CANFD not used 				*/
                                                   /* CODE=4: MB set to RX inactive 				*/
                                                   /* IDE=0: Standard ID 							*/
                                                   /* SRR, RTR, TIME STAMP = 0: not applicable 	*/
                                                   /* Node A receives msg with std ID 0x511 		*/
    CAN0->RAMn[4 * MSG_BUF_SIZE + 1] = 0x14440000; /* Msg Buf 4, word 1: Standard ID = 0x111 		*/

    CAN0->MCR = 0x0000001F;
    while ((CAN0->MCR && CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT)
    {
    }
    while ((CAN0->MCR && CAN_MCR_NOTRDY_MASK) >> CAN_MCR_NOTRDY_SHIFT)
    {
    }
}
void FLEXCAN0_transmit_msg(void)
{
    CAN0->IFLAG1 = 0x00000001;                     /* Clear CAN 0 MB 0 flag without clearing others*/
    CAN0->RAMn[0 * MSG_BUF_SIZE + 2] = 0xA5112233; /* MB0 word 2: data word 0 */
    CAN0->RAMn[0 * MSG_BUF_SIZE + 3] = 0x44556677; /* MB0 word 3: data word 1 */
    CAN0->RAMn[0 * MSG_BUF_SIZE + 1] = 0x15540000; /* MB0 word 1: Tx msg with STD ID 0x555 */
    CAN0->RAMn[0 * MSG_BUF_SIZE + 0] = 0x0C400000 | 8 << CAN_WMBn_CS_DLC_SHIFT;
                                                    /* MB0 word 0: 								    */
                                                    /* EDL,BRS,ESI=0: CANFD not used 				*/
                                                    /* CODE=0xC: Activate msg buf to transmit 		*/
                                                    /* IDE=0: Standard ID 							*/
                                                    /* SRR=1 Tx frame (not req'd for std ID) 		*/
                                                    /* RTR = 0: data, not remote tx request frame	*/
                                                    /* DLC = 8 bytes 								*/
}
void FLEXCAN0_receive_msg(void)
{
    /*! Receive msg from ID 0x556 using msg buffer 4
     * =============================================
     */
    uint8_t datalength;
    uint32_t dummy;

    RxCODE = (CAN0->RAMn[4 * MSG_BUF_SIZE + 0] & 0x07000000) >> 24;                                /* Read CODE field */
    RxID = (CAN0->RAMn[4 * MSG_BUF_SIZE + 1] & CAN_WMBn_ID_ID_MASK) >> CAN_WMBn_ID_ID_SHIFT;       /* Read ID 			*/
    RxLENGTH = (CAN0->RAMn[4 * MSG_BUF_SIZE + 0] & CAN_WMBn_CS_DLC_MASK) >> CAN_WMBn_CS_DLC_SHIFT; /* Read Message Length */

    for (datalength = 0; datalength < 2; datalength++)
    { /* Read two words of data (8 bytes) */
        RxDATA[datalength] = CAN0->RAMn[4 * MSG_BUF_SIZE + 2 + datalength];
    }
    RxTIMESTAMP = (CAN0->RAMn[0 * MSG_BUF_SIZE + 0] & 0x000FFFF);
    dummy = CAN0->TIMER;       /* Read TIMER to unlock message buffers */
    CAN0->IFLAG1 = 0x00000010; /* Clear CAN 0 MB 4 flag without clearing others*/
}