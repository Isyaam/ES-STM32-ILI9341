//
// RB_GPIO.H
//

/// \file RB_GPIO.h
/// General Purpose I/O

#ifndef guard_RB_GPIO_H
# define guard_RB_GPIO_H

# include <RB.h>

/// Datentyp für GPIO-Registerbank.
typedef struct __regbank_GPIO
{
  WORD MODER;                   ///< Mode register.
  HWRD OTYPER;                  ///< Output type register.
  HWRD dontTouchMe0;

  WORD OSPEEDR;                 ///< Output sp register.
  WORD PUPDR;                   ///< Pull-up/pull-down register

  HWRD IDR;                     ///< Input data register.
  HWRD dontTouchMe1;

  HWRD ODR;                     ///< Output data register.
  HWRD dontTouchMe2;

  union {
    struct {
      HWRD BSR;                 ///< Bit set register.     
      HWRD BRR;                 ///< Bit reset register.
    };
    
    WORD BSRR;                  ///< Bit set reset register.
  };

  WORD LCKR;                    ///< Lock register.

  union {
    struct {
      WORD AFRL;                ///< Alternate function register low.
      WORD AFRH;                ///< Alternate function register high.
    };
    
    WORD AFR[2];                ///< Alternate function registers.
  };
} RegbankTypeGPIO;

extern RegbankTypeGPIO volatile rbGPIOA;              ///< GPIOA-Registerbank.
extern RegbankTypeGPIO volatile rbGPIOB;              ///< GPIOB-Registerbank.
extern RegbankTypeGPIO volatile rbGPIOC;              ///< GPIOC-Registerbank.
extern RegbankTypeGPIO volatile rbGPIOD;              ///< GPIOD-Registerbank.
extern RegbankTypeGPIO volatile rbGPIOE;              ///< GPIOE-Registerbank.
extern RegbankTypeGPIO volatile rbGPIOF;              ///< GPIOF-Registerbank.
extern RegbankTypeGPIO volatile rbGPIOG;              ///< GPIOG-Registerbank.
extern RegbankTypeGPIO volatile rbGPIOH;              ///< GPIOH-Registerbank.
extern RegbankTypeGPIO volatile rbGPIOI;              ///< GPIOI-Registerbank.
extern RegbankTypeGPIO volatile rbGPIOJ;              ///< GPIOJ-Registerbank.
extern RegbankTypeGPIO volatile rbGPIOK;              ///< GPIOK-Registerbank.

/// \cond RB_DEFS

// MODER

# define MASK_GPIO_MODER_INPUT  0x0U
# define MASK_GPIO_MODER_GPOUT  0x1U
# define MASK_GPIO_MODER_ALTFNC 0x2U
# define MASK_GPIO_MODER_ANALOG 0x3U
# define MASK_GPIO_MODER        0x3U

// PUPDR

# define MASK_GPIO_PUPDR        0x3U
# define MASK_GPIO_PUPDR_NOTHING 0U
# define MASK_GPIO_PUPDR_UP     1U
# define MASK_GPIO_PUPDR_DOWN   2U
# define MASK_GPIO_PUPDR_UPDOWN 3U

// OTYPER

# define MASK_GPIO_OTYPER       1U
# define MASK_GPIO_OTYPER_PP    0U                    // push-pull output
# define MASK_GPIO_OTYPER_OD    1U                    // open drain output

// OSPEEDT

# define MASK_GPIO_OSPEEDR      0x3U
# define MASK_GPIO_OSPEEDR_LOW  0x0U
# define MASK_GPIO_OSPEEDR_MED  0x1U
# define MASK_GPIO_OSPEEDR_FAST 0x2U
# define MASK_GPIO_OSPEEDR_HIGH 0x3U

// AFR bit definitions

# define MASK_GPIO_AFR_AF00     0x0U
# define MASK_GPIO_AFR_AF01     0x1U
# define MASK_GPIO_AFR_AF02     0x2U
# define MASK_GPIO_AFR_AF03     0x3U
# define MASK_GPIO_AFR_AF04     0x4U
# define MASK_GPIO_AFR_AF05     0x5U
# define MASK_GPIO_AFR_AF06     0x6U
# define MASK_GPIO_AFR_AF07     0x7U
# define MASK_GPIO_AFR_AF08     0x8U
# define MASK_GPIO_AFR_AF09     0x9U
# define MASK_GPIO_AFR_AF10     0xAU
# define MASK_GPIO_AFR_AF11     0xBU
# define MASK_GPIO_AFR_AF12     0xCU
# define MASK_GPIO_AFR_AF13     0xDU
# define MASK_GPIO_AFR_AF14     0xEU
# define MASK_GPIO_AFR_AF15     0xFU
# define MASK_GPIO_AFR          0xFU

/// \endcond

# include <Debug.h>
# include <Atomic.h>

# define GPIO_SP_WIDTH          2U
# define GPIO_SP_BIT2POS(N)     ((N) * GPIO_SP_WIDTH)

inline WORD WrGpioSP(RegbankTypeGPIO volatile & gpio, unsigned const n, WORD const sp)
{
  unsigned const pos = GPIO_SP_BIT2POS(n);
  
  return Atomic::Bfld(gpio.OSPEEDR, (sp & MASK_GPIO_OSPEEDR) << pos, MASK_GPIO_OSPEEDR << pos);    
}

# define GPIO_MD_WIDTH          2U
# define GPIO_MD_BIT2POS(N)     ((N) * GPIO_MD_WIDTH)

inline WORD WrGpioMD(RegbankTypeGPIO volatile & gpio, unsigned const n, WORD const md)
{
  unsigned const pos = GPIO_MD_BIT2POS(n);
  
  return Atomic::Bfld(gpio.MODER, (md & MASK_GPIO_MODER) << pos, MASK_GPIO_MODER << pos);
}

# define GPIO_PUPDR_WIDTH          2U
# define GPIO_PUPDR_BIT2POS(N)     ((N) * GPIO_PUPDR_WIDTH)

inline WORD WrGpioPUPDR(RegbankTypeGPIO volatile & gpio, unsigned const n, WORD const pupdr)
{
  unsigned const pos = GPIO_PUPDR_BIT2POS(n);
  
  return Atomic::Bfld(gpio.PUPDR, (pupdr & MASK_GPIO_PUPDR) << pos, MASK_GPIO_PUPDR << pos);
}

# define GPIO_BSR_WIDTH          1U
# define GPIO_BSR_BIT2POS(N)     ((N) * GPIO_BSR_WIDTH)

inline WORD WrGpioSet(RegbankTypeGPIO volatile & gpio, unsigned const n)
{
  unsigned const pos = GPIO_BSR_BIT2POS(n);
  
  return Atomic::Bfld(gpio.BSRR, 1U << pos, 1U << pos);
}

inline WORD WrGpioClear(RegbankTypeGPIO volatile & gpio, unsigned const n)
{
  unsigned const pos = GPIO_BSR_BIT2POS(n);
  
  return Atomic::Bfld(gpio.BSRR, (1U << pos) << 16, (1U << pos) << 16);
}

inline void EnableAF(RegbankTypeGPIO volatile & gpio, WORD const af, WORD const sp, bool const od, unsigned const n) noexcept 
{
  ASSERT(n < 16U);
  ASSERT(af < 16U);

  auto const pos((n % 8U) * 4U);
  WORD const set(af            << pos);
  WORD const res(MASK_GPIO_AFR << pos);
  auto const indx(n / 8U);

  Atomic::Bfld(gpio.AFR[indx], set, res);
  
  HWRD const mask = 1U << n;
  
  if ( od )
    Atomic::Orr(gpio.OTYPER, mask);
  else
    Atomic::Bic(gpio.OTYPER, mask);

  WrGpioSP(gpio, n, sp);
  WrGpioMD(gpio, n, MASK_GPIO_MODER_ALTFNC);     
}

inline void EnableAF(RegbankTypeGPIO volatile & gpio, WORD const af, WORD const sp, bool const od, BYTE const * nums, unsigned dim)
{
  while ( dim-- > 0U )
  {
    EnableAF(gpio, af, sp, od, *nums++);
  }
}

template<unsigned DIM>
inline void EnableAF(RegbankTypeGPIO volatile & gpio, WORD const af, WORD const sp, bool const od, BYTE const (& nums)[DIM])
{
  EnableAF(gpio, af, sp, od, nums, DIM);
}

#endif
