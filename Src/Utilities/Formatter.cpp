#include <Compiler.h>
#include <Formatter.h>
#include <Num2Ascii.h>
#include <Debug.h>

/// Ausgabe erzeugen.
/// Diese Funktion wandelt einen (vorzeichenlosen) numerischen Wert in einen ASCIIZ-String um, wobei eine Zahlendarstellung 
/// mit variabler Basis verwendet wird. Die Mindestanzahl der Stellen und der Mindestfeldbreite können angegeben werden.
/// Es wird \b kein Prefix (Vorzeichen oder ähnliches) ausgegeben.
/// \param[in] put ist das Ziel-Interface, das die formatierte Ausgabe aufnehmen soll.
/// \param[in] value ist der numerische Wert, der serialisiert werden soll.
/// \param[in] digits gibt die Mindestanzahl der Ziffern an.
/// \param[in] length ist die Mindestfeldbreite; ggf. wird mit Leerzeichen linksseitig aufgefüllt.
/// \return Anzahl der formatierten Zeichen.
/// \sa Num2Ascii
/// \note Es wird \b kein Stringende in die Zielschnittstelle eingetragen.
template<typename TYPE, unsigned RADIX>
static inline unsigned WriteVal(Num2Ascii::ISink & intrf, TYPE const value, int const digits, int const length) noexcept
{
  Num2Ascii writer(intrf);

  return writer.Format<TYPE, RADIX>(value, digits, length);
}

/// Ausgabe erzeugen (Zahlenwert in Text umwandeln).
/// Diese Funktion wandelt einen (vorzeichenlosen) numerischen Wert in einen ASCIIZ-String um, wobei eine Zahlendarstellung 
/// mit variabler Basis verwendet wird. Die Mindestanzahl der Stellen und der Mindestfeldbreite können angegeben werden.
/// Es kann ein Prefix (z.B. führende \c "0x" oder Vorzeichen) ausgegeben werden.
/// \param[in] put ist das Ziel-Interface, das die formatierte Ausgabe aufnehmen soll.
/// \param[in] value ist der numerische Wert, der serialisiert werden soll.
/// \param[in] digits gibt die Mindestanzahl der Ziffern an.
/// \param[in] length ist die Mindestfeldbreite; ggf. wird mit Leerzeichen linksseitig aufgefüllt.
/// \param[in] prefix gibt den Hex-Prefix an.
/// \return Anzahl der formatierten Zeichen.
/// \sa Num2Ascii
template<typename TYPE, unsigned RADIX>
static inline unsigned WriteVal(Num2Ascii::ISink & intrf, TYPE const value, int const digits, int const length, char const prefix[]) noexcept
{
  Num2Ascii writer(intrf, prefix);

  return writer.Format<TYPE, RADIX>(value, digits, length);
}

static inline unsigned WriteValHex(Num2Ascii::ISink & intrf, UINT32 const   value, int const digits, int const length)                      noexcept { return WriteVal<UINT32, 16U>(intrf, value, digits, length); }
static inline unsigned WriteValHex(Num2Ascii::ISink & intrf, UINT32 const   value, int const digits, int const length, char const prefix[]) noexcept { return WriteVal<UINT32, 16U>(intrf, value, digits, length, prefix); }  

static inline unsigned WriteValHex(Num2Ascii::ISink & intrf, UINT64 const & value, int const digits, int const length)                      noexcept { return WriteVal<UINT64, 16U>(intrf, value, digits, length); }
static inline unsigned WriteValHex(Num2Ascii::ISink & intrf, UINT64 const & value, int const digits, int const length, char const prefix[]) noexcept { return WriteVal<UINT64, 16U>(intrf, value, digits, length, prefix); }  

static inline unsigned WriteValDec(Num2Ascii::ISink & intrf, UINT32 const   value, int const digits, int const length)                      noexcept { return WriteVal<UINT32, 10U>(intrf, value, digits, length); }
static inline unsigned WriteValDec(Num2Ascii::ISink & intrf, UINT32 const   value, int const digits, int const length, char const prefix[]) noexcept { return WriteVal<UINT32, 10U>(intrf, value, digits, length, prefix); }  

static inline unsigned WriteValDec(Num2Ascii::ISink & intrf, UINT64 const & value, int const digits, int const length)                      noexcept { return WriteVal<UINT64, 10U>(intrf, value, digits, length); }
static inline unsigned WriteValDec(Num2Ascii::ISink & intrf, UINT64 const & value, int const digits, int const length, char const prefix[]) noexcept { return WriteVal<UINT64, 10U>(intrf, value, digits, length, prefix); }  
  
class SinkConverter : public Num2Ascii::ISink
{
  public:
    
  constexpr SinkConverter(Formatter::ISink & intrf) noexcept : sink(intrf) { }
  
  SinkConverter(SinkConverter const &) = delete;
  SinkConverter(SinkConverter      &&) = delete;
  
  virtual ~SinkConverter() = default;
  
  SinkConverter & operator = (SinkConverter const &) = delete;
  SinkConverter & operator = (SinkConverter      &&) = delete;

  virtual void WriteByte(BYTE const chr) noexcept { sink.WriteByte(chr); }
  
  private:
  
  Formatter::ISink & sink;
};

void Formatter::PrintTxt(char const * text, int length) noexcept
{
  char chr;
  
  while ( (chr = *VERPTR(text)) != '\0' )
  {
    WriteByte(chr);

    length--;
    text++;
  }
  
  WriteByteRepeated(' ', length);
}

void Formatter::PrintTxtQuoted(char const text[]) noexcept
{
  WriteByte('"');
  PrintTxt(VERPTR(text), 1);
  WriteByte('"');
}

void Formatter::PrintChrQuoted(BYTE const chr) noexcept
{
  WriteByte('\'');
  PrintChr(chr);
  WriteByte('\'');
}

void Formatter::PrintUINT32Hex(UINT32 const value, int const digits, int const length, bool const xp) noexcept
{
  SinkConverter converter(sink);
  
  if ( xp && ! prefixed )
    WriteValHex(converter, value, digits, length, "0x");
  else
    WriteValHex(converter, value, digits, length);

  ResetWidth();
}

void Formatter::PrintUINT64Hex(UINT64 const & value, int const digits, int const length, bool const xp) noexcept
{
  SinkConverter converter(sink);
  
  if ( xp && ! prefixed )
    WriteValHex(converter, value, digits, length, "0x");
  else
    WriteValHex(converter, value, digits, length);

  ResetWidth();
}

void Formatter::PrintUINT32Dec(UINT32 const value, int const digits, int const length, bool const pm) noexcept
{
  SinkConverter converter(sink);

  if ( pm )
    WriteValDec(converter, value, digits, length - 1, (value == 0U) ? " " : "+");
  else
    WriteValDec(converter, value, digits, length);

  ResetWidth();
}
  
void Formatter::PrintUINT64Dec(UINT64 const & value, int const digits, int const length, bool const pm) noexcept
{
  SinkConverter converter(sink);

  if ( pm )
    WriteValDec(converter, value, digits, length - 1, (value == 0U) ? " " : "+");
  else
    WriteValDec(converter, value, digits, length);

  ResetWidth();
}
  
void Formatter::PrintSINT32Dec(SINT32 const value, int const digits, int const length, bool const pm) noexcept
{
  /// Bei negativen Werten \b muss immer ein '-' vorangestellt werden. 
  /// Bei positiven Werten ist das Vorzeichen (hier: '+') optional und kann angegeben werden (muss aber nicht).

  if ( value < 0L )
  {
    SinkConverter converter(sink);
    Int32Type const tmp = { -value };

    WriteValDec(converter, tmp.u, digits, length - 1, "-");
    ResetWidth();
  } else 
  {
    Int32Type const tmp = {  value };
    
    PrintUINT32Dec(tmp.u, digits, length, pm);
  }
}

void Formatter::PrintSINT64Dec(SINT64 const & value, int const digits, int const length, bool const pm) noexcept
{
  if ( value < 0LL )
  {
    SinkConverter converter(sink);
    Int64Type const tmp = { -value };

    WriteValDec(converter, tmp.u, digits, length - 1, "-");
    ResetWidth();
  } else 
  {
    Int64Type const tmp = {  value };
    
    PrintUINT64Dec(tmp.u, digits, length, pm);
  }
}

void Formatter::SetFormat(FmtModeType const mode) noexcept
{
  switch(mode)
  {
    case FmtModeType::showSign  : SetSign(); break;
    case FmtModeType::nakedNum  : SetSign(false); break;
    case FmtModeType::plainHex  : SetRadix(RadixMdType::printHex); SetPrefix(false); break;
    case FmtModeType::hexMode   : SetRadix(RadixMdType::printHex); SetPrefix(); break;
    case FmtModeType::decMode   : SetRadix(RadixMdType::printDec); break;
    case FmtModeType::autoHex   : SetRadix(RadixMdType::autoMode); break;
  }
}

void Formatter::WriteByte(BYTE const chr) noexcept
{
  switch(chr)
  {
    case '\0': PrintTxt("\\0", 1); break;
    case '\r': PrintTxt("\\r", 1); break;
    case '\n': PrintTxt("\\n", 1); break;
    case '\a': PrintTxt("\\a", 1); break;
    case '\b': PrintTxt("\\b", 1); break;
    case '\t': PrintTxt("\\t", 1); break;
    case '\v': PrintTxt("\\v", 1); break;
    default:
    history[1] = history[0];
    history[0] = chr;
    prefixed = (chr == 'x' || chr == 'X') && history[1] == '0';

    if ( chr < ' ' || chr >= 127 )
    {
      PrintTxt("\\x");
      PrintUINT32Hex((UINT32)chr, 2, 2, false);
    } else
      sink.WriteByte(chr);
    break;
  }
}


