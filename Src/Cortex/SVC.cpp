//
// SVC.cpp
//

/// \file SVC.cpp
/// Funktionen zum Installieren von SVC-Handlern (Implementierung).
/// \sa SVC.h

#include <Compiler.h>
#include <Cortex.h>
#include <Debug.h>

#include <SVC.h>
#include <PSV.h>

static inline WORD * Word2WordPtr(WORD const data) noexcept { return reinterpret_cast<WORD *>(data); }

extern "C" void HandleSVC(WORD const * const stack)
{
  auto const pc(stack[6]);
  BYTE const svc(reinterpret_cast<BYTE const *>(pc)[-2]);

  switch(svc)
  {
    case svcSetCONTROL:                           Cortex::SetCONTROL_privileged(              stack[0] ); break;
    case svcSetBASEPRI:                           Cortex::SetBASEPRI_privileged(              stack[0] ); break;
    case svcGetBASEPRI: *Word2WordPtr(stack[0]) = Cortex::GetBASEPRI_privileged(                       ); break;
    case svcSetPRIMASK:                           Cortex::SetPRIMASK_privileged(                       ); break;
    case svcGetPRIMASK: *Word2WordPtr(stack[0]) = Cortex::GetPRIMASK_privileged(                       ); break;
    
    case svcCallIntrf : 
    reinterpret_cast<ISvcCall *>((void *)stack[0])->Action(); 
    break;
    
    case svcCtrlReset :
    Cortex::Reset_privileged(); 
    break; 
    
    case svcPsvTrigger: 
    PsvTrigger_privileged(); 
    break;
  }
}

void Cortex::SetCONTROL(WORD const value) noexcept 
{        
  if ( Cortex::IsPrivileged() )
    Cortex::SetCONTROL_privileged(value);
  else
    SVC_SetCONTROL(value);
}

void Cortex::SetBASEPRI(WORD const value) noexcept 
{        
  if ( Cortex::IsPrivileged() ) 
    SetBASEPRI_privileged(value);
  else
    SVC_SetBASEPRI(value);
}

WORD Cortex::GetBASEPRI() noexcept
{ 
  if ( Cortex::IsPrivileged() )
    return GetBASEPRI_privileged();
  else
    return SVC_GetBASEPRI(); 
}

void Cortex::SetPRIMASK() noexcept                   
{
  if ( Cortex::IsPrivileged() )
    SetPRIMASK_privileged();
  else
    SVC_SetPRIMASK();
}

WORD Cortex::GetPRIMASK() noexcept
{ 
  if ( Cortex::IsPrivileged() )
    return GetPRIMASK_privileged();
  else
    return SVC_GetPRIMASK(); 
}

void PsvTrigger() noexcept
{
  Cortex::ISB();

  if ( Cortex::IsPrivileged() )
    PsvTrigger_privileged(); 
  else
    SVC_PsvTrigger();
}

[[noreturn]] void Cortex::Reset() noexcept
{ 
  ITM_PUTS(FUNC);

  if ( Cortex::IsPrivileged() )
    Cortex::Reset_privileged(); 
  else
    SVC_CtrlReset();
}
