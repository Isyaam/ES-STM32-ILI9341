//
// Debug.h
//

#ifndef guard_DEBUG_H
# define guard_DEBUG_H

# include <Compiler.h>

# if defined(DEBUG) && ! defined(NO_STACK_CHECK)
#  define STACK_CHECK_DEFINED

void StackCheck() noexcept;
void StackCheckInit() noexcept;

#  define STACK_CHECK           StackCheck
#  define STACK_CHECK_INIT      StackCheckInit
# else
#  define STACK_CHECK()
#  define STACK_CHECK_INIT()
# endif

# if defined(DEBUG)

/// Klassentemplate um das Textmuster für Feldauffüllungen in Abhängigkeit von Datentyp unterschiedlich definieren zu können.
/// \tparam TYPE ist der Datentyp des Feldes.
template<typename TYPE> struct DbgFillItem;

template<> struct DbgFillItem<UINT08> { DbgFillItem() = delete; static constexpr UINT08 const data =               0xAAU;   };
template<> struct DbgFillItem<UINT16> { DbgFillItem() = delete; static constexpr UINT16 const data =             0xAAAAU;   };
template<> struct DbgFillItem<UINT32> { DbgFillItem() = delete; static constexpr UINT32 const data =         0xAAAAAAAAU;   };
template<> struct DbgFillItem<UINT64> { DbgFillItem() = delete; static constexpr UINT64 const data = 0xAAAAAAAAAAAAAAAAULL; };

template<> struct DbgFillItem<SINT08> { DbgFillItem() = delete; static constexpr SINT08 const data =               0x55;    };
template<> struct DbgFillItem<SINT16> { DbgFillItem() = delete; static constexpr SINT16 const data =             0x5555;    };
template<> struct DbgFillItem<SINT32> { DbgFillItem() = delete; static constexpr SINT32 const data =         0x55555555;    };
template<> struct DbgFillItem<SINT64> { DbgFillItem() = delete; static constexpr SINT64 const data = 0x5555555555555555LL;  };

template<> struct DbgFillItem<char> { DbgFillItem() = delete; static constexpr char const data = '\0'; };

template<typename TYPE> struct DbgFillItem<TYPE *> { DbgFillItem() = delete; static constexpr TYPE * const data = nullptr; };

/// Funktion zum Füllen eines Feldes mit definierten Mustern.
/// \param array ist das Datenfeld.
/// \param dim ist die Dimension des Datenfeldes (Anzahl der Einträge).
/// \tparam TYPE ist der Datentyp des Feldes, durch den auch das Muster definiert wird.
template<typename TYPE>
static inline void DbgMemFill(TYPE array[], unsigned const dim) noexcept
{
  auto i = dim;
  
  while ( --i > 0U )
    array[i] = DbgFillItem<TYPE>::data;
    
  STACK_CHECK();
}

/// Funktion zum Füllen eines Feldes mit definierten Mustern.
/// \param array ist das Datenfeld.
/// \tparam TYPE ist der Datentyp des Feldes, durch den auch das Muster definiert wird.
/// \tparam DIM ist die Feldimension.
template<typename TYPE, unsigned DIM>
static inline void DbgMemFill(TYPE (& array)[DIM]) noexcept
{
  DbgMemFill(array, DIM);
}

#  define DBG_MEM_FILL(A)       DbgMemFill(A)         ///< Auffüllen eines Feldes mit Debug-Mustern, damit ein möglicher Stacküberlauf sicherer erkannt werdne kann.
# else
#  define DBG_MEM_FILL(A)       ((void)0)             // Füllen eines Arrays mit Debug-Mustern soll in der Release-Variante NICHT erfolgen.
# endif

# define STATIC_ASSERT_EXT(MSG, ...) static_assert(__VA_ARGS__, MSG)
# define STATIC_ASSERT(EXPR)    STATIC_ASSERT_EXT(#EXPR, EXPR)

# if defined(DEBUG) && ! defined(NO_ITM)
#  define ITM_TRACE

void ItmPutS(char const * text) noexcept;

#  include <Formatter.h>

Formatter & ItmFmt() noexcept;

template<typename ... ARGS> 
inline void ItmPrint(ARGS const & ... args) noexcept
{
  auto & fmt(ItmFmt());
  
  fmt.Print(args ...);
  
  STACK_CHECK();
}
#  include <Cortex.h>

#  define ITM_PUTS              ItmPutS
#  define ITM_PRINT(...)        ItmPrint(__VA_ARGS__)
#  define LOG_PRINT(...)        ItmPrint(Formatter::Digits(8), Cortex::GetTicks(), ' ', Formatter::Length(25), FILE, "(", Formatter::Digits(4), LINE, ") ", __FUNCTION__, ": ", __VA_ARGS__)
# else
#  define ITM_PUTS(T)
#  define ITM_PRINT(...)
#  define LOG_PRINT(...)
# endif

/// Hilfsklasse, um zu Prüfen, ob ein Index gültig ist.
/// \tparam TYPE ist der Index-Datentyp.
/// \tparam SIGNED ist true, wenn der Index auch negative Werte annehmen kann.
template<typename TYPE, bool SIGNED>
class IndexHelper;

template<typename TYPE> class IndexHelper<TYPE, true>
{
  public:
  
  IndexHelper() = delete;
  
  static constexpr TYPE const zero = 0;
  
  /// Prüfe, ob Index gültig ist.
  /// \param indx ist der zu prüfende Index.
  /// \param max ist die Indexobergrenze.
  static constexpr bool Verify(TYPE const indx, TYPE const max) noexcept { return indx > max || indx < zero; }
};

template<typename TYPE> class IndexHelper<TYPE, false>
{
  public:
  
  IndexHelper() = delete;
  
  /// Prüfe, ob Index gültig ist.
  /// \param indx ist der zu prüfende Index.
  /// \param max ist die Indexobergrenze.
  static constexpr bool Verify(TYPE const indx, TYPE const max) noexcept { return indx > max; }
};

# include <Meta.h>

/// Klasse, um zu Prüfen, ob ein Index gültig ist.
/// \tparam TYPE ist der Index-Datentyp.
/// \tparam ist die Indexobergrenze (inklusive),
template<typename TYPE, TYPE MAX>
class CheckIndex
{
  public:
  
  CheckIndex() = delete;
  
  using DataType = typename RemConst<TYPE>::Type;

  static constexpr bool const si = IsSINTxx<DataType>::flag;

  STATIC_ASSERT(IsUINTxx<DataType>::flag || si);

  /// Prüfe, ob Index gültig ist.
  /// \param indx ist eine Referenz des zu prüfenden Index.
  /// \param errfnc ist eine Lambda-Expression, die dann aufzurufen ist wenn der Indes ungültig ist.
  /// \tparam FNC ist der Datentype der Lambda-Expression.
  /// \return Referenz des Index-Wertes.
  template<typename FNC>
  static TYPE & Verify(TYPE & indx, FNC const errfnc) noexcept
  {
    if ( IndexHelper<DataType, si>::Verify(indx, MAX) )
    {
      ITM_PRINT("!!! Index error: indx=", indx);
      
      errfnc();
    }
    
    return indx;
  }
};

/// Klasse, um einen Wert überprüfen zu können.
template<typename TYPE>
class CheckValue
{
  public:
  
  CheckValue() = delete;
  
  template<typename FNC>
  static TYPE & Verify(TYPE & data, FNC const lambda) noexcept
  {
    STATIC_ASSERT(noexcept(lambda(data)));
    
    lambda(data);

    return data;
  }
};

# if defined(DEBUG) 

[[noreturn]] void AssertionFailed(char const expr[], char const file[], unsigned line, char const func[]) noexcept;
[[noreturn]] void ProgramAbortion(char const expr[], char const file[], unsigned line, char const func[]) noexcept;

/// Prüfen, ob ein Speicher in gültiges RAM oder ROM zeigt (keine Peripherie).
/// \param ptr ist der zu prüfende Zeiger.
/// \return \c true, wenn der Zeiger gültig ist.
bool IsValidPointer(void volatile const * ptr) noexcept;

template<typename TYPE> TYPE & __DataTypeConverter(TYPE       & data) noexcept;
template<typename TYPE> TYPE   __DataTypeConverter(TYPE const & data) noexcept;

/// Prüfe, on ein Zeiger gültig ist (kann wie p selbst verwendet werden).
#  define VERPTR(p)             CheckValue<decltype(__DataTypeConverter(p))>::Verify(p, [] (void volatile const * const xxx) noexcept { if ( ! IsValidPointer(xxx) ) AssertionFailed(#p " is not valid", FILE, LINE, __FUNCTION__); })

/// Prüfe ob ein Index gültig ist.
#  define VERINDX(i, m)         CheckIndex<decltype(i), m>::Verify(i, [] () noexcept { AssertionFailed("Array index " #i " out of range", FILE, LINE, __FUNCTION__); })

#  define ASSERT(c)             ((c) ? (void)0 : AssertionFailed(#c, FILE, LINE, FUNC)) 
#  define ABORT(t)              ProgramAbortion(t, FILE, LINE, FUNC)
# else
#  define VERPTR(p)             (p) 
#  define VERINDX(i, m)         (i)

#  define ASSERT(c)             ((void)0)
#  define ABORT(t)
# endif

/// Bereichsüberprüfung eines Felkdindex.
# define ARRAY_INDX(i, a)       VERINDX(i, ArrayMax(a))

/// Zugriff auf ein Feld mit Bereichsüberprüfung des Index.
# define ACCESS_ARRAY(a, i)     ((a)[ARRAY_INDX(i, a)])

template<typename TYPE, unsigned DIM>
class SecureArray final
{
  public:
  
  STATIC_ASSERT(DIM > 1U);
  
  using RawArrType = TYPE[DIM];
  
  SecureArray() noexcept { DBG_MEM_FILL(a); }
 
  template<typename ... ARGS>
  SecureArray(ARGS const ... ini) noexcept : 
    SecureArray() 
  { 
    Setup(a, ini ...); 
    
    STATIC_ASSERT(sizeof ...(ini) <= DIM); 
  }
  
  SecureArray(SecureArray const &) = delete;
  SecureArray(SecureArray      &&) = delete;

  ~SecureArray() = default;

  SecureArray & operator = (SecureArray const &) = delete;
  SecureArray & operator = (SecureArray      &&) = delete;

  FORCE_INLINE TYPE const & operator [] (unsigned const i) const noexcept { return a[VERINDX(i, DIM - 1U)]; }
  FORCE_INLINE TYPE       & operator [] (unsigned const i)       noexcept { return a[VERINDX(i, DIM - 1U)]; }

  private:
  
  template<typename TINI>
  FORCE_INLINE static void Setup(TYPE a[], TINI const ini) noexcept { a[0] = ini; }

  template<typename TINI, typename ... ARGS>
  FORCE_INLINE static void Setup(TYPE a[], TINI const ini, ARGS const ... more) noexcept { Setup(a, ini); Setup(a + 1U, more ...); }

  RawArrType a;
};

#endif

