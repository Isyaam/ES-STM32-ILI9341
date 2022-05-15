//
// RB_TIM.h
//

/// \file RB_TIM.h
/// Deklaration der Timer-Registerbänke (TIM).

#ifndef guard_RB_TIM_H
# define guard_RB_TIM_H

# include <RB.h>

/// Datentyp für Timer-Registerbank, s. RM0033 Reference Manual, Abschnitt 13.
typedef struct __regbank_TIM
{
  HWRD CR1;                                           ///< Control register 1.
  HWRD reserved00;

  HWRD CR2;                                           ///< Control register 2.
  HWRD reserved01;
  
  HWRD SMCR;                                          ///< Slave mode control register (NOT for basic timer TIM6 & TIM7).
  HWRD reserved02;

  HWRD DIER;                                          ///< DMA/interrupt enable register.
  HWRD reserved03;
  
  HWRD SR;                                            ///< Status register.
  HWRD reserved04;

  HWRD EGR;                                           ///< Event generation register.
  HWRD reserved05;

  /// Capture/Compare mode registers.
  /// \warning Ein Zugriff auf diese Register als \c BYTE ist nicht möglich (überschreibt die Einstellung von zwei Kanälen)
  WORD CCMR[2];                                          

  HWRD CCER;                                          ///< Capture/Compare enable register (NOT for basic timer TIM6 & TIM7).
  HWRD reserved08;
  
  WORD CNT;                                           ///< Counter.
  
  HWRD PSC;                                           ///< Prescaler.
  HWRD reserved09;
  
  WORD ARR;                                           ///< Auto-reload register.
  
  HWRD RCR;                                           ///< Repetition count register (TIM1 & TIM8 only).
  HWRD reserved11;

  WORD CCR[4];                                        ///< Capture/Compare register 1 .. 4  (NOT for basic timer TIM6 & TIM7).

  HWRD BDTR;                                          ///< Break and dead time register (TIM1 & TIM8 only).
  HWRD reserved12;

  WORD DCR;                                           ///< DMA control register (NOT for basic timer TIM6 & TIM7).
  WORD DMAR;                                          ///< DMA address for full transfer (NOT for basic timer TIM6 & TIM7).
} RegbankTypeTIM;

extern RegbankTypeTIM volatile rbTIM01;               ///< TIM01-Registerbank (erweitert).
extern RegbankTypeTIM volatile rbTIM02;               ///< TIM02-Registerbank.
extern RegbankTypeTIM volatile rbTIM03;               ///< TIM03-Registerbank.
extern RegbankTypeTIM volatile rbTIM04;               ///< TIM04-Registerbank.
extern RegbankTypeTIM volatile rbTIM05;               ///< TIM05-Registerbank.
extern RegbankTypeTIM volatile rbTIM06;               ///< TIM06-Registerbank (Basic).
extern RegbankTypeTIM volatile rbTIM07;               ///< TIM07-Registerbank (Basic).
extern RegbankTypeTIM volatile rbTIM08;               ///< TIM08-Registerbank (erweitert).
extern RegbankTypeTIM volatile rbTIM09;               ///< TIM09-Registerbank (nur zwei CC-Kanäle).
extern RegbankTypeTIM volatile rbTIM10;               ///< TIM10-Registerbank (nur ein CC-Kanal).
extern RegbankTypeTIM volatile rbTIM11;               ///< TIM11-Registerbank (nur ein CC-Kanal).
extern RegbankTypeTIM volatile rbTIM12;               ///< TIM12-Registerbank (nur zwei CC-Kanäle).
extern RegbankTypeTIM volatile rbTIM13;               ///< TIM13-Registerbank (nur ein CC-Kanal).
extern RegbankTypeTIM volatile rbTIM14;               ///< TIM14-Registerbank (nur ein CC-Kanal).

/// \cond RB_DEFS

// CR1

# define INDX_TIM_CR1_CEN       0                     // 1 = counter enable
# define MASK_TIM_CR1_CEN       (HWRD)REG_BITMASK(TIM_CR1_CEN)

# define INDX_TIM_CR1_URS       2 
# define MASK_TIM_CR1_URS       (HWRD)REG_BITMASK(TIM_CR1_URS)

# define INDX_TIM_CR1_OPM       3                     ///< one pulse mode, 1 = counter stops counting at the next update event (clearing CEN).
# define MASK_TIM_CR1_OPM       (HWRD)REG_BITMASK(TIM_CR1_OPM)

# define INDX_TIM_CR1_DIR       4                     ///< count direction, 1 = down, 0 = up.

# define INDX_TIM_CR1_ARPE      7
# define MASK_TIM_CR1_ARPE      (HWRD)REG_BITMASK(TIM_CR1_ARPE)

# define INDX_TIM_CR1_CKD       8
# define MASK_TIM_CR1_CKD       (HWRD)(3U << INDX_TIM_CR1_CKD)
# define MASK_TIM_CR1_CKD_1     (HWRD)(0U << INDX_TIM_CR1_CKD)
# define MASK_TIM_CR1_CKD_2     (HWRD)(1U << INDX_TIM_CR1_CKD)
# define MASK_TIM_CR1_CKD_4     (HWRD)(2U << INDX_TIM_CR1_CKD)

// SR

# define INDX_TIM_SR_UIF        0
# define MASK_TIM_SR_UIF        (HWRD)REG_BITMASK(TIM_SR_UIF)

# define INDX_TIM_SR_CC1IF      1
# define MASK_TIM_SR_CC1IF      (HWRD)REG_BITMASK(TIM_SR_CC1IF)

# define INDX_TIM_SR_CC2IF      2
# define MASK_TIM_SR_CC2IF      (HWRD)REG_BITMASK(TIM_SR_CC2IF)

# define INDX_TIM_SR_CC3IF      3
# define MASK_TIM_SR_CC3IF      (HWRD)REG_BITMASK(TIM_SR_CC3IF)

# define INDX_TIM_SR_CC4IF      4
# define MASK_TIM_SR_CC4IF      (HWRD)REG_BITMASK(TIM_SR_CC4IF)

// EGR

# define INDX_TIM_EGR_UG        0
# define MASK_TIM_EGR_UG        (HWRD)REG_BITMASK(TIM_EGR_UG)

// DEIR

# define INDX_TIM_DIER_UIE      0
# define MASK_TIM_DIER_UIE      (HWRD)REG_BITMASK(TIM_DIER_UIE)

# define INDX_TIM_DIER_CC1IE    1
# define MASK_TIM_DIER_CC1IE    (HWRD)REG_BITMASK(TIM_DIER_CC1IE)

# define INDX_TIM_DIER_CC2IE    2
# define MASK_TIM_DIER_CC2IE    (HWRD)REG_BITMASK(TIM_DIER_CC2IE)

# define INDX_TIM_DIER_CC3IE    3
# define MASK_TIM_DIER_CC3IE    (HWRD)REG_BITMASK(TIM_DIER_CC3IE)

# define INDX_TIM_DIER_CC4IE    4
# define MASK_TIM_DIER_CC4IE    (HWRD)REG_BITMASK(TIM_DIER_CC4IE)

# define MASK_TIM_DIER_CCxIE    (MASK_TIM_DIER_CC4IE | MASK_TIM_DIER_CC2IE | MASK_TIM_DIER_CC3IE | MASK_TIM_DIER_CC4IE)

// CCMRx

# define INDX_TIM_CCMR_CCxS     0
# define MASK_TIM_CCMR_CCxS     (BYTE)(3 << INDX_TIM_CCMR_CCxS)
# define MASK_TIM_CCMR_CCxS_O   (BYTE)(0 << INDX_TIM_CCMR_CCxS)
# define MASK_TIM_CCMR_CCxS_I_TIx (BYTE)(1 << INDX_TIM_CCMR_CCxS)
# define MASK_TIM_CCMR_CCxS_I_TIy (BYTE)(2 << INDX_TIM_CCMR_CCxS)
# define MASK_TIM_CCMR_CCxS_I_TRC (BYTE)(3 << INDX_TIM_CCMR_CCxS)

# define INDX_TIM_CCMR_ICxPSC   2
# define MASK_TIM_CCMR_ICxPSC   (BYTE)(3 << INDX_TIM_CCMR_ICxPSC)
# define MASK_TIM_CCMR_ICxPSC_1 (BYTE)(0 << INDX_TIM_CCMR_ICxPSC)
# define MASK_TIM_CCMR_ICxPSC_2 (BYTE)(1 << INDX_TIM_CCMR_ICxPSC)
# define MASK_TIM_CCMR_ICxPSC_4 (BYTE)(2 << INDX_TIM_CCMR_ICxPSC)
# define MASK_TIM_CCMR_ICxPSC_8 (BYTE)(3 << INDX_TIM_CCMR_ICxPSC)

# define INDX_TIM_CCMR_ICxF     4
# define MASK_TIM_CCMR_ICxF     (BYTE)(0xF << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_INT_01_2 (BYTE)(0x1 << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_INT_01_4 (BYTE)(0x2 << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_INT_01_8 (BYTE)(0x3 << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_DTS_02_8 (BYTE)(0x5 << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_DTS_04_8 (BYTE)(0x7 << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_DTS_08_8 (BYTE)(0x9 << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_DTS_16_8 (BYTE)(0xC << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_DTS_32_5 (BYTE)(0xD << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_DTS_32_6 (BYTE)(0xE << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_DTS_32_8 (BYTE)(0xF << INDX_TIM_CCMR_ICxF)

# define INDX_TIM_CCMR_OCxM     4
# define MASK_TIM_CCMR_OCxM     (BYTE)(0x7 << INDX_TIM_CCMR_OCxM)
# define MASK_TIM_CCMR_OCxM_PWM1 (BYTE)(0x6 << INDX_TIM_CCMR_OCxM)
# define MASK_TIM_CCMR_OCxM_PWM2 (BYTE)(0x7 << INDX_TIM_CCMR_OCxM)

// CCER

# define INDX_TIM_CCER_CC1E     0
# define MASK_TIM_CCER_CC1E     (HWRD)REG_BITMASK(TIM_CCER_CC1E)

# define INDX_TIM_CCER_CC1P     1
# define MASK_TIM_CCER_CC1P     (HWRD)REG_BITMASK(TIM_CCER_CC1P)

# define INDX_TIM_CCER_CC1NP    3

# define INDX_TIM_CCER_CC2E     4
# define MASK_TIM_CCER_CC2E     (HWRD)REG_BITMASK(TIM_CCER_CC2E)

# define INDX_TIM_CCER_CC2P     5
# define MASK_TIM_CCER_CC2P     (HWRD)REG_BITMASK(TIM_CCER_CC2P)

# define INDX_TIM_CCER_CC2NP    7

# define INDX_TIM_CCER_CC3E     8
# define MASK_TIM_CCER_CC3E     (HWRD)REG_BITMASK(TIM_CCER_CC3E)

# define INDX_TIM_CCER_CC3P     9
# define MASK_TIM_CCER_CC3P     (HWRD)REG_BITMASK(TIM_CCER_CC3P)

# define INDX_TIM_CCER_CC3NP    11

# define INDX_TIM_CCER_CC4E     12
# define MASK_TIM_CCER_CC4E     (HWRD)REG_BITMASK(TIM_CCER_CC4E)

# define INDX_TIM_CCER_CC4P     13
# define MASK_TIM_CCER_CC4P     (HWRD)REG_BITMASK(TIM_CCER_CC4P)

# define INDX_TIM_CCER_CC4NP    15


// BDTR

# define INDX_TIM_BDTR_MOE      15
# define MASK_TIM_BDTR_MOE      (HWRD)REG_BITMASK(TIM_BDTR_MOE)

# define INDX_TIM_BDTR_AOE      14
# define MASK_TIM_BDTR_AOE      (HWRD)REG_BITMASK(TIM_BDTR_AOE)

# define INDX_TIM_BDTR_OSSR     11
# define MASK_TIM_BDTR_OSSR     (HWRD)REG_BITMASK(TIM_BDTR_OSSR)

# define INDX_TIM_BDTR_OSSI     10
# define MASK_TIM_BDTR_OSSI     (HWRD)REG_BITMASK(TIM_BDTR_OSSI)

/// \endcond

#endif
