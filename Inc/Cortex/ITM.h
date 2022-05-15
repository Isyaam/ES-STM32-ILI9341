//
// ITM.h
//

#ifndef __ITM_H__
# include <Compiler.h>
# include <Debug.h>

# if defined(ITM_TRACE)

bool TestItm(void) noexcept;

bool TestItmChan0(void) noexcept;

int  SaveItmChan0(BYTE c) noexcept;

# endif
#endif
