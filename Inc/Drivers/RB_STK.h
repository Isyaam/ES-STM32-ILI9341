//
// RB_STK.h
//

/// \file RB_STK.h
/// System tick (STK, core periphery).

#ifndef guard_RB_STK_H
# define  guard_RB_STK_H

# include <RB.h>

/// Datentyp für STK-Registerbank (System Tick).
typedef struct __regbank_STK
{
  WORD CSR;                     ///< Control and Status Register.
  
  WORD RVR;                     ///< Reload Value Register.
  WORD CVR;                     ///< Current Value Register.
  
  /// Calibration register.
  WORD CALIB;
} RegbankTypeSTK;

/// STK-Registerbank.
extern RegbankTypeSTK volatile rbSTK;

/// \cond RB_DEFS

// CTRL bit definitions

# define INDX_STK_CTRL_ENABLE   0
# define MASK_STK_CTRL_ENABLE   REG_BITMASK(STK_CTRL_ENABLE)

/// \endcond

#endif









































































