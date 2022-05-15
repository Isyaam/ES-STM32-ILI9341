//
// RB_NVIC.h
//

#ifndef guard_RB_NVIC_H
# define  guard_RB_NVIC_H

/// \file RB_NVIC.h
/// Nested Vector Interrupt Controller (NVIC, core periphery).

# include <RB.h>

/// Datentyp für NVIC-Registerbank.
typedef struct __regbank_NVIC
{
  WORD ISER[3];                 ///< Interrupt set enable registers.
  WORD reserved0[29];

  WORD ICER[3];                 ///< Interrupt clear enable registers.
  WORD reserved1[29];
  
  WORD ISPR[3];                 ///< Interrupt set pending registers.
  WORD reserved2[29];
  
  WORD ICPR[3];                 ///< Interrupt clear pending registers.
  WORD reserved3[29];

  WORD IABR[3];                 ///< Interrupt active bit register.
  WORD reserved4[61]; 

  /// Interrupt pending registers.
  union {
    WORD asWord[60];
    BYTE asByte[60 * sizeof(WORD)];
  } IPR;                                              
} RegbankTypeNVIC;

extern RegbankTypeNVIC volatile rbNVIC;               ///< NVIC-Registerbank.

# define EXTIRQ_WWDG             0                    ///< IRQ-Nummer des WWDG.
# define EXTIRQ_PVD              1                    ///< IRQ-Nummer des PVD.

# define EXTIRQ_RTC_WKUP         3
# define EXTIRQ_FLASH            4                    ///< IRQ-Nummer des Flash-Interrupts.

# define EXTIRQ_EXTI00           6
# define EXTIRQ_EXTI01           7
# define EXTIRQ_EXTI02           8
# define EXTIRQ_EXTI03           9
# define EXTIRQ_EXTI04          10
# define EXTIRQ_DMA1_STREAM0    11
# define EXTIRQ_DMA1_STREAM1    12
# define EXTIRQ_DMA1_STREAM2    13
# define EXTIRQ_DMA1_STREAM3    14
# define EXTIRQ_DMA1_STREAM4    15
# define EXTIRQ_DMA1_STREAM5    16
# define EXTIRQ_DMA1_STREAM6    17
# define EXTIRQ_ADC             18                    ///< IRQ-Nummer für ADC1 und ADC2, für STM32F2xx zusätzlich auch ADC3. \note Der STM32F1xx verwednet für ADC3 eine andere IRQ-Nummer.

# define EXTIRQ_EXTI05TO09      23                    ///< IRQ-Nummer für EXTI5 bis EXTI9.
# define EXTIRQ_TIM01_BR_TIM09  24                    ///< IRQ-Nummer für den Break-Interrupt von TIM1 und alle Interrupts von TIM9.
# define EXTIRQ_TIM01_UE_TIM10  25                    ///< IRQ-Nummer für Update-Event-Interrupts von TIM1 und alle Interrupts von TIM10.
# define EXTIRQ_TIM01_TR_TIM11  26
# define EXTIRQ_TIM01_CC        27                    ///< IRQ-Nummer für die Capture-Compare-Interrupts von TIM1.
# define EXTIRQ_TIM02           28                    ///< IRQ-Nummer für TIM2.
# define EXTIRQ_TIM03           29                    ///< IRQ-Nummer für TIM3.
# define EXTIRQ_TIM04           30                    ///< IRQ-Nummer für TIM4.
# define EXTIRQ_I2C1_EV         31
# define EXTIRQ_I2C1_ER         32
# define EXTIRQ_I2C2_EV         33
# define EXTIRQ_I2C2_ER         34
# define EXTIRQ_SPI1            35                    ///< IRQ-Nummer für SPI1.
# define EXTIRQ_SPI2            36                    ///< IRQ-Nummer für SPI2.
# define EXTIRQ_USART1          37                    ///< IRQ-Nummer für UASRT1.
# define EXTIRQ_USART2          38                    ///< IRQ-Nummer für UASRT2.
# define EXTIRQ_USART3          39                    ///< IRQ-Nummer für UASRT3.
# define EXTIRQ_EXTI10TO15      40                    ///< IRQ-Nummer für EXTI10 bis EXTI15.
# define EXTIRQ_RTC_ALARM       41

# define EXTIRQ_TIM08_BR_TIM12  43
# define EXTIRQ_TIM08_UE_TIM13  44
# define EXTIRQ_TIM08_TR_TIM14  45
# define EXTIRQ_TIM08_CC        46
# define EXTIRQ_DMA1_STREAM7    47

# define EXTIRQ_TIM05           50                    ///< IRQ-Nummer für TIM5.
# define EXTIRQ_SPI3            51                    ///< IRQ-Nummer für SPI1 (für STM32F1xx kaum zu verwenden, da Pins gemeinsam mit den JTAG-Pins).
# define EXTIRQ_UART4           52                    ///< IRQ-Nummer für UART4.
# define EXTIRQ_UART5           53                    ///< IRQ-Nummer für UART5.
# define EXTIRQ_TIM06_DAC       54                    ///< IRQ-Nummer für TIM6 und DAC1/2 underrun error.
# define EXTIRQ_TIM07           55                    ///< IRQ-Nummer für TIM7.
# define EXTIRQ_DMA2_STREAM0    56
# define EXTIRQ_DMA2_STREAM1    57
# define EXTIRQ_DMA2_STREAM2    58
# define EXTIRQ_DMA2_STREAM3    59
# define EXTIRQ_DMA2_STREAM4    60
# define EXTIRQ_ETH             61
# define EXTIRQ_ETH_WKUP        62

# define EXTIRQ_DMA2_STREAM5    68
# define EXTIRQ_DMA2_STREAM6    69
# define EXTIRQ_DMA2_STREAM7    70
# define EXTIRQ_USART6          71
# define EXTIRQ_I2C3_ER         72
# define EXTIRQ_I2C3_EV         73

# define EXTIRQ_DCMI            78
# define EXTIRQ_CRYP            79
# define EXTIRQ_HASH_RNG        80

# define EXTIRQ_SPI4            84
# define EXTIRQ_SPI5            85
# define EXTIRQ_SPI6            86
# define EXTIRQ_SAI1            87
# define EXTIRQ_LTDC            88
# define EXTIRQ_LTDC_ERR        89
# define EXTIRQ_DMA2D           90

# define EXTIRQ_SET_PRIO(N, P)  (rbNVIC.IPR.asByte[N] = (P))
# define EXTIRQ_GET_PRIO(N)     (rbNVIC.IPR.asByte[N])

# define EXTIRQ_SET_ENA(N)      (rbNVIC.ISER[(N) / 32U] = 1U << ((WORD)(N) % 32U))
# define EXTIRQ_CLR_ENA(N)      (rbNVIC.ICER[(N) / 32U] = 1U << ((WORD)(N) % 32U))

# include <RB_SCB.h>

inline void TriggerInterrupt(unsigned const num) 
{ 
  regSTIR = num;
}

inline void AvtivateExtIrq(unsigned const num) 
{ 
  rbNVIC.ISPR[num / 32U] = 1U << (num % 32U);
}

/// IRQ freischalten.
/// \param[in] num ist die Nummer des IRQs.
/// \note Mehrfaches aufrufen dieser Funktion, ohne dass zuvor der IRQ gesperrt wurde, hat keine Wirkung.
inline void ExtIrqSetEnaNonShared(unsigned const num) { EXTIRQ_SET_ENA(num); }

template<unsigned IRQNUM>
inline void ExtIrqSetEna() { ExtIrqSetEnaNonShared(IRQNUM); }

/// IRQ sperren.
/// \param[in] num ist die Nummer des IRQs.
/// \note Mehrfaches aufrufen dieser Funktion, ohne dass zuvor der IRQ freigeschaltet wurde, hat keine Wirkung.
inline void ExtIrqClrEnaNonShared(unsigned const num) { EXTIRQ_CLR_ENA(num); }

template<unsigned IRQNUM>
inline void ExtIrqClrEna() { ExtIrqClrEnaNonShared(IRQNUM); }

#endif
