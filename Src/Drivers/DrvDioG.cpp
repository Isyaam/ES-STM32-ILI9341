#include <Compiler.h>
#include <Singleton.h>

#include "DrvDio_private.h"

IDio & IDio::CreateInstanceA() noexcept { return Singleton<Port<rbGPIOA>>::GetInstance(); }
IDio & IDio::CreateInstanceB() noexcept { return Singleton<Port<rbGPIOB>>::GetInstance(); }
IDio & IDio::CreateInstanceC() noexcept { return Singleton<Port<rbGPIOC>>::GetInstance(); }
IDio & IDio::CreateInstanceD() noexcept { return Singleton<Port<rbGPIOD>>::GetInstance(); }
IDio & IDio::CreateInstanceF() noexcept { return Singleton<Port<rbGPIOF>>::GetInstance(); }
IDio & IDio::CreateInstanceG() noexcept { return Singleton<Port<rbGPIOG>>::GetInstance(); }

