//
// RB_ETH.h
//

/// \file RB_ETH.h
/// Deklaration der Ethernet-Registerbänke.

#ifndef __RB_ETH_H__
# define __RB_ETH_H__

# include <RB.h>

/// Datentyp für ETH-Registerbank, s. RM0033 Reference Manual
typedef struct __regbank_ETH
{
  WORD MACCR;
  WORD MACFFR;
  WORD MACHTHR;
  WORD MACHTLR;
  WORD MACMIIAR;
  WORD MACMIIDR;
  WORD MACFCR;
  WORD MACVLANTR;
  WORD reserved00[2];
  WORD MACRWUFFR;
  WORD MACPMTCSR;
  WORD reserved01[2];
  WORD MACSR;
  WORD MACIMR;
  union {
    WORD MACA0HR;
    BYTE MACA0HRbytes[2];
  };
  union {
    WORD MACA0LR;
    BYTE MACA0LRbytes[4];
  };
  WORD MACA1HR;
  WORD MACA1LR;
  WORD MACA2HR;
  WORD MACA2LR;
  WORD MACA3HR;
  WORD MACA3LR;                 // 24
  WORD reserved02[40];
  
  WORD MMCCR;                   // 65
  WORD MMCRIR;
  WORD MMCTIR;
  WORD MMCRIMR;
  WORD MMCTIMR;                 // 69
  WORD reserved03[14];
  WORD MMCTGFSCCR;              // 84 
  WORD MMCTGFMSCCR;
  WORD reserved04[5];
  WORD MMCTGFCR;
  WORD reserved05[10];
  WORD MMCRFCECR;
  WORD MMCRFAECR;
  WORD reserved06[10];
  WORD MMCRGUFCR;
  WORD reserved07[334];
  
  WORD PTPTSCR;
  WORD PTPSSIR;
  WORD PTPTSHR;
  WORD PTPTSLR;
  WORD PTPTSHUR;
  WORD PTPTSLUR;
  WORD PTPTSAR;
  WORD PTPTTHR;
  WORD PTPTTLR;
  WORD reserved08;
  WORD PTPTSSR;                 // added for STM32F2xx
  WORD reserved09[565];
  
  WORD DMABMR;
  WORD DMATPDR;
  WORD DMARPDR;
  WORD DMARDLAR;
  WORD DMATDLAR;
  WORD DMASR;
  WORD DMAOMR;
  WORD DMAIER;
  WORD DMAMFBOCR;
  WORD DMARSWTR;                // added for STM32F2xx
  WORD reserved10[8];
  WORD DMACHTDR;
  WORD DMACHRDR;
  WORD DMACHTBAR;
  WORD DMACHRBAR;
} RegbankTypeETH;

static_assert(OFFSET_OF(RegbankTypeETH, DMABMR) == 0x1000U, "Invalid RegbankTypeETH [DMABMR]");

extern RegbankTypeETH volatile rbETH;                 ///< ETH-Registerbank.

/// \cond RB_DEFS

// MACSR

# define INDX_ETH_DMASR_NIS     16
# define MASK_ETH_DMASR_NIS     (WORD)(1U << INDX_ETH_DMASR_NIS)

# define INDX_ETH_DMASR_RS      6
# define MASK_ETH_DMASR_RS      (WORD)(1U << INDX_ETH_DMASR_RS)

# define INDX_ETH_DMASR_TS      0
# define MASK_ETH_DMASR_TS      (WORD)(1U << INDX_ETH_DMASR_TS)

// MACCR

# define INDX_ETH_MACCR_FES     14
# define MASK_ETH_MACCR_FES     (WORD)(1U << INDX_ETH_MACCR_FES)

# define INDX_ETH_MACCR_ROD     13
# define MASK_ETH_MACCR_ROD     (WORD)(1U << INDX_ETH_MACCR_ROD)

# define INDX_ETH_MACCR_DM      11
# define MASK_ETH_MACCR_DM      (WORD)(1U << INDX_ETH_MACCR_DM)

# define INDX_ETH_MACCR_TE      3
# define MASK_ETH_MACCR_TE      (WORD)(1U << INDX_ETH_MACCR_TE)

# define INDX_ETH_MACCR_RE      2
# define MASK_ETH_MACCR_RE      (WORD)(1U << INDX_ETH_MACCR_RE)

// MACMIIAR

# define INDX_ETH_MACMIIAR_MB   0                     ///< PHY-busy.
# define MASK_ETH_MACMIIAR_MB   (WORD)(0x1U << INDX_ETH_MACMIIAR_MB)

# define INDX_ETH_MACMIIAR_MW   1                     ///< PHY-write.
# define MASK_ETH_MACMIIAR_MW   (WORD)(0x1U << INDX_ETH_MACMIIAR_MW)

# define INDX_ETH_MACMIIAR_CR   2
# define MASK_ETH_MACMIIAR_CR_DIV026 (WORD)(0x3U << INDX_ETH_MACMIIAR_CR)
# define MASK_ETH_MACMIIAR_CR_DIV102 (WORD)(0x4U << INDX_ETH_MACMIIAR_CR)

# define INDX_ETH_MACMIIAR_MR   6                     ///< Position der Registernummer (0..31) des PHY
# define MASK_ETH_MACMIIAR_MR   (WORD)(0x1FU << INDX_ETH_MACMIIAR_MR)

# define INDX_ETH_MACMIIAR_PA   11                    ///< Position der PHY-Adresse (0..31)
# define MASK_ETH_MACMIIAR_PA   (WORD)(0x1FU << INDX_ETH_MACMIIAR_PA)

// MACFFR

# define INDX_ETH_MACFFR_HPF    10
# define MASK_ETH_MACFFR_HPF    (WORD)(1U << INDX_ETH_MACFFR_HPF)

# define INDX_ETH_MACFFR_HM     10
# define MASK_ETH_MACFFR_HM     (WORD)(1U << INDX_ETH_MACFFR_HM)

// DMASR

# define INDX_ETH_DMASR_RBUS    7
# define MASK_ETH_DMASR_RBUS    (WORD)(1U << INDX_ETH_DMASR_RBUS)

# define INDX_ETH_DMASR_TBUS    2
# define MASK_ETH_DMASR_TBUS    (WORD)(1U << INDX_ETH_DMASR_TBUS)

// DMAOMR

# define INDX_ETH_DMAOMR_RSF    25
# define MASK_ETH_DMAOMR_RSF    (WORD)(1U << INDX_ETH_DMAOMR_RSF)

# define INDX_ETH_DMAOMR_TSF    21
# define MASK_ETH_DMAOMR_TSF    (WORD)(1U << INDX_ETH_DMAOMR_TSF)

# define INDX_ETH_DMAOMR_ST     13
# define MASK_ETH_DMAOMR_ST     (WORD)(1U << INDX_ETH_DMAOMR_ST)

# define INDX_ETH_DMAOMR_SR     1
# define MASK_ETH_DMAOMR_SR     (WORD)(1U << INDX_ETH_DMAOMR_SR)

// DMABMR

# define INDX_ETH_DMABMR_AAB    25
# define MASK_ETH_DMABMR_AAB    (WORD)(1U << INDX_ETH_DMABMR_AAB)

# define INDX_ETH_DMABMR_USP    23
# define MASK_ETH_DMABMR_USP    (WORD)(1U << INDX_ETH_DMABMR_USP)

# define INDX_ETH_DMABMR_RDP    17
# define MASK_ETH_DMABMR_RDP_01 (WORD)(0x01U << INDX_ETH_DMABMR_RDP)
# define MASK_ETH_DMABMR_RDP_02 (WORD)(0x02U << INDX_ETH_DMABMR_RDP)
# define MASK_ETH_DMABMR_RDP_04 (WORD)(0x04U << INDX_ETH_DMABMR_RDP)
# define MASK_ETH_DMABMR_RDP_08 (WORD)(0x08U << INDX_ETH_DMABMR_RDP)

# define INDX_ETH_DMABMR_PM     14
# define MASK_ETH_DMABMR_PM_1_1 (WORD)(0x0U << INDX_ETH_DMABMR_PM)
# define MASK_ETH_DMABMR_PM_2_1 (WORD)(0x1U << INDX_ETH_DMABMR_PM)
# define MASK_ETH_DMABMR_PM_3_1 (WORD)(0x2U << INDX_ETH_DMABMR_PM)
# define MASK_ETH_DMABMR_PM_4_1 (WORD)(0x3U << INDX_ETH_DMABMR_PM)

# define INDX_ETH_DMABMR_BPL    8
# define MASK_ETH_DMABMR_BPL_01 (WORD)(0x01U << INDX_ETH_DMABMR_BPL)
# define MASK_ETH_DMABMR_BPL_02 (WORD)(0x02U << INDX_ETH_DMABMR_BPL)
# define MASK_ETH_DMABMR_BPL_04 (WORD)(0x04U << INDX_ETH_DMABMR_BPL)
# define MASK_ETH_DMABMR_BPL_08 (WORD)(0x08U << INDX_ETH_DMABMR_BPL)

# define INDX_ETH_DMABMR_EDFE   7
# define MASK_ETH_DMABMR_EDFE   (WORD)(1U << INDX_ETH_DMABMR_EDFE)

# define INDX_ETH_DMABMR_SR     0
# define MASK_ETH_DMABMR_SR     (WORD)(1U << INDX_ETH_DMABMR_SR)

// DMAIER

# define INDX_ETH_DMAIER_NISE   16
# define MASK_ETH_DMAIER_NISE   (WORD)(1U << INDX_ETH_DMAIER_NISE)

# define INDX_ETH_DMAIER_AISE   15
# define MASK_ETH_DMAIER_AISE   (WORD)(1U << INDX_ETH_DMAIER_AISE)

# define INDX_ETH_DMAIER_FBEIE  13
# define MASK_ETH_DMAIER_FBEIE  (WORD)(1U << INDX_ETH_DMAIER_FBEIE)

# define INDX_ETH_DMAIER_RIE    6
# define MASK_ETH_DMAIER_RIE    (WORD)(1U << INDX_ETH_DMAIER_RIE)

# define INDX_ETH_DMAIER_TPSIS  1
# define MASK_ETH_DMAIER_TPSIS  (WORD)(1U << INDX_ETH_DMAIER_TPSIS)

# define INDX_ETH_DMAIER_TIE    0
# define MASK_ETH_DMAIER_TIE    (WORD)(1U << INDX_ETH_DMAIER_TIE)

/// \endcond 

typedef struct __TxDmaStruct TxDmaDescrType;

struct __TxDmaStruct
{
  WORD tdescr0;
  struct {
    HWRD tbs1 : 13;
    HWRD res1 :  3;
    HWRD zero;
  };
  BYTE * buffer;
  TxDmaDescrType volatile * next;
  WORD tdescr4;
  WORD tdescr5;
  WORD tdescr6;
  WORD tdescr7;
};

constexpr WORD const tdescr0OWN = 0x80000000U;
constexpr WORD const tdescr0IC  = 0x40000000U;
constexpr WORD const tdescr0LS  = 0x20000000U;
constexpr WORD const tdescr0FS  = 0x10000000U;
constexpr WORD const tdescr0TCH = 0x00100000U;

typedef struct __RxDmaStruct RxDmaDescrType;

struct __RxDmaStruct
{
  WORD rdescr0;
  struct {
    HWRD rbs1 : 13;
    HWRD res1 :  1;
    HWRD ctrl :  2;
    HWRD zero;
  };
  BYTE * buffer;
  RxDmaDescrType volatile * next;
  WORD extStat;
  WORD rdescr5;
  WORD rdescr6;
  WORD rdescr7;
};

constexpr WORD const rdescr0OWN = 0x80000000U;
constexpr WORD const rdescr0FL  = 0x3FFF0000U;
constexpr WORD const rdescr0ES  = 0x00008000U;
constexpr WORD const rdescr0FS  = 0x00000200U;
constexpr WORD const rdescr0LS  = 0x00000100U;

#endif

