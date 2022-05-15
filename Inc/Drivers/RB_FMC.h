//
// RB_FMC.h
//

#ifndef guard_RB_FMC_H
# define guard_RB_FMC_H

/// \file RB_FMC.h
/// Flexible memory controller (FMC).

# include <RB.h>

/// Datentyp für FMC-Registerbank.
typedef struct __regbank_FMC
{
  struct {
    WORD BCR;                   ///< SRAM/NOR-Flash control registers.
    WORD BTR;                   ///< SRAM/NOR-Flash timing registers.
  } bankArr[4];
  BYTE reserved0[0x60 - sizeof(bankArr)];

  WORD PCR2;
  WORD SR2;
  BYTE reserved1[0x20 - sizeof(PCR2) - sizeof(SR2)];

  WORD PCR3;
  WORD SR3;
  BYTE reserved2[0x20 - sizeof(PCR3) - sizeof(SR3)];

  WORD PCR4;
  WORD SR4;
  BYTE reserved3[0x20 - sizeof(PCR3) - sizeof(SR4) + 0x80];

  WORD SDCR1;                   ///< SDRAM control register 1.
  WORD SDCR2;                   ///< SDRAM control register 2.
  WORD SDTR1;                   ///< SDRAM timing register 1.
  WORD SDTR2;                   ///< SDRAM timing register 2.
  WORD SDCMR;                   ///< SDRAM command mode register.
  WORD SDRTR;                   ///< SDRAM refresh timer register.
  WORD SDSR;                    ///< SDRAM status register.
} RegbankTypeFMC;

static_assert(offsetof(RegbankTypeFMC, PCR2 ) == 0x060, "Invalid RegbankTypeFMC [PCR2]");
static_assert(offsetof(RegbankTypeFMC, PCR3 ) == 0x080, "Invalid RegbankTypeFMC [PCR3]");
static_assert(offsetof(RegbankTypeFMC, PCR4 ) == 0x0A0, "Invalid RegbankTypeFMC [PCR4]");

static_assert(offsetof(RegbankTypeFMC, SDCR1) == 0x140, "Invalid RegbankTypeFMC [SDCR1]");
static_assert(offsetof(RegbankTypeFMC, SDCR2) == 0x144, "Invalid RegbankTypeFMC [SDCR2]");
static_assert(offsetof(RegbankTypeFMC, SDCMR) == 0x150, "Invalid RegbankTypeFMC [SDCMR]");
static_assert(offsetof(RegbankTypeFMC, SDRTR) == 0x154, "Invalid RegbankTypeFMC [SDRTR]");
static_assert(offsetof(RegbankTypeFMC, SDSR ) == 0x158, "Invalid RegbankTypeFMC [SDSR]");

extern RegbankTypeFMC volatile rbFMC;                 ///< FMC-Registerbank.

inline bool CheckFMC_SDSR(WORD const argMask)
{
  return (rbFMC.SDSR & argMask) != 0U;
}

/// \cond RB_DEFS

// BCR

# define INDX_FSMC_BCR_MBKEN    0
# define MASK_FSMC_BCR_MBKEN    (WORD)REG_BITMASK(FSMC_BCR_MBKEN)

# define INDX_FSMC_BCR_MTYP     2
# define MASK_FSMC_BCR_MTYP     (WORD)(3U << INDX_FSMC_BCR_MTYP)
# define MASK_FSMC_BCR_MTYP_SRAM (WORD)(0U << INDX_FSMC_BCR_MTYP)
# define MASK_FSMC_BCR_MTYP_PSRAM (WORD)(1U << INDX_FSMC_BCR_MTYP)
# define MASK_FSMC_BCR_MTYP_NOR (WORD)(2U << INDX_FSMC_BCR_MTYP)

# define INDX_FSMC_BCR_MWID     4
# define MASK_FSMC_BCR_MWID     (WORD)(3U << INDX_FSMC_BCR_MWID)
# define MASK_FSMC_BCR_MWID_BYTE (WORD)(0U << INDX_FSMC_BCR_MWID)
# define MASK_FSMC_BCR_MWID_HWRD (WORD)(1U << INDX_FSMC_BCR_MWID)

# define INDX_FSMC_BCR_WREN     12
# define MASK_FSMC_BCR_WREN     (WORD)REG_BITMASK(FSMC_BCR_WREN)

# define INDX_FSMC_BCR_WAITEN   13
# define MASK_FSMC_BCR_WAITEN   (WORD)REG_BITMASK(FSMC_BCR_WAITEN)

# define INDX_FSMC_BCR_ASYNCWAIT 15
# define MASK_FSMC_BCR_ASYNCWAIT (WORD)REG_BITMASK(FSMC_BCR_ASYNCWAIT)

// BTR

# define INDX_FSMC_BTR_ADDSET   0
# define MASK_FSMC_BTR_ADDSET   (WORD)(0x0FU << INDX_FSMC_BTR_ADDSET)

# define INDX_FSMC_BTR_DATAST   8
# define MASK_FSMC_BTR_DATAST   (WORD)(0xFFU << INDX_FSMC_BTR_DATAST)

// SDSR

# define INDX_FMC_SDSR_BUSY     5
# define MASK_FMC_SDSR_BUSY     (WORD)REG_BITMASK(FMC_SDSR_BUSY)

// SDCMR

# define MASK_FMC_CMR_MODE      0x7U
# define MASK_FMC_CMR_MODE_NORMAL_MODE 0x0U
# define MASK_FMC_CMR_MODE_CLK_CFG_ENABLE 0x1U
# define MASK_FMC_CMR_MODE_PALL 0x2U
# define MASK_FMC_CMR_MODE_AUTO_REFRESH 0x3U
# define MASK_FMC_CMR_MODE_LOAD_MODE 0x4U
# define MASK_FMC_CMR_MODE_SELF_REFRESH 0x5U
# define MASK_FMC_CMR_MODE_POWER_DOWN 0x6U

# define INDX_FMC_SDCMR_CTB2    3
# define MASK_FMC_SDCMR_CTB2    (WORD)REG_BITMASK(FMC_SDCMR_CTB2)

# define INDX_FMC_SDCMR_CTB1    4
# define MASK_FMC_SDCMR_CTB1    (WORD)REG_BITMASK(FMC_SDCMR_CTB1)

# define INDX_FMC_SDCMR_NRFS    5

# define INDX_FMC_SDCMR_MRD     9

// SDCRx

# define INDX_FMC_SDCRx_NC      0
# define MASK_FMC_SDCRx_NC_08   (WORD)(0U << INDX_FMC_SDCRx_NC)
# define MASK_FMC_SDCRx_NC_09   (WORD)(1U << INDX_FMC_SDCRx_NC)
# define MASK_FMC_SDCRx_NC_10   (WORD)(2U << INDX_FMC_SDCRx_NC)
# define MASK_FMC_SDCRx_NC_11   (WORD)(3U << INDX_FMC_SDCRx_NC)

# define INDX_FMC_SDCRx_NR      2
# define MASK_FMC_SDCRx_NR_11   (WORD)(0U << INDX_FMC_SDCRx_NR)
# define MASK_FMC_SDCRx_NR_12   (WORD)(1U << INDX_FMC_SDCRx_NR)
# define MASK_FMC_SDCRx_NR_13   (WORD)(1U << INDX_FMC_SDCRx_NR)

# define INDX_FMC_SDCRx_MWID    4
# define MASK_FMC_SDCRx_MWID_08 (WORD)(0U << INDX_FMC_SDCRx_MWID)
# define MASK_FMC_SDCRx_MWID_16 (WORD)(1U << INDX_FMC_SDCRx_MWID)
# define MASK_FMC_SDCRx_MWID_32 (WORD)(2U << INDX_FMC_SDCRx_MWID)

# define INDX_FMC_SDCRx_NB      6
# define MASK_FMC_SDCRx_NB      (WORD)REG_BITMASK(FMC_SDCRx_NB)

# define INDX_FMC_SDCRx_CAS     7
# define MASK_FMC_SDCRx_CAS_1   (WORD)(1U << INDX_FMC_SDCRx_CAS)
# define MASK_FMC_SDCRx_CAS_2   (WORD)(2U << INDX_FMC_SDCRx_CAS)
# define MASK_FMC_SDCRx_CAS_3   (WORD)(3U << INDX_FMC_SDCRx_CAS)

# define INDX_FMC_SDCRx_SDCLK   10
# define MASK_FMC_SDCRx_SDCLK   (WORD)(3U << INDX_FMC_SDCRx_SDCLK)
# define MASK_FMC_SDCRx_SDCLK_DISABLED (WORD)(0U << INDX_FMC_SDCRx_SDCLK)
# define MASK_FMC_SDCRx_SDCLK_2HCLK (WORD)(2U << INDX_FMC_SDCRx_SDCLK)
# define MASK_FMC_SDCRx_SDCLK_3HCLK (WORD)(3U << INDX_FMC_SDCRx_SDCLK)

# define INDX_FMC_SDCRx_RBURST  12
# define MASK_FMC_SDCRx_RBURST  (WORD)REG_BITMASK(FMC_SDCRx_RBURST)

# define INDX_FMC_SDCRx_RPIPE   13
# define MASK_FMC_SDCRx_RPIPE_0HCLK (WORD)(0U << INDX_FMC_SDCRx_RPIPE)
# define MASK_FMC_SDCRx_RPIPE_1HCLK (WORD)(1U << INDX_FMC_SDCRx_RPIPE)
# define MASK_FMC_SDCRx_RPIPE_2HCLK (WORD)(2U << INDX_FMC_SDCRx_RPIPE)

// SDTRx

# define INDX_FMC_SDTRx_TRCD    24

# define INDX_FMC_SDTRx_TRP     20

# define INDX_FMC_SDTRx_TWR     16

# define INDX_FMC_SDTRx_TRC     12

# define INDX_FMC_SDTRx_TRAS    8

# define INDX_FMC_SDTRx_TXSR    4

# define INDX_FMC_SDTRx_TMRD    0

/// \endcond

inline bool FMC_SDSR_IsBusy()
{
  return CheckFMC_SDSR(MASK_FMC_SDSR_BUSY);
}

inline void SDRAM_Command(WORD const sdcmrVal)
{
  while ( FMC_SDSR_IsBusy() ) { }
  
  rbFMC.SDCMR = sdcmrVal;
}

# define SDRAM_MRD_BURST_LENGTH_1             ((HWRD)0x0000)
# define SDRAM_MRD_BURST_LENGTH_2             ((HWRD)0x0001)
# define SDRAM_MRD_BURST_LENGTH_4             ((HWRD)0x0002)
# define SDRAM_MRD_BURST_LENGTH_8             ((HWRD)0x0004)
# define SDRAM_MRD_BURST_TYPE_SEQUENTIAL      ((HWRD)0x0000)
# define SDRAM_MRD_BURST_TYPE_INTERLEAVED     ((HWRD)0x0008)
# define SDRAM_MRD_CAS_LATENCY_2              ((HWRD)0x0020)
# define SDRAM_MRD_CAS_LATENCY_3              ((HWRD)0x0030)
# define SDRAM_MRD_OPERATING_MODE_STANDARD    ((HWRD)0x0000)
# define SDRAM_MRD_WRITEBURST_MODE_PROGRAMMED ((HWRD)0x0000) 
# define SDRAM_MRD_WRITEBURST_MODE_SINGLE     ((HWRD)0x0200)  

# define FSMC_SRAM_BANK1_START  0x60000000U
# define FSMC_SRAM_BANK2_START  0x70000000U
# define FSMC_SRAM_BANK3_START  0x80000000U
# define FSMC_SRAM_BANK4_START  0x90000000U

# define FSMC_SDRAM_BANK1_START 0xC0000000U
# define FSMC_SDRAM_BANK2_START 0xD0000000U

#endif
