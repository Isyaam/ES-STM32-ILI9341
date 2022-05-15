//
// Num2Ascii.h
//

/// \file Num2Ascii.h (Klasse Num2Ascii, Umwandlung einer Integer-Zahl in einen ASCIIZ-String)

#ifndef guard_NUM2ASCII_H
# define guard_NUM2ASCII_H

# include <Compiler.h>
//# include <Misc.h>
# include <Debug.h>

/// Basis-Klasse, um numerische Werte in Text (dezimal oder hexadezimal) umzuwandeln.
class Num2Ascii
{
  public:

  class ISink
  {
    protected:
    
    constexpr ISink() noexcept { }
    
    public:
    
    ISink(ISink const &) = delete;
    ISink(ISink      &&) = delete;
    
    virtual ~ISink() = default;
    
    ISink & operator = (ISink const &) = delete;
    ISink & operator = (ISink      &&) = delete;

    virtual void WriteByte(BYTE chr) noexcept = 0;    
  };
  
  Num2Ascii(ISink & intrf, char const s[]) noexcept : sink(intrf) { SetPrefix(s); }
  explicit Num2Ascii(ISink & intrf) noexcept : Num2Ascii(intrf, nullptr) { }

  Num2Ascii(Num2Ascii const &) = delete;
  Num2Ascii(Num2Ascii      &&) = delete;
  
  virtual ~Num2Ascii() = default;
  
  Num2Ascii & operator = (Num2Ascii const &) = delete;
  Num2Ascii & operator = (Num2Ascii      &&) = delete;
  
  void ResPrefix() noexcept { prefix = ""; }

  void SetPrefix(char const s[]) noexcept { if ( s == nullptr ) ResPrefix(); else prefix = s; }
  
  unsigned GetLength() const noexcept { return length; }

  unsigned GetDigits() const noexcept { return digits; }

  template<typename TYPE, unsigned RADIX>
  unsigned Format(TYPE value, int const num, int const width) noexcept
  {
    STATIC_ASSERT(RADIX >=  2U);
    STATIC_ASSERT(RADIX <= 16U);   
    STACK_CHECK();
    
    auto const tn(num - 1);
    auto const tw(width - 1);
    
    if ( tn > 0 || value >= RADIX )
    {
      TYPE const div(value / RADIX);
      
      value = value % RADIX;

      Format<TYPE, RADIX>(div, tn, tw);
    } else
      WriteChars(tw);
    
    if ( digits == 0U )
      WritePrefix();

    ASSERT(value < RADIX);
    
    static BYTE const d2c[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',       'A', 'B', 'C', 'D', 'E', 'F' };

    WriteDigit(d2c[value]);
    //---WriteDigit(ACCESS_ARRAY(d2c, value));
    
    return GetLength();
  }

  template<unsigned RADIX>
  unsigned FormatUINT32(UINT32 value, int const num, int const width) noexcept
  {
    return Format<UINT32, RADIX>(value, num, width);
  }

  template<unsigned RADIX>
  unsigned FormatUINT64(UINT64 value, int const num, int const width) noexcept
  {
    return Format<UINT64, RADIX>(value, num, width);
  }

  void Reset() noexcept { ResetCntrs(); ResPrefix(); }

  private:

  void ResetCntrs() noexcept { length = digits = 0U; }

  void WriteChar(BYTE const chr) noexcept
  {
    sink.WriteByte(chr);
    length++;
  }

  void WriteDigit(BYTE const chr) noexcept
  {
    WriteChar(chr);
    digits++;
  }
  
  void WriteChars(int cntr, BYTE const chr = ' ') noexcept
  {
    while ( cntr-- > 0 )
    {
      WriteChar(chr);
    }
  }

  void WritePrefix() noexcept
  {
    auto s = VERPTR(prefix);
    BYTE chr;
    
    while ( (chr = *s++) != '\0' )
    {
      WriteChar(chr);
    }          
  }
  
  ISink & sink;
  char const * prefix = "";
  unsigned length = 0U;         ///< Anzahl der Zeichen bei der Umwandlung des Zahlenwertes in einen Text.
  unsigned digits = 0U;         ///< Anzahl der (bisher) erzeugten Ziffern im Text.
};

#endif
