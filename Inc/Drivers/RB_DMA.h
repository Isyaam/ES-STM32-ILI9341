//
// RB_DMA.h
//

/// \file RB_DMA.h
/// DMA controller.

#ifndef guard_RB_DMA_H
# define guard_RB_DMA_H

# include <RB.h>

/// Datentyp für DMA-Stream-Registerbank, s. RM0033 Reference Manual, Abschnitt 9.5.
typedef struct __regbank_DMA_Stream
{
  WORD SxCR;                    ///< Stream configuration register.
  WORD SxNDTR;                  ///< Stream number of data register.
  WORD SxPAR;                   ///< Stream peripheral address register.
  WORD SxM0AR;                  ///< Stream memory 0 address register.
  WORD SxM1AR;                  ///< Stream memory 1 address register.
  WORD SxFCR;                   ///< Stream FIFO control register.
} RegbankTypeDMAStream;

# define DMA_NUM_OF_STREAMS     8U

/// Datentyp für DMA-Registerbank, s. RM0033 Reference Manual, Abschnitt 9.5.
typedef struct __regbank_DMA
{
  union {
    struct {
      WORD LISR;                ///< Low interrupt status register.
      WORD HISR;                ///< High interrupt status register.
    };
    WORD ISR[2];
  };
  
  union {
    struct {
      WORD LIFCR;               ///< Low interrupt flag clear register.
      WORD HIFCR;               ///< High interrupt flag clear register.
    };
    WORD IFCR[2];
  };

  RegbankTypeDMAStream streams[DMA_NUM_OF_STREAMS]; ///< Stream configuration structures.
} RegbankTypeDMA;

extern RegbankTypeDMA volatile rbDMA1;                ///< DMA1-Registerbank.
extern RegbankTypeDMA volatile rbDMA2;                ///< DMA2-Registerbank.

/// \cond RB_DEFS

# define INDX_STREAM_SxCR_EN    0
# define MASK_STREAM_SxCR_EN    (WORD)REG_BITMASK(STREAM_SxCR_EN)

# define INDX_STREAM_SxCR_HTIE  3
# define MASK_STREAM_SxCR_HTIE  (WORD)REG_BITMASK(STREAM_SxCR_HTIE)

# define INDX_STREAM_SxCR_TCIE  4
# define MASK_STREAM_SxCR_TCIE  (WORD)REG_BITMASK(STREAM_SxCR_TCIE)

# define INDX_STREAM_SxCR_PFCTRL 5
# define MASK_STREAM_SxCR_PFCTRL (WORD)REG_BITMASK(STREAM_SxCR_PFCTRL)

# define INDX_STREAM_SxCR_DIR   6
# define MASK_STREAM_SxCR_DIR   (WORD)(0x3U << INDX_STREAM_SxCR_DIR)
# define MASK_STREAM_SxCR_DIR_PER2MEM (WORD)(0x0U << INDX_STREAM_SxCR_DIR)
# define MASK_STREAM_SxCR_DIR_MEM2PER (WORD)(0x1U << INDX_STREAM_SxCR_DIR)

# define INDX_STREAM_SxCR_CIRC  8
# define MASK_STREAM_SxCR_CIRC  (WORD)REG_BITMASK(STREAM_SxCR_CIRC)

# define INDX_STREAM_SxCR_PINC  9
# define MASK_STREAM_SxCR_PINC  (WORD)REG_BITMASK(STREAM_SxCR_PINC)

# define INDX_STREAM_SxCR_MINC  10
# define MASK_STREAM_SxCR_MINC  (WORD)REG_BITMASK(STREAM_SxCR_MINC)

# define INDX_STREAM_SxCR_PSIZE 11
# define MASK_STREAM_SxCR_PSIZE (WORD)(0x3U << INDX_STREAM_SxCR_PSIZE)
# define MASK_STREAM_SxCR_PSIZE_BYTE (WORD)(0x0U << INDX_STREAM_SxCR_PSIZE)
# define MASK_STREAM_SxCR_PSIZE_HWRD (WORD)(0x1U << INDX_STREAM_SxCR_PSIZE)
# define MASK_STREAM_SxCR_PSIZE_WORD (WORD)(0x2U << INDX_STREAM_SxCR_PSIZE)

# define INDX_STREAM_SxCR_MSIZE 13
# define MASK_STREAM_SxCR_MSIZE (WORD)(0x3U << INDX_STREAM_SxCR_MSIZE)
# define MASK_STREAM_SxCR_MSIZE_BYTE (WORD)(0x0U << INDX_STREAM_SxCR_MSIZE)
# define MASK_STREAM_SxCR_MSIZE_HWRD (WORD)(0x1U << INDX_STREAM_SxCR_MSIZE)
# define MASK_STREAM_SxCR_MSIZE_WORD (WORD)(0x2U << INDX_STREAM_SxCR_MSIZE)

# define INDX_STREAM_SxCR_MBURST 23
# define MASK_STREAM_SxCR_MBURST (WORD)(0x3U << INDX_STREAM_SxCR_MBURST)
# define MASK_STREAM_SxCR_MBURST_SINGLE (WORD)(0x0U << INDX_STREAM_SxCR_MBURST)
# define MASK_STREAM_SxCR_MBURST_INCR4 (WORD)(0x1U << INDX_STREAM_SxCR_MBURST)
# define MASK_STREAM_SxCR_MBURST_INCR8 (WORD)(0x2U << INDX_STREAM_SxCR_MBURST)

# define INDX_STREAM_SxCR_CHSEL 25

# define INDX_STREAM_SxCR_PL    16
# define MASK_STREAM_SxCR_PL    (WORD)(0x3U << INDX_STREAM_SxCR_PL)
# define MASK_STREAM_SxCR_PL_LOW (WORD)(0x0U << INDX_STREAM_SxCR_PL)
# define MASK_STREAM_SxCR_PL_MEDIUM (WORD)(0x1U << INDX_STREAM_SxCR_PL)
# define MASK_STREAM_SxCR_PL_HIGH (WORD)(0x2U << INDX_STREAM_SxCR_PL)
# define MASK_STREAM_SxCR_PL_VERYHIGH (WORD)(0x3U << INDX_STREAM_SxCR_PL)

# define INDX_STREAM_SxFCR_FTH  0
# define MASK_STREAM_SxFCR_FTH  (WORD)(0x3U << INDX_STREAM_SxFCR_FTH)
# define MASK_STREAM_SxFCR_FTH_25PERCENT (WORD)(0x0U << INDX_STREAM_SxFCR_FTH)
# define MASK_STREAM_SxFCR_FTH_50PERCENT (WORD)(0x1U << INDX_STREAM_SxFCR_FTH)
# define MASK_STREAM_SxFCR_FTH_75PERCENT (WORD)(0x2U << INDX_STREAM_SxFCR_FTH)
# define MASK_STREAM_SxFCR_FTH_FULL (WORD)(0x3U << INDX_STREAM_SxFCR_FTH)

# define INDX_STREAM_SxFCR_DMDIS 2
# define MASK_STREAM_SxFCR_DMDIS (WORD)REG_BITMASK(STREAM_SxFCR_DMDIS)

# define MASK_DMA_ISR           0x7DU

# define INDX_DMA_ISR_FEIF      0
# define MASK_DMA_ISR_FEIF      (WORD)REG_BITMASK(DMA_ISR_FEIF)

# define INDX_DMA_ISR_DMEIF     2
# define MASK_DMA_ISR_DMEIF     (WORD)REG_BITMASK(DMA_ISR_DMEIF)

# define INDX_DMA_ISR_TEIF      3
# define MASK_DMA_ISR_TEIF      (WORD)REG_BITMASK(DMA_ISR_TEIF)

# define INDX_DMA_ISR_HCIF      4
# define MASK_DMA_ISR_HCIF      (WORD)REG_BITMASK(DMA_ISR_HCIF)

# define INDX_DMA_ISR_TCIF      5
# define MASK_DMA_ISR_TCIF      (WORD)REG_BITMASK(DMA_ISR_TCIF)

/// \endcond

#endif

