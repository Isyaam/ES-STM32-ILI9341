//
// Meta.h
//

/// \file Meta.h
/// Meta-Programmierung (inspiriert und zum Teil auch Idee geklaut von www.boost.org).

#ifndef guard_META_H
# define guard_META_H

// Some plain type traits etc. re-inventions.

/// Typengenerator um das Typenattribut \c const von einem Typ zu entfernen.
/// \tparam TYPE ist der Input-Typ.
template<typename TYPE>
struct RemConst
{
  typedef TYPE Type;
};

template<typename TYPE> struct RemConst<TYPE const> { typedef TYPE Type; };

/// Typengenerator um das Typenattribut \c const zu einem Typ hinzuzufügen.
/// \tparam TYPE ist der Input-Typ.
template<typename TYPE>
struct AddConst
{
  typedef typename RemConst<TYPE>::Type const Type;
};

/// Typengenerator um das Typenattribut \c volatile von einem Typ zu entfernen.
/// \tparam TYPE ist der Input-Typ.
template<typename TYPE>
struct RemVolatile
{
  typedef TYPE Type;
};

template<typename TYPE> struct RemVolatile<TYPE const> { typedef TYPE Type; };

template<typename TYPE>
struct RemAttr
{
  typedef typename RemVolatile<typename RemConst<TYPE>::Type>::Type Type;
};

/// Typengenerator um aus einem Referenz-Typ einen Werte-Typ zu machen (entfernt \c &, 
/// d.h. macht aus der Referenz auf ein Datum (l-value or r-value reference) einen Wert.
/// \tparam TYPE ist der Input-Typ.
template<typename TYPE>
struct RemRef
{
  typedef TYPE Type;
};

template<typename TYPE> struct RemRef<TYPE  &> { typedef TYPE Type; };
template<typename TYPE> struct RemRef<TYPE &&> { typedef TYPE Type; };

/// Typengenerator um das Typenattribut \c const von einem Typ zu entfernen und daraus einen Werte-Typ zu machen.
/// \tparam TYPE ist der Input-Typ.
/// \sa RemConst
/// \sa RemRef
template<typename TYPE>
struct RemAll
{
  typedef typename RemRef<typename RemAttr<TYPE>::Type>::Type Type;
};

/// Typengenerator um in Abhängigkeit eines (zur Compile-Zeit konstanten) logischen Ausdrucks zwischen zwei Typen auszuwählen.
template<bool COND, class THEN, class ELSE> 
struct IfThenElse
{
  typedef THEN Type;
};

template<class THEN, class ELSE> struct IfThenElse<false, THEN, ELSE> { typedef ELSE Type; };

struct IsTrue  { static constexpr bool const flag = true;  };
struct IsFalse { static constexpr bool const flag = false; };

# include <Compiler.h>

/// Metaprogrammierung: Feststellung, on ein Datentyp ein integraler Datentyp ist.
/// Diese Klasse implementiert nur einen statischen, konstanten Wert \c theFlag. Dieser Wert ist eine sog. constant expresssion
/// und wird zur Compile-Zeit evaluiert. Dieses Flag (\c true für einen integrale Datentyp, \c false für einen nicht-integralen
/// Datentyp) kann somit wiederum als Template-Argument verwendet werden.
template<typename TYPE> struct IsIntegral : public IfThenElse<sizeof(TYPE) <= sizeof(WORD), IsTrue, IsFalse>::Type { };

/// Metaprogrammierung: Feststellung, on ein Datentyp ein Zeiger ist.
/// Diese Klasse implementiert nur einen statischen, konstanten Wert \c theFlag. Dieser Wert ist eine sog. constant expresssion
/// und wird zur Compile-Zeit evaluiert. Dieses Flag (\c true für einen Zeiger-Typ, \c false sonst) 
/// kann somit wiederum als Template-Argument verwendet werden.
template<typename TYPE> struct IsPointer : public IsFalse { };

template<typename TYPE> struct IsPointer<TYPE                *>  : public IsTrue  { };
template<typename TYPE> struct IsPointer<TYPE          const *>  : public IsTrue  { };
template<typename TYPE> struct IsPointer<TYPE volatile       *>  : public IsTrue  { };
template<typename TYPE> struct IsPointer<TYPE volatile const *>  : public IsTrue  { };

template<typename TYPE> struct IsUINTxx : public IsFalse { };

template<>              struct IsUINTxx<UINT08> : public IsTrue  { };
template<>              struct IsUINTxx<UINT16> : public IsTrue  { };
template<>              struct IsUINTxx<UINT32> : public IsTrue  { };
template<>              struct IsUINTxx<UINT64> : public IsTrue  { };

template<typename TYPE> struct IsSINTxx : public IsFalse { };

template<>              struct IsSINTxx<SINT08> : public IsTrue  { };
template<>              struct IsSINTxx<SINT16> : public IsTrue  { };
template<>              struct IsSINTxx<SINT32> : public IsTrue  { };
template<>              struct IsSINTxx<SINT64> : public IsTrue  { };

template<typename TYPE> struct __ArgType_Val { typedef typename RemAll<TYPE>::Type         Type; };
template<typename TYPE> struct __ArgType_Ref { typedef typename RemAll<TYPE>::Type const & Type; };

/// Typengenerator für Übergabeparameter.
/// Übergabeparameter werden immer als (konstante) Referenz übergeben, wenn es sich um Strukturen oder sonstige größere Objekte handelt.
/// Integer und %Pointer können effektiv als Wert übergeben werden. Diese Klasse bietet die Möglichkeit der Meta-Programmierung.
template<typename TYPE> struct __ArgType : public IfThenElse<IsIntegral<TYPE>::flag, typename __ArgType_Val<TYPE>::Type, typename __ArgType_Ref<TYPE>::Type> { };

template<typename TYPE>
using ArgType = typename __ArgType<TYPE>::Type;

/// Klasse um festzustellen, ob eine Klasse eine Basisklasse zu einer gegebenen Klasse ist (und das ist alles nur geklaut!).
template <typename BASE, typename DRVD>
struct IsBaseOf
{
  typedef char (& yes)[1];
  typedef char (&  no)[2];

  struct Host
  {
    operator BASE * () const;
    operator DRVD * ();
  };

  template <typename T> 
  static yes Check(DRVD *, T);

  static no  Check(BASE *, int);

  static constexpr bool const flag = sizeof(Check(Host(), int())) == sizeof(yes);
};

/// Klasse zur Metadaten-Definition für Bereichsgrenzen von POD-Typen.
template<typename TYPE> struct Limits;

# include <limits.h>

template<> struct Limits<UINT64>
{
  static UINT64 const min = 0ULL;
  static UINT64 const max = ~0ULL;
};

template<> struct Limits<SINT64>
{
  static SINT64 const max = 0x7FFFFFFFFFFFFFFFLL;
  static SINT64 const min = ~max;
};

template<> struct Limits<UINT32>
{
  static UINT32 const min = 0;
  static UINT32 const max = UINT_MAX;
};

template<> struct Limits<SINT32>
{
  static SINT32 const min = INT_MIN;
  static SINT32 const max = INT_MAX;
};

template<> struct Limits<UINT16>
{
  static UINT16 const min = 0;
  static UINT16 const max = USHRT_MAX;
};
 
template<> struct Limits<SINT16>
{
  static SINT16 const min = SHRT_MIN;
  static SINT16 const max = SHRT_MAX;
};
 
template<> struct Limits<UINT08>
{
  static UINT08 const min = 0;
  static UINT08 const max = CHAR_MAX;
};
 
template<> struct Limits<SINT08>
{
  static SINT08 const min = SCHAR_MIN;
  static SINT08 const max = SCHAR_MAX;
};

# define UPPER_LIMIT(X)         Limits<decltype(X)>::max;
# define LOWER_LIMIT(X)         Limits<decltype(X)>::min;

/// Ersatz für die fehlende Implementierung von std::forward<>().
template<typename TYPE> 
TYPE && StdForward(typename RemRef<TYPE>::Type & anything)
{
  return static_cast<TYPE &&>(anything);
} 

/// Ersatz für die fehlende Implementierung von std::move<>().
template<typename TYPE> 
typename RemRef<TYPE>::Type && StdMove(TYPE && anything) 
{
  return static_cast<typename RemRef<TYPE>::Type &&>(anything);
} 

#endif

