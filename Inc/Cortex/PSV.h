//
// PSV.h
//

/// \file PSV.h
/// Funktionen zur Nutzung des PSV (pending service call)

#ifndef guard_PSV_H
# define guard_PSV_H

/// PSV auslösen.
/// \note Der Prozessor muss sich im privilegierten Modus befinden, damit diese Funktion
/// ausgeführt werden kann. Wenn er sich nicht privilegierten Modus befindet, wird ein Usage-Fault ausgelöst.
void PsvTrigger_privileged() noexcept;

/// PSV auslösen.
void PsvTrigger() noexcept;

#endif
