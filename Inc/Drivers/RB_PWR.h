//
// RB_PWR.h
//

/// \file RB_PWR.h
/// Deklaration der Registerbank für Power-Control (PWR).

#ifndef guard_RB_PWR_H
# define guard_RB_PWR_H

# include <RB.h>

/// Datentyp für PWR-Registerbank, s. RM0033 Reference Manual, chapter 4.4.
typedef struct __regbank_PWR
{
  WORD CR;                      ///< Control register.
  WORD CSR;                     ///< Control/status register.
} RegbankTypePWR;

/// PWR-Registerbank.
extern RegbankTypePWR volatile rbPWR;

/// \cond RB_DEFS

// CR

# define INDX_PWR_CR_PVDE       4
# define MASK_PWR_CR_PVDE       (WORD)REG_BITMASK(PWR_CR_PVDE)

# define INDX_PWR_CR_PLS        5
# define MASK_PWR_CR_PLS        (0x7U << INDX_PWR_CR_PLS)
# define MASK_PWR_CR_PLS_2_0V   (0x0U << INDX_PWR_CR_PLS)
# define MASK_PWR_CR_PLS_2_1V   (0x1U << INDX_PWR_CR_PLS)
# define MASK_PWR_CR_PLS_2_3V   (0x2U << INDX_PWR_CR_PLS)
# define MASK_PWR_CR_PLS_2_5V   (0x3U << INDX_PWR_CR_PLS)
# define MASK_PWR_CR_PLS_2_6V   (0x4U << INDX_PWR_CR_PLS)
# define MASK_PWR_CR_PLS_2_7V   (0x5U << INDX_PWR_CR_PLS)
# define MASK_PWR_CR_PLS_2_8V   (0x6U << INDX_PWR_CR_PLS)
# define MASK_PWR_CR_PLS_2_9V   (0x7U << INDX_PWR_CR_PLS)

# define INDX_PWR_CR_DBP        8
# define MASK_PWR_CR_DBP        (WORD)REG_BITMASK(PWR_CR_DBP)

# define INDX_PWR_CR_FPDS       9
# define MASK_PWR_CR_FPDS       (WORD)REG_BITMASK(PWR_CR_FPDS)

# define INDX_PWR_CR_VOS        14

# define INDX_PWR_CR_ODEN       16
# define MASK_PWR_CR_ODEN       (WORD)REG_BITMASK(PWR_CR_ODEN)

# define INDX_PWR_CR_ODSWEN   	17
# define MASK_PWR_CR_ODSWEN    	(WORD)REG_BITMASK(PWR_CR_ODSWEN)

/// CSR

# define INDX_PWR_CSR_PVDO      2
# define MASK_PWR_CSR_PVDO      (WORD)REG_BITMASK(PWR_CSR_PVDO)

# define INDX_PWR_CSR_BRR       3
# define MASK_PWR_CSR_BRR       (WORD)REG_BITMASK(PWR_CSR_BRR)

# define INDX_PWR_CSR_BRE       9
# define MASK_PWR_CSR_BRE       (WORD)REG_BITMASK(PWR_CSR_BRE)

# define INDX_PWR_CSR_VOSRDY    14

# define INDX_PWR_CSR_ODRDY     16
# define MASK_PWR_CSR_ODRDY     (WORD)REG_BITMASK(PWR_CSR_ODRDY)

# define INDX_PWR_CSR_ODSWRDY   17
# define MASK_PWR_CSR_ODSWRDY   (WORD)REG_BITMASK(PWR_CSR_ODSWRDY)

/// \endcond

#endif

