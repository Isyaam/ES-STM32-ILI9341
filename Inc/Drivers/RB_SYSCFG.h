//
// RB_SYSCFG.h
//

/// \file RB_SYSCFG.h
/// Deklaration der Registerbank des System Configuration controllers (SYSCFG).

#ifndef guard_RB_SYSCFG_H
# define guard_RB_SYSCFG_H

# include <RB.h>

/// Datentyp für SYSCFG-Registerbank, s. RM0033 Reference Manual, Abschnitt 7.
typedef struct __regbank_SYSCFG
{
  WORD MEMRMP;                  ///< Memory remap register.
  WORD PMC;                     ///< Peripheral mode configuration register.
  WORD EXTICR[4];               ///< External interrupt configuration registers.
  WORD reserved[2];
  WORD CMPCR;                   ///< Compensation cell control register.
} RegbankTypeSYSCFG;

/// SYSCFG-Registerbank.
extern RegbankTypeSYSCFG volatile rbSYSCFG;

/// \cond RB_DEFS

// PMC

# define INDX_SYSCFG_PMC_MII_RMII_SEL 23
# define MASK_SYSCFG_PMC_MII_RMII_SEL (WORD)(1U << INDX_SYSCFG_PMC_MII_RMII_SEL)

// EXTICR

# define MASK_SYSCFG_EXTICR_PA  0x0U
# define MASK_SYSCFG_EXTICR_PB  0x1U
# define MASK_SYSCFG_EXTICR_PC  0x2U
# define MASK_SYSCFG_EXTICR_PD  0x3U
# define MASK_SYSCFG_EXTICR_PE  0x4U
# define MASK_SYSCFG_EXTICR_PF  0x5U
# define MASK_SYSCFG_EXTICR_PG  0x6U
# define MASK_SYSCFG_EXTICR_PH  0x7U
# define MASK_SYSCFG_EXTICR_PI  0x8U

/// \endcond

#endif

