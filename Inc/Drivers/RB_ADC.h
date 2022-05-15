//
// RB_ADC.h
//

#ifndef guard_RB_ADC_H
# define guard_RB_ADC_H

/// \file RB_ADC.h
/// ADC-spezifische Deklarationen.

# include <RB.h>

/// Datentyp für ADC register bank.
/// STM32F2xx Analog-to-digital Converter (ADC), see reference manual, chapter 10
typedef struct __regbank_ADC
{
  WORD SR;                                            ///< Status register
  WORD CR1;                                           ///< Control register 1
  WORD CR2;                                           ///< Control register 2
  WORD SMPR1;                                         ///< Sample time register 1
  WORD SMPR2;                                         ///< Sample time register 2
  WORD JOFR1;                                         ///< Injected channel data offset register 1
  WORD JOFR2;                                         ///< Injected channel data offset register 2
  WORD JOFR3;                                         ///< Injected channel data offset register 3
  WORD JOFR4;                                         ///< Injected channel data offset register 4
  WORD HTR;                                           ///< Watchdog high threshold register
  WORD LTR;                                           ///< watchdog low threshold register
  WORD SQR1;                                          ///< Regular sequence register 1
  WORD SQR2;                                          ///< Regular sequence register 2
  WORD SQR3;                                          ///< Regular sequence register 3
  WORD JSQR;                                          ///< Injected sequence register
  WORD JDR1;                                          ///< Injected data register 1
  WORD JDR2;                                          ///< Injected data register 2
  WORD JDR3;                                          ///< Injected data register 3
  WORD JDR4;                                          ///< Injected data register 4
  WORD DR;                                            ///< Regular data register
} RegbankTypeADC;

extern RegbankTypeADC volatile rbADC1;                ///< Registerbank für ADC1
extern RegbankTypeADC volatile rbADC2;                ///< Registerbank für ADC2
extern RegbankTypeADC volatile rbADC3;                ///< Registerbank für ADC3


// SR

# define INDX_ADC_SR_AWD        0                     // Analog watchdog flag
# define MASK_ADC_SR_AWD        (WORD)REG_BITMASK(ADC_SR_AWD)

# define INDX_ADC_SR_EOC        1                     // End of conversion
# define MASK_ADC_SR_EOC        (WORD)REG_BITMASK(ADC_SR_EOC)

// CR1

# define INDX_ADC_CR1_AWDEN     23                    // Analog watchdog enable on regular channels
# define MASK_ADC_CR1_AWDEN     (WORD)REG_BITMASK(ADC_CR1_AWDEN)

# define INDX_ADC_CR1_AWDSGL    9                     // Enable the watchdog on a single channel (0) or all channels (1) in scan mode
# define MASK_ADC_CR1_AWDSGL    (WORD)REG_BITMASK(ADC_CR1_AWDSGL)

# define INDX_ADC_CR1_SCAN      8                     // Scan mode (interrupt on EOC of last channel)
# define MASK_ADC_CR1_SCAN      (WORD)REG_BITMASK(ADC_CR1_SCAN)

# define INDX_ADC_CR1_AWDIE     6                     // Analog watchdog interrupt enable
# define MASK_ADC_CR1_AWDIE     (WORD)REG_BITMASK(ADC_CR1_AWDIE)

# define INDX_ADC_CR1_EOCIE     5                     // End of conversion interrupt enable
# define MASK_ADC_CR1_EOCIE     (WORD)REG_BITMASK(ADC_CR1_EOCIE)

# define MASK_ADC_CR1_AWDCH     0x1F                  // Analog watchdog channel selection (0..17)

// CR2

# define INDX_ADC_CR2_SWSTART   30                    // Start conversion of regular channels
# define MASK_ADC_CR2_SWSTART   (WORD)REG_BITMASK(ADC_CR2_SWSTART)

# define INDX_ADC_CR2_JSWSTART  22                    // Start conversion of injected channels
# define MASK_ADC_CR2_JSWSTART  (WORD)REG_BITMASK(ADC_CR2_JSWSTART)

# define INDX_ADC_CR2_DDS       9                     // Enable DMA disable (infinite DMA requests)
# define MASK_ADC_CR2_DDS       (WORD)REG_BITMASK(ADC_CR2_DDS)

# define INDX_ADC_CR2_DMA       8                     // Enable DMA
# define MASK_ADC_CR2_DMA       (WORD)REG_BITMASK(ADC_CR2_DMA)

# define INDX_ADC_CR2_CONT      1                     // Continuous conversion mode
# define MASK_ADC_CR2_CONT      (WORD)REG_BITMASK(ADC_CR2_CONT)

# define INDX_ADC_CR2_ADON      0                     // Enable ADC
# define MASK_ADC_CR2_ADON      (WORD)REG_BITMASK(ADC_CR2_ADON)

// SQR1

# define INDX_ADC_SQR1_L        20                    // Regular channel sequence length
# define MASK_ADC_SQR1_L        (WORD)(0xFU << INDX_ADC_SQR1_L)

#endif
