//
// Cortex.cpp
//

/// \file Cortex.cpp
/// %Cortex-spezifische Funktionen (Implementierung).
/// \sa Cortex.h

#include <Compiler.h>
#include <Cortex.h>

#include <RB.h>
#include <RB_SCB.h>

static constexpr WORD const magical = 0x55555555U; ///< Magical fill number for alternative stack (used to detect stack corruption).
static WORD volatile const * boas = nullptr; ///< Bottom of alternative stack.

void Cortex::FpuEnable() noexcept  
{ 
  ISB();

  constexpr WORD const fpuOn = (3U << (10 * 2)) | (3U << (11 * 2));  // CP10 and CP11 Full Access
  
  rbSCB.CPACR = fpuOn; 
  
  DSB();
}

void Cortex::FpuDisable() noexcept
{ 
  ISB();
 
  rbSCB.CPACR = 0U;
 
  DSB();
  
  ARM_WSR(control, ARM_RSR(control) & ~CONTROL_fpucntxt);
}

void Cortex::Reset_privileged() noexcept
{
  for ( ;; ) 
  {
    DEBUG_BREAK(3);

    rbSCB.AIRCR = MASK_SCB_AIRCR_SYSRESETREQ | MASK_SCB_AIRCR_VECTKEY_WR;
  }
}

__weak void Cortex::Reset() noexcept 
{ 
  Cortex::Reset_privileged(); 
}

bool Cortex::AltStackIsOk() noexcept
{
  return boas == nullptr || *boas == magical;
}

__weak BYTE Cortex::GetPSVPrio() noexcept { return 0xF0; }
__weak BYTE Cortex::GetSVCPrio() noexcept { return 0x10; }
__weak BYTE Cortex::GetSTKPrio() noexcept { return 0x20; }
__weak BYTE Cortex::GetMinPrio() noexcept { return GetSTKPrio(); }

__weak void Cortex::SetCONTROL(WORD const value) noexcept {        SetCONTROL_privileged(value); }
__weak void Cortex::SetBASEPRI(WORD const value) noexcept {        SetBASEPRI_privileged(value); }
__weak WORD Cortex::GetBASEPRI()                 noexcept { return GetBASEPRI_privileged(); }
__weak void Cortex::SetPRIMASK()                 noexcept {        SetPRIMASK_privileged(); }
__weak WORD Cortex::GetPRIMASK()                 noexcept { return GetPRIMASK_privileged(); }

void Cortex::SetPRIMASK_privileged() noexcept
{
  ISB(); 
  
  ARM_WSR_primask(1U);
  ARM_WSR_control(ARM_RSR_control() & ~CONTROL_usermode);
}

void Cortex::ClrPRIMASK_privileged() noexcept { ISB();        ARM_WSR_primask(0U); }
WORD Cortex::GetPRIMASK_privileged() noexcept { ISB(); return ARM_RSR_primask(); }

void Cortex::SwitchStack(WORD * const stack, unsigned num) noexcept
{
  auto i = num;
  
  do {
    stack[--i] = magical;
  } while ( i > 0 );

  boas = stack;

  ISB();
  
  WORD const tos((WORD)(stack + num - 1U));
  
  ARM_WSR_psp(ARM_RSR_msp());
  ARM_WSR_msp(tos);
  
  ARM_WSR_control(ARM_RSR_control() |  CONTROL_altstack);
}

bool Cortex::IsInterruptable(BYTE const prio) noexcept
{
  if ( GetPRIMASK() != 0U )
    return false;
    
  auto const basepri(GetBASEPRI());
  
  if ( basepri == 0x00U )
    return true;
    
  return basepri > prio;
}


