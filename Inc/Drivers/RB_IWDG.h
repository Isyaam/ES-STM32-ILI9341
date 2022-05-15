//
// RB_IWDG.h
//

/// \file RB_IWDG.h
/// Deklaration der Registerbank des unabhängigen Watchdogs (IWDG).

#ifndef guard_RB_IWDG_H
# define guard_RB_IWDG_H

# include <RB.h>

/// Datentyp für Watchdog-Registerbank, s. RM0033 Reference Manual, chapter 25.5.
typedef struct __regbank_IWDG
{
  HWRD KR;                      ///< Key register (write only).
  HWRD reserved00;  
  
  WORD PR;                      ///< Prescaler register.
  
  HWRD RLR;                     ///< Reload register (12 bit).
  HWRD reserved01;

  WORD SR;                      ///< Status register (\b read only).
} RegbankTypeIWDG;

/// IWDG-Registerbank.
extern RegbankTypeIWDG volatile rbIWDG;

/// \cond RB_DEFS

// KR

# define MASK_IWDG_KR_VALUE     (HWRD)0xAAAAU
# define MASK_IWDG_KR_START     (HWRD)0xCCCCU
# define MASK_IWDG_KR_UNLOCK    (HWRD)0x5555U         // used to unlock PR and PLR

// SR

# define INDX_IWDG_SR_PVU       0
# define MASK_IWDG_SR_PVU       (WORD)REG_BITMASK(IWDG_SR_PVU)

# define INDX_IWDG_SR_RVU       1
# define MASK_IWDG_SR_RVU       (WORD)REG_BITMASK(IWDG_SR_RVU)

// PR

# define MASK_IWDG_PR_DIV032    (HWRD)3U
# define MASK_IWDG_PR_DIV064    (HWRD)4U
# define MASK_IWDG_PR_DIV128    (HWRD)5U
# define MASK_IWDG_PR_DIV256    (HWRD)6U

/// \endcond

#endif


















































