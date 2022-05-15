/// \file InitSDRAM.cpp
/// Funktion zur Initialisierung des SDRAM.

#include <Compiler.h>

#include <RB_RCC.h>
#include <RB_GPIO.h>
#include <RB_FMC.h>

void InitSDRAM() noexcept
{
  /*
  +----------------------------------------------------------------------------------+
  |                       SDRAM pins assignment                                      |
  +-------------------+--------------------+--------------------+--------------------+
  | PD0  <-> FMC_D2   | PE0  <-> FMC_NBL0  | PF0  <-> FMC_A0    | PG0  <-> FMC_A10   |
  | PD1  <-> FMC_D3   | PE1  <-> FMC_NBL1  | PF1  <-> FMC_A1    | PG1  <-> FMC_A11   |
  | PD8  <-> FMC_D13  | PE7  <-> FMC_D4    | PF2  <-> FMC_A2    | PG8  <-> FMC_SDCLK |
  | PD9  <-> FMC_D14  | PE8  <-> FMC_D5    | PF3  <-> FMC_A3    | PG15 <-> FMC_NCAS  |
  | PD10 <-> FMC_D15  | PE9  <-> FMC_D6    | PF4  <-> FMC_A4    |--------------------+ 
  | PD14 <-> FMC_D0   | PE10 <-> FMC_D7    | PF5  <-> FMC_A5    |   
  | PD15 <-> FMC_D1   | PE11 <-> FMC_D8    | PF11 <-> FMC_NRAS  | 
  +-------------------| PE12 <-> FMC_D9    | PF12 <-> FMC_A6    | 
                      | PE13 <-> FMC_D10   | PF13 <-> FMC_A7    |    
                      | PE14 <-> FMC_D11   | PF14 <-> FMC_A8    |
                      | PE15 <-> FMC_D12   | PF15 <-> FMC_A9    |
  +-------------------+--------------------+--------------------+
  | PB5 <-> FMC_SDCKE1| 
  | PB6 <-> FMC_SDNE1 | 
  | PC0 <-> FMC_SDNWE |
  | PG4 <-> FMC_BA0   |
  | PG5 <-> FMC_BA1   |
  +-------------------+
  */

  AHB1ClockEnableByMask(
  (1U << INDX_RCC_AHB1_GPIOB) |
  (1U << INDX_RCC_AHB1_GPIOC) |
  (1U << INDX_RCC_AHB1_GPIOD) |
  (1U << INDX_RCC_AHB1_GPIOE) |
  (1U << INDX_RCC_AHB1_GPIOF) |
  (1U << INDX_RCC_AHB1_GPIOG));

  static constexpr BYTE const bPins[] = {                5, 6                                  };
  static constexpr BYTE const dPins[] = { 0, 1,                   8, 9, 10,             14, 15 };
  static constexpr BYTE const ePins[] = { 0, 1,                7, 8, 9, 10, 11, 12, 13, 14, 15 };
  static constexpr BYTE const fPins[] = { 0, 1, 2, 3, 4, 5,                 11, 12, 13, 14, 15 };
  static constexpr BYTE const gPins[] = { 0, 1,       4, 5,       8,                        15 };
  
  EnableAF(rbGPIOB, MASK_GPIO_AFR_AF12, MASK_GPIO_OSPEEDR_HIGH, false, bPins);
  EnableAF(rbGPIOC, MASK_GPIO_AFR_AF12, MASK_GPIO_OSPEEDR_HIGH, false, 0U);
  EnableAF(rbGPIOD, MASK_GPIO_AFR_AF12, MASK_GPIO_OSPEEDR_HIGH, false, dPins);
  EnableAF(rbGPIOE, MASK_GPIO_AFR_AF12, MASK_GPIO_OSPEEDR_HIGH, false, ePins);
  EnableAF(rbGPIOF, MASK_GPIO_AFR_AF12, MASK_GPIO_OSPEEDR_HIGH, false, fPins);
  EnableAF(rbGPIOG, MASK_GPIO_AFR_AF12, MASK_GPIO_OSPEEDR_HIGH, false, gPins);
  
  AHBClockEnable(PERIPHERY_AHB_FMC);

  rbFMC.SDCR1 = MASK_FMC_SDCRx_SDCLK_2HCLK | MASK_FMC_SDCRx_RPIPE_1HCLK;
  rbFMC.SDCR2 = MASK_FMC_SDCRx_CAS_3 | MASK_FMC_SDCRx_NC_08 | MASK_FMC_SDCRx_NR_12 | MASK_FMC_SDCRx_MWID_16 | MASK_FMC_SDCRx_NB;
  rbFMC.SDTR1 = (7U << INDX_FMC_SDTRx_TRC) | (2U << INDX_FMC_SDTRx_TRP);
  rbFMC.SDTR2 = (2U << INDX_FMC_SDTRx_TWR) | (4U << INDX_FMC_SDTRx_TRAS) | (7U << INDX_FMC_SDTRx_TXSR) | (1U << INDX_FMC_SDTRx_TMRD);
  
  for ( unsigned volatile i = 0U; i < 500000U; i++ ) { Cortex::DSB(); }
  
  SDRAM_Command(MASK_FMC_CMR_MODE_CLK_CFG_ENABLE | MASK_FMC_SDCMR_CTB2 | (1U << INDX_FMC_SDCMR_NRFS));
  SDRAM_Command(MASK_FMC_CMR_MODE_PALL           | MASK_FMC_SDCMR_CTB2 | (1U << INDX_FMC_SDCMR_NRFS));
  SDRAM_Command(MASK_FMC_CMR_MODE_AUTO_REFRESH   | MASK_FMC_SDCMR_CTB2 | (4U << INDX_FMC_SDCMR_NRFS));
  SDRAM_Command(MASK_FMC_CMR_MODE_AUTO_REFRESH   | MASK_FMC_SDCMR_CTB2 | (4U << INDX_FMC_SDCMR_NRFS));
  SDRAM_Command(MASK_FMC_CMR_MODE_LOAD_MODE      | MASK_FMC_SDCMR_CTB2 | (1U << INDX_FMC_SDCMR_NRFS) |
  (SDRAM_MRD_BURST_LENGTH_2 | SDRAM_MRD_BURST_TYPE_SEQUENTIAL | SDRAM_MRD_CAS_LATENCY_3 | SDRAM_MRD_OPERATING_MODE_STANDARD | SDRAM_MRD_WRITEBURST_MODE_SINGLE) << INDX_FMC_SDCMR_MRD);

  while ( FMC_SDSR_IsBusy() ) { }

  rbFMC.SDRTR = 1386U << 1;
}

