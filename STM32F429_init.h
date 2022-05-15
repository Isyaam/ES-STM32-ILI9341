//
// STM32F429_init.h
//

#ifndef guard_STM32F4XX_INIT_H
# define guard_STM32F4XX_INIT_H

# include <Compiler.h>

# if ! defined(SYSCLK_MHZ)
#  define SYSCLK_MHZ            180U                  ///< (Maximale) System-Frequenz des SMT32F429 in MHz.
# endif

# define SYSCLK                 (SYSCLK_MHZ * 1000000U)

# define PRIO_GRANULARITY       0x10
#endif
