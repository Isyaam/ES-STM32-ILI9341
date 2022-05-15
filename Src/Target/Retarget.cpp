int getkey(void) noexcept;
int sendchar(int c) noexcept;

#if __ARMCC_VERSION >= 6000000

#else

struct __FILE { int handle; };

#endif

#include <stdio.h>
#include <stdlib.h>

int std::fputc(int const c, FILE * const f) { return sendchar(c); }
int std::fgetc(FILE * const f) { return getkey(); }
int std::ferror(FILE * const f) { return EOF; }

#if __ARMCC_VERSION >= 6000000
#else

FILE std::__stdout;
FILE std::__stdin;

#endif

#include <Compiler.h>
#include <Cortex.h>

IMPORT(__use_no_semihosting_swi)
IMPORT(__use_no_semihosting)
IMPORT(__ARM_use_no_argv)

void std::abort(void) { DEBUG_BREAK(1); Cortex::Reset(); }
void std::exit(int)   { DEBUG_BREAK(1); Cortex::Reset(); }

#include <rt_sys.h>

void _sys_exit(int) { DEBUG_BREAK(1); Cortex::Reset(); }

#include <rt_misc.h>

extern "C" void __rt_exit(int)            { DEBUG_BREAK(1); Cortex::Reset(); }  
extern "C" void __rt_raise(int, intptr_t) { DEBUG_BREAK(1); Cortex::Reset(); }

__weak int getkey(void) noexcept { return EOF; }

__weak int sendchar(int const c) noexcept { return c; }

void _ttywrch(int const c) { sendchar(c); }

extern "C" unsigned __stack_chk_guard = 0xDEADBEEFU;

extern "C" void __stack_chk_fail(void) { DEBUG_BREAK(1); }

