//
// Cortex.H
//

/// \file Cortex.h
/// %Cortex-spezifische Funktionen.

#ifndef guard_CORTEX_H
# define guard_CORTEX_H

# include <Compiler.h>

extern "C" WORD _LdrExW(void const volatile * p            );
extern "C" HWRD _LdrExH(void const volatile * p            );
extern "C" BYTE _LdrExB(void const volatile * p            );
  
extern "C" WORD _StrExW(void       volatile * p, WORD value);
extern "C" WORD _StrExH(void       volatile * p, HWRD value); 
extern "C" WORD _StrExB(void       volatile * p, BYTE value);

# if   CORTEX_M == 4
#  define IRAM2_START             0x10000000U // CCM
#  define IRAM2_LENGTH            0x00010000U
#  define IRAM1_START             0x20000000U
#  define IRAM1_LENGTH            0x00020000U
#  define IROM1_START             0x08000000U
#  define IROM1_LENGTH            0x00100000U
# elif CORTEX_M == 7
#  define IRAM2_START             0x20000000U // TCM
#  define IRAM2_LENGTH            0x00010000U
#  define IRAM1_START             (IRAM2_START + IRAM2_LENGTH)
#  define IRAM1_LENGTH            0x00040000U
#  define IROM1_START             0x08000000U
#  define IROM1_LENGTH            0x00100000U
# else
#  error Missing CORTEX_M definition (must be 4 or 7)
# endif

DEFINE_ARM_RSR(control)
DEFINE_ARM_WSR(control)
DEFINE_ARM_RSR(basepri)
DEFINE_ARM_WSR(basepri)
DEFINE_ARM_RSR(primask)
DEFINE_ARM_WSR(primask)
DEFINE_ARM_RSR(faultmask)
DEFINE_ARM_WSR(faultmask)

DEFINE_ARM_RSR(psp)
DEFINE_ARM_WSR(psp)
DEFINE_ARM_RSR(msp)
DEFINE_ARM_WSR(msp)

DEFINE_ARM_RSR(epsr)
DEFINE_ARM_RSR(apsr)
DEFINE_ARM_RSR(ipsr)

/// Spezifische Funktionen des %Cortex(-M3/M4/M7) bzw. des zugehörigen aktuellen Befehlssatzes (ARMv7-M).
namespace Cortex 
{
  template<unsigned SIZE> struct ArmExclusive;

  template<> struct ArmExclusive<sizeof(WORD)> final
  { 
    ArmExclusive() = delete;
    ArmExclusive(ArmExclusive const &) = delete;
    ArmExclusive(ArmExclusive      &&) = delete;
    
    static WORD LdrEx(WORD const volatile & data)                   noexcept { return _LdrExW(&data); }
    static bool StrEx(WORD       volatile & data, WORD const value) noexcept { return _StrExW(&data, value) != 0U; }

    template<typename TYPE>
    static TYPE * LdrEx(TYPE * const volatile & p)                  noexcept { return (TYPE *)_LdrExW(&p); }

    template<typename TYPE>
    static bool   StrEx(TYPE *       volatile & p, TYPE * const q)  noexcept { return _StrExW(&p, (WORD)q) != 0U; }
  };

  template<> struct ArmExclusive<sizeof(HWRD)> final
  { 
    ArmExclusive() = delete;
    ArmExclusive(ArmExclusive const &) = delete;
    ArmExclusive(ArmExclusive      &&) = delete;
    
    static HWRD LdrEx(HWRD const volatile & data)                   noexcept { return _LdrExH(&data); }
    static bool StrEx(HWRD       volatile & data, HWRD const value) noexcept { return _StrExH(&data, value) != 0U; }
  };

  template<> struct ArmExclusive<sizeof(BYTE)> final
  { 
    ArmExclusive() = delete;
    ArmExclusive(ArmExclusive const &) = delete;
    ArmExclusive(ArmExclusive      &&) = delete;
    
    static BYTE LdrEx(BYTE const volatile & data)                   noexcept { return _LdrExB(&data); }
    static bool StrEx(BYTE       volatile & data, BYTE const value) noexcept { return _StrExB(&data, value) != 0U; }
  };

  // This are the (core) numbers of the current exception, see Cortex-M3/M4/M7 PSR

  constexpr unsigned const isrNum_THREAD_MODE =  0U; ///< ISR-Nummer in PSR für Thread-Modus
  constexpr unsigned const isrNum_RESET       =  1U;
  constexpr unsigned const isrNum_NMI         =  2U;
  constexpr unsigned const isrNum_HRD_FAULT   =  3U; ///< ISR-Nummer in PSR für Hard-Fault
  constexpr unsigned const isrNum_MEM_FAULT   =  4U; ///< ISR-Nummer in PSR für Memory-Fault
  constexpr unsigned const isrNum_BUS_FAULT   =  5U; ///< ISR-Nummer in PSR für Bus-Fault
  constexpr unsigned const isrNum_USG_FAULT   =  6U; ///< ISR-Nummer in PSR für Usage-Fault
  constexpr unsigned const isrNum_SVC         = 11U; ///< ISR-Nummer in PSR für SVC
  constexpr unsigned const isrNum_DEBMON      = 12U; 
  constexpr unsigned const isrNum_PSV         = 14U; ///< ISR-Nummer in PSR für PSV
  constexpr unsigned const isrNum_STK         = 15U; ///< ISR-Nummer in PSR für STK (System tick)
  constexpr unsigned const isrNum_EXTERN0     = 16U; // ab 16 beginnen die externen ISRs

  FORCE_INLINE constexpr unsigned isrNum_EXTERN(unsigned const n) noexcept { return n + isrNum_EXTERN0; }

  constexpr WORD const excReturnNonFp = 0xFFFFFFFDU; ///< Exception return code (thumb mode, return to thread mode, use PSP after return, non-FP state).
  constexpr WORD const excReturnUseFp = 0xFFFFFFEDU; ///< Exception return code (thumb mode, return to thread mode, use PSP after return, use FP state).

  [[noreturn]] void Reset() noexcept;

  [[noreturn]] void Reset_privileged() noexcept;

  FORCE_INLINE void DMB() noexcept { SCHEDULE_BARRIER(); __dmb(0xF); SCHEDULE_BARRIER(); }  
  FORCE_INLINE void DSB() noexcept { SCHEDULE_BARRIER(); __dsb(0xF); SCHEDULE_BARRIER(); }
  FORCE_INLINE void ISB() noexcept { SCHEDULE_BARRIER(); __isb(0xF); SCHEDULE_BARRIER(); }

  FORCE_INLINE WORD RBIT(WORD w) noexcept { return __rbit(w); }
  
  FORCE_INLINE WORD REV(WORD w) noexcept { return __rev(w); }
  
  FORCE_INLINE void WFI() noexcept { __wfi(); }
  FORCE_INLINE void WFE() noexcept { __wfe(); }

  /// Anzahl der (linksseitig) führenden 0-Bits (beginnend bei Bit 31) bestimmen.
  /// \param value ist der zu analysierende Wert.
  /// \return Anzahl der 'linksbündigen' 0-en (0 bis 32)
  FORCE_INLINE int CLZ(WORD const value) { return __clz( value); }

  /// Anzahl der (linksseitig) führenden 1-Bits (beginnend bei Bit 31) bestimmen.
  /// \param value ist der zu analysierende Wert.
  /// \return Anzahl der 'linksbündigen' 1-en (0 bis 32)
  FORCE_INLINE int CLO(WORD const value) { return __clz(~value); }

  BYTE GetPSVPrio() noexcept;
  BYTE GetSVCPrio() noexcept;
  BYTE GetSTKPrio() noexcept;
  BYTE GetMinPrio() noexcept;
  
  constexpr unsigned const CONTROL_usermode = 1U;
  constexpr unsigned const CONTROL_altstack = 2U;
  constexpr unsigned const CONTROL_fpucntxt = 4U;

  /// CONTROL-Register auslesen.
  /// \return Wert des CONTROL-Registers
  FORCE_INLINE WORD GetCONTROL() noexcept { return ARM_RSR(control); }

  /// CONTROL-Register einstellen.
  /// \param[in] value ist der neue Wert des CONTROL-Registers
  /// \note Der Prozessor muss sich im privilegierten Modus befinden. Es findet keine Prüfung statt, ob diese Voraussetzung zutrifft.
  FORCE_INLINE void SetCONTROL_privileged(WORD const value) noexcept { ARM_WSR(control, value); }

  void SetCONTROL(WORD value) noexcept;

  /// BASEPRI-Register auslesen.
  /// \return Wert des BASEPRI-Registers
  /// \note Der Prozessor muss sich im privilegierten Modus befinden. Es findet keine Prüfung statt, ob diese Voraussetzung zutrifft.
  FORCE_INLINE WORD GetBASEPRI_privileged() noexcept { return ARM_RSR(basepri); }

  /// BASEPRI-Register einstellen.
  /// \param[in] basePri ist der neue Wert des BASEPRI-Registers
  /// \note Der Prozessor muss sich im privilegierten Modus befinden. Es findet keine Prüfung statt, ob diese Voraussetzung zutrifft.
  /// BASEPRI-Register auslesen.
  /// \return Wert des BASEPRI-Registers.
  WORD GetBASEPRI() noexcept;

  FORCE_INLINE void SetBASEPRI_privileged(WORD const value) noexcept { ARM_WSR(basepri, value); }

  /// BASEPRI-Register einstellen.
  /// \param[in] value ist der neue Wert des BASEPRI-Registers
  void SetBASEPRI(WORD value) noexcept;

  /// PRIMASK-Register auslesen im privilegierten Modus.
  /// \copydetails Cortex::GetPRIMASK()
  /// \return Wert des PRIMASK-Registers.
  /// \warning Der Prozessor muss sich im privilegierten Modus befinden, damit diese Funktion ausgeführt werden kann.
  /// Befindet sich der Prozessor nicht im privilegierten Modus, wird ein Usage-Fault ausgelöst.
  WORD GetPRIMASK_privileged() noexcept;

  /// PRIMASK-Register auslesen.
  /// Das PRIMASK-Register besteht aus einem Bit. Ist es gesetzt, so werden \b alle IRQs (Exceptions) mit einstellbarer 
  /// Priorität gesperrt. Achtung, dies betrifft auch den SVC-IRQ.
  /// Wenn dieses Bit gesetzt ist, können folglich auch keine SVC-IRQs mehr bedient werden. Ein SVC-Aufruf ist dann verboten.
  /// Es muss deshalb sichergestellt werden, dass immer dann, wenn das PRIMASK-Register gesetzt wird auch gleichzeitig
  /// das System in den Exception-Modus versetzt wird, weil sonst keine privilegierten Befehle mehr ausgeführt werden können.
  /// Ist das PRIMASK-Register gelöscht, so können auch nicht-privilegierte Befehle indirekt via SVC-Aufruf implementiert werden.
  /// Hierzu löst man einen SVC aus, der dann in dem zugehörigen Handler (immer im Exception-Modus) die entsprechenden 
  /// Operationen ausführt. 
  /// \return Wert des PRIMASK-Registers.
  WORD GetPRIMASK() noexcept;

  /// PRIMASK aktivieren (alle Interrupts bis auf NMI und Hard-fault sperren).
  /// \note Der Prozessor muss sich im privilegierten Modus befinden. Es findet keine Prüfung statt, ob diese Voraussetzung zutrifft.
  /// \note Der Prozessor wird zusätzlich auch außerhalb einer IRQ in den privilegierten Modus versetzt, damit man ein Möglichkeit hat, die
  /// Exception wieder zu erlauben, da man auf das PRIMASK-Register nur im privilegierten Modus zugreifen kann.
  /// \warning
  /// Ist das PRIMASK-Register gesetzt und befindet sich der Controller gleichzeitig im User-Modus, 
  /// so gibt es somit keine generelle Möglichkeit mehr, privilegierte Operationen auszuführen, weil dann auch der
  /// SVC-IRQ nicht mehr verwendbar ist. Da das Ändern der PRIMASK-Register eine privilegierte Anweisung darstellt, könnte man
  /// dann das PRIMASK-Register nie mehr ändern.
  /// \warning Diese Funktion sperrt auch die Ausführung aller Exceptions mit programmierbarer Priorität, also \b auch den SVC
  /// und ebenfalls Usage-/Bus- und Memory-Faults!
  void SetPRIMASK_privileged() noexcept;

  /// PRIMASK löschen.
  /// \note Der Prozessor muss sich im privilegierten Modus befinden. Es findet keine Prüfung statt, ob diese Voraussetzung zutrifft.
  /// \warning Es gibt keine User-Mode-Variante dieser Funktion. 
  void ClrPRIMASK_privileged() noexcept;

  /// PRIMASK setzen.
  void SetPRIMASK() noexcept;

  FORCE_INLINE WORD GetIPSR() noexcept { return ARM_RSR(ipsr); }
  FORCE_INLINE WORD GetAPSR() noexcept { return ARM_RSR(apsr); }
  FORCE_INLINE WORD GetEPSR() noexcept { return ARM_RSR(epsr); }

  /// FAULTMASK auslesen.
  /// \return Wert des FAULTMASK-Registers
  /// \note Der Prozessor muss sich im privilegierten Modus befinden. Es findet keine Prüfung statt, ob diese Voraussetzung zutrifft.
  FORCE_INLINE WORD GetFLTMASK_privileged() noexcept { return ARM_RSR(faultmask); }

  /// FAULTMASK einstellen.
  /// \param[in] value ist der neue Wert des FAULTMASK-Registers
  /// \note Der Prozessor muss sich im privilegierten Modus befinden. Es findet keine Prüfung statt, ob diese Voraussetzung zutrifft.
  FORCE_INLINE void SetFLTMASK_privileged(WORD const value) { ARM_WSR(faultmask, value); }

  void FpuEnable() noexcept;

  void FpuDisable() noexcept;

  /// Load-linked-Befehl.
  /// Diese Funktion lädt ein Datum (1, 2 oder 4 Bytes breit) und markiert die Ownership des Datums. 
  /// \param data ist eine Referenz auf das zu lesende Datum
  /// \return Es wird der gelesene Wert zurückgegeben
  /// \tparam TYPE ist der Typ des zu lesenden Datums
  /// \warning Ein weiterer Aufruf dieser Funktion mit einem anderen Argument, löscht die Ownership des vorangegangenen 
  /// Aufrufs; ein verschachtelter Aufruf ist nicht erlaubt.
  /// \sa Cortex::SaveConditional()
  template<typename TYPE>
  FORCE_INLINE TYPE LoadLinked(TYPE const volatile & data) noexcept { DMB(); return ArmExclusive<sizeof(TYPE)>::LdrEx(data); }
  
  /// Store-conditional-Befehl.  
  /// Diese Funktion überschreibt ein Datum (1, 2 oder 4 Bytes breit) dessen Ownership zuvor belegt wurde.
  /// Die Speicherung scheitert, wenn die Ownership nicht belegt ist. 
  /// \param data ist eine Referenz auf das zu Datum, das überschrieben werden soll.
  /// \param value ist der Wert, mit dem das Datum überschrieben wird.
  /// \return \c false bei Erfolg; \c true, wenn der Vorgang wiederholt werden muss. 
  /// \tparam TYPE ist der Typ des zu speichernden Datums
  /// \sa Cortex::LoadLinked()
  template<typename TYPE>
  FORCE_INLINE bool SaveConditional(TYPE volatile & data, TYPE const value) noexcept
  {
    if ( ArmExclusive<sizeof(TYPE)>::StrEx(data, value) )
      return true;

    DSB();
      
    return false;
  }
  
  /// Ownership entfernen.
  /// \sa Cortex::SaveConditional()
  /// \sa Cortex::LoadLinked()
  FORCE_INLINE void ClearOwnership() noexcept { __clrex(); ISB(); }

  /// Nummer der aktuellen Exception zurückgeben.
  /// Die Nummer der aktuellen Exception (bzw. der aktiven Interrupt-Service-Routine) wird vom Cortex-M3 im (I)PSR zur Verfügung
  /// gestellt. Diese Nummer ist 0-relativ (0 = thread mode, d.h. keine Exception). Werte größer als 15 geben externe
  /// Exceptions an.
  /// \return Nummer der aktiven Exception.
  FORCE_INLINE WORD GetCurrentIsrNum() noexcept { return GetIPSR(); }

  /// Abfrage, ob sich der Prozessor im Thread-Modus befindet.
  /// \return \c true, wenn sich der Prozessor im Thread-Mode befindet und somit zurzeit keine IRQ bedient wird.
  /// \note Die Bestimmung, ob sich der Prozessor im Thread-Modus befindet, erfolgt anhand der aktuellen ISR-Nummer.
  FORCE_INLINE bool IsThreadMode() noexcept { return GetCurrentIsrNum() == isrNum_THREAD_MODE; }

  /// Abfrage, ob sich der Prozessor im aktuellen Kontext privilegierte Befehle ausführen kann.
  /// \return \c true, wenn privilegierte Befehle ausführbar sind.
  /// \note Exception mode ist immer privilegiert, unabhängig von CONTROL[0]!
  FORCE_INLINE bool IsPrivileged() noexcept { return (GetCONTROL() & CONTROL_usermode) == 0U || ! IsThreadMode(); }
  
  bool IsInterruptable(BYTE prio) noexcept;

  inline bool IsInterruptableByPSV() noexcept { return IsInterruptable(GetPSVPrio()); }
  inline bool IsInterruptableBySVC() noexcept { return IsInterruptable(GetSVCPrio()); }
  inline bool IsInterruptableBySTK() noexcept { return IsInterruptable(GetSTKPrio()); }

  /// Anzahl der System-Ticks zurückgeben.
  /// Da der Cortex-Core einen System-Timer beinhaltet (Modul STK), kann man diesen dazu verwenden, um eine Systemzeit 
  /// zu implementieren.
  /// \return Anzahl der System-Ticks (Zyklusdauer normalerweise 1 ms) seit Systemstart.
  WORD GetTicks() noexcept;

  /// Anzahl der System-Ticks als 64-Bit-Zahl zurückgeben, um Probleme bei tagelanger Betriebsdauer zu vermeiden.
  /// \return Anzahl der System-Ticks (Zyklusdauer normalerweise 1 ms) seit Systemstart.
  UINT64 GetWideTicks() noexcept;

  /// Systemzeit (Anzal der System-Ticks) mit erhöhter Auflösung bzw. Genauigkeit zurückgeben.
  UINT64 GetFineTime(UINT32 const scf) noexcept;

  /// Alternativen Stack einrichten.
  /// \param[in] stack ist die \b Endadresse des Stack-Speicherbereiches. \b Achtung: Must be 8-byte-aligned!
  /// \param[in] num gibt die Anzahl der Wörter des Stacks an.
  /// \warning Der Prozessor muss sich im privilegierten Modus befinden. Es findet keine Prüfung statt, ob diese Voraussetzung zutrifft.
  /// Wird die Voraussetzung verletzt, wird ein Usage-Fault ausgelöst.
  void SwitchStack(WORD * stack, unsigned num) noexcept;

  template<unsigned DIM>
  FORCE_INLINE void SwitchStack(WORD (& stack)[DIM]) noexcept { return SwitchStack(stack, DIM); } 

  bool AltStackIsOk() noexcept;
}

#endif
