// \file ILI9341.cpp

#include <Compiler.h>
#include <Debug.h>

#include <ILI9341.h>

static constexpr BYTE LsbFromHwrd(HWRD const value) noexcept { return static_cast<BYTE>(value & 0xFFU); }
static constexpr BYTE MsbFromHwrd(HWRD const value) noexcept { return static_cast<BYTE>(value >> 8); }

Ili9341:: Ili9341() noexcept :
  csx((IDio::CreateInstanceC()).CreateWrPin(2)),
  dcx((IDio::CreateInstanceD()).CreateWrPin(13)),
	reset((IDio::CreateInstanceD()).CreateWrPin(12)),
  spi(),
  ltdc()
{
  /* I/O pins und SPI initialisieren */
 
	AHBClockEnable(PERIPHERY_AHB_GPIOD);
	//Init DCX
	WrGpioMD(rbGPIOD, ILI9341_WRX, MASK_GPIO_MODER_GPOUT);
	WrGpioSP(rbGPIOD, ILI9341_WRX, MASK_GPIO_OSPEEDR_MED);
	//Init RST
	WrGpioPUPDR(rbGPIOD, ILI9341_RST, MASK_GPIO_PUPDR_UP);
	WrGpioMD(rbGPIOD, ILI9341_RST, MASK_GPIO_MODER_GPOUT);
	
	//Init CS
	AHBClockEnable(PERIPHERY_AHB_GPIOC);
	WrGpioMD(rbGPIOC, ILI9341_CS, MASK_GPIO_MODER_GPOUT);
	WrGpioSP(rbGPIOC, ILI9341_CS, MASK_GPIO_OSPEEDR_MED);
	
	WrGpioSet(rbGPIOC, ILI9341_CS);
	//Init Ltdc
	ltdc.setPins();
	//Init SPI5
	spi.initSPI();
}

void Ili9341::CmdPrefix(BYTE const ctrl) const noexcept
{
  // Steuerleitungen setzen und Kommando-Byte via SPI senden
}

void Ili9341::SendCmd(BYTE const ctrl, BYTE const * p, unsigned num) const noexcept 
{
	SendCommand(ctrl);
	for(int i = 0; i < num; i++)
	{
		
		SendData(p[i]);
	}
}

void Ili9341::SendCommand(uint8_t data) const noexcept {
	dcx.Clr();
	csx.Clr();
	spi.SPI_Send(data);
	csx.Set();
}

void Ili9341::SendData(uint8_t data) const noexcept {
	dcx.Set();
	csx.Clr();
	spi.SPI_Send(data);
	csx.Set();
}

void Ili9341::Start() noexcept 
{
  // In verschiedenen Quellen (u.a Application-note von ILITEK!) findet man nachfolgende Kommandierung. 
  // Die ILI9341-Doku beschreibt dieses Kommando jedoch nicht. 

  static constexpr BYTE const unknown[] { 0xC3, 0x08, 0x50 }; // <== ???

  Command(ctrlUnknown  , unknown);

  static constexpr BYTE const dataPowerA  [] { 0x39, 0x2C, 0x00, 0x34, 0x02 };

  Command(ctrlPowerA   , dataPowerA  );

  static constexpr BYTE const dataPowerB  [] { 0x00, 0xC1, 0x30 };
  
  Command(ctrlPowerB   , dataPowerB  );

  static constexpr BYTE const dataDTCA    [] { 0x85, 0x00, 0x78 };

  Command(ctrlDTCA     , dataDTCA    );
  Command(ctrlDTCB     , 0x00, 0x00  );

  static constexpr BYTE const dataPwrOnSeq[] { 0x64, 0x03, 0x12, 0x81 };

  Command(ctrlPwrOnSeq , dataPwrOnSeq);

  Command(ctrlPRC      , 0x20);
  Command(ctrlPower1   , 0x23);
  Command(ctrlPower2   , 0x10);
  Command(ctrlVCOM1    , 0x45, 0x15);
  Command(ctrlVCOM2    , 0x90);
  Command(ctrlMAC      , 0xC8);
  Command(ctrlColMod   , 0x65);
 
  Command(ctrlFRC      , 0x00, static_cast<BYTE>(ILtdc::osccklFrequency / ((ILtdc::height + 2U + 2U) * ILtdc::frameRate))); 

  static constexpr BYTE const dataDFC     [] { 0x0A, 0xA2, (ILtdc::height / 8) - 1, ILtdc::pcdivValue };

  Command(ctrlDFC      , dataDFC);
  Command(ctrl3GammaEna, 0x00);
  
  constexpr HWRD const horMax = ILtdc::width - 1U;
  static constexpr BYTE const dataSetCA   [] { 0x00, 0x00, MsbFromHwrd(horMax), LsbFromHwrd(horMax) };

  Command(ctrlSetCA    , dataSetCA);

  constexpr HWRD const verMax = ILtdc::height - 1U;
  static constexpr BYTE const dataSetPA   [] { 0x00, 0x00, MsbFromHwrd(verMax), LsbFromHwrd(verMax) };

  Command(ctrlSetPA    , dataSetPA);
  Command(ctrlGamma    , 0x01);

  static constexpr BYTE const dataPGamma  [] { 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00 };

  Command(ctrlPGamma   , dataPGamma);

  static constexpr BYTE const dataNGamma  [] { 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F };

  Command(ctrlNGamma   , dataNGamma);
  Command(ctrlSleepOut);
  Command(ctrlDisplayOn);
  Command(ctrlRgbInterf, 0xC0); //Seite 154 ILITEK -> Lese Daten aus Memory statt Reg 

  static constexpr BYTE const dataLcdIntrf[] { 0x01, 0x00, 0x06 };

  Command(ctrlLcdInterf, dataLcdIntrf);

	ltdc.initLTDC();
	
}
