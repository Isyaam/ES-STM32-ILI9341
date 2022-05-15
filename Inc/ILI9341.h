/// \file ILI9341.h

#ifndef guard_ILI9341_H
# define guard_ILI9341_H

# include <Compiler.h>
# include <Debug.h>
# include <DrvDio.h>
# include <DrvSpi.h>
# include <RB_GPIO.h>
# include <DrvLtdc.h>
# include <RB_LTDC.h>

/* Private defines */
#define ILI9341_RESET				0x01
#define ILI9341_SLEEP_OUT			0x11
#define ILI9341_GAMMA				0x26
#define ILI9341_DISPLAY_OFF			0x28
#define ILI9341_DISPLAY_ON			0x29
#define ILI9341_COLUMN_ADDR			0x2A
#define ILI9341_PAGE_ADDR			0x2B
#define ILI9341_GRAM				0x2C
#define ILI9341_MAC					0x36
#define ILI9341_PIXEL_FORMAT		0x3A
#define ILI9341_WDB					0x51
#define ILI9341_WCD					0x53
#define ILI9341_RGB_INTERFACE		0xB0
#define ILI9341_FRC					0xB1
#define ILI9341_BPC					0xB5
#define ILI9341_DFC					0xB6
#define ILI9341_POWER1				0xC0
#define ILI9341_POWER2				0xC1
#define ILI9341_VCOM1				0xC5
#define ILI9341_VCOM2				0xC7
#define ILI9341_POWERA				0xCB
#define ILI9341_POWERB				0xCF
#define ILI9341_PGAMMA				0xE0
#define ILI9341_NGAMMA				0xE1
#define ILI9341_DTCA				0xE8
#define ILI9341_DTCB				0xEA
#define ILI9341_POWER_SEQ			0xED
#define ILI9341_3GAMMA_EN			0xF2
#define ILI9341_INTERFACE			0xF6
#define ILI9341_PRC					0xF7

#define ILI9341_CS 2
#define ILI9341_WRX 13
#define ILI9341_RST 12


class Ili9341 final{
  public:

  Ili9341() noexcept;

  Ili9341(Ili9341 const &) = delete;
  Ili9341(Ili9341      &&) = delete;

  ~Ili9341() = default;

  Ili9341 & operator = (Ili9341 const &) = delete;
  Ili9341 & operator = (Ili9341      &&) = delete;

//--------------------------------------------------------------
// Register vom ILI9341
//--------------------------------------------------------------

  static constexpr BYTE const ctrlReset      = 0x01;
  static constexpr BYTE const ctrlSleepOut   = 0x11;
  static constexpr BYTE const ctrlDisplayStd = 0x20;
  static constexpr BYTE const ctrlDisplayInv = 0x21;
  static constexpr BYTE const ctrlGamma      = 0x26;
  static constexpr BYTE const ctrlDisplayOff = 0x28;
  static constexpr BYTE const ctrlDisplayOn  = 0x29;
  static constexpr BYTE const ctrlSetCA      = 0x2A;
  static constexpr BYTE const ctrlSetPA      = 0x2B;
  static constexpr BYTE const ctrlWrMemStart = 0x2C;
  static constexpr BYTE const ctrlMAC        = 0x36;
  static constexpr BYTE const ctrlColMod     = 0x3A;
  static constexpr BYTE const ctrlWrMemCont  = 0x3C;
  static constexpr BYTE const ctrlWDB        = 0x51;
  static constexpr BYTE const ctrlWCD        = 0x53;
  static constexpr BYTE const ctrlUnknown    = 0xCA;
  static constexpr BYTE const ctrlPowerA     = 0xCB;
  static constexpr BYTE const ctrlPowerB     = 0xCF;
  static constexpr BYTE const ctrlRgbInterf  = 0xB0;
  static constexpr BYTE const ctrlFRC        = 0xB1;  ///< ILI9341: Frame Rate Control
  static constexpr BYTE const ctrlBPC        = 0xB5;
  static constexpr BYTE const ctrlDFC        = 0xB6;  ///< ILI9341: Display Function Control.
  static constexpr BYTE const ctrlPower1     = 0xC0;
  static constexpr BYTE const ctrlPower2     = 0xC1;
  static constexpr BYTE const ctrlVCOM1      = 0xC5;
  static constexpr BYTE const ctrlVCOM2      = 0xC7;
  static constexpr BYTE const ctrlPGamma     = 0xE0;
  static constexpr BYTE const ctrlNGamma     = 0xE1;
  static constexpr BYTE const ctrlDTCA       = 0xE8;
  static constexpr BYTE const ctrlDTCB       = 0xEA;
  static constexpr BYTE const ctrlPwrOnSeq   = 0xED;
  static constexpr BYTE const ctrl3GammaEna  = 0xF2;
  static constexpr BYTE const ctrlLcdInterf  = 0xF6;
  static constexpr BYTE const ctrlPRC        = 0xF7;

  void Setup() noexcept;

  void Command(BYTE const ctrl) const noexcept { SendCmd(ctrl); }

  template<unsigned NUM>
  void Command(BYTE const ctrl, BYTE const (& bytes)[NUM]) const noexcept { SendCmd(ctrl, bytes, NUM); }
  
  void Command(BYTE const ctrl, BYTE const value) noexcept
  { 
    data[0] = value;

    SendCmd(ctrl, data, 1U);
  }

  void Command(BYTE const ctrl, BYTE const dat0, BYTE const dat1) noexcept
  { 
    data[0] = dat0;
    data[1] = dat1;

    SendCmd(ctrl, data, 2U);
  }

  void Command(BYTE const ctrl, BYTE const dat0, BYTE const dat1, BYTE const dat2) noexcept
  { 
    data[0] = dat0;
    data[1] = dat1;
    data[2] = dat2;

    SendCmd(ctrl, data, 3U);
  }

  void Command(BYTE const ctrl, BYTE const dat0, BYTE const dat1, BYTE const dat2, BYTE const dat3) noexcept
  { 
    data[0] = dat0;
    data[1] = dat1;
    data[2] = dat2;
    data[3] = dat3;

    SendCmd(ctrl, data, 4U);
  }
  
  /// Kommando-Prefix senden (Kommando-Byte).
  /// \param[in] ctrl ist das Kommando-Byte, z.B. ctrlReset für das Reset-Kommando.
  void CmdPrefix(BYTE ctrl) const noexcept;
  
  /// Kommando mit weiteren Daten  senden.
  /// \param[in] ctrl ist das Kommando-Byte, z.B. ctrlReset für das Reset-Kommando.
  /// \param[in] p zeigt auf die Nutzdaten des Kommandos.
  /// \param[in] num gibt die Anzahl der Nutzdatenbytes an.
  void SendCmd(BYTE const ctrl, BYTE const * p = NULL, unsigned num = 0) const noexcept;
	
	void SendCommand(uint8_t data) const noexcept;
	void SendData(uint8_t data) const noexcept;

  /// Kommando ohne Argumente senden.
  /// \param[in] ctrl ist das Kommando-Byte, z.B. ctrlReset für das Reset-Kommando.
  //void SendCmd(BYTE       ctrl) const noexcept;
	
	void Start() noexcept;

  IWrPin & csx;   // chip enable, active low
  IWrPin & dcx;   // 1 = data, 0 = command
	IWrPin & reset;
  ISpi spi;   
  ILtdc ltdc;
  BYTE data[4];
};

#endif
