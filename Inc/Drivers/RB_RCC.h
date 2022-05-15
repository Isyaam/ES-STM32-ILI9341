 //
// RB_RCC.h
//

/// \file RB_RCC.h
/// Reset and clock control (RCC).

#ifndef guard_RB_RCC_H
# define  guard_RB_RCC_H

# include <RB.h>

/// Registerbank für RCC
typedef struct __regbank_RCC
{
  WORD CR;                                            ///< Control register.
  WORD PLLCFGR;                                       ///< PLL configuration register.
  WORD CFGR;                                          ///< Configuration register.
  WORD CIR;                                           ///< clock interrupt register.
  WORD AHB1RSTR;                                      ///< AHB1 peripheral reset register.
  WORD AHB2RSTR;                                      ///< AHB2 peripheral reset register.
  WORD AHB3RSTR;                                      ///< AHB3 peripheral reset register.

  WORD reserved0;

  WORD APB1RSTR;                                      ///< APB1 peripheral reset register.
  WORD APB2RSTR;                                      ///< APB2 peripheral reset register.

  WORD reserved1[2];

  union {
    struct {
      WORD AHB1ENR;                                   ///< AHB1 enable register.
      WORD AHB2ENR;                                   ///< AHB2 enable register.
      WORD AHB3ENR;                                   ///< AHB3 enable register.
    };
    WORD AHBENR[3];                                   ///< AHB1..3 enable registers.
  };

  WORD reserved2;

  union {
    struct {
      WORD APB1ENR;                                   ///< APB1 enable registers.
      WORD APB2ENR;                                   ///< APB2 enable registers.
    };
    WORD APBENR[2];                                   ///< APB1..2 enable registers.
  };
  
  WORD reserved3[2];
  
  WORD AHB1LPENR;
  WORD AHB2LPENR;
  WORD AHB3LPENR;
  WORD reserved4;
  WORD APB1LPENR;
  WORD APB2LPENR;
  WORD reserved5[2];
  
  WORD BDCR;                                          ///< Backup domain control register.
  WORD CSR;                                           ///< Control & status register.

  WORD reserved6[2];

  WORD SSCGR;                                         ///< Spread spectrum clock generation register.
  WORD PLLI2SCFGR;                                    ///< PLLI2S configuration register.
  WORD PLLSAICFGR;
  WORD DCKCFGR;
} RegbankTypeRCC;

extern RegbankTypeRCC volatile 	rbRCC;                 ///< RCC-Registerbank.

static_assert(offsetof(RegbankTypeRCC, PLLSAICFGR) == 0x88, "Invalid RegbankTypeRCC [PLLSAICFGR]");
static_assert(offsetof(RegbankTypeRCC, DCKCFGR) == 0x8C, "Invalid RegbankTypeRCC [DCKCFGR]");

/// \cond RB_DEFS

// CR

# define INDX_RCC_CR_HSEON      16
# define MASK_RCC_CR_HSEON      (WORD)REG_BITMASK(RCC_CR_HSEON)

# define INDX_RCC_CR_HSERDY     17 
# define MASK_RCC_CR_HSERDY     (WORD)REG_BITMASK(RCC_CR_HSERDY)

# define INDX_RCC_CR_PLLON      24 
# define MASK_RCC_CR_PLLON      (WORD)REG_BITMASK(RCC_CR_PLLON)

# define INDX_RCC_CR_PLLRDY     25 
# define MASK_RCC_CR_PLLRDY     (WORD)REG_BITMASK(RCC_CR_PLLRDY)

# define INDX_RCC_CR_PLLI2SON   26 
# define MASK_RCC_CR_PLLI2SON   (WORD)REG_BITMASK(RCC_CR_PLLI2SON)

# define INDX_RCC_CR_PLLI2SRDY  27 
# define MASK_RCC_CR_PLLI2SRDY  (WORD)REG_BITMASK(RCC_CR_PLLI2SRDY)

# define INDX_RCC_CR_PLLSAION   28 
# define MASK_RCC_CR_PLLSAION   (WORD)REG_BITMASK(RCC_CR_PLLSAION)

# define INDX_RCC_CR_PLLSAIRDY  29
# define MASK_RCC_CR_PLLSAIRDY  (WORD)REG_BITMASK(RCC_CR_PLLSAIRDY)

// CFGR

# define INDX_RCC_CFGR_SW       0 
# define MASK_RCC_CFGR_SW       (WORD)0x3
# define MASK_RCC_CFGR_SW_HSI   (WORD)0x0
# define MASK_RCC_CFGR_SW_HSE   (WORD)0x1
# define MASK_RCC_CFGR_SW_PLL   (WORD)0x2

# define INDX_RCC_CFGR_SWS      2 
# define MASK_RCC_CFGR_SWS      (WORD)(MASK_RCC_CFGR_SW     << INDX_RCC_CFGR_SWS)
# define MASK_RCC_CFGR_SWS_HSI  (WORD)(MASK_RCC_CFGR_SW_HSI << INDX_RCC_CFGR_SWS)
# define MASK_RCC_CFGR_SWS_HSE  (WORD)(MASK_RCC_CFGR_SW_HSE << INDX_RCC_CFGR_SWS)
# define MASK_RCC_CFGR_SWS_PLL  (WORD)(MASK_RCC_CFGR_SW_PLL << INDX_RCC_CFGR_SWS)

# define INDX_RCC_CFGR_HPRE     4                     /// AHB prescaler: HCLK = SYSCLK / HPRE.
# define MASK_RCC_CFGR_HPRE     (WORD)(0xFU << INDX_RCC_CFGR_HPRE)
# define MASK_RCC_CFGR_HPRE_001 (WORD)(0x0U << INDX_RCC_CFGR_HPRE)
# define MASK_RCC_CFGR_HPRE_002 (WORD)(0x8U << INDX_RCC_CFGR_HPRE)
# define MASK_RCC_CFGR_HPRE_004 (WORD)(0x9U << INDX_RCC_CFGR_HPRE)
# define MASK_RCC_CFGR_HPRE_008 (WORD)(0xAU << INDX_RCC_CFGR_HPRE)
# define MASK_RCC_CFGR_HPRE_016 (WORD)(0xBU << INDX_RCC_CFGR_HPRE)
# define MASK_RCC_CFGR_HPRE_064 (WORD)(0xCU << INDX_RCC_CFGR_HPRE)
# define MASK_RCC_CFGR_HPRE_128 (WORD)(0xDU << INDX_RCC_CFGR_HPRE)
# define MASK_RCC_CFGR_HPRE_256 (WORD)(0xEU << INDX_RCC_CFGR_HPRE)
# define MASK_RCC_CFGR_HPRE_512 (WORD)(0xFU << INDX_RCC_CFGR_HPRE)

# define INDX_RCC_CFGR_PPRE1    10                    ///< APB1 prescaler: PCLK1 = HCLK / PRE1.
# define MASK_RCC_CFGR_PPRE1    (WORD)(0x7U << INDX_RCC_CFGR_PPRE1)
# define MASK_RCC_CFGR_PPRE1_01 (WORD)(0x0U << INDX_RCC_CFGR_PPRE1)
# define MASK_RCC_CFGR_PPRE1_02 (WORD)(0x4U << INDX_RCC_CFGR_PPRE1)
# define MASK_RCC_CFGR_PPRE1_04 (WORD)(0x5U << INDX_RCC_CFGR_PPRE1)
# define MASK_RCC_CFGR_PPRE1_08 (WORD)(0x6U << INDX_RCC_CFGR_PPRE1)
# define MASK_RCC_CFGR_PPRE1_16 (WORD)(0x7U << INDX_RCC_CFGR_PPRE1)

# define INDX_RCC_CFGR_PPRE2    13                    ///< APB2 prescaler: PCLK2 = HCLK / PRE2.
# define MASK_RCC_CFGR_PPRE2    (WORD)(0x7U << INDX_RCC_CFGR_PPRE2)
# define MASK_RCC_CFGR_PPRE2_01 (WORD)(0x0U << INDX_RCC_CFGR_PPRE2)
# define MASK_RCC_CFGR_PPRE2_02 (WORD)(0x4U << INDX_RCC_CFGR_PPRE2)
# define MASK_RCC_CFGR_PPRE2_04 (WORD)(0x5U << INDX_RCC_CFGR_PPRE2)
# define MASK_RCC_CFGR_PPRE2_08 (WORD)(0x6U << INDX_RCC_CFGR_PPRE2)
# define MASK_RCC_CFGR_PPRE2_16 (WORD)(0x7U << INDX_RCC_CFGR_PPRE2)

# define INDX_RCC_CFGR_I2SSRC   23
# define MASK_RCC_CFGR_I2SSRC   (WORD)REG_BITMASK(RCC_CFGR_I2SSRC)
  
// PLLCFGR

# define INDX_RCC_PLLCFGR_PLLM  0
# define MASK_RCC_PLLCFGR_PLLM  (WORD)(0x03FU << INDX_RCC_PLLCFGR_PLLM)  

# define INDX_RCC_PLLCFGR_PLLN  6
# define MASK_RCC_PLLCFGR_PLLN  (WORD)(0x1FFU << INDX_RCC_PLLCFGR_PLLN)  

# define INDX_RCC_PLLCFGR_PLLP  16
# define MASK_RCC_PLLCFGR_PLLP  (WORD)(0x003U << INDX_RCC_PLLCFGR_PLLP)  

# define INDX_RCC_PLLCFGR_PLLQ  24
# define MASK_RCC_PLLCFGR_PLLQ  (WORD)(0x00FU << INDX_RCC_PLLCFGR_PLLQ)  

# define INDX_RCC_PLLCFGR_PLLSRC 22
# define MASK_RCC_PLLCFGR_PLLSRC (WORD)REG_BITMASK(RCC_PLLCFGR_PLLSRC)

# define MASK_RCC_PLLCFGR       (MASK_RCC_PLLCFGR_PLLM | MASK_RCC_PLLCFGR_PLLN | MASK_RCC_PLLCFGR_PLLP | MASK_RCC_PLLCFGR_PLLQ | MASK_RCC_PLLCFGR_PLLSRC)

// BDCR

# define INDX_RCC_BDCR_LSEON    0
# define MASK_RCC_BDCR_LSEON    (WORD)REG_BITMASK(RCC_BDCR_LSEON)

# define INDX_RCC_BDCR_LSERDY   1
# define MASK_RCC_BDCR_LSERDY   (WORD)REG_BITMASK(RCC_BDCR_LSERDY)

# define INDX_RCC_BDCR_RTCSEL   8
# define MASK_RCC_BDCR_RTCSEL   (WORD)(0x3U << INDX_RCC_BDCR_RTCSEL)
# define MASK_RCC_BDCR_RTCSEL_OFF (WORD)(0x0U << INDX_RCC_BDCR_RTCSEL)
# define MASK_RCC_BDCR_RTCSEL_LSE (WORD)(0x1U << INDX_RCC_BDCR_RTCSEL)
# define MASK_RCC_BDCR_RTCSEL_LSI (WORD)(0x2U << INDX_RCC_BDCR_RTCSEL)
# define MASK_RCC_BDCR_RTCSEL_HSE (WORD)(0x3U << INDX_RCC_BDCR_RTCSEL)

# define INDX_RCC_BDCR_RTCEN    15
# define MASK_RCC_BDCR_RTCEN    (WORD)REG_BITMASK(RCC_BDCR_RTCEN)

// SSCGR

# define INDX_RCC_SSCGR_MODPER  0                     // MODPER = round(f_PLL_IN / (4 * f_mod))
                                                      // f_mod = modulation frequency, max. 10 kHz

# define INDX_RCC_SSCGR_INCSTEP 13                    // INCSTEP = round((0xFFFFU * md * PLLN) / (100 * 5 * MODPER))
                                                      // md = peak modulation depth (in percent, max 2 %, min 0.25 %)
                                                      // MODPER * INCSTEP <= 0xFFFFU

# define INDX_RCC_SSCGR_SPREADSEL 30
# define MASK_RCC_SSCGR_SPREADSEL (WORD)REG_BITMASK(RCC_SSCGR_SPREADSEL)

# define INDX_RCC_SSCGR_SSCGEN  31
# define MASK_RCC_SSCGR_SSCGEN  (WORD)REG_BITMASK(RCC_SSCGR_SSCGEN)

// PLLI2SCFGR

# define INDX_RCC_PLLI2SCFGR_N  6
# define MASK_RCC_PLLI2SCFGR_N  (WORD)(0x1FFU << INDX_RCC_PLLI2SCFGR_N)

# define INDX_RCC_PLLI2SCFGR_R  28
# define MASK_RCC_PLLI2SCFGR_R  (WORD)(0x7U << INDX_RCC_PLLI2SCFGR_R)

// PLLSAICFGR

# define INDX_RCC_PLLSAICFGR_PLLSAIR 28

# define INDX_RCC_PLLSAICFGR_PLLSAIQ 24

# define INDX_RCC_PLLSAICFGR_PLLSAIP 16

# define INDX_RCC_PLLSAICFGR_PLLSAIN 6

// DCKCFGR

# define INDX_RCC_DCKCFGR_PLLI2SDIVQ 0
# define MASK_RCC_DCKCFGR_PLLI2SDIVQ (WORD)(0x1FU << INDX_RCC_DCKCFGR_PLLI2SDIVQ)

# define INDX_RCC_DCKCFGR_PLLSAIDIVQ 8
# define MASK_RCC_DCKCFGR_PLLSAIDIVQ (WORD)(0x1FU << INDX_RCC_DCKCFGR_PLLSAIDIVQ)

# define INDX_RCC_DCKCFGR_PLLSAIDIVR 16
# define MASK_RCC_DCKCFGR_PLLSAIDIVR (WORD)(0x3U << INDX_RCC_DCKCFGR_PLLSAIDIVR)

# define INDX_RCC_DCKCFGR_SAI1ASRC 20
# define MASK_RCC_DCKCFGR_SAI1ASRC (WORD)(3U << INDX_RCC_DCKCFGR_SAI1ASRC)

# define INDX_RCC_DCKCFGR_SAI1BSRC 22
# define MASK_RCC_DCKCFGR_SAI1BSRC (WORD)(3U << INDX_RCC_DCKCFGR_SAI1BSRC)

# define INDX_RCC_DCKCFGR_TIMPRE 24
# define MASK_RCC_DCKCFGR_TIMPRE (WORD)REG_BITMASK(RCC_DCKCFGR_TIMPRE)

/// \endcond

# include <RB_RCC_AHB.h>

# define PERIPHERY_INDX_POS     8U
  
# define PERIPHERY_APB_1        (0 << PERIPHERY_INDX_POS)
# define PERIPHERY_APB_2        (1 << PERIPHERY_INDX_POS)

# define PERIPHERY_APB_TIM02    (PERIPHERY_APB_1 |  0U)
# define PERIPHERY_APB_TIM03    (PERIPHERY_APB_1 |  1U)
# define PERIPHERY_APB_TIM04    (PERIPHERY_APB_1 |  2U)
# define PERIPHERY_APB_TIM05    (PERIPHERY_APB_1 |  3U)
# define PERIPHERY_APB_TIM06    (PERIPHERY_APB_1 |  4U)
# define PERIPHERY_APB_TIM07    (PERIPHERY_APB_1 |  5U)
# define PERIPHERY_APB_TIM12    (PERIPHERY_APB_1 |  6U)
# define PERIPHERY_APB_TIM13    (PERIPHERY_APB_1 |  7U)
# define PERIPHERY_APB_TIM14    (PERIPHERY_APB_1 |  8U)
# define PERIPHERY_APB_SPI2     (PERIPHERY_APB_1 | 14U)
# define PERIPHERY_APB_SPI3     (PERIPHERY_APB_1 | 15U)
# define PERIPHERY_APB_USART2   (PERIPHERY_APB_1 | 17U)
# define PERIPHERY_APB_USART3   (PERIPHERY_APB_1 | 18U)
# define PERIPHERY_APB_UART4    (PERIPHERY_APB_1 | 19U)
# define PERIPHERY_APB_UART5    (PERIPHERY_APB_1 | 20U)
# define PERIPHERY_APB_I2C1     (PERIPHERY_APB_1 | 21U)
# define PERIPHERY_APB_I2C2     (PERIPHERY_APB_1 | 22U)
# define PERIPHERY_APB_I2C3     (PERIPHERY_APB_1 | 23U)
# define PERIPHERY_APB_CAN1     (PERIPHERY_APB_1 | 25U)
# define PERIPHERY_APB_CAN2     (PERIPHERY_APB_1 | 26U)
# define PERIPHERY_APB_PWR      (PERIPHERY_APB_1 | 28U)
# define PERIPHERY_APB_DAC      (PERIPHERY_APB_1 | 29U)

# define PERIPHERY_APB_TIM01    (PERIPHERY_APB_2 |  0U)
# define PERIPHERY_APB_TIM08    (PERIPHERY_APB_2 |  1U)
# define PERIPHERY_APB_USART1   (PERIPHERY_APB_2 |  4U)
# define PERIPHERY_APB_USART6   (PERIPHERY_APB_2 |  5U)
# define PERIPHERY_APB_ADC1     (PERIPHERY_APB_2 |  8U)
# define PERIPHERY_APB_ADC2     (PERIPHERY_APB_2 |  9U)
# define PERIPHERY_APB_ASC3     (PERIPHERY_APB_2 | 10U)
# define PERIPHERY_APB_SDIO     (PERIPHERY_APB_2 | 11U)
# define PERIPHERY_APB_SPI1     (PERIPHERY_APB_2 | 12U)
# define PERIPHERY_APB_SPI4     (PERIPHERY_APB_2 | 13U)
# define PERIPHERY_APB_SYSCFG   (PERIPHERY_APB_2 | 14U)
# define PERIPHERY_APB_TIM09    (PERIPHERY_APB_2 | 16U)
# define PERIPHERY_APB_TIM10    (PERIPHERY_APB_2 | 17U)
# define PERIPHERY_APB_TIM11    (PERIPHERY_APB_2 | 18U)
# define PERIPHERY_APB_SPI5     (PERIPHERY_APB_2 | 20U)
# define PERIPHERY_APB_SPI6     (PERIPHERY_APB_2 | 21U)
# define PERIPHERY_APB_SAI1     (PERIPHERY_APB_2 | 22U)
# define PERIPHERY_APB_LTDC     (PERIPHERY_APB_2 | 26U)

# define PERIPHERY_AHB_1        (0 << PERIPHERY_INDX_POS)
# define PERIPHERY_AHB_2        (1 << PERIPHERY_INDX_POS)
# define PERIPHERY_AHB_3        (2 << PERIPHERY_INDX_POS)
                                                                
# define PERIPHERY_AHB_CCM      (PERIPHERY_AHB_1 | INDX_RCC_AHB1_CCM)
# define PERIPHERY_AHB_TCM      (PERIPHERY_AHB_1 | INDX_RCC_AHB1_TCM)
# define PERIPHERY_AHB_DMA2     (PERIPHERY_AHB_1 | INDX_RCC_AHB1_DMA2)
# define PERIPHERY_AHB_DMA1     (PERIPHERY_AHB_1 | INDX_RCC_AHB1_DMA1)
# define PERIPHERY_AHB_BKPSRAM  (PERIPHERY_AHB_1 | INDX_RCC_AHB1_BKPSRAM)
# define PERIPHERY_AHB_CRC      (PERIPHERY_AHB_1 | INDX_RCC_AHB1_CRC)
# define PERIPHERY_AHB_GPIOK    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_GPIOK)
# define PERIPHERY_AHB_GPIOJ    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_GPIOJ)
# define PERIPHERY_AHB_GPIOI    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_GPIOI)
# define PERIPHERY_AHB_GPIOH    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_GPIOH)
# define PERIPHERY_AHB_GPIOG    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_GPIOG)
# define PERIPHERY_AHB_GPIOF    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_GPIOF)
# define PERIPHERY_AHB_GPIOE    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_GPIOE)
# define PERIPHERY_AHB_GPIOD    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_GPIOD)
# define PERIPHERY_AHB_GPIOC    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_GPIOC)
# define PERIPHERY_AHB_GPIOB    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_GPIOB)
# define PERIPHERY_AHB_GPIOA    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_GPIOA)
# define PERIPHERY_AHB_DMA_2D   (PERIPHERY_AHB_1 | INDX_RCC_AHB1_DMA_2D)
# define PERIPHERY_AHB_ETHMAC   (PERIPHERY_AHB_1 | INDX_RCC_AHB1_ETHMAC)
# define PERIPHERY_AHB_ETHTX    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_ETHTX)
# define PERIPHERY_AHB_ETHRX    (PERIPHERY_AHB_1 | INDX_RCC_AHB1_ETHRX)
# define PERIPHERY_AHB_ETHPTP   (PERIPHERY_AHB_1 | INDX_RCC_AHB1_ETHPTP)

# define PERIPHERY_AHB_RNG      (PERIPHERY_AHB_2 | INDX_RCC_AHB2_RNG)
# define PERIPHERY_AHB_DCMI     (PERIPHERY_AHB_2 | INDX_RCC_AHB2_DCMI)

# define PERIPHERY_AHB_FMC      (PERIPHERY_AHB_3 | INDX_RCC_AHB3_FMC)

# include <Atomic.h>

inline void AHB1ClockEnableByMask(WORD const mask) noexcept
{
  Atomic::Orr(rbRCC.AHBENR[0], mask);
}

# define AHB1_ENABLE(M)         AHB1ClockEnableByMask(1U << INDX_RCC_AHB1_ ## M)

/// Takt einer AHB-Peripherie einschalten.
/// \param[in] num kennzeichnet die AHB-Periphery.
inline void AHBClockEnable(WORD const num) noexcept
{
  auto const i = num >> PERIPHERY_INDX_POS;
  auto const n = num % 32U;
  
  Atomic::Orr(rbRCC.AHBENR[i], 1U << n);
}

/// Takt einer APB-Peripherie einschalten.
/// \param[in] num kennzeichnet die APB-Periphery.
inline void APBClockEnable(WORD const num) noexcept
{
  auto const i = num >> PERIPHERY_INDX_POS;
  auto const n = num % 32U;
  
  Atomic::Orr(rbRCC.APBENR[i], 1U << n);
}

#endif
