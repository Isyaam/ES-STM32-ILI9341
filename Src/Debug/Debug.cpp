#include <Compiler.h>
#include <Cortex.h>
#include <Debug.h>

#if ! defined(DEBUG)
# error THIS FILE MUST BE EXCLUDED FROM PROJECT IN CASE OF NON-DEBUG BUILD!
#endif

#ifndef STACK_GUARD_VALUE
# define STACK_GUARD_VALUE      0x000A5000U
#endif

extern WORD volatile StackGuard_1;
extern WORD volatile StackGuard_2;

void StackCheckInit() noexcept 
{
  StackGuard_1 = STACK_GUARD_VALUE;
  StackGuard_2 = STACK_GUARD_VALUE;
}

void StackCheck() noexcept 
{
  if ( StackGuard_1 != STACK_GUARD_VALUE
  ||   StackGuard_2 != STACK_GUARD_VALUE )
  {
    ITM_PUTS("Stack corrupted");
    DEBUG_BREAK(3);
    
    Cortex::Reset();
  }
  /*
  if ( ! Cortex::AltStackIsOk() )
  {
    ITM_PUTS("Stack corrupted [ALT]");
    DEBUG_BREAK(3);
    
    Cortex::Reset();
  }*/
}

static inline bool CheckRange(WORD const addr, WORD const start, WORD const length) noexcept
{
	return addr >= start && addr < (start + length);
}

__weak bool IsValidPointer(void volatile const * const ptr) noexcept 
{
	WORD const addr = reinterpret_cast<WORD>(ptr);
	
	if ( CheckRange(addr, IRAM1_START, IRAM1_LENGTH) 
	||   CheckRange(addr, IRAM2_START, IRAM2_LENGTH) 
	||   CheckRange(addr, IROM1_START, IROM1_LENGTH) ) 
		return true;
	
	return false;
}

[[noreturn]]
__weak void AssertionFailed(char const expr[], char const file[], unsigned line, char const func[]) noexcept 
{
  ITM_PRINT("*** ", file, '(', Formatter::Digits(4), line, ") ", func, ' ', Formatter::AsTxt(expr)); 
  
  for ( ;; ) 
  { 
    DEBUG_BREAK(3); 
    Cortex::Reset(); 
  }
}

[[noreturn]]
__weak void ProgramAbortion(char const expr[], char const file[], unsigned line, char const func[]) noexcept 
{
  ITM_PRINT("*** ", file, '(', Formatter::Digits(4), line, ") ", func, ' ', Formatter::AsTxt(expr)); 
  
  for ( ;; ) 
  { 
    DEBUG_BREAK(3); 
    Cortex::Reset(); 
  }
}

#if defined(ITM_TRACE)
# include <ITM.h>

# include <RB_ITM.h>

static bool trace = false;

inline bool TestItmChan0() noexcept 
{
  return trace && (rbITM.TCR & MASK_ITM_TCR_ITMENA) != 0U && (rbITM.TER & MASK_ITM_TER_ENAPORT00) != 0U;
}

int SaveItmChan0(BYTE const c) noexcept 
{
  unsigned retry = 100000U;
  
  while ( rbITM.PORT[0].asWord == 0 ) 
  {
    if ( --retry == 0U )
      return -1;
  }

  rbITM.PORT[0].asByte = c;

  return c;
}

__weak 
void ItmPutS(char const * text) noexcept 
{
  if ( TestItmChan0() )
  {
    SaveItmChan0('\r');
    SaveItmChan0('\n');

    if ( text != nullptr )
    {
      char c;
      
      while ( (c = *text++) != '\0' )
      {
        SaveItmChan0(c);
      }
    }
  }
}

class SinkForItm : public Formatter::ISink
{
  public:
  
  constexpr SinkForItm() noexcept { }
  
  SinkForItm(SinkForItm const &) = delete;
  SinkForItm(SinkForItm      &&) = delete;
  
  virtual ~SinkForItm() = default;
  
  SinkForItm & operator = (SinkForItm const &) = delete;
  SinkForItm & operator = (SinkForItm      &&) = delete;

  virtual void WriteByte(BYTE chr) noexcept
  {
    if ( TestItmChan0() )
      SaveItmChan0(chr);
  }
};

Formatter & ItmFmt() noexcept
{
  static SinkForItm sink;
  static Formatter fmt(sink);

  ItmPutS(nullptr);
  
  return fmt;
}

int sendchar(int const c) noexcept 
{
  if ( TestItmChan0() )
    SaveItmChan0((BYTE)c);

  return c;
}

static __attribute__((constructor(101))) void LocalInit(void) noexcept 
{
  STACK_CHECK_INIT();

	static WORD volatile dbgmcuCr LOCATE_AT(0xE0042004);

	trace = (dbgmcuCr & 0x20U) != 0U;

  ITM_PUTS("ITM trace initialized");  
}

#endif
