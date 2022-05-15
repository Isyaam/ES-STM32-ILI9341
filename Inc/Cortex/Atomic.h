//
// Atomic.h
//

/// \file Atomic.h
/// Klassen für atomare (thread/async-sichere) Operationen.

#ifndef guard_ATOMIC_H
# define guard_ATOMIC_H

# include <Compiler.h>
# include <Cortex.h>

/// Helper-Klasse für thread-sichere Operationen, die somit als atomar angesehen werden können.
/// Mit Hilfe der Load-linked/Store-conditional-Befehle des Prozessors (LDREX, STREX) können BYTE-, HWRD- und WORD-Daten
/// thread-sicher manipuliert werden. Diese Klasse implementiert die hierzu notwendigen statischen Funktionen.
/// \sa Cortex::LoadLinked()
/// \sa Cortex::SaveConditional()
namespace  Atomic
{
  /// Typendefinition zur Beschreibung binärer Operationen.
  enum class BinOpType
  {
    opSet,                      ///< Kennzeichnung der Zuweisung.
    opAdd,                      ///< Kennzeichnung der Addition.
    opSub,                      ///< Kennzeichnung der Subtraktion.
    opMul,                      ///< Kennzeichnung der Multiplikation.
    opAnd,                      ///< Kennzeichnung der Und-Operation für einzelnen Bits (bitweise).
    opOrr                       ///< Kennzeichnung der Oder-Operation für einzelnen Bits (bitweise).  
  };
  
  /// Hilfsklasse mit statischer Funktion, um unterschiedliche Rechenoperation durch Spezialisierung zu definieren (statischer Polymorphismus).
  /// \tparam OP gibt die Art der binären Rechenoperation an.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE, BinOpType OP> struct BinOp { static constexpr TYPE Calc(TYPE l, TYPE r) noexcept; };

  template<typename TYPE> struct BinOp<TYPE, BinOpType::opSet> { static constexpr TYPE Calc(TYPE        , TYPE const r) noexcept { return     r; } };
  template<typename TYPE> struct BinOp<TYPE, BinOpType::opAdd> { static constexpr TYPE Calc(TYPE const l, TYPE const r) noexcept { return l + r; } };
  template<typename TYPE> struct BinOp<TYPE, BinOpType::opSub> { static constexpr TYPE Calc(TYPE const l, TYPE const r) noexcept { return l - r; } };
  template<typename TYPE> struct BinOp<TYPE, BinOpType::opMul> { static constexpr TYPE Calc(TYPE const l, TYPE const r) noexcept { return l * r; } };
  template<typename TYPE> struct BinOp<TYPE, BinOpType::opAnd> { static constexpr TYPE Calc(TYPE const l, TYPE const r) noexcept { return l & r; } };
  template<typename TYPE> struct BinOp<TYPE, BinOpType::opOrr> { static constexpr TYPE Calc(TYPE const l, TYPE const r) noexcept { return l | r; } };
  
  /// Funktion um generische Read/Modify/Wtite-Operationen zu implementieren.
  /// Beim Ändern von Variablen wird nach folgendem Schema vorgegangen. Zuerst wird der aktuelle Wert via LDREX geladen (read).
  /// Dann wird anhand dieses Wertes und dem Operanden ein neuer Wert berechnet (modify).
  /// Dieser Wert wird anschließend via STREX gespeichert (write). Falls die Schreiboperation nicht ausgeführt werden kann, werden alle
  /// drei Schritte von Anfang an wiederholt.
  /// \param[in, out] data gibt den (ersten) Zieloperand sowie das Ergebsnis der (binären) Rechenoperation an.
  /// \param[in] operand ist der (zweite) Operand den (binären) Rechenoperation.
  /// \return Wert des Zieloperanden \b vor der Operation.
  /// \tparam OP gibt die Art der binären Rechenoperation an (Addition, Subtraktion etc.).
  /// \tparam TYPE ist der Datentyp der atomaren Operation (WORD, HWRD oder BYTE).
  template<typename TYPE, BinOpType OP> 
  inline TYPE Modify(TYPE volatile & data, TYPE const operand) noexcept
  {
    TYPE result;
    
    do 
    {
      result = Cortex::LoadLinked(data);
    } while ( Cortex::SaveConditional(data, BinOp<TYPE, OP>::Calc(result, operand)) );
    
    return result;
  }

  template<typename TYPE, typename FNC> 
  inline TYPE RMW(TYPE volatile & data, FNC const lambda) noexcept
  {
    TYPE result;
    
    do 
    {
      result = Cortex::LoadLinked(data);
    } while ( Cortex::SaveConditional(data, lambda(result)) );
    
    return result;
  }

  template<typename TYPE, typename FNC> 
  inline bool RMWCond(TYPE volatile & data, FNC const lambda) noexcept
  {
    TYPE value;
    
    do 
    {
      value = Cortex::LoadLinked(data);

      if ( ! lambda(value) )
      {
        Cortex::ClearOwnership();
        
        return false;
      }
    } while ( Cortex::SaveConditional(data, value) );
    
    return true;
  }

  /// Typendefinition für Vergleichsoperationen.
  enum class CmpOpType
  {
    opEq,                       ///< Prüfung auf Gleichheit.
    opNe,                       ///< Prüfung auf Ungleichheit.
    opLt,                       ///< Prüfung ob das linke Argument kleiner ist, als das rechte Argument der Überprüfungsfunktion.
    opLe,                       ///< Prüfung ob das linke Argument kleiner oder gleich dem rechten Argument der Überprüfungsfunktion ist.
    opGt,                       ///< Prüfung ob das linke Argument größer ist, als das rechte Argument der Überprüfungsfunktion.
    opGe                        ///< Prüfung ob das linke Argument größer oder gleich dem rechten Argument der Überprüfungsfunktion ist.
  };

  /// Hilfsklasse mit statischer Funktion, um unterschiedliche Vergleichsoperation durch Spezialisierung zu definieren (statischer Polymorphismus).
  template<typename TYPE, CmpOpType CO> struct CmpOp { static constexpr bool Chck(TYPE l, TYPE r) noexcept; };

  template<typename TYPE> struct CmpOp<TYPE, CmpOpType::opEq > { static constexpr bool Chck(TYPE const l, TYPE const r) noexcept { return l == r; } };
  template<typename TYPE> struct CmpOp<TYPE, CmpOpType::opNe > { static constexpr bool Chck(TYPE const l, TYPE const r) noexcept { return l != r; } };
  template<typename TYPE> struct CmpOp<TYPE, CmpOpType::opLt > { static constexpr bool Chck(TYPE const l, TYPE const r) noexcept { return l <  r; } };
  template<typename TYPE> struct CmpOp<TYPE, CmpOpType::opLe > { static constexpr bool Chck(TYPE const l, TYPE const r) noexcept { return l <= r; } };
  template<typename TYPE> struct CmpOp<TYPE, CmpOpType::opGt > { static constexpr bool Chck(TYPE const l, TYPE const r) noexcept { return l >  r; } };
  template<typename TYPE> struct CmpOp<TYPE, CmpOpType::opGe > { static constexpr bool Chck(TYPE const l, TYPE const r) noexcept { return l >= r; } };

  /// Funktion um \b bedingte, generische Read/Modify/Write-Operationen zu implementieren.
  /// Die Vorgehensweise ist im Prinzip wie bei Atomic::BinOp<TYPE, OP>, jedoch die Rechenoperation und die Zuweisung
  /// nur dann ausgeführt, wenn die geforderte Bedingung erfüllt ist. Ist die Bedingung nicht erfüllt, so 
  /// wird der Zieloperand nicht modifiziert.
  /// \param[in, out] data gibt den (ersten) Zieloperand sowie das Ergebsnis der (binären) Rechenoperation an.
  /// \param[in] operand ist der (zweite) Operand den (binären) Rechenoperation.
  /// \param[in] cmp ist der Wert, mit dem verglichen wird; er wird bei der Vergleichsoperation verwendet.
  /// \param[out] old beinhaltet nach Return den Wert des Zieloperanden vor der Operation.
  /// \return \c true, wenn die Operation ausgeführt wurde (Bedingung erfüllt) oder \c false, wenn die
  /// Operation nicht ausgeführt werden konnte (Bedingung nicht erfüllt).
  /// \tparam OP gibt die Art der binären Rechenoperation an (Addition, Subtraktion etc.).
  /// \tparam CO gibt die Art der Ausführungsbedingung an (Gleichheit, Ungleichheit etc.).
  /// \tparam TYPE ist der Datentyp der atomaren Operation (WORD, HWRD oder BYTE).
  template<typename TYPE, BinOpType OP, CmpOpType CO> 
  inline bool CmpAndMod(TYPE volatile & data, TYPE const operand, TYPE const cmp, TYPE & old) noexcept 
  {
    do 
    {
      if ( ! CmpOp<TYPE, CO>::Chck(old = Cortex::LoadLinked(data), cmp) )
      {
        Cortex::ClearOwnership();

        return false;
      }
    } while ( Cortex::SaveConditional(data, BinOp<TYPE, OP>::Calc(old, operand)) );

    return true;
  }
  
  /// Atomare Addition.
  /// \param[in, out] data ist der erste Operand, nach der Ausführung die Summe der Operanden.
  /// \param[in] value ist der zweite Operand.
  /// \return Wert des ersten Operanden \b vor der Addition.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE> inline TYPE Add(TYPE volatile & data, TYPE const value) noexcept { return Modify<TYPE, BinOpType::opAdd>(data, value); }

  /// Atomare Subtraktion.
  /// \param[in, out] data ist der erste Operand, nach der Ausführung die Differenz der Operanden.
  /// \param[in] value ist der zweite Operand.
  /// \return Wert des ersten Operanden \b vor der Subtraktion.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE> inline TYPE Sub(TYPE volatile & data, TYPE const value) noexcept { return Modify<TYPE, BinOpType::opSub>(data, value); }

  /// Atomare Multiplikation.
  /// \param[in, out] data ist der erste Operand, nach der Ausführung das Produkt der Operanden.
  /// \param[in] value ist der zweite Operand.
  /// \return Wert des ersten Operanden \b vor der Multiplikation.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE> inline TYPE Mul(TYPE volatile & data, TYPE const value) noexcept { return Modify<TYPE, BinOpType::opMul>(data, value); }

  /// Atomare Und-Operation (bitweise).
  /// \param[in, out] data ist der erste Operand, nach der Ausführung das Produkt der Operanden.
  /// \param[in] mask ist der zweite Operand.
  /// \return Wert des Zieloperanden \b vor der Und-Operation.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE> inline TYPE And(TYPE volatile & data, TYPE const mask ) noexcept { return Modify<TYPE, BinOpType::opAnd>(data, mask); }

  /// Atomare Oder-Operation (bitweise).
  /// \param[in, out] data ist der erste Operand, nach der Ausführung das Produkt der Operanden.
  /// \param[in] mask ist der zweite Operand.
  /// \return Wert des Zieloperanden \b vor der Oder-Operation.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE> inline TYPE Orr(TYPE volatile & data, TYPE const mask ) noexcept { return Modify<TYPE, BinOpType::opOrr>(data, mask); }

  /// Atomare Nand-Operation (bitweise).
  /// \param[in, out] data ist der erste Operand, nach der Ausführung das Produkt der Operanden.
  /// \param[in] mask ist der zweite Operand.
  /// \return Wert des Zieloperanden \b vor der Nand-Operation.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE> inline TYPE Bic(TYPE volatile & data, TYPE const mask ) noexcept { return And(data, (TYPE)(~mask)); }

  template<typename TYPE> inline TYPE Mod(TYPE volatile & data, TYPE const mask, bool const flag) 
  noexcept {
    return flag ? Orr(data, mask) : Bic(data, mask);
  }
  
  /// Atomare Set-Anweisung (Zuweisungsoperation).
  /// \param[in, out] data ist der Zieloperand, nach der Ausführung der nuene Wert.
  /// \param[in] value ist der Wert der Zuweisung.
  /// \return Wert des Zieloperanden \b vor der Zuweisungsoperation.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE> inline TYPE Set(TYPE volatile & data, TYPE const value) noexcept { return Modify<TYPE, BinOpType::opSet>(data, value); }

  /// Set if equal.
  template<typename TYPE> inline bool SetEQ(TYPE volatile & data, TYPE const value, TYPE const cmp, TYPE & old) noexcept { return CmpAndMod<TYPE, BinOpType::opSet, CmpOpType::opEq>(data, value, cmp, old); }
  template<typename TYPE> inline bool SetEQ(TYPE volatile & data, TYPE const value, TYPE const cmp)   noexcept { TYPE old; return SetEQ                                             (data, value, cmp, old); }

  /// Set if not equal.
  template<typename TYPE> inline bool SetNE(TYPE volatile & data, TYPE const value, TYPE const cmp, TYPE & old) noexcept { return CmpAndMod<TYPE, BinOpType::opSet, CmpOpType::opNe>(data, value, cmp, old); }
  template<typename TYPE> inline bool SetNE(TYPE volatile & data, TYPE const value, TYPE const cmp)   noexcept { TYPE old; return SetNE                                             (data, value, cmp, old); }
  template<typename TYPE> inline bool SetNE(TYPE volatile & data, TYPE const value)                   noexcept {           return SetNE                                             (data, value, value);           }

  /// Set if greater then.
  template<typename TYPE> inline bool SetGT(TYPE volatile & data, TYPE const value, TYPE const cmp, TYPE & old) noexcept { return CmpAndMod<TYPE, BinOpType::opSet, CmpOpType::opGt>(data, value, cmp, old); }
  template<typename TYPE> inline bool SetGT(TYPE volatile & data, TYPE const value, TYPE const cmp)   noexcept { TYPE old; return SetGT                                             (data, value, cmp, old); }
  template<typename TYPE> inline bool SetGT(TYPE volatile & data, TYPE const value)                   noexcept {           return SetGT                                             (data, value, value); }

  /// Set if less then.
  template<typename TYPE> inline bool SetLT(TYPE volatile & data, TYPE const value, TYPE const cmp, TYPE & old) noexcept { return CmpAndMod<TYPE, BinOpType::opSet, CmpOpType::opLt>(data, value, cmp, old); }
  template<typename TYPE> inline bool SetLT(TYPE volatile & data, TYPE const value, TYPE const cmp)   noexcept { TYPE old; return SetLT                                             (data, value, cmp, old); }
  template<typename TYPE> inline bool SetLT(TYPE volatile & data, TYPE const value)                   noexcept {           return SetLT                                             (data, value, value); }

  /// Add if equal.
  template<typename TYPE> inline bool AddEQ(TYPE volatile & data, TYPE const value, TYPE const cmp, TYPE & old) noexcept { return CmpAndMod<TYPE, BinOpType::opAdd, CmpOpType::opEq>(data, value, cmp, old); }
  template<typename TYPE> inline bool AddEQ(TYPE volatile & data, TYPE const value, TYPE const cmp)   noexcept { TYPE old; return AddEQ                                             (data, value, cmp, old); }

  /// Add if less then.
  template<typename TYPE> inline bool AddLT(TYPE volatile & data, TYPE const value, TYPE const cmp, TYPE & old) noexcept { return CmpAndMod<TYPE, BinOpType::opAdd, CmpOpType::opLt>(data, value, cmp, old); }
  template<typename TYPE> inline bool AddLT(TYPE volatile & data, TYPE const value, TYPE const cmp)   noexcept { TYPE old; return AddLT                                             (data, value, cmp, old); }

  /// Add if less then or equal.
  template<typename TYPE> inline bool AddLE(TYPE volatile & data, TYPE const value, TYPE const cmp, TYPE & old) noexcept { return CmpAndMod<TYPE, BinOpType::opAdd, CmpOpType::opLe>(data, value, cmp, old); }
  template<typename TYPE> inline bool AddLE(TYPE volatile & data, TYPE const value, TYPE const cmp)   noexcept { TYPE old; return AddLE                                             (data, value, cmp, old); }

  /// Sub if greater then.
  template<typename TYPE> inline bool SubGT(TYPE volatile & data, TYPE const value, TYPE const cmp, TYPE & old) noexcept { return CmpAndMod<TYPE, BinOpType::opSub, CmpOpType::opGt>(data, value, cmp, old); }
  template<typename TYPE> inline bool SubGT(TYPE volatile & data, TYPE const value, TYPE const cmp)   noexcept { TYPE old; return SubGT                                             (data, value, cmp, old); }

  /// Sub if greater equal.
  template<typename TYPE> inline bool SubGE(TYPE volatile & data, TYPE const value, TYPE const cmp, TYPE & old) noexcept { return CmpAndMod<TYPE, BinOpType::opSub, CmpOpType::opGe>(data, value, cmp, old); }
  template<typename TYPE> inline bool SubGE(TYPE volatile & data, TYPE const value, TYPE const cmp)   noexcept { TYPE old; return SubGE                                             (data, value, cmp, old); }
  template<typename TYPE> inline bool SubGE(TYPE volatile & data, TYPE const value)                   noexcept {           return SubGE                                             (data, value, value          ); }
  
  template<typename TYPE> inline TYPE SubClipped(TYPE volatile & data, TYPE const value) noexcept
  {
    TYPE result;
    constexpr TYPE const zero = 0;
    
    do
    {
      if ( (result = Cortex::LoadLinked(data)) > value )
        result -= value;
      else
        result  = zero;
    } while ( Cortex::SaveConditional(data, result) );
    
    return result;
  }

  template<typename TYPE> inline TYPE Incr(TYPE volatile & data) noexcept { constexpr TYPE const one = 1; return Add(data, one); }
  template<typename TYPE> inline TYPE Decr(TYPE volatile & data) noexcept { constexpr TYPE const one = 1; return Sub(data, one); }

  template<typename TYPE> inline TYPE * XchgPtr(TYPE * volatile & ptr, TYPE * const value = nullptr) noexcept { return Set(ptr, value); }

  /// Werte austauschen.
  /// Dem Zieloperand wird ein neuer Wert zugewiesen und der ursprüngliche Wert des Zieloperanden wird zurückgegeben.
  /// \param[in, out] data ist der Zieloperand.
  /// \param[out] old enthält nach Ausführung den ursprünglichen Wert des Zieloperanden.
  /// \param[in] value ist der neue Wert für den Zieloperanden.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE> inline void Swap(TYPE volatile & data, TYPE volatile & old, TYPE const value) noexcept
  {
    do 
    {
      old = Cortex::LoadLinked(data);
    } while ( Cortex::SaveConditional(data, value) );
  }
  
  /// Werte austauschen.
  /// Dem Zieloperand wird ein neuer Wert zugewiesen und der ursprüngliche Wert des Zieloperanden wird zurückgegeben.
  /// \param[in, out] data ist der Zieloperand.
  /// \param[in, out] value ist der neue Wert für den Zieloperanden und enthält nach Ausführung den ursprünglichen Wert des Zieloperanden.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE> inline void Swap(TYPE volatile & data, TYPE volatile & value) noexcept { Swap(data, value, value); }

  /// Prüfen, ob ein noch mindestens ein beliebiges Bit im Zieloperand gesetzt ist, dieses Bit löschen und die Nummer des Bits rückmelden.
  /// \param[in, out] data ist der Zieloperand.
  /// \return Nummer des zu Bits oder -1, wenn kein Bit gefunden wurde.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE> inline int  Find(TYPE volatile & data) noexcept
  {
    TYPE value;    
    constexpr TYPE const one = 1;
    int indx;
    
    do
    { 
      int const n(Cortex::CLZ(value = Cortex::LoadLinked(data)));
      
      if ( n > 31 )
      {
        Cortex::ClearOwnership();
        
        return -1;
      } 
        
      indx = 31 - n;        
    } while ( Cortex::SaveConditional(data, (TYPE)(value & ~(one << indx))) );
    
    return indx;
  }

  /// Prüfen, ob ein bestimmtes Bit im Zieloperand gesetzt ist und dieses Bit löschen.
  /// \param[in, out] data ist der Zieloperand.
  /// \param[in] indx ist die Nummer des zu prüfenden Bits.
  /// \return \c true, wenn das angegebene Bit gesetzt war.
  /// \tparam TYPE ist der Datentyp der atomaren Operation.
  template<typename TYPE> inline bool Test(TYPE volatile & data, int const indx) noexcept
  {
    constexpr TYPE const zero = 0;
    constexpr TYPE const one = 1;
    TYPE const mask(one << indx);
    
    return (Bic(data, mask) & mask) != zero;
  }
  
  template<typename TYPE> inline TYPE Bfld(TYPE volatile & data, TYPE const set, TYPE const res) noexcept
  {
    TYPE value;
    
    do 
    {
      value = Cortex::LoadLinked(data);
    } while ( Cortex::SaveConditional(data, (TYPE)(set | (value & ~res))) );
    
    return value;
  }
};

#endif

