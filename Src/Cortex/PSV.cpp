//
// PSV.cpp
//

/// \file PSV.cpp
/// Pending SVC Handler (Implementierung).
/// \sa PSV.h

#include <Compiler.h>
#include <Cortex.h>
#include <Debug.h>

#include <PSV.h>

#include <RB_SCB.h>

void PsvTrigger_privileged() noexcept
{ 
  ASSERT(Cortex::IsPrivileged()); 
  
  rbSCB.ICSR = MASK_SCB_ICSR_PENDSVCSET; 
}

__weak void PsvTrigger() noexcept { PsvTrigger_privileged(); }

extern "C" void IRQ_PSV(void)
{
  DEBUG_BREAK(1U);
}

