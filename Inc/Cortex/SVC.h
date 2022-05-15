//
// SVC.h
//

/// \file SVC.h
/// Funktionen zum Installieren von SVC-Handlern.

#ifndef guard_SVC_H
# define guard_SVC_H

# include <Compiler.h>
# include <Cortex.h>
# include <Debug.h>

constexpr unsigned svcSetCONTROL = 0U;
constexpr unsigned svcSetBASEPRI = 1U;
constexpr unsigned svcGetBASEPRI = 2U;
constexpr unsigned svcSetPRIMASK = 3U;
constexpr unsigned svcGetPRIMASK = 4U;

constexpr unsigned svcCallIntrf  = 5U;

constexpr unsigned svcCtrlReset  = 6U;

constexpr unsigned svcPsvTrigger = 7U;

/// Schnittstelle, um Methoden im Kontext des SVC auzurufen.
class ISvcCall
{
  protected:
  
  constexpr ISvcCall() noexcept { }

  public:
  
  virtual ~ISvcCall() = default;

  /// SVC starten und entsprechende Methode dieser Schnittstelle indirekt aufrufen.
  void Invoke() noexcept;
  
  /// Methode, die im Kontext des SVCs aufgerufen werden soll.
  virtual void Action() noexcept = 0;
};

# if __ARMCC_VERSION >= 6000000

template <BYTE CODE> 
inline void SVC() noexcept
{
  asm volatile (
  "\tSVC    %[num]\r\n" :: [num] "i" (CODE)                    :       "memory", "cc");
}

template <BYTE CODE> 
inline void SVC(WORD const value) noexcept
{
  asm volatile (
  "\tMOV    r0, %[arg]\r\n"
  "\tSVC    %[num]\r\n" :: [num] "i" (CODE), [arg] "r" (value) : "r0", "memory", "cc");
}

[[noreturn]]
inline void SVC_CtrlReset() noexcept
{
  for ( ;; )
    SVC<svcCtrlReset>();
}

inline void SVC_PsvTrigger() noexcept { SVC<svcPsvTrigger>(); }

inline void SVC_SetPRIMASK() noexcept { SVC<svcSetPRIMASK>(); }

inline void SVC_CallIntrf(ISvcCall * const intrf) noexcept { SVC<svcCallIntrf>((WORD)intrf); }

inline void SVC_SetCONTROL(WORD const value) noexcept { SVC<svcSetCONTROL>(    value); } 
inline void SVC_SetBASEPRI(WORD const value) noexcept { SVC<svcSetBASEPRI>(    value); } 
inline void SVC_GetBASEPRI(WORD * const ptr) noexcept { SVC<svcGetBASEPRI>((WORD)ptr); } 
inline void SVC_GetPRIMASK(WORD * const ptr) noexcept { SVC<svcGetPRIMASK>((WORD)ptr); } 

# else

[[noreturn]]
void __svc(svcCtrlReset)  SVC_CtrlReset() noexcept;

void __svc(svcPsvTrigger) SVC_PsvTrigger() noexcept;

void __svc(svcSetPRIMASK) SVC_SetPRIMASK() noexcept;

void __svc(svcCallIntrf)  SVC_CallIntrf(ISvcCall * intrf) noexcept;

void __svc(svcSetCONTROL) SVC_SetCONTROL(WORD value) noexcept;
void __svc(svcSetBASEPRI) SVC_SetBASEPRI(WORD value) noexcept;
void __svc(svcGetBASEPRI) SVC_GetBASEPRI(WORD * ptr) noexcept;
void __svc(svcGetPRIMASK) SVC_GetPRIMASK(WORD * ptr) noexcept;

# endif

inline WORD SVC_GetBASEPRI()           noexcept { WORD value; SVC_GetBASEPRI(&value); return value;  }
inline WORD SVC_GetPRIMASK()           noexcept { WORD value; SVC_GetPRIMASK(&value); return value;  }

inline void ISvcCall::Invoke() noexcept { SVC_CallIntrf(this); }

#endif

