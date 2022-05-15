//
// RB_LTDC.h
//

/// \file RB_LTDC.h
/// Definition der Register-Bänke für den LCD-TFT-Controller.

#ifndef guard_RB_LTDC_H
# define  guard_RB_LTDC_H

# include <RB.h>

typedef struct __regbank_LTDC_Layer
{  
  WORD CR;                      ///< Control Register
  WORD WHPCR;                   ///< Window Horizontal Position Configuration Register
  WORD WVPCR;                   ///< Window Vertical Position Configuration Register   
  WORD CKCR;                    ///< Color Keying Configuration Register
  WORD PFCR;                    ///< Pixel Format Configuration Register
  BYTE CACR;                    ///< Constant Alpha Configuration Register (0xFF == Wichtung 1.0, 0x00 == Wichtung 0.0)
  BYTE reserved0[3];
  WORD DCCR;                    ///< Default Color Configuration Register
  WORD BFCR;                    ///< Blending Factors Configuration Register
  WORD reserved1[2];
  WORD CFBAR;                   ///< Color Frame Buffer Address Register
  WORD CFBLR;                   ///< Color Frame Buffer Length Register
  WORD CFBLNR;                  ///< ColorFrame Buffer Line Number Register
  WORD reserved2[3];
  WORD CLUTWR;                  ///< CLUT Write Register
} RegbankTypeLTDCLayer;

static_assert(offsetof(RegbankTypeLTDCLayer, CLUTWR) == 0x040, "Invalid RegbankTypeLTDRLayer [CLUTWR]");

/// \cond RB_DEFS

// WHPCR

# define INDX_LTDC_Lx_WHPCR_WHSTPOS 0

# define INDX_LTDC_Lx_WHPCR_WHSPPOS 16

// WVPCR

# define INDX_LTDC_Lx_WVPCR_WVSTPOS 0

# define INDX_LTDC_Lx_WVPCR_WVSPPOS 16

// CR

# define INDX_LTDC_Lx_CR_LEN    0
# define MASK_LTDC_Lx_CR_LEN    (WORD)REG_BITMASK(LTDC_Lx_CR_LEN)

# define INDX_LTDC_Lx_CR_CLUTEN 4
# define MASK_LTDC_Lx_CR_CLUTEN (WORD)REG_BITMASK(LTDC_Lx_CR_CLUTEN)

// PFCR

# define MASK_LTDC_Lx_PFCR_ARGB8888 0U
# define MASK_LTDC_Lx_PFCR_RGB888 1U
# define MASK_LTDC_Lx_PFCR_RGB565 2U
# define MASK_LTDC_Lx_PFCR_ARGB1555 3U
# define MASK_LTDC_Lx_PFCR_ARGB4444 4U
# define MASK_LTDC_Lx_PFCR_L8   5U
# define MASK_LTDC_Lx_PFCR_AL44 6U
# define MASK_LTDC_Lx_PFCR_AL88 7U

// CFBLR

# define INDX_LTDC_Lx_CFBLR_CFBLL 0

# define INDX_LTDC_Lx_CFBLR_CFBP 16

// BFCR

# define INDX_LTDC_Lx_BFCR_BF1  8
# define MASK_LTDC_Lx_BFCR_BF1_CONST (WORD)(4U << INDX_LTDC_Lx_BFCR_BF1) // Vordergrund mit konstanter Wichtung alpha
# define MASK_LTDC_Lx_BFCR_BF1_PA_MUL_CA (WORD)(6U << INDX_LTDC_Lx_BFCR_BF1) 

# define INDX_LTDC_Lx_BFCR_BF2  0
# define MASK_LTDC_Lx_BFCR_BF2_CONST (WORD)(5U << INDX_LTDC_Lx_BFCR_BF2) // Hintergrund mit konstanter Wichtung (1-alpha)
# define MASK_LTDC_Lx_BFCR_BF2_PA_MUL_CA (WORD)(7U << INDX_LTDC_Lx_BFCR_BF2)

# define MASK_LTDC_Lx_BFCR_PA_MUL_CA (MASK_LTDC_Lx_BFCR_BF1_PA_MUL_CA | MASK_LTDC_Lx_BFCR_BF2_PA_MUL_CA)
# define MASK_LTDC_Lx_BFCR_CONST     (MASK_LTDC_Lx_BFCR_BF1_CONST     | MASK_LTDC_Lx_BFCR_BF2_CONST)

/// \endcond 

/// Registerbank für LTDC
typedef struct __regbank_LTDC
{
  WORD reserved0[2];
  WORD SSCR;                    ///< Synchronization Size Configuration Register
  WORD BPCR;                    ///< Back Porch Configuration Register
  WORD AWCR;                    ///< Active Width Configuration Register
  WORD TWCR;                    ///< Total Width Configuration Register
  WORD GCR;                     ///< Global Control Register
  WORD reserved1[2];
  WORD SRCR;                    ///< Shadow Reload Configuration Register
  WORD reserved2[1];
  WORD BCCR;                    ///< Background Color Configuration Register
  WORD reserved3[1];
  WORD IER;                     ///< Interrupt Enable Register
  WORD ISR;                     ///< Interrupt Status Register
  WORD ICR;                     ///< Interrupt Clear Register
  WORD LIPCR;                   ///< Line Interrupt Position Configuration Register
  WORD CPSR;                    ///< Current Position Status Register
  WORD CDSR;                    ///< Current Display Status Register
  WORD reserved4[14];
  RegbankTypeLTDCLayer Layer0;
  WORD reserved5[15];
  RegbankTypeLTDCLayer Layer1;
} RegbankTypeLTDC;

static_assert(offsetof(RegbankTypeLTDC, CDSR) == 0x048, "Invalid RegbankTypeLTDR [CDSR]");
static_assert(offsetof(RegbankTypeLTDC, Layer0) == 0x084, "Invalid RegbankTypeLTDR [Layer0]");
static_assert(offsetof(RegbankTypeLTDC, Layer1) == 0x104, "Invalid RegbankTypeLTDR [Layer1]");

extern RegbankTypeLTDC volatile rbLTDC;               ///< LTDC-Registerbank.

/// \cond RB_DEFS

# define MASK_LTDC_HOR          0x0FFFU
# define MASK_LTDC_VER          0x07FFU

// SSCR

# define INDX_LTDC_SSCR_VSH     0

# define INDX_LTDC_SSCR_HSW     16

// BPCR

# define INDX_LTDC_BPCR_AVBP    0

# define INDX_LTDC_BPCR_AHBP    16

// AWCR
// Achtung: Bei AWCR steht das H bzw. W bei AAx für Height (NICHT für horizontal) und Width. 

# define INDX_LTDC_AWCR_AAH     0

# define INDX_LTDC_AWCR_AAW     16

// TWCR
// Achtung: Bei TWCR steht das H bzw. W bei AAx für Height (NICHT für horizontal) und Width. 

# define INDX_LTDC_TWCR_TOTALH  0

# define INDX_LTDC_TWCR_TOTALW  16

// GCR

# define INDX_LTDC_GCR_LTDCEN   0
# define MASK_LTDC_GCR_LTDCEN   (WORD)REG_BITMASK(LTDC_GCR_LTDCEN) 

# define INDX_LTDC_GCR_DBW      4

# define INDX_LTDC_GCR_DGW      8

# define INDX_LTDC_GCR_DRW      12

# define INDX_LTDC_GCR_DEN      16
# define MASK_LTDC_GCR_DEN      (WORD)REG_BITMASK(LTDC_GCR_DEN) 

# define INDX_LTDC_GCR_PCPOL    28
# define MASK_LTDC_GCR_PCPOL    (WORD)REG_BITMASK(LTDC_GCR_PCPOL) 

# define INDX_LTDC_GCR_DEPOL    29
# define MASK_LTDC_GCR_DEPOL    (WORD)REG_BITMASK(LTDC_GCR_DEPOL) 

# define INDX_LTDC_GCR_VSPOL    30
# define MASK_LTDC_GCR_VSPOL    (WORD)REG_BITMASK(LTDC_GCR_VSPOL) 

# define INDX_LTDC_GCR_HSPOL    31
# define MASK_LTDC_GCR_HSPOL    (WORD)REG_BITMASK(LTDC_GCR_HSPOL) 

// SRCR

# define INDX_LTDC_SRCR_IMR     0
# define MASK_LTDC_SRCR_IMR     (WORD)REG_BITMASK(LTDC_SRCR_IMR)

# define INDX_LTDC_SRCR_VBR     1
# define MASK_LTDC_SRCR_VBR     (WORD)REG_BITMASK(LTDC_SRCR_VBR)

// IER

# define INDX_LTDC_IER_RRIE     3
# define MASK_LTDC_IER_RRIE     (WORD)REG_BITMASK(LTDC_IER_RRIE)

// ISR

# define INDX_LTDC_ISR_RRIF     3
# define MASK_LTDC_ISR_RRIF     (WORD)REG_BITMASK(LTDC_ISR_RRIF)

// ICR

# define INDX_LTDC_ICR_CRRIF    3
# define MASK_LTDC_ICR_CRRIF    (WORD)REG_BITMASK(LTDC_ICR_CRRIF)

/// \endcond 

#endif

