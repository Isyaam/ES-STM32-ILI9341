/// \file DrvDio.cpp
/// Schnittstelle zur Definition der Funktionen zum Zugriff auf einen I/O-Port (Implementierung).

#include <Compiler.h>
#include <MemPool.h>
#include <Debug.h>

#include "DrvDio_private.h"

#if ! defined(NUM_OF_WR_PINS)
# define NUM_OF_WR_PINS         16U
#endif

#if ! defined(NUM_OF_RD_PINS)
# define NUM_OF_RD_PINS         16U
#endif

IDio::~IDio() = default;

IRdPin::~IRdPin() = default;
IWrPin::~IWrPin() = default;

static inline WORD WrGpioMDExt(RegbankTypeGPIO volatile & gpio, unsigned const n, WORD const md, bool const ini0, bool const ini1) noexcept
{
  // Falls gewünscht, Pin-Zustand einstellen.
  if ( ini0 ) gpio.BRR = static_cast<HWRD>(1U << n); else
  if ( ini1 ) gpio.BSR = static_cast<HWRD>(1U << n);

  // Pin-Modus (input vs. output) etc. einstellen.
  return WrGpioMD(gpio, n, md);
}

/// Hilfsklasse, um einen Pin zu initialisieren, auszulesen oder zu setzen.
class PinHelper final
{
  public:

  /// Ctor.
  /// \param g ist eine Referenz auf die GPIO-Registerbank dieses Pins.
  /// \param n ist die Pin-Nummer (0 bis 15 in Bits 0 bis 4, in den höherwertigen Bits Sonderkommandierung).
  PinHelper(RegbankTypeGPIO volatile & g, unsigned const n, WORD const md) noexcept : 
    gpio(g),
    pin(n & 15U)
  { 
    WrGpioSP   (gpio, pin, MASK_GPIO_OSPEEDR_HIGH);
    WrGpioMDExt(gpio, pin, md, (n & IDio::numSet0) != 0U, (n & IDio::numSet1) != 0U);
  }
  
  PinHelper(PinHelper const &) = delete;
  PinHelper(PinHelper      &&) = delete;

  ~PinHelper() = default;

  PinHelper & operator = (PinHelper const &) = delete;
  PinHelper & operator = (PinHelper      &&) = delete;

  bool RdIdr() const noexcept { return (gpio.IDR & static_cast<HWRD>(1U << pin)) != 0U; }
  bool RdOdr() const noexcept { return (gpio.ODR & static_cast<HWRD>(1U << pin)) != 0U; }

  void WrBit(bool const value) noexcept 
  {
    HWRD const mask = static_cast<HWRD>(1U << pin);
    
    (value ? gpio.BSR : gpio.BRR) = mask;
  }  
  
  private:
  
  RegbankTypeGPIO volatile & gpio;
  unsigned const pin;
};

class RdPin final : public IRdPin
{
  public:

  RdPin(RegbankTypeGPIO volatile & g, unsigned const n) noexcept : 
    helper(g, n, MASK_GPIO_MODER_INPUT)
  { }
  
  RdPin(RdPin const &) = delete;
  RdPin(RdPin      &&) = delete;

  virtual ~RdPin() override = default;

  RdPin & operator = (RdPin const &) = delete;
  RdPin & operator = (RdPin      &&) = delete;

  virtual bool Get() const noexcept override;
  
  private:
  
  PinHelper helper;
};

bool RdPin::Get() const noexcept { return helper.RdIdr(); }

class WrPin final : public IWrPin
{
  public:
   
  WrPin(RegbankTypeGPIO volatile & g, unsigned const n) noexcept : 
    helper(g, n, MASK_GPIO_MODER_GPOUT)
  { }
  
  WrPin(WrPin const &) = delete;
  WrPin(WrPin      &&) = delete;

  virtual ~WrPin() override = default;

  WrPin & operator = (WrPin const &) = delete;
  WrPin & operator = (WrPin      &&) = delete;

  virtual bool Get() const noexcept override;
  virtual void Set(bool const value) noexcept override;
  
  private:
  
  PinHelper helper;
};

bool WrPin::Get() const noexcept { return helper.RdOdr(); }
void WrPin::Set(bool const value) noexcept { helper.WrBit(value); }

IRdPin & PortBase::CreateRdPin(unsigned const pin) noexcept
{
  auto const indx = pin & 15U;
  auto & used(usedReaders[indx]);
  
  if ( used == nullptr )
  {
    static MemPool<sizeof(RdPin), NUM_OF_RD_PINS> pool;
    
    used = new(pool.Alloc()) RdPin(gpio, pin);
  }
    
  return *used;
}

IWrPin & PortBase::CreateWrPin(unsigned const pin) noexcept
{
  auto const indx = pin & 15U;
  auto & used(usedWriters[indx]);
  
  if ( used == nullptr )
  {
    static MemPool<sizeof(WrPin), NUM_OF_WR_PINS> pool;
    
    used = new(pool.Alloc()) WrPin(gpio, pin);
  }
  
  return *used;
}
