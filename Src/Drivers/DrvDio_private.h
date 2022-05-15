/// \file DrvDio_private.h

#ifndef guard_DRV_DIO_PRIVATE_H
# define guard_DRV_DIO_PRIVATE_H

# include <Compiler.h>
# include <Singleton.h>
# include <Debug.h>

# include <DrvDio.h>

# include <RB_GPIO.h>
# include <RB_RCC.h>

class PortBase : public IDio
{
  protected:
  
  PortBase(RegbankTypeGPIO volatile & g) noexcept : 
    gpio(g) 
  { }
  
  public:
  
  PortBase(PortBase const &) = delete;
  PortBase(PortBase      &&) = delete;

  virtual ~PortBase() override = default;

  PortBase & operator = (PortBase const &) = delete;
  PortBase & operator = (PortBase      &&) = delete;

  virtual IRdPin & CreateRdPin(unsigned pin) noexcept override;
  virtual IWrPin & CreateWrPin(unsigned pin) noexcept override;
 
  static constexpr unsigned const maxNumOfPin = 16U;
  
  private:
  
  
  RegbankTypeGPIO volatile & gpio;
  IRdPin * usedReaders[maxNumOfPin] { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
  IWrPin * usedWriters[maxNumOfPin] { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
};

template<RegbankTypeGPIO volatile & GPIO> WORD GpioPeriphery() noexcept;

template<> constexpr WORD GpioPeriphery<rbGPIOA>() noexcept { return PERIPHERY_AHB_GPIOA; }
template<> constexpr WORD GpioPeriphery<rbGPIOB>() noexcept { return PERIPHERY_AHB_GPIOB; }
template<> constexpr WORD GpioPeriphery<rbGPIOC>() noexcept { return PERIPHERY_AHB_GPIOC; }
template<> constexpr WORD GpioPeriphery<rbGPIOD>() noexcept { return PERIPHERY_AHB_GPIOD; }
template<> constexpr WORD GpioPeriphery<rbGPIOE>() noexcept { return PERIPHERY_AHB_GPIOE; }
template<> constexpr WORD GpioPeriphery<rbGPIOF>() noexcept { return PERIPHERY_AHB_GPIOF; }
template<> constexpr WORD GpioPeriphery<rbGPIOG>() noexcept { return PERIPHERY_AHB_GPIOG; }
template<> constexpr WORD GpioPeriphery<rbGPIOH>() noexcept { return PERIPHERY_AHB_GPIOH; }
template<> constexpr WORD GpioPeriphery<rbGPIOI>() noexcept { return PERIPHERY_AHB_GPIOI; }
template<> constexpr WORD GpioPeriphery<rbGPIOJ>() noexcept { return PERIPHERY_AHB_GPIOJ; }
template<> constexpr WORD GpioPeriphery<rbGPIOK>() noexcept { return PERIPHERY_AHB_GPIOK; }

template<RegbankTypeGPIO volatile & GPIO>
class Port final : public PortBase
{
  friend class InstanceWrapper<Port>;
  
  private:
  
  Port() noexcept : PortBase(GPIO) { AHBClockEnable(GpioPeriphery<GPIO>()); }
  
  public:
  
  Port(Port const &) = delete;
  Port(Port      &&) = delete;

  virtual ~Port() override = default;

  Port & operator = (Port const &) = delete;
  Port & operator = (Port      &&) = delete;
};

#endif
