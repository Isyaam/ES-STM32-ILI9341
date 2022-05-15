//
// Compiler.h
//

/// \file Compiler.h
/// Compiler-spezifische Definitions, Macros und Funktionen.
/// Um die Quellen auch zu Testzwecken auch mit anderen Compilern (z.B. MSC) übersetzen zu können, müssten in dieser Datei
/// mittels bedingter Kompilierung verschiedene Makros für die unterschiedlichen Compiler definiert werden.

#if ! defined(guard_COMPILER_H) && defined(__arm__)
# define guard_COMPILER_H

# if ! defined(__cplusplus)
#  error C++ only!
# endif

# if   defined(_DEBUG)  && ! defined(DEBUG)
#  define DEBUG
# endif

# if   defined(RELEASE) &&   defined(DEBUG)
#  error You cannot define RELEASE and DEBUG at the same time
# endif
# if ! defined(RELEASE) && ! defined(DEBUG)
#  error You must define ether RELEASE or DEBUG
# endif

# include <stdint.h>
# include <stdbool.h>

# define BYTE                   uint8_t               ///< Byte-Datentyp (8 Bits).
# define WORD                   uint32_t              ///< Wort-Datentyp (nach ARM-Konvention 32 Bits, d.h. 4 Bytes).
# define HWRD                   uint16_t              ///< Halbwort-Datentyp (nach ARM-Konvention 16 Bits, d.h. 2 Bytes).
# define DWRD                   uint64_t              ///< Doppelwort-Datentyp (nach ARM-Konvention 8 Bytes).

// Nomenklatur <s>INT<nn>:
// <s> = U bzw. S für unsigned bzw. signed
// <nn> = 08, 12, 32, 64 für 8 bis 64 Bits

# define UINT64                 uint64_t              ///< 8 byte unsigned int.
# define SINT64                 int64_t               ///< 8 byte signed int.

# define UINT32                 uint32_t              ///< 4 byte unsigned int.
# define SINT32                 int32_t               ///< 4 byte signed int.

# define UINT16                 uint16_t              ///< 2 byte unsigned int.
# define SINT16                 int16_t               ///< 2 byte signed int.

# define UINT08                 uint8_t               ///< Single byte unsigned int.
# define SINT08                 int8_t                ///< Single byte signed int.

# include <stddef.h>

# if __ARMCC_VERSION >= 6000000
#  pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#  pragma clang diagnostic ignored "-Wnested-anon-types"
#  pragma clang diagnostic ignored "-Wc++17-compat-mangling"
#  pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wgcc-compat"

#  define IMPORT(X)             asm(".global " #X);

static __attribute__((always_inline)) inline void ___barrier(void) { asm volatile("" ::: "memory", "cc"); }

#  define SCHEDULE_BARRIER      ___barrier
#  define FORCE_STORES          ___barrier
#  define MEMORY_CHANGED        ___barrier

#  define __weak                __attribute__((weak))
#  define __svc(...)
#  define __align(x)            __attribute__((aligned(x)))

#  define __clrex               __builtin_arm_clrex
#  define __dmb                 __builtin_arm_dmb
#  define __dsb                 __builtin_arm_dsb
#  define __isb                 __builtin_arm_isb
#  define __wfi                 __builtin_arm_wfi
#  define __wfe                 __builtin_arm_wfe
#  define __rbit                __builtin_arm_rbit
#  define __rev                 __builtin_bswap32
#  define __clz                 __builtin_clz

#  define ARM_RSR(NAME)         __builtin_arm_rsr(#NAME)
#  define ARM_WSR(NAME, VALUE)  __builtin_arm_wsr(#NAME, VALUE)

#  define DEFINE_ARM_RSR(NAME)  inline WORD ARM_RSR_ ## NAME()                 noexcept { return ARM_RSR(NAME); }
#  define DEFINE_ARM_WSR(NAME)  inline void ARM_WSR_ ## NAME(WORD const value) noexcept { ARM_WSR(NAME, value); }

#  define OFFSET_OF(S, M)       __builtin_offsetof(S, M)

#  define BREAKPOINT(v)         asm volatile("bkpt %0" :: "i"(v))

#  define WRITEONLY             /// not implemented
#  define READONLY              const

#  define __AT(ADDR)            __attribute__((section(".ARM.__at_" #ADDR)))
#  define LOCATE_AT(ADDR)       __AT(ADDR)

#  define FORCE_INLINE          __attribute__((always_inline)) inline

#  define FILE                  __FILE__
#  define FUNC                  __FUNCTION__
#  define LINE                  __LINE__
# else
#  pragma anon_unions
#  define PRAGMA(X)             _Pragma(#X)

#  define IMPORT(X)             PRAGMA(import(X))

#  define SCHEDULE_BARRIER()    __schedule_barrier() ///< Compiler-spezifische Pseudo-Anweisung, um die compiler-bedingte Umsortierung von Befehlen über diese Grenze hinaus zu unterbinden. 
#  define FORCE_STORES()        __force_stores()
#  define MEMORY_CHANGED()      __memory_changed()

#  define DEFINE_ARM_RSR(NAME)  inline WORD ARM_RSR_ ## NAME()                 noexcept { register WORD NAME __asm(#NAME); return NAME; }
#  define DEFINE_ARM_WSR(NAME)  inline void ARM_WSR_ ## NAME(WORD const value) noexcept { register WORD NAME __asm(#NAME); NAME = value; }

#  define ARM_RSR(NAME)         ARM_RSR_ ## NAME()
#  define ARM_WSR(NAME, VALUE)  ARM_WSR_ ## NAME(VALUE)

#  define OFFSET_OF(S, M)       offsetof(S, M)

#  define BREAKPOINT(n)         __breakpoint(n)

#  define WRITEONLY             __writeonly
#  define READONLY              const

#  define LOCATE_AT(ADDR)       __attribute__((at(ADDR)))

#  define FORCE_INLINE          __forceinline

#  define FILE                  __MODULE__            ///< Name der aktuellen Datei.

#  define FUNC                  __PRETTY_FUNCTION__   ///< Name der aktuellen Funktion.
#  define LINE                  __LINE__              ///< Aktuelle Zeilennummer.
# endif

namespace std { using nullptr_t = decltype(nullptr); }

# if defined(DEBUG) && ! defined(NO_BREAK)
#  define DEBUG_BREAK(n)        BREAKPOINT(n)
# else
#  define DEBUG_BREAK(n)
# endif

# define __CONCAT(A, B)         A##B
# define CONCAT(A, B)           __CONCAT(A, B)

template<typename TYPE, unsigned DIM> constexpr unsigned ArrayDim(TYPE const (&)[DIM]) noexcept { return DIM; }
template<typename TYPE, unsigned DIM> constexpr unsigned ArrayMax(TYPE const (&)[DIM]) noexcept { return DIM - 1U; }

template<typename TYPE, unsigned H, unsigned W> constexpr unsigned MatrixRows(TYPE const (&)[H][W]) noexcept { return H; }
template<typename TYPE, unsigned H, unsigned W> constexpr unsigned MatrixCols(TYPE const (&)[H][W]) noexcept { return W; }

/// Achtung: Die obigen Varianten zur Bestimmung von Feld oder Matrixdimensionen funktionieren nicht, wenn das Feld
/// nicht-statische Member-Variable in einer Klasse ist, weil der this-Zeiger nicht constexpr ist.

inline void * operator new   (unsigned, void * const p) noexcept { return p; }
inline void   operator delete(void *, void *) noexcept { }

#endif

