/// \file DrvDio.h
/// Schnittstelle zur Definition der Funktionen zum Zugriff auf einen I/O-Port.

#ifndef guard_DRV_DIO_H
# define guard_DRV_DIO_H

class IRdPin 
{
  protected:
  
  constexpr IRdPin() noexcept { }
  
  public:
  
  IRdPin(IRdPin const &) = delete;
  IRdPin(IRdPin      &&) = delete;
  
  virtual ~IRdPin();

  IRdPin & operator = (IRdPin const &) = delete;
  IRdPin & operator = (IRdPin      &&) = delete;

  /// Zustand eines Pins auslesen.
  /// \return \c true, wenn am Eingangs-Pin ein High-Pegel anliegt, \c false, wenn am Eingangs-Pin ein Low-Pegel anliegt.
  virtual bool Get() const noexcept = 0;
};

class IWrPin : public IRdPin
{
  protected:
  
  constexpr IWrPin() noexcept { }
  
  public:
  
  IWrPin(IWrPin const &) = delete;
  IWrPin(IWrPin      &&) = delete;
  
  virtual ~IWrPin();

  IWrPin & operator = (IWrPin const &) = delete;
  IWrPin & operator = (IWrPin      &&) = delete;
  
  /// Zustand des Pins sezen.
  /// \param[in] value ist \c true, wenn der Pin einen High-Pegel ausgeben soll.
  virtual void Set(bool value = true) noexcept = 0;
  
  void Clr() noexcept { Set(false); } 
};

/// Interface zum Zugriff auf einen I/O-Port.
class IDio 
{
  protected:
  
  constexpr IDio() noexcept { }
  
  public:
  
  IDio(IDio const &) = delete;
  IDio(IDio      &&) = delete;
  
  virtual ~IDio();

  IDio & operator = (IDio const &) = delete;
  IDio & operator = (IDio      &&) = delete;

  static constexpr unsigned const numSet0 = 1U << 8U;
  static constexpr unsigned const numSet1 = 1U << 9U;
  
  /// RO-Pin initialisieren. 
  /// \param pin ist die Nummer des Pins (0 bis 15).
  virtual IRdPin & CreateRdPin(unsigned pin) noexcept = 0;

  /// RW-Pin initialisieren. 
  /// \param pin ist die Nummer des Pins (0 bis 15).
  virtual IWrPin & CreateWrPin(unsigned pin) noexcept = 0;
  
  static IDio & CreateInstanceA() noexcept;
  static IDio & CreateInstanceB() noexcept;
  static IDio & CreateInstanceC() noexcept;
  static IDio & CreateInstanceD() noexcept;
  static IDio & CreateInstanceE() noexcept;
  static IDio & CreateInstanceF() noexcept;
  static IDio & CreateInstanceG() noexcept;
  static IDio & CreateInstanceH() noexcept;
  static IDio & CreateInstanceI() noexcept;
  static IDio & CreateInstanceJ() noexcept;
  static IDio & CreateInstanceK() noexcept;
};

#endif
