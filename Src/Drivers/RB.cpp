//
// RB.cpp
//

/// \file RB.cpp
/// Definitionen der Registerbänke.

#include <Compiler.h>
#include <Cortex.h>

#include <RB.h>
#include <RB_NVIC.h>
#include <RB_SCB.h>
#include <RB_STK.h>
#include <RB_ITM.h>
#include <RB_RCC.h>
#include <RB_DMA.h>
#include <RB_GPIO.h>
#include <RB_FLASH.h>
#include <RB_EXTI.h>
#include <RB_SYSCFG.h>
#include <RB_PWR.h>
#include <RB_RTC.h>
#include <RB_TIM.h>
#include <RB_USART.h>
#include <RB_SPI.h>
#include <RB_IWDG.h>
#include <RB_ADC.h>
#include <RB_I2C.h>
#include <RB_RNG.h>
#include <RB_FMC.h>
#include <RB_LTDC.h>
#include <RB_DMA2D.h>
#include <RB_ETH.h>

#define SCSPER_ADDR_PREFIX      CONCAT(PRVPER_ADDR_PREFIX, 0E)

// Achtung: Der sog. SCS (System Control Space) von 0xE000E000 bis 0xE000EFFF kann NICHT genutzt werden, wenn sich der Prozessor 
// im User-Mode befindet (priviliged mode zwingend notwendig, sonst fault exception!)

#define APB1PE_ADDR_PREFIX      CONCAT(PERIPH_ADDR_PREFIX, 0) ///< STM32Fyxx periphery start address prefix of APB1 (first 4 hex digits of address).
#define APB2PE_ADDR_PREFIX      CONCAT(PERIPH_ADDR_PREFIX, 1) ///< STM32Fyxx periphery start address prefix of APB2 (first 4 hex digits of address).

#define AHB1PE_ADDR_PREFIX      CONCAT(PERIPH_ADDR_PREFIX, 2) ///< STM32Fyxx periphery start address prefix of AHB1 (first 4 hex digits of address).
#define AHB2PE_ADDR_PREFIX      EXTPER_ADDR_PREFIX
#define AHB3PE_ADDR_PREFIX      DEVICE_ADDR_PREFIX

#define RB_ADDR_GPIOA           CONCAT(AHB1PE_ADDR_PREFIX,  0000U)
#define RB_ADDR_GPIOB           CONCAT(AHB1PE_ADDR_PREFIX,  0400U)
#define RB_ADDR_GPIOC           CONCAT(AHB1PE_ADDR_PREFIX,  0800U)
#define RB_ADDR_GPIOD           CONCAT(AHB1PE_ADDR_PREFIX,  0C00U)
#define RB_ADDR_GPIOE           CONCAT(AHB1PE_ADDR_PREFIX,  1000U)
#define RB_ADDR_GPIOF           CONCAT(AHB1PE_ADDR_PREFIX,  1400U)
#define RB_ADDR_GPIOG           CONCAT(AHB1PE_ADDR_PREFIX,  1800U)
#define RB_ADDR_GPIOH           CONCAT(AHB1PE_ADDR_PREFIX,  1C00U)
#define RB_ADDR_GPIOI           CONCAT(AHB1PE_ADDR_PREFIX,  2000U)
#define RB_ADDR_GPIOJ           CONCAT(AHB1PE_ADDR_PREFIX,  2400U)
#define RB_ADDR_GPIOK           CONCAT(AHB1PE_ADDR_PREFIX,  2800U)
#define RB_ADDR_RCC             CONCAT(AHB1PE_ADDR_PREFIX,  3800U)
#define RB_ADDR_FLASH           CONCAT(AHB1PE_ADDR_PREFIX,  3C00U) 
#define RB_ADDR_BKP             CONCAT(AHB1PE_ADDR_PREFIX,  4000U)
#define RB_ADDR_DMA1            CONCAT(AHB1PE_ADDR_PREFIX,  6000U)
#define RB_ADDR_DMA2            CONCAT(AHB1PE_ADDR_PREFIX,  6400U)
#define RB_ADDR_DMA_2D          CONCAT(AHB1PE_ADDR_PREFIX,  B000U)
#define RB_ADDR_ETH             CONCAT(AHB1PE_ADDR_PREFIX,  8000U)

#define RB_ADDR_USB_OTG_FS      CONCAT(AHB2PE_ADDR_PREFIX, 00000U)
#define RB_ADDR_DCMI            CONCAT(AHB2PE_ADDR_PREFIX, 50000U)
#define RB_ADDR_CRYP            CONCAT(AHB2PE_ADDR_PREFIX, 60000U)
#define RB_ADDR_HASH            CONCAT(AHB2PE_ADDR_PREFIX, 60400U)
#define RB_ADDR_RNG             CONCAT(AHB2PE_ADDR_PREFIX, 60800U)

#define RB_ADDR_FMC             CONCAT(AHB3PE_ADDR_PREFIX, 00000U)
#define RB_ADDR_QUAD_SPI        CONCAT(AHB3PE_ADDR_PREFIX, 01000U)

#define RB_ADDR_TIM02           CONCAT(APB1PE_ADDR_PREFIX,  0000U)
#define RB_ADDR_TIM03           CONCAT(APB1PE_ADDR_PREFIX,  0400U)
#define RB_ADDR_TIM04           CONCAT(APB1PE_ADDR_PREFIX,  0800U)
#define RB_ADDR_TIM05           CONCAT(APB1PE_ADDR_PREFIX,  0C00U)
#define RB_ADDR_TIM06           CONCAT(APB1PE_ADDR_PREFIX,  1000U)
#define RB_ADDR_TIM07           CONCAT(APB1PE_ADDR_PREFIX,  1400U)
#define RB_ADDR_TIM12           CONCAT(APB1PE_ADDR_PREFIX,  1800U)
#define RB_ADDR_TIM13           CONCAT(APB1PE_ADDR_PREFIX,  1C00U)
#define RB_ADDR_TIM14           CONCAT(APB1PE_ADDR_PREFIX,  2000U)
#define RB_ADDR_RTC             CONCAT(APB1PE_ADDR_PREFIX,  2800U)
#define RB_ADDR_IWDG            CONCAT(APB1PE_ADDR_PREFIX,  3000U)
#define RB_ADDR_SPI2            CONCAT(APB1PE_ADDR_PREFIX,  3800U)
#define RB_ADDR_SPI3            CONCAT(APB1PE_ADDR_PREFIX,  3C00U)
#define RB_ADDR_USART2          CONCAT(APB1PE_ADDR_PREFIX,  4400U)
#define RB_ADDR_USART3          CONCAT(APB1PE_ADDR_PREFIX,  4800U)
#define RB_ADDR_UART4           CONCAT(APB1PE_ADDR_PREFIX,  4C00U)
#define RB_ADDR_UART5           CONCAT(APB1PE_ADDR_PREFIX,  5000U)
#define RB_ADDR_I2C1            CONCAT(APB1PE_ADDR_PREFIX,  5400U)
#define RB_ADDR_I2C2            CONCAT(APB1PE_ADDR_PREFIX,  5800U)
#define RB_ADDR_I2C3            CONCAT(APB1PE_ADDR_PREFIX,  5C00U)
#define RB_ADDR_PWR             CONCAT(APB1PE_ADDR_PREFIX,  7000U)
#define RB_ADDR_DAC             CONCAT(APB1PE_ADDR_PREFIX,  7400U)
#define RB_ADDR_TIM12           CONCAT(APB1PE_ADDR_PREFIX,  1800U)
#define RB_ADDR_TIM13           CONCAT(APB1PE_ADDR_PREFIX,  1C00U)
#define RB_ADDR_TIM14           CONCAT(APB1PE_ADDR_PREFIX,  2000U)

#define RB_ADDR_TIM01           CONCAT(APB2PE_ADDR_PREFIX,  0000U)
#define RB_ADDR_TIM08           CONCAT(APB2PE_ADDR_PREFIX,  0400U)
#define RB_ADDR_USART1          CONCAT(APB2PE_ADDR_PREFIX,  1000U)
#define RB_ADDR_USART6          CONCAT(APB2PE_ADDR_PREFIX,  1400U)
#define RB_ADDR_ADC1            CONCAT(APB2PE_ADDR_PREFIX,  2000U)
#define RB_ADDR_ADC2            CONCAT(APB2PE_ADDR_PREFIX,  2100U)
#define RB_ADDR_ADC3            CONCAT(APB2PE_ADDR_PREFIX,  2200U)
#define RB_ADDR_SPI1            CONCAT(APB2PE_ADDR_PREFIX,  3000U)
#define RB_ADDR_SPI4            CONCAT(APB2PE_ADDR_PREFIX,  3400U) 
#define RB_ADDR_SYSCFG          CONCAT(APB2PE_ADDR_PREFIX,  3800U)
#define RB_ADDR_EXTI            CONCAT(APB2PE_ADDR_PREFIX,  3C00U)
#define RB_ADDR_TIM09           CONCAT(APB2PE_ADDR_PREFIX,  4000U)
#define RB_ADDR_TIM10           CONCAT(APB2PE_ADDR_PREFIX,  4400U)
#define RB_ADDR_TIM11           CONCAT(APB2PE_ADDR_PREFIX,  4800U)
#define RB_ADDR_SPI5            CONCAT(APB2PE_ADDR_PREFIX,  5000U)
#define RB_ADDR_SPI6            CONCAT(APB2PE_ADDR_PREFIX,  5400U)
#define RB_ADDR_LTDC            CONCAT(APB2PE_ADDR_PREFIX,  6800U)

#define RB_ADDR_ITM             CONCAT(PRVPER_ADDR_PREFIX, 00000U)
#define RB_ADDR_DWT             CONCAT(PRVPER_ADDR_PREFIX, 01000U)

#define RB_ADDR_DBG             CONCAT(SCSPER_ADDR_PREFIX,   DF0U)
#define RB_ADDR_STK             CONCAT(SCSPER_ADDR_PREFIX,   010U)
#define RB_ADDR_NVIC            CONCAT(SCSPER_ADDR_PREFIX,   100U)
#define RB_ADDR_SCB             CONCAT(SCSPER_ADDR_PREFIX,   D00U)
#define RB_ADDR_MPU             CONCAT(SCSPER_ADDR_PREFIX,   D90U)

RegbankTypeADC    volatile rbADC1   LOCATE_AT(RB_ADDR_ADC1  );
RegbankTypeADC    volatile rbADC2   LOCATE_AT(RB_ADDR_ADC2  );
RegbankTypeADC    volatile rbADC3   LOCATE_AT(RB_ADDR_ADC3  );
RegbankTypeITM    volatile rbITM    LOCATE_AT(RB_ADDR_ITM   );
RegbankTypeSCB    volatile rbSCB    LOCATE_AT(RB_ADDR_SCB   );
RegbankTypeDBG    volatile rbDBG    LOCATE_AT(RB_ADDR_DBG   );
RegbankTypeMPU    volatile rbMPU    LOCATE_AT(RB_ADDR_MPU   );
RegbankTypeSTK    volatile rbSTK    LOCATE_AT(RB_ADDR_STK   );
RegbankTypeNVIC   volatile rbNVIC   LOCATE_AT(RB_ADDR_NVIC  );
RegbankTypeRCC    volatile rbRCC    LOCATE_AT(RB_ADDR_RCC   );
RegbankTypeFLASH  volatile rbFLASH  LOCATE_AT(RB_ADDR_FLASH );
RegbankTypeGPIO   volatile rbGPIOA  LOCATE_AT(RB_ADDR_GPIOA );
RegbankTypeGPIO   volatile rbGPIOB  LOCATE_AT(RB_ADDR_GPIOB );
RegbankTypeGPIO   volatile rbGPIOC  LOCATE_AT(RB_ADDR_GPIOC );
RegbankTypeGPIO   volatile rbGPIOD  LOCATE_AT(RB_ADDR_GPIOD );
RegbankTypeGPIO   volatile rbGPIOE  LOCATE_AT(RB_ADDR_GPIOE );
RegbankTypeGPIO   volatile rbGPIOF  LOCATE_AT(RB_ADDR_GPIOF );
RegbankTypeGPIO   volatile rbGPIOG  LOCATE_AT(RB_ADDR_GPIOG );
RegbankTypeGPIO   volatile rbGPIOH  LOCATE_AT(RB_ADDR_GPIOH );
RegbankTypeGPIO   volatile rbGPIOI  LOCATE_AT(RB_ADDR_GPIOI );
RegbankTypeGPIO   volatile rbGPIOJ  LOCATE_AT(RB_ADDR_GPIOJ );
RegbankTypeGPIO   volatile rbGPIOK  LOCATE_AT(RB_ADDR_GPIOK );
RegbankTypeDMA    volatile rbDMA1   LOCATE_AT(RB_ADDR_DMA1  );
RegbankTypeDMA    volatile rbDMA2   LOCATE_AT(RB_ADDR_DMA2  );
RegbankTypeEXTI   volatile rbEXTI   LOCATE_AT(RB_ADDR_EXTI  );
RegbankTypeSYSCFG volatile rbSYSCFG LOCATE_AT(RB_ADDR_SYSCFG);
RegbankTypePWR    volatile rbPWR    LOCATE_AT(RB_ADDR_PWR   );
RegbankTypeRTC    volatile rbRTC    LOCATE_AT(RB_ADDR_RTC   );
RegbankTypeTIM    volatile rbTIM01  LOCATE_AT(RB_ADDR_TIM01 );
RegbankTypeTIM    volatile rbTIM02  LOCATE_AT(RB_ADDR_TIM02 );
RegbankTypeTIM    volatile rbTIM03  LOCATE_AT(RB_ADDR_TIM03 );
RegbankTypeTIM    volatile rbTIM04  LOCATE_AT(RB_ADDR_TIM04 );
RegbankTypeTIM    volatile rbTIM05  LOCATE_AT(RB_ADDR_TIM05 );
RegbankTypeTIM    volatile rbTIM06  LOCATE_AT(RB_ADDR_TIM06 );
RegbankTypeTIM    volatile rbTIM07  LOCATE_AT(RB_ADDR_TIM07 );
RegbankTypeTIM    volatile rbTIM08  LOCATE_AT(RB_ADDR_TIM08 );
RegbankTypeTIM    volatile rbTIM09  LOCATE_AT(RB_ADDR_TIM09 );
RegbankTypeTIM    volatile rbTIM10  LOCATE_AT(RB_ADDR_TIM10 );
RegbankTypeTIM    volatile rbTIM11  LOCATE_AT(RB_ADDR_TIM11 );
RegbankTypeTIM    volatile rbTIM12  LOCATE_AT(RB_ADDR_TIM12 );
RegbankTypeTIM    volatile rbTIM13  LOCATE_AT(RB_ADDR_TIM13 );
RegbankTypeTIM    volatile rbTIM14  LOCATE_AT(RB_ADDR_TIM14 );
RegbankTypeUSART  volatile rbUSART1 LOCATE_AT(RB_ADDR_USART1);
RegbankTypeUSART  volatile rbUSART2 LOCATE_AT(RB_ADDR_USART2);
RegbankTypeUSART  volatile rbUSART3 LOCATE_AT(RB_ADDR_USART3);
RegbankTypeUSART  volatile rbUART4  LOCATE_AT(RB_ADDR_UART4 );
RegbankTypeUSART  volatile rbUART5  LOCATE_AT(RB_ADDR_UART5 );
RegbankTypeUSART  volatile rbUSART6 LOCATE_AT(RB_ADDR_USART6);
RegbankTypeSPI    volatile rbSPI1   LOCATE_AT(RB_ADDR_SPI1  );
RegbankTypeSPI    volatile rbSPI2   LOCATE_AT(RB_ADDR_SPI2  );
RegbankTypeSPI    volatile rbSPI3   LOCATE_AT(RB_ADDR_SPI3  );
RegbankTypeSPI    volatile rbSPI4   LOCATE_AT(RB_ADDR_SPI4  );
RegbankTypeSPI    volatile rbSPI5   LOCATE_AT(RB_ADDR_SPI5  );
RegbankTypeSPI    volatile rbSPI6   LOCATE_AT(RB_ADDR_SPI6  );
RegbankTypeI2C    volatile rbI2C1   LOCATE_AT(RB_ADDR_I2C1  );
RegbankTypeI2C    volatile rbI2C2   LOCATE_AT(RB_ADDR_I2C2  );
RegbankTypeI2C    volatile rbI2C3   LOCATE_AT(RB_ADDR_I2C3  );
RegbankTypeIWDG   volatile rbIWDG   LOCATE_AT(RB_ADDR_IWDG  );
RegbankTypeRNG    volatile rbRNG    LOCATE_AT(RB_ADDR_RNG   );
RegbankTypeFMC    volatile rbFMC    LOCATE_AT(RB_ADDR_FMC   );
RegbankTypeLTDC   volatile rbLTDC   LOCATE_AT(RB_ADDR_LTDC  );
RegbankTypeDMA_2D volatile rbDMA_2D LOCATE_AT(RB_ADDR_DMA_2D);
RegbankTypeETH    volatile rbETH    LOCATE_AT(RB_ADDR_ETH   );

WORD volatile WRITEONLY regSTIR     LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F00U));  
WORD volatile WRITEONLY regICIALLU  LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F50U));  
WORD volatile WRITEONLY regICIMVAU  LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F58U));  
WORD volatile WRITEONLY regDCIMVAC  LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F5CU));  
WORD volatile WRITEONLY regDCISW    LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F60U));  
WORD volatile WRITEONLY regDCCMVAU  LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F64U));  
WORD volatile WRITEONLY regDCCMVAC  LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F68U));  
WORD volatile WRITEONLY regDCCSW    LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F6CU));  
WORD volatile WRITEONLY regDCCIMVAC LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F70U));  
WORD volatile WRITEONLY regDCCISW   LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F74U));  

WORD volatile           regITCMCR   LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F90U));           
WORD volatile           regDTCMCR   LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F94U));           
WORD volatile           regAHBPCR   LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F98U));           
WORD volatile           regCACR     LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, F9CU));           
WORD volatile           regAHBSCR   LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, FA0U));           
WORD volatile           regABFSR    LOCATE_AT(CONCAT(SCSPER_ADDR_PREFIX, FA8U));           

void TriggerWatchdog() noexcept
{
  rbIWDG.KR = MASK_IWDG_KR_VALUE;
}

