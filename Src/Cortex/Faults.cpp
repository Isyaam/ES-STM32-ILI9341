//
// Faults.cpp
//

/// \file Faults.cpp
/// Handler für Bus-, Mem-, Usage- und Hard-Faults sowie für den NMI.

#include <Compiler.h>
#include <Cortex.h>

#include <RB_SCB.h>

static void ResetOnFault() noexcept
{
  DEBUG_BREAK(2);

  Cortex::SetPRIMASK_privileged();
  Cortex::SetFLTMASK_privileged(1U);
  
  rbSCB.AIRCR = MASK_SCB_AIRCR_SYSRESETREQ | MASK_SCB_AIRCR_VECTKEY_WR;
}

extern "C" void IRQ_NMI(void)
{
  for ( ;; ) ResetOnFault();
}

extern "C" void HandleHrdFlt(WORD * const stack) { for ( ;; ) ResetOnFault(); }
extern "C" void HandleUsgFlt(WORD * const stack) { for ( ;; ) ResetOnFault(); }
extern "C" void HandleBusFlt(WORD * const stack) { for ( ;; ) ResetOnFault(); }
extern "C" void HandleMemFlt(WORD * const stack) { for ( ;; ) ResetOnFault(); }


