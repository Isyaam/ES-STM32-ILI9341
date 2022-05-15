//
// RB_DMA2D.h
//

/// \file RB_DMA2D.h
/// Deklaration der Registerbank für den Chrom-Art-Accelerator (DMA2D).

#ifndef guard_RB_DMA2D_H
# define guard_RB_DMA2D_H

# include <RB.h>

/// Datentyp für DMA2D-Registerbank.
typedef struct __regbank_DMA_2D
{ 
  WORD CR;                      ///< Control Register                        
  WORD ISR;                     ///< Interrupt Status Register               
  WORD IFCR;                    ///< Interrupt Flag Clear Register           
  WORD FGMAR;                   ///< Foreground Memory Address Register      
  WORD FGOR;                    ///< Foreground Offset Register              
  WORD BGMAR;                   ///< Background Memory Address Register      
  WORD BGOR;                    ///< Background Offset Register              
  WORD FGPFCCR;                 ///< Foreground PFC Control Register         
  WORD FGCOLR;                  ///< Foreground Color Register               
  WORD BGPFCCR;                 ///< Background PFC Control Register         
  WORD BGCOLR;                  ///< Background Color Register               
  WORD FGCMAR;                  ///< Foreground CLUT Memory Address Register 
  WORD BGCMAR;                  ///< Background CLUT Memory Address Register 
  WORD OPFCCR;                  ///< Output PFC Control Register             
  WORD OCOLR;                   ///< Output Color Register                   
  WORD OMAR;                    ///< Output Memory Address Register          
  WORD OOR;                     ///< Output Offset Register                  
  WORD NLR;                     ///< Number of Line Register                 
  WORD LWR;                     ///< Line Watermark Register                 
  WORD AMTCR;                   ///< AHB Master Timer Configuration Register 
  WORD reserved[236];
  WORD FGCLUT[256];             ///< Foreground CLUT                         
  WORD BGCLUT[256];             ///< Background CLUT                         
} RegbankTypeDMA_2D;

static_assert(offsetof(RegbankTypeDMA_2D, FGCLUT) == 0x400, "Invalid RegbankTypeDMA_2D [FGCLUT]");
static_assert(offsetof(RegbankTypeDMA_2D, BGCLUT) == 0x800, "Invalid RegbankTypeDMA_2D [BGCLUT]");

/// DMA2D-Registerbank.
extern RegbankTypeDMA_2D volatile rbDMA_2D;

/// \cond RB_DEFS

// CR

# define INDX_DMA2D_CR_START    0
# define MASK_DMA2D_CR_START    (WORD)REG_BITMASK(DMA2D_CR_START)

# define INDX_DMA2D_CR_SUSP     1

# define INDX_DMA2D_CR_ABORT    2

# define INDX_DMA2D_CR_TEIE     8
# define MASK_DMA2D_CR_TEIE     (WORD)REG_BITMASK(DMA2D_CR_TEIE)

# define INDX_DMA2D_CR_TCIE     9
# define MASK_DMA2D_CR_TCIE     (WORD)REG_BITMASK(DMA2D_CR_TCIE)

# define INDX_DMA2D_CR_TWIE     10
# define MASK_DMA2D_CR_TWIE     (WORD)REG_BITMASK(DMA2D_CR_TWIE)

# define INDX_DMA2D_CR_MODE     16
# define MASK_DMA2D_CR_MODE     (WORD)(3U << INDX_DMA2D_CR_MODE)
# define MASK_DMA2D_CR_MODE_MEM2MEM (WORD)(0U << INDX_DMA2D_CR_MODE)
# define MASK_DMA2D_CR_MODE_M2M_PFC (WORD)(1U << INDX_DMA2D_CR_MODE)
# define MASK_DMA2D_CR_MODE_BLENDING (WORD)(2U << INDX_DMA2D_CR_MODE)
# define MASK_DMA2D_CR_MODE_REG2MEM (WORD)(3U << INDX_DMA2D_CR_MODE)

// ISR

# define INDX_DMA2D_ISR_TEIF    0
# define MASK_DMA2D_ISR_TEIF    (WORD)REG_BITMASK(DMA2D_ISR_TEIF)

# define INDX_DMA2D_ISR_TCIF    1
# define MASK_DMA2D_ISR_TCIF    (WORD)REG_BITMASK(DMA2D_ISR_TCIF)

// IFCR

# define INDX_DMA2D_IFCR_CTEIF  0
# define MASK_DMA2D_IFCR_CTEIF  (WORD)REG_BITMASK(DMA2D_IFCR_CTEIF)

# define INDX_DMA2D_IFCR_CTCIF  1
# define MASK_DMA2D_IFCR_CTCIF  (WORD)REG_BITMASK(DMA2D_IFCR_CTCIF)

// xPFCCR

# define INDX_DMA2D_xPFCCR_CM    0
# define MASK_DMA2D_xPFCCR_CM    (WORD)(0xFU << INDX_DMA2D_xPFCCR_CM)
# define MASK_DMA2D_xPFCCR_CM_ARGB8888 (WORD)(0x0U << INDX_DMA2D_xPFCCR_CM)
# define MASK_DMA2D_xPFCCR_CM_RGB888 (WORD)(0x1U << INDX_DMA2D_xPFCCR_CM)
# define MASK_DMA2D_xPFCCR_CM_RGB565 (WORD)(0x2U << INDX_DMA2D_xPFCCR_CM)
# define MASK_DMA2D_xPFCCR_CM_ARGB1555 (WORD)(0x3U << INDX_DMA2D_xPFCCR_CM)
# define MASK_DMA2D_xPFCCR_CM_ARGB4444 (WORD)(0x4U << INDX_DMA2D_xPFCCR_CM)
# define MASK_DMA2D_xPFCCR_CM_L8 (WORD)(0x5U << INDX_DMA2D_xPFCCR_CM)
# define MASK_DMA2D_xPFCCR_CM_AL44 (WORD)(0x6U << INDX_DMA2D_xPFCCR_CM)
# define MASK_DMA2D_xPFCCR_CM_AL88 (WORD)(0x7U << INDX_DMA2D_xPFCCR_CM)
# define MASK_DMA2D_xPFCCR_CM_L4 (WORD)(0x8U << INDX_DMA2D_xPFCCR_CM)
# define MASK_DMA2D_xPFCCR_CM_A8 (WORD)(0x9U << INDX_DMA2D_xPFCCR_CM)
# define MASK_DMA2D_xPFCCR_CM_A4 (WORD)(0xAU << INDX_DMA2D_xPFCCR_CM)

# define INDX_DMA2D_xPFCCR_CCM   8

# define INDX_DMA2D_xPFCCR_AM    16
# define MASK_DMA2D_xPFCCR_AM    (WORD)(0x3U << INDX_DMA2D_xPFCCR_AM)
# define MASK_DMA2D_xPFCCR_AM_PA (WORD)(0x0U << INDX_DMA2D_xPFCCR_AM)
# define MASK_DMA2D_xPFCCR_AM_CA (WORD)(0x1U << INDX_DMA2D_xPFCCR_AM)
# define MASK_DMA2D_xPFCCR_AM_PA_MUL_CA (WORD)(0x2U << INDX_DMA2D_xPFCCR_AM)

# define INDX_DMA2D_xPFCCR_ALPHA 24
# define MASK_DMA2D_xPFCCR_ALPHA (WORD)(0xFFU << INDX_DMA2D_xPFCCR_ALPHA)

# define DMA2D_WORKING ((rbDMA_2D.CR & MASK_DMA2D_CR_START))
# define DMA2D_WAIT do{while(DMA2D_WORKING); rbDMA_2D.IFCR = MASK_DMA2D_IFCR_CTCIF;}while(0);

/// \endcond

#endif

