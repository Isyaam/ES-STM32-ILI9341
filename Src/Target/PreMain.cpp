//
// PreMain.cpp
//

/// \file PreMain.cpp
/// Initialisierungfunktionen, die vor \c main() aufgerufen werden und Routinen zum Fehler-Handling.

#include <Compiler.h>
#include <Debug.h>
#include <Cortex.h>

IMPORT(__use_realtime_heap)

extern "C" void __cxa_get_globals(void);

extern "C" void __cxa_pure_virtual()  
{ 
  ITM_PUTS(__FUNCTION__);
  DEBUG_BREAK(2);
  
  Cortex::Reset();
}

extern "C" int __aeabi_atexit(void *, void (*)(void *), void * d) 
{ 
  // Keine at-exit-Funktionen, da das Programm nie beendet wird bzw. über Reset beu gestartet wird.
  
  return 0; // 0 ==> OK; non-0 ==> failed 
}
  
extern "C" int __aeabi_idiv0(void) 
{ 
  ITM_PUTS(__FUNCTION__);
  DEBUG_BREAK(2); 
  
  return 0;
}

extern "C" void __ARM_exceptions_init(void) { __cxa_get_globals(); } // pre-allocate memory for exceptions

# include <signal.h>
# include <stdlib.h>

extern "C" void __default_signal_handler(int const sig, int)
{
  ITM_PUTS(__FUNCTION__);

  switch(sig)
  {
    case SIGOUTOFHEAP: ITM_PUTS("SIGOUTOFHEAP"  ); break;
    case SIGABRT     : ITM_PUTS("SIGABRT"       ); break;
    case SIGTERM     : ITM_PUTS("SIGTERM"       ); break;
    case SIGSTAK     : ITM_PUTS("SIGSTAK"       ); break;
    case SIGPVFN     : ITM_PUTS("SIGPVFN"       ); break;
    case SIGCPPL     : ITM_PUTS("SIGCPPL"       ); break;
    default          : ITM_PUTS("Unknown signal"); break;
  }
  
  DEBUG_BREAK(2);

  Cortex::Reset();
}

extern "C" __weak int  __cxa_guard_acquire(WORD volatile * const guard)
{
  ASSERT(Cortex::IsThreadMode());

  if ( *guard == 1U )
  {
    return 0;
  } else
  {
    return 1;
  }
}

extern "C" __weak void __cxa_guard_release(WORD volatile * const guard)
{
  *guard = 1U;
}

extern "C" __weak void __cxa_guard_abort()
{
  ITM_PUTS(FUNC);
  DEBUG_BREAK(2);

  Cortex::Reset();
}

extern "C" void _mutex_release(WORD * handle) __attribute__((used)); // is weakly referenced
extern "C" void _mutex_acquire(WORD * handle) __attribute__((used)); // is weakly referenced

static constexpr WORD const magicnum = 0x00AFFE00U;

extern "C" __weak void _mutex_acquire(WORD * const handle)
{ 
  ASSERT(Cortex::IsThreadMode()); 
  ASSERT(*handle == magicnum);
}

extern "C" __weak void _mutex_release(WORD * const handle) 
{ 
  ASSERT(Cortex::IsThreadMode()); 
  ASSERT(*handle == magicnum);
}

extern "C" __weak int  _mutex_initialize(WORD * const handle)
{
  ASSERT(Cortex::IsThreadMode()); 

  *handle = magicnum;
  
  return 1; // 1=multi threaded application, 0=single threaded application
}  

