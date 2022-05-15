//
// RB_EXTI.h
//

/// \file RB_EXTI.h
/// Deklaration der Registerbank für externe Interrupts (EXTI).

#ifndef guard_RB_EXTI_H
# define guard_RB_EXTI_H

# include <RB.h>

/// Datentyp für EXTI-Registerbank, s. RM0033 Reference Manual, Abschnitt 8.3.
typedef struct __regbank_EXTI
{
  WORD IMR;                     ///< Interrupt mask register.
  WORD EMR;                     ///< Event mask register.
  WORD RTSR;                    ///< Rising trigger selection register.
  WORD FTSR;                    ///< Falling trigger selection register. 
  WORD SWIER;                   ///< Software interrupt event register.
  WORD PR;                      ///< Pending register.
} RegbankTypeEXTI;

/// EXTI-Registerbank.
extern RegbankTypeEXTI volatile rbEXTI;

/// \cond RB_DEFS

# define INDX_EXTI_PVD          16U
# define MASK_EXTI_PVD          (1U << INDX_EXTI_PVD)

# define INDX_EXTI_RTC_ALARM    17U
# define MASK_EXTI_RTC_ALARM    (1U << INDX_EXTI_RTC_ALARM)

# define INDX_EXTI_RTC_WKUP     22U
# define MASK_EXTI_RTC_WKUP     (1U << INDX_EXTI_RTC_WKUP)

# define INDX_EXTI_ETH_WKUP     24U
# define MASK_EXTI_ETH_WKUP     (1U << INDX_EXTI_ETH_WKUP)

/// \endcond

#endif





























































