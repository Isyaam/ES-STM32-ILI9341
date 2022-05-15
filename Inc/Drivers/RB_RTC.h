//
// RB_RTC.h
//

/// \file RB_RTC.h
/// Deklaration der Registerbank der Echtzeituhr (RTC).

#ifndef guard_RB_RTC_H
# define guard_RB_RTC_H

# include <RB.h>

typedef union {
  WORD TR;
  struct {
    WORD TR_SU  : 4;
    WORD TR_ST  : 3;
    WORD fill0  : 1;
    WORD TR_MNU : 4;
    WORD TR_MNT : 3;
    WORD fill1  : 1;
    WORD TR_HU  : 4;
    WORD TR_HT  : 2;
    WORD TR_PM  : 1;
  };
} TRType;

typedef union {
  WORD DR;
  struct {
    WORD DR_DU  : 4;
    WORD DR_DT  : 2;
    WORD fill0  : 2;
    WORD DR_MU  : 4;
    WORD DR_MT  : 1;
    WORD DR_WDU : 3;
    WORD DR_YU  : 4;
    WORD DR_YT  : 4;
  };
} DRType;

/// Registerbank der Echtzeituhr (RTC), s. RM0033 Reference Manual, Abschnitt 22.6.
typedef struct __regbank_RTC
{
  WORD TR;                      ///< Time register.
  WORD DR;                      ///< Date register.
  WORD CR;                      ///< Control register.

  union {
    WORD ISR;                   ///< Initialisation and status register.
    
    struct {
      BYTE ISR_msb;             ///< ISR MSB.
      BYTE ISR_lsb;             ///< ISR LSB.
    };
  };
  
  struct {
    HWRD PRERS;                 ///< Prescaler register (part S).
    HWRD PRERA;                 ///< Prescaler register (part A).
  };
  
  WORD WUTR;                    ///< Wakeup timer register.
  WORD CALIBR;                  ///< Calibration register.
  WORD ALRMAR;                  ///< Alarm A register.
  WORD ALRMBR;                  ///< Alarm B register.
  WORD WPR;                     ///< Write protection register.

  WORD reserved0[2];

  WORD TSTR;                    ///< Time stamp time register.
  WORD TSDR;                    ///< Time stamp date register.

  WORD reserved1[2];

  WORD TAFCR;                   ///< Tamper and alternate function configuration register.

  WORD reserved2[3];

  WORD BKPR[20];                ///< Backup registers.
} RegbankTypeRTC;

/// Registerbank der RTC.
extern RegbankTypeRTC volatile rbRTC;

/// \cond RB_DEFS

// CR

#define INDX_RTC_CR_WUCKSEL     (WORD)0U
#define MASK_RTC_CR_WUCKSEL     (WORD)(0x7U << INDX_RTC_CR_WUCKSEL)
#define MASK_RTC_CR_WUCKSEL_1HZ (WORD)(0x4U << INDX_RTC_CR_WUCKSEL)

#define INDX_RTC_CR_FMT         6

#define INDX_RTC_CR_WUTE        10
#define MASK_RTC_CR_WUTE        (WORD)REG_BITMASK(RTC_CR_WUTE)

#define INDX_RTC_CR_WUTIE       14
#define MASK_RTC_CR_WUTIE       (WORD)REG_BITMASK(RTC_CR_WUTIE)

#define INDX_RTC_CR_TSIE        15

#define INDX_RTC_CR_BKP         18
#define MASK_RTC_CR_BKP         (WORD)REG_BITMASK(RTC_CR_BKP)

#define INDX_RTC_CR_SUB1H       17
#define MASK_RTC_CR_SUB1H       (WORD)REG_BITMASK(RTC_CR_SUB1H)

#define INDX_RTC_CR_ADD1H       16
#define MASK_RTC_CR_ADD1H       (WORD)REG_BITMASK(RTC_CR_ADD1H)

// ISR

#define INDX_RTC_ISR_WUTWF      2

#define INDX_RTC_ISR_INITS      4
#define MASK_RTC_ISR_INITS      (WORD)REG_BITMASK(RTC_ISR_INITS)

#define INDX_RTC_ISR_RSF        5
#define MASK_RTC_ISR_RSF        (WORD)REG_BITMASK(RTC_ISR_RSF)

#define INDX_RTC_ISR_INITF      6
#define MASK_RTC_ISR_INITF      (WORD)REG_BITMASK(RTC_ISR_INITF)

#define INDX_RTC_ISR_INIT       7
#define MASK_RTC_ISR_INIT       (WORD)REG_BITMASK(RTC_ISR_INIT)

#define INDX_RTC_ISR_ALRAF      8
#define MASK_RTC_ISR_ALRAF      (WORD)REG_BITMASK(RTC_ISR_ALRAF)

#define INDX_RTC_ISR_ALRBF      9
#define MASK_RTC_ISR_ALRBF      (WORD)REG_BITMASK(RTC_ISR_ALRBF)

#define INDX_RTC_ISR_WUTF       10
#define MASK_RTC_ISR_WUTF       (WORD)REG_BITMASK(RTC_ISR_WUTF)

#define INDX_RTC_ISR_TSF        11
#define MASK_RTC_ISR_TSF        (WORD)REG_BITMASK(RTC_ISR_TSF)

#define INDX_RTC_ISR_TSOVF      12
#define MASK_RTC_ISR_TSOVF      (WORD)REG_BITMASK(RTC_ISR_TSOVF)

#define INDX_RTC_ISR_TAMP1F     13
#define MASK_RTC_ISR_TAMP1F     (WORD)REG_BITMASK(RTC_ISR_TAMP1F)

// PRERx

#define MASK_RTC_PRERS          0x1FFFU
#define MASK_RTC_PRERS_DEFAULT  0xFFU

#define MASK_RTC_PRERA          0x7FU
#define MASK_RTC_PRERA_DEFAULT  0x7FU

// WPR

# define MASK_RTC_WPR_KEY0      0xCAU
# define MASK_RTC_WPR_KEY1      0x53U

/// \endcond

#endif

