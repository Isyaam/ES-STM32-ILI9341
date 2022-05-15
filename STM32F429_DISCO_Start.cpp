//
// STM32F429_DISCO_Start.cpp
//
#include <Compiler.h>
#include <Cortex.h>
#include <Debug.h>

#include <STM32Fnxx.h>

#include <RB_RCC.h>

#include <RB_GPIO.h>


#include <DrvDio.h>

#include <ILI9341.h>


using namespace Cortex;

static void Initialize() noexcept
{
  ITM_PUTS("Initializing system ...");
  
  FpuDisable();

  STACK_CHECK();
  ITM_PUTS("System has been initialized");
}

static volatile uint8_t buttonIsPressed = 0;

uint8_t buttonOnPressed() {
	if(rbGPIOA.IDR & 1) {
		if(!buttonIsPressed){
			buttonIsPressed = 1;
			return 1;
		} 
	} else {
		buttonIsPressed = 0;
	}
	
	return 0;
}

/// Program entry.
[[noreturn]] int main()
{
  Initialize();
  
  ASSERT(HClk() == 180000000U);
  ASSERT(IsPrivileged());
  ASSERT(IsThreadMode());
  
  /// Das BASEPRI-Register ist im Start-up-Code auf 0x20 eingestellt worden. Damit kann kein IRQ mit niedrigerer oder gleicher Prio
  /// aktiv werden. Erst mit dem Auruf der nachfolgenden Funktion können alle IRQs aktiv werden.

  SetBASEPRI_privileged(0U);

  /// Indem Bit #0 im CONTROL-Register des Cortex-M4 gesetzt wird, wird der Prozessor in den non-priviliegierten Modus gesetzt.
  /// Damit können diverse, wichtige Einstellungen nicht mehr versehentlich überschrieben werden.
  /// Aber Achtung: Der Exception-Modus ist immer privilegiert, unabhängig von CONTROL[0].
  
  SetCONTROL_privileged(GetCONTROL() | CONTROL_usermode);

  ASSERT(! IsPrivileged());
	
	Ili9341 init;
	init.Start();

	
  endless:
  WFI();
  
	
  goto endless;
}

