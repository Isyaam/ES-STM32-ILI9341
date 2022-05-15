#include <stdlib.h>

#include <exception>
#include <new>

__attribute__((weak, noreturn)) void MyTerminate () noexcept { exit(1); }
__attribute__((weak, noreturn)) void MyNewHandler() noexcept { MyTerminate(); }

static __attribute__((constructor(110))) void LocalInit() noexcept 
{
  extern void MyTerminate() noexcept;
  extern void MyNewHandler() noexcept; 

  std::set_terminate(&MyTerminate);
  std::set_new_handler(&MyNewHandler);
}
