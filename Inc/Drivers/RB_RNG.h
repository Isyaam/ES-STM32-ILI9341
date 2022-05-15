//
// RB_RNG.h
//

/// \file RB_RNG.h
/// Deklaration der Registerbank für 'Random Number Generator' (RNG).

#ifndef guard_RB_RNG_H
# define guard_RB_RNG_H

# include <RB.h>

/// Datentyp für RNG-Registerbank.
typedef struct __regbank_RNG
{ 
  WORD CR;
  WORD SR;
  WORD DR;
} RegbankTypeRNG;

/// RNG-Registerbank.
extern RegbankTypeRNG volatile rbRNG;

/// \cond RB_DEFS

// CR

# define INDX_RNG_CR_RNGEN      2
# define MASK_RNG_CR_RNGEN      (WORD)REG_BITMASK(RNG_CR_RNGEN)

# define INDX_RNG_CR_IE         3
# define MASK_RNG_CR_IE         (WORD)REG_BITMASK(RNG_CR_IR)

// SR

# define INDX_RNG_SR_DRDY       0
# define MASK_RNG_SR_DRDY       (WORD)REG_BITMASK(RNG_SR_DRDY)

# define INDX_RNG_SR_CECS       1

# define INDX_RNG_SR_SECS       2

# define INDX_RNG_SR_CEIS       5

# define INDX_RNG_SR_SEIS       6

/// \endcond

#endif

