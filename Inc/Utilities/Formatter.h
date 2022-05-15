//
// Formatter.h
//

/// \file Formatter.h

#ifndef guard_FORMATTER_H
# define guard_FORMATTER_H

# include <Compiler.h>

class Formatter;

template<typename TYPE> inline void PrintObj(Formatter & fmt, TYPE const & obj) noexcept { obj.ToString(fmt); }

/// Klasse zur allgemeinen Ausgabeformatierung.
/// Dieser Klasse ermöglicht es, beliebige Datentypen in einen Text umzuwandeln, d.h. sie menschenlesbar darzustellen.
/// Hierzu wird ausgabeseitig ein (sequentieller) Bytedatenstrom erzeugt, welcher die ASCII-Zeichen der Textdarstellung beinhaltet.
/// Die zu formatierenden Daten werden nacheinander, in der Reihenfolge des entspr. Funktionsaufrufs dargestellt.
class Formatter 
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
  
  class SinkFromBuf : public Formatter::ISink
  {
    public:
    
    SinkFromBuf(char buffer[], unsigned const dim) noexcept : 
      string(buffer), 
      max(dim - 1U) 
    { 
      Reset(); 
    }

    template<unsigned DIM>
    explicit SinkFromBuf(char (& buffer)[DIM]) noexcept : SinkFromBuf(buffer, DIM) { }
    
    SinkFromBuf(SinkFromBuf const &) = delete;
    SinkFromBuf(SinkFromBuf      &&) = delete;
    
    virtual ~SinkFromBuf() override = default;

    SinkFromBuf & operator = (SinkFromBuf const &) = delete;
    SinkFromBuf & operator = (SinkFromBuf      &&) = delete;
    
    operator char const * () const noexcept { return GetString(); }
    operator unsigned     () const noexcept { return GetLength(); }
    
    unsigned GetLength() const noexcept { return length; }
    
    char const * GetString() const noexcept { return string; }
    
    virtual void WriteByte(BYTE const chr) noexcept override 
    {
      if ( length < max ) 
      {
        string[length++] = chr;
        string[length  ] = '\0';
      }
    }
    
    void Reset() { length = 0U; *string = '\0'; }

    private:
    
    char * const string;
    unsigned const max;
    unsigned length;
  };
  
  /// Ctor.
  /// \param[in] put ist die Datensenke zu Aufnahme des Ausgabe-Datenstroms (ASCII-Zeichen, nicht-darstellbare Zeichen werden kodiert).
  explicit Formatter(ISink & intrf) noexcept : sink(intrf) { }

  Formatter(Formatter const &) = delete;
  Formatter(Formatter      &&) = delete;

  virtual ~Formatter() = default;

  Formatter & operator = (Formatter const &) = delete;
  Formatter & operator = (Formatter      &&) = delete;

  /// Datentype zur Darstellung der Zahlenbasis bei der Ausgabe numerischer Werte.
  enum class RadixMdType
  {
    printDec,                   ///< Dezimale Zahlendarstellung.
    printHex,                   ///< Hexadezimale Zahlendarstellung.    
    autoMode                    ///< Automatische Umschaltung zwischen hexadezimaler (bei führender \c 0x) und dezimaler Darstellung.
  };

  /// Allgemeine Formatierungsangabe.
  /// Diese Aufzählungen lassen sich wie Daten und Objekte in die Ausgabe einfügen. Sie bewirken
  /// nicht, dass Zeichen in den Ausgabestrom hinzugefügt werden, sondern verändern die nachfolgende Art der Formatierung
  /// bzw. bewirken sonstige Sonderfunktionen.
  enum class FmtModeType
  {
    showSign,                   ///< Zahlenwerte immer mit Vorzeichen (Minus- oder Plus-Zeichen) darstellen.
    nakedNum,                   ///< Zahlenwerte nur wenn negativ mit Vorzeichen (Minus-Zeichem) darstellen.
    plainHex,                   ///< Hexadezimale Zahlendarstellung ohne führendes \c 0x aktivieren.
    hexMode,                    ///< Hexadezimale Zahlendarstellung aktivieren.
    decMode,                    ///< Dezimale Zahlendarstellung aktivieren.   
    autoHex                     ///< Automatische hexdezimal/dezimal-Umschaltung aktivieren.
  };

  /// Wrapper, um einzelnes Zeichen codiert (in Hochkommas, Steuerzeichen werden nach der C-Konvention expandiert) auszugeben.
  class AsChr final
  {
    public:

    explicit
    constexpr AsChr(BYTE  const arg)   noexcept : chr(arg)     { }
    constexpr AsChr(AsChr const & org) noexcept : chr(org.chr) { }
    constexpr AsChr(AsChr      && org) noexcept : chr(org.chr) { }

    ~AsChr() = default;
    
    AsChr & operator = (AsChr const &) = delete;
    AsChr & operator = (AsChr      &&) = delete;

    BYTE GetChr() const noexcept { return chr; }

    void ToString(Formatter & fmt) const noexcept { fmt.PrintChr(*this); }

    private:

    BYTE const chr;
  };

  /// Wrapper um einen Text-String codiert (in Hochkommas, Steuerzeichen werden nach der C-Konvention expandiert) auszugeben.
  class AsTxt final
  {
    public:

    explicit
    constexpr AsTxt(char const arg[])  noexcept : text(arg)   { }
    explicit
    constexpr AsTxt(BYTE const arg[])  noexcept : data(arg)   { }
    constexpr AsTxt(AsTxt const & org) noexcept : text(org.text) { }
    constexpr AsTxt(AsTxt      && org) noexcept : text(org.text) { }

    ~AsTxt() = default;

    AsTxt & operator = (AsTxt const &) = delete;
    AsTxt & operator = (AsTxt      &&) = delete;

    char const * GetTxt() const noexcept { return text; }

    void ToString(Formatter & fmt) const noexcept
    { 
      auto const tmp(GetTxt());
      
      if ( tmp == nullptr )
        fmt.PrintTxt("nullptr", 1);
      else
        fmt.PrintTxtQuoted(tmp); 
    }

    private:

    union {
      char const * text;
      BYTE const * data;
    };
  };

  /// Wrapper um Anzahl der Stellen bei numerischen Werten anzugeben.
  class Digits final
  {
    public:

    explicit
    constexpr Digits(int const arg)      noexcept : num(arg)   { }
    constexpr Digits(Digits const & org) noexcept : num(org.num) { }
    constexpr Digits(Digits      && org) noexcept : num(org.num) { }

    ~Digits() = default;
    
    Digits & operator = (Digits const &) = delete;
    Digits & operator = (Digits      &&) = delete;

    int GetNum() const noexcept { return num; }

    void ToString(Formatter & fmt) const noexcept { fmt.SetNumDigits(GetNum()); }

    private:

    int const num;
  };

  /// Wrapper um Feldbreite anzugeben.
  class Length final
  {
    public:

    explicit
    constexpr Length(int const arg)      : num(arg)   { }
    constexpr Length(Length const & org) : num(org.num) { }
    constexpr Length(Length      && org) : num(org.num) { }

    ~Length() = default;

    Length & operator = (Length const &) = delete;
    Length & operator = (Length      &&) = delete;

    int GetNum() const noexcept { return num; }

    void ToString(Formatter & fmt) const noexcept { fmt.SetMinLength(GetNum()); }

    private:

    int const num;
  };

  /// UINT32 dezimal darstellen.
  /// \param[in] value ist der darzustellende Wert.
  /// \param[in] digits gibt die Mindestanzahl der Stellen an, ggf. wird mit Nullen linksseitig aufgefüllt.
  /// \param[in] length gibt die Feldbreite an, ggf. wird mit Leerzeichen linksseitig aufgefüllt.
  /// \param[in] pm ist \c true, wenn der Wert mit führendem Vorzeichen (immer \c '+') dargestellt werden soll.
  void PrintUINT32Dec(UINT32         value, int digits, int length, bool pm = false) noexcept;

  void PrintUINT64Dec(UINT64 const & value, int digits, int length, bool pm = false) noexcept;

  /// SINT32 dezimal darstellen.
  /// \param[in] value ist der darzustellende Wert.
  /// \param[in] digits gibt die Mindestanzahl der Stellen an, ggf. wird mit Nullen linksseitig aufgefüllt.
  /// \param[in] length gibt die Feldbreite an, ggf. wird mit Leerzeichen linksseitig aufgefüllt.
  /// \param[in] pm ist \c true, wenn der Wert mit führendem Vorzeichen (entweder \c '+' oder \c '-') dargestellt werden soll.
  void PrintSINT32Dec(SINT32         value, int digits, int length, bool pm) noexcept;

  void PrintSINT64Dec(SINT64 const & value, int digits, int length, bool pm) noexcept;

  /// UINT32 hexadezimal hexadarstellen.
  /// \param[in] value ist der darzustellende Wert.
  /// \param[in] digits gibt die Mindestanzahl der Stellen an, ggf. wird mit Nullen linksseitig aufgefüllt.
  /// \param[in] length gibt die Feldbreite an, ggf. wird mit Leerzeichen linksseitig aufgefüllt.
  /// \param[in] xp ist \c true, wenn der Hex-Wert mit führendem \c 0x dargestellt werden soll.
  void PrintUINT32Hex(UINT32         value, int digits, int length, bool xp) noexcept;

  void PrintSINT32Hex(SINT32 const   value, int digits, int length, bool xp) noexcept
  {
    Int32Type const tmp = { value };
      
    PrintUINT32Hex(tmp.u, digits, length, xp);
  }
  
  void PrintUINT64Hex(UINT64 const & value, int digits, int length, bool xp) noexcept;

  void PrintSINT64Hex(SINT64 const & value, int digits, int length, bool xp) noexcept
  {
    Int64Type const tmp = { value };
      
    PrintUINT64Hex(tmp.u, digits, length, xp);
  }

  /// UINT32 dezimal darstellen.
  /// \param[in] value ist der darzustellende Wert.
  /// \param[in] digits gibt die Mindestanzahl der Stellen an, ggf. wird mit Nullen linksseitig aufgefüllt.
  void PrintUINT32Dec(UINT32 const   value, int const digits) noexcept { PrintUINT32Dec(value, digits, minlen, sign); }

  void PrintUINT64Dec(UINT64 const & value, int const digits) noexcept { PrintUINT64Dec(value, digits, minlen, sign); }

  /// SINT32 dezimal darstellen.
  /// \param[in] value ist der darzustellende Wert.
  /// \param[in] digits gibt die Mindestanzahl der Stellen an, ggf. wird mit Nullen linksseitig aufgefüllt.
  void PrintSINT32Dec(SINT32 const   value, int const digits) noexcept { PrintSINT32Dec(value, digits, minlen, sign); }

  void PrintSINT64Dec(SINT64 const & value, int const digits) noexcept { PrintSINT64Dec(value, digits, minlen, sign); }

  /// UINT32 hexadezimal hexadarstellen.
  /// \param[in] value ist der darzustellende Wert.
  /// \param[in] digits gibt die Mindestanzahl der Stellen an, ggf. wird mit Nullen linksseitig aufgefüllt.
  void PrintUINT32Hex(UINT32 const   value, int const digits) noexcept { PrintUINT32Hex(value, digits, minlen, mark); }

  void PrintSINT32Hex(SINT32 const   value, int const digits) noexcept { PrintSINT32Hex(value, digits, minlen, mark); }

  void PrintUINT64Hex(UINT64 const & value, int const digits) noexcept { PrintUINT64Hex(value, digits, minlen, mark); }

  void PrintSINT64Hex(SINT64 const & value, int const digits) noexcept { PrintSINT64Hex(value, digits, minlen, mark); }

  /// UINT32 dezimal darstellen.
  /// \param[in] value ist der darzustellende Wert.
  void PrintUINT32Dec(UINT32 const   value) noexcept { PrintUINT32Dec(value, mindig); }

  void PrintUINT64Dec(UINT64 const & value) noexcept { PrintUINT64Dec(value, mindig); }
  
  /// SINT32 dezimal darstellen (Anzahl der Stellen wie zuvor angegeben).
  /// \param[in] value ist der darzustellende Wert.
  void PrintSINT32Dec(SINT32 const   value) noexcept { PrintSINT32Dec(value, mindig); }

  void PrintSINT64Dec(SINT64 const & value) noexcept { PrintSINT64Dec(value, mindig); }

  /// UINT32 hexadezimal hexadarstellen (Anzahl der Stellen wie zuvor angegeben).
  /// \param[in] value ist der darzustellende Wert.
  void PrintUINT32Hex(UINT32 const   value) noexcept { PrintUINT32Hex(value, mindig); }

  void PrintSINT32Hex(SINT32 const   value) noexcept { PrintSINT32Hex(value, mindig); }

  void PrintUINT64Hex(UINT64 const & value) noexcept { PrintUINT64Hex(value, mindig); }

  void PrintSINT64Hex(SINT64 const & value) noexcept { PrintSINT64Hex(value, mindig); }

  /// UINT32 darstellen (je nach aktuellem Modus dezimal oder hexadezimal).
  /// \param[in] value ist der darzustellende Wert.
  void PrintUINT32(UINT32 const value) noexcept
  {
    if ( HexFlag() )
      PrintUINT32Hex(value);
    else
      PrintUINT32Dec(value);
  }

  void PrintUINT64(UINT64 const & value) noexcept
  {
    if ( HexFlag() )
      PrintUINT64Hex(value);
    else
      PrintUINT64Dec(value);
  }

  /// SINT32 darstellen (je nach aktuellem Modus dezimal oder hexadezimal).
  /// \param[in] value ist der darzustellende Wert.
  void PrintSINT32(SINT32 const   value) noexcept
  {
    if ( HexFlag() )
      PrintSINT32Hex(value);
    else
      PrintSINT32Dec(value);
  }

  void PrintSINT64(SINT64 const & value) noexcept
  {
    if ( HexFlag() )
      PrintSINT64Hex(value);
    else
      PrintSINT64Dec(value);
  }

  void PrintArr(BYTE const arr[], unsigned dim, char sep) noexcept;

  template<unsigned DIM>
  inline void PrintArr(BYTE const (& arr)[DIM], char const sep) noexcept { PrintArr(arr, DIM, sep); }

  /// ASCII-Zeichen darstellen.
  /// \param[in] chr ist der ASCII-Code des darzustellenden Zeichens.
  void PrintChr(BYTE const chr) noexcept { WriteByte(chr); ResetWidth(); }

  /// ASCII-Zeichen in einfachen Anführungszeichen darstellen.
  /// \param[in] value stellt den Zeichencode dar.
  void PrintChrQuoted(BYTE const chr) noexcept;

  /// ASCII-Zeichen in einfachen Anführungszeichen darstellen.
  /// \param[in] value stellt den Zeichencode dar.
  void PrintChr(AsChr const & value) noexcept { return PrintChrQuoted(value.GetChr()); }

  /// ASCIIZ-String (zeichenweise, linksbuendig) darstellen.
  /// \param[in] text zeigt auf den darzustellenden Text.
  /// \param[in] length gibt die minimale Feldbreite an, übersteuert die Einstellung von Formater::SetMinLength()
  void PrintTxt(char const * text, int length) noexcept;

  /// ASCIIZ-String (zeichenweise) darstellen.
  /// \param[in] text zeigt auf den darzustellenden Text (Steuerzeichen möglich, werden jedoch sinnvoll dargestellt).
  void PrintTxt(char const * const text) noexcept { PrintTxt(text, minlen); ResetWidth(); }

  /// ASCIIZ-String mit CH_DQUOTE einschliessen und darstellen, Steuerzeichen wie CR oder LF werden nach der C-Konvention expandiert.
  /// \param[in] text zeigt auf den darzustellenden Text (Steuerzeichen erlaubt und werden sinnvoll dargestellt).
  void PrintTxtQuoted(char const * text) noexcept;
  
  /// ASCIIZ-String mit CH_DQUOTE einschliessen und darstellen, Steuerzeichen wie CR oder LF werden nach der C-Konvention expandiert.
  /// \param[in] value beinhaltet den darzustellenden Text (Steuerzeichen erlaubt und werden sinnvoll dargestellt).
  void PrintTxt(AsTxt const & value) noexcept { value.ToString(*this); }

  void Print(UINT64           const   value) noexcept { PrintUINT64(value); }

  void Print(SINT64           const & value) noexcept { PrintSINT64(value); }

  /// \copydoc PrintUINT32(UINT32)
  void Print(UINT32           const   value) noexcept { PrintUINT32(value); }

  /// \copydoc PrintSINT32(SINT32)
  void Print(SINT32           const   value) noexcept { PrintSINT32(value); }

  /// UINT16 darstellen (je nach aktuellem Modus dezimal oder hexadezimal).
  /// \param[in] value ist der darzustellende Wert.
  void Print(UINT16           const   value) noexcept { PrintUINT32(value); }

  /// SINT16 darstellen (je nach aktuellem Modus dezimal oder hexadezimal).
  /// \param[in] value ist der darzustellende Wert.
  void Print(SINT16           const   value) noexcept { PrintSINT32(value); }

  /// UINT08 darstellen (je nach aktuellem Modus dezimal oder hexadezimal).
  /// \param[in] value ist der darzustellende Wert.
  void Print(UINT08           const   value) noexcept { PrintUINT32(value); }

  /// SINT08 darstellen (je nach aktuellem Modus dezimal oder hexadezimal).
  /// \param[in] value ist der darzustellende Wert.
  void Print(SINT08           const   value) noexcept { PrintSINT32(value); }

  /// ASCIIZ-String ohne Anführungszeichen ausgeben.
  /// \param[in] text zeigt auf den ASCIIZ-String.
  /// \note Der auszugebende String sollte nur darstellbare Zeichen beinhalten.
  void Print(char const *     const   text  ) noexcept { PrintTxt(text); }

  /// ASCII-Zeichen ohne Anführungszeichen ausgeben.
  /// \param[in] value ist der ASCII-Code des Zeichens.
  /// \note Das auszugebende Zeichen sollte darstellbar sein.
  void Print(char             const   value) noexcept { PrintChr(value); }

  void Print(FmtModeType      const   value) noexcept { SetFormat(value); }
  void Print(RadixMdType      const   value) noexcept { SetRadix(value); }

  /// Wert eines Boole'sche Variable ausgeben.
  /// \param[in] value ist der Wert der Boole'schen Variable .
  void Print(bool             const   value) noexcept { PrintTxt(value ? "true" : "false", 1); }

  /// Generische Print-Funktion.
  /// \param[in] obj ist die Referenz auf die Instanz des darzustellenden Objektes
  /// \tparam TYPE ist der Datentyp des darzustellenden Objektes (\b muss eine Funktion \c ToString(Formater &) 
  /// oder (alternativ) \c ToString(IPutNoThrow<BYTE> &) implementieren.
  template<typename TYPE> void Print(TYPE const & obj) noexcept { PrintObj(*this, obj); }

  template<typename TYPE, typename ... ARGS> void Print(TYPE const & obj, ARGS const & ... args) noexcept
  {
    Print(obj);
    Print(args ...);
  }

  /// Zahlenbasis kommandieren (persistent, d.h. bleibt gültig bis zum nächsten Aufruf).
  /// \param[in] mode gibt die Zahlenbasis an.
  void SetRadix(RadixMdType const mode) noexcept { radix = mode; }

  RadixMdType GetRadix() const noexcept { return radix; }

  /// Vorzeichenmodus kommandieren.
  /// \param[in] mode ist \c true, wenn alle Dezimalzahlen (auch die positiven oder 0) immer mit Vorzeichen ausgegben werden sollen.
  void SetSign(bool const mode = true) noexcept { sign = mode; }

  /// Kommandieren, ob hexadezimale Darstellungen immer ein führendes "0x" haben sollen.
  /// \param[in] mode ist \c true, wenn alle hexadezimale Darstellungen mit "0x" beginnen sollen.
  void SetPrefix(bool const mode = true) noexcept { mark = mode; }

  /// Feldbreite einstellen (wirkt nur einmal für die nächste Darstellung).
  /// \param[in] length ist die minimale Feldbreite.
  void SetMinLength(int const length) noexcept { minlen = length; }
  
  /// Anzahl der Stellen angeben (wirkt nur einmal für die nächste Darstellung).
  /// Ganze Zahlen können mit führenden Nullen dargestellt werden. Diese Funktion gibt an, über wieviele Stellen die
  /// Darstellung mindestens verfügen soll. Ggf. wird dann linksseitig mit Nullen aufgefüllt. Es ist jedoch auch möglich, dass
  /// mehr Stellen als angegeben zur fehlerfreien Darstellung verwendet werden müssen, z.B. dann wenn die Zahl größer ist, als
  /// durch die angegebene Stellenanzahl definiert.
  /// \param[in] digits gibt die Mindestanzahl der Stellen an.
  void SetNumDigits(int const digits) noexcept { mindig = digits; }

  /// Formatinformation kommandieren.
  /// \param[in] mode beinhaltet die Formatinformation.
  void SetFormat(FmtModeType mode) noexcept;

  void SetCoding(bool const mode) noexcept { coding = mode; }

  bool GetCoding() const noexcept { return coding; }

  /// Rückstellen der Stellenanzahl und Breite.
  void ResetWidth() noexcept
  {
    mindig = 0;
    minlen = 0;
  }

  void WriteByte(BYTE chr) noexcept;

  void WriteByteRepeated(BYTE const chr, int n) noexcept
  {
    while ( n-- > 0 ) 
      WriteByte(chr);
  }
  
  private:

  bool HexFlag() const noexcept { return radix == RadixMdType::printHex || (radix == RadixMdType::autoMode && prefixed); }

  typedef union {
    SINT32 s;
    UINT32 u;
  } Int32Type;

  typedef union {
    SINT64 s;
    UINT64 u;
  } Int64Type;

  ISink & sink;
  int mindig = 1;               ///< Mindestanzahl der Ziffern bei numerischer Darstellung (wird verwendet, wenn keine Mindestanzahl explizit angegeben wurde).
  int minlen = 1;               ///< Default-Wert der aktuellen Mindestfeldbreite (wird verwendet, wenn keine Mindestfeldbreite explizit angegeben wurde).
  RadixMdType radix = RadixMdType::autoMode; ///< Aktuelle Modus um zwischen dezimaler und hexadezimaler Darstellung zu wählen.
  BYTE history[2] { '\0', '\0' }; ///< Puffer für die letzten beiden ausgegbenen Zeichen.
  bool prefixed = false;        ///< Flag; \c true, wenn \c 0x zuletzt ausgegeben.
  bool mark = true;             ///< Flag; \c true, wenn hexadezimale Zahlen immer mit führendem \c 0x dargestellt werden sollen.
  bool sign = false;            ///< Vorzeichen-Flag (ist \c true, wenn immer mit Vorzeichen dargestellt wird, es sein denn es wird explizit übersteuert).
  bool coding = true;
  HWRD reserved = 0;
};

#endif
