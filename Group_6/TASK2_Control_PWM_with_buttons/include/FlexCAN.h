#ifndef FLEX_CAN
#define FLEX_CAN
#include <stdint.h>
#define FLEXCAN0_BASE_ADDRESS 0x40024000
#define FLEXCAN1_BASE_ADDRESS 0x40025000
#define FLEXCAN2_BASE_ADDRESS 0x4002B000
#define CAN_MCR_MDIS_MASK 0x80000000u
#define CAN_CTRL1_CLKSRC_MASK 0x2000u
#define CAN_MCR_FRZACK_MASK 0x1000000u
#define CAN_MCR_FRZACK_SHIFT 24u
#define CAN_MCR_NOTRDY_MASK 0x8000000u
#define CAN_MCR_NOTRDY_SHIFT 27u
#define CAN_WMBn_CS_DLC_SHIFT 16u
#define CAN_WMBn_ID_ID_MASK 0x1FFFFFFFu
#define CAN_WMBn_ID_ID_SHIFT 0u
#define CAN_WMBn_CS_DLC_MASK 0xF0000u
typedef union
{
    uint32_t Register;
    struct
    {
        uint32_t PROPSEG;
        uint32_t LOM;
        uint32_t LBUF;
        uint32_t TSYN;
        uint32_t BOFFREC;
        uint32_t SMP;
        uint32_t Reserved[2];
        uint32_t RWRNMSK;
        uint32_t TWRNMSK;
        uint32_t LPB;
        uint32_t CLKSRC;
        uint32_t ERRMSK;
        uint32_t BOFFMSK;
        uint32_t PSEG2;
        uint32_t PSEG1;
        uint32_t RJW;
        uint32_t PRESDIV;
    } Fields;
} CTRL1_t;

typedef struct
{
    volatile uint32_t MCR;
    volatile CTRL1_t CTRL1;
    volatile uint32_t TIMER;
    uint32_t Reserved;
    volatile uint32_t RXMGMASK;
    volatile uint32_t RX14MASK;
    volatile uint32_t RX15MASK;
    volatile uint32_t ECR;
    volatile uint32_t ESR1;
    uint32_t Reserved1;
    volatile uint32_t IMASK1;
    uint32_t Reserved2;
    volatile uint32_t IFLAG1;
    volatile uint32_t CTRL2;
    volatile uint32_t ESR2;
    uint32_t Reserved3[2];
    volatile uint32_t CRCR;
    volatile uint32_t RXFGMASK;
    volatile uint32_t RXFIR;
    volatile uint32_t CBT;
    uint32_t Reserved0[11];
    volatile uint32_t RAMn[128];
    uint32_t Reserved5[384];
    volatile uint32_t RXIMRn[32];
    uint32_t Reserved4[128];
    volatile uint32_t CTRL1_PN;
    volatile uint32_t CTRL2_PN;
    volatile uint32_t WU_MTC;
    volatile uint32_t FLT_ID1;
    volatile uint32_t FLT_DLC;
    volatile uint32_t PL1_LO;
    volatile uint32_t PL1_HI;
    volatile uint32_t FLT_ID2_IDMASK;
    volatile uint32_t PL2_PLMASK_LO;
    volatile uint32_t PL2_PLMASK_HI;
    volatile uint32_t WMB0_CS;
    volatile uint32_t WMB0_ID;
    volatile uint32_t WMB0_D03;
    volatile uint32_t WMB0_D47;
    volatile uint32_t WMB1_CS;
    volatile uint32_t WMB1_ID;
    volatile uint32_t WMB1_D03;
    volatile uint32_t WMB1_D47;
    volatile uint32_t WMB2_CS;
    volatile uint32_t WMB2_ID;
    volatile uint32_t WMB2_D03;
    volatile uint32_t WMB2_D47;
    volatile uint32_t WMB3_CS;
    volatile uint32_t WMB3_ID;
    volatile uint32_t WMB3_D03;
    volatile uint32_t WMB3_D47;
    uint32_t Reserved6[32];
    volatile uint32_t FDCTRL;
    volatile uint32_t FDCBT;
    volatile uint32_t FDCRC;
} FlexCAN_type;
void FlexCAN0init(void);
void FLEXCAN0_transmit_msg(void);
void FLEXCAN0_receive_msg(void);
#define CAN0 ((FlexCAN_type *)(FLEXCAN0_BASE_ADDRESS))
#define CAN1 ((FlexCAN_type *)(FLEXCAN1_BASE_ADDRESS))
#define CAN2 ((FlexCAN_type *)(FLEXCAN2_BASE_ADDRESS))
#endif
