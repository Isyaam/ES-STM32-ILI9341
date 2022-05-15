#include <Compiler.h>
#include <Cortex.h>

[[noreturn]]
void MyTerminate() noexcept
{ 
  DEBUG_BREAK(2);

  Cortex::Reset();
}

[[noreturn]]
void MyNewHandler() noexcept
{ 
  DEBUG_BREAK(2);

  Cortex::Reset();
}

