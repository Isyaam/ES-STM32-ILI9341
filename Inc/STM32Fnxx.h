//
// STM32Fnxx.h
//

/// \file STM32Fnxx.h Common functions for STM32F4xx and STM32F7xx.

#ifndef guard_STM32FNXX_H
# define guard_STM32FNXX_H

# include <Compiler.h>

/// AHB Clock.
/// \return AHB-Takt in Hz.
unsigned HClk() noexcept;

/// APB1 Clock (low speed periphery).
/// \return APB1-Takt in Hz.
unsigned PClk1() noexcept;

/// APB2 Clock (high speed periphery).
/// \return APB2-Takt in Hz.
unsigned PClk2() noexcept;

#endif

