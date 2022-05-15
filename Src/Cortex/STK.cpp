//
// STK.cpp
// 

#include <Compiler.h>
#include <Cortex.h>
#include <Atomic.h>
#include <Debug.h>

#include <STK.h>

#include <RB_STK.h>

static union TicksType
{
  UINT64 x;
  struct { 
    WORD l;
    WORD h;
  };
} volatile ticks = { 0ULL };

inline UINT64 UMULL(UINT32 const a, UINT32 const b) noexcept { return (UINT64)a * (UINT64)b; }

static inline UINT64 STK_FineTime(WORD const t, WORD const s) noexcept
{ 
  WORD const r = rbSTK.RVR;
  WORD const n = r - rbSTK.CVR;
  WORD const d = r + 1U;
  auto const x = UMULL(t, d);
  
  return ((x + n) * s) / d;
}

UINT64 Cortex::GetFineTime(UINT32 const scf) noexcept 
{
  ASSERT(IsInterruptableBySTK());
  ASSERT(IsPrivileged()); 
  
  WORD tref;
  UINT64 fine; 
 
  do {
    fine = STK_FineTime(tref = ticks.l, scf);
  } while ( tref != ticks.l ); 

  return fine;
}

UINT64 Cortex::GetWideTicks() noexcept
{
  TicksType result;

  do {
    result.x = ticks.x;
  } while ( ticks.h != result.h );
  
  return result.x;
}

unsigned Cortex::GetTicks() noexcept { return ticks.l; }

extern "C" void IRQ_STK(void)
{
  WORD const csr = rbSTK.CSR; // dummy read to reset

  if ( Atomic::Incr(ticks.l) == ~0U )
    ticks.h++;

  STACK_CHECK();
}

