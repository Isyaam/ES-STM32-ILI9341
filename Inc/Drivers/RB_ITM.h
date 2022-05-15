//
// RB_ITM.h
//

/// \file RB_ITM.h
/// Deklaration für die Instrumentation Trace Macrocell) (ITM).

#ifndef guard_RB_ITM_H
# define  guard_RB_ITM_H

# include <RB.h>

/// Datentyp für ITM-Registerbank, s. RM0033 Reference Manual, Abschnitt 32.14.
typedef struct __regbank_ITM
{
  /// Stimulus ports.
  union
  {
    BYTE asByte;
    HWRD asHwrd;
    WORD asWord;
  } PORT[32];

  WORD reserved0[864];
  
  // offset + 0xE00
  
  WORD TER;                     ///< Trace enable register.
  WORD reserved1[15];
  
  WORD TPR;                     ///< Trace priviledge register.
  WORD reserved2[15];

  WORD TCR;                     ///< Trace control register.
  WORD reserved3[29];                                  

  WORD IWR;
  WORD IRR;
  WORD IMCR;
  WORD reserved4[43];                                  
  WORD LAR;
  WORD LSR;
  WORD reserved5[6];                                   
  WORD PID4;
  WORD PID5;
  WORD PID6;
  WORD PID7;
  WORD PID0;
  WORD PID1;
  WORD PID2;
  WORD PID3;
  WORD CID0;
  WORD CID1;
  WORD CID2;
  WORD CID3;
} RegbankTypeITM;

/// ITM-Registerbank.
extern RegbankTypeITM volatile rbITM;                 ///< Registerbank für ITM.

/// \cond RB_DEFS

// TCR definitions

# define INDX_ITM_TCR_ITMENA    0
# define MASK_ITM_TCR_ITMENA    REG_BITMASK(ITM_TCR_ITMENA)

// TER definitions

# define INDX_ITM_TER_ENAPORT00 0  
# define MASK_ITM_TER_ENAPORT00 REG_BITMASK(ITM_TER_ENAPORT00)

/// \endcond

#endif
