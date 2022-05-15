//
// Priority.cpp
//

#include <Compiler.h>

#include <RB_SCB.h>
#include <RB_NVIC.h>

// <<< Use Configuration Wizard in Context Menu >>>

// <h> IRQ priorities (external) 

//   <h> RTC
//     <o0> Wakeup <0-15><#*16>
//     <o1> Alarms (A+B) <0-15><#*16>
//   </h>
#define __PRIO_RTC_WKUP         128
#define __PRIO_RTC_ALARM        128

//   <h> Timers
//     <h> TIM01, TIM09, TIM10, TIM11
//       <o0> TIM01_BK, TIM09 <0-15><#*16>
//       <o1> TIM01_UE, TIM10 <0-15><#*16>
//       <o2> TIM01_TR, TIM11 <0-15><#*16>
//       <o3> TIM01_CC <0-15><#*16>
//     </h>
//     <o4> TIM02 <0-15><#*16>
//     <o5> TIM03 <0-15><#*16>
//     <o6> TIM04 <0-15><#*16>
//     <o7> TIM05 <0-15><#*16>
//     <o8> TIM06 <0-15><#*16>
//     <o9> TIM07 <0-15><#*16>
//     <h> TIM08, TIM12, TIM13, TIM14
//       <o10> TIM08_BK, TIM12 <0-15><#*16>
//       <o11> TIM08_UE, TIM13 <0-15><#*16>
//       <o12> TIM08_TR, TIM14 <0-15><#*16>
//       <o13> TIM08_CC <0-15><#*16>
//     </h>
//   </h>
#define __PRIO_TIM01_BR_TIM09   128
#define __PRIO_TIM01_UE_TIM10   128
#define __PRIO_TIM01_TR_TIM11   128
#define __PRIO_TIM01_CC         128
#define __PRIO_TIM02            128
#define __PRIO_TIM03            128
#define __PRIO_TIM04            128
#define __PRIO_TIM05            128
#define __PRIO_TIM06            128
#define __PRIO_TIM07            128
#define __PRIO_TIM08_BR_TIM12   128
#define __PRIO_TIM08_UE_TIM13   128
#define __PRIO_TIM08_TR_TIM14   128
#define __PRIO_TIM08_CC         128

//   <h> EXTI
//     <o0> EXTI00 <0-15><#*16>
//     <o1> EXTI01 <0-15><#*16>
//     <o2> EXTI02 <0-15><#*16>
//     <o3> EXTI03 <0-15><#*16>
//     <o4> EXTI04 <0-15><#*16>
//     <o5> EXTI05 .. EXTI09 <0-15><#*16>
//     <o6> EXTI10 .. EXTI15 <0-15><#*16>
//   </h>
#define __PRIO_EXTI00           128
#define __PRIO_EXTI01           128
#define __PRIO_EXTI02           128
#define __PRIO_EXTI03           128
#define __PRIO_EXTI04           128
#define __PRIO_EXTI05TO09       128
#define __PRIO_EXTI10TO15       128

//   <h> U(S)ARTs
//     <o0> USART1 <0-15><#*16>
//     <o1> USART2 <0-15><#*16>
//     <o2> USART3 <0-15><#*16>
//     <o2> UART4 <0-15><#*16>
//     <o3> UART5 <0-15><#*16>
//     <o5> USART6 <0-15><#*16>
//   </h>
#define __PRIO_USART1           128
#define __PRIO_USART2           128
#define __PRIO_USART3           128
#define __PRIO_UART4            128
#define __PRIO_UART5            128
#define __PRIO_USART6           128

//   <h> DMA Streams
//     <h> DMA1
//       <o0> Stream #0 <0-15><#*16>
//       <o1> Stream #1 <0-15><#*16>
//       <o2> Stream #2 <0-15><#*16>
//       <o3> Stream #3 <0-15><#*16>
//       <o4> Stream #4 <0-15><#*16>
//       <o5> Stream #5 <0-15><#*16>
//       <o6> Stream #6 <0-15><#*16>
//       <o7> Stream #7 <0-15><#*16>
//     </h>
//     <h> DMA2
//       <o8> Stream #0 <0-15><#*16>
//       <o9> Stream #1 <0-15><#*16>
//       <o10> Stream #2 <0-15><#*16>
//       <o11> Stream #3 <0-15><#*16>
//       <o12> Stream #4 <0-15><#*16>
//       <o13> Stream #5 <0-15><#*16>
//       <o14> Stream #6 <0-15><#*16>
//       <o15> Stream #7 <0-15><#*16>
//     </h>
//   </h>
#define __PRIO_DMA1_STREAM0     128
#define __PRIO_DMA1_STREAM1     128
#define __PRIO_DMA1_STREAM2     128
#define __PRIO_DMA1_STREAM3     128
#define __PRIO_DMA1_STREAM4     128
#define __PRIO_DMA1_STREAM5     128
#define __PRIO_DMA1_STREAM6     128
#define __PRIO_DMA1_STREAM7     128
#define __PRIO_DMA2_STREAM0     128
#define __PRIO_DMA2_STREAM1     128
#define __PRIO_DMA2_STREAM2     128
#define __PRIO_DMA2_STREAM3     128
#define __PRIO_DMA2_STREAM4     128
#define __PRIO_DMA2_STREAM5     128
#define __PRIO_DMA2_STREAM6     128
#define __PRIO_DMA2_STREAM7     128

//   <h> SPIs
//     <o0> SPI1 <0-15><#*16>
//     <o1> SPI2 <0-15><#*16>
//     <o2> SPI3 <0-15><#*16>
//     <o3> SPI4 <0-15><#*16>
//     <o4> SPI5 <0-15><#*16>
//     <o5> SPI6 <0-15><#*16>
//   </h>
#define __PRIO_SPI1             128
#define __PRIO_SPI2             128
#define __PRIO_SPI3             128
#define __PRIO_SPI4             128
#define __PRIO_SPI5             128
#define __PRIO_SPI6             128

//   <h> I2Cs
//     <o0> I2C1 (Event) <0-15><#*16>
//     <o1> I2C2 (Event) <0-15><#*16>
//     <o2> I2C3 (Event) <0-15><#*16>
//     <o3> I2C1 (Error) <0-15><#*16>
//     <o4> I2C2 (Error) <0-15><#*16>
//     <o5> I2C3 (Error) <0-15><#*16>
//   </h>
#define __PRIO_I2C1_EV          128
#define __PRIO_I2C2_EV          128
#define __PRIO_I2C3_EV          128
#define __PRIO_I2C1_ER          128
#define __PRIO_I2C2_ER          128
#define __PRIO_I2C3_ER          128

//   <o0> ADC123 <0-15><#*16>
#define __PRIO_ADC              128

//   <o0> FLASH <0-15><#*16>
#define __PRIO_FLASH            128

//   <o0> ETH <0-15><#*16>
#define __PRIO_ETH              128

// </h>

// <h> Core IRQ priorities

//  <o0> Memory management faut prioriry <0-15><#*16>
//  <o1> Bus faut prioriry <0-15><#*16>
//  <o2> Usage faut prioriry <0-15><#*16>
//  <o3> SVC prioriry <0-15><#*16>
//  <o4> PSV prioriry <0-15><#*16>
//  <o5> STK (system tick) prioriry <0-15><#*16>
//  <o6> Highest prioriry <0-15><#*16>
#define __PRIO_MEMFAULT         0
#define __PRIO_BUSFAULT         0
#define __PRIO_USGFAULT         0
#define __PRIO_SVC              16
#define __PRIO_PSV              240
#define __PRIO_STK              32
#define __PRIO_MIN              32
// </h>

static inline void SetPrio(unsigned const irqNum, BYTE const prio) noexcept
{
  EXTIRQ_SET_PRIO(irqNum, prio);
}

static void LocalInit() __attribute__((constructor(103)));

static void LocalInit()
{
  rbSCB.AIRCR = MASK_SCB_AIRCR_VECTKEY_WR | MASK_SCB_AIRCR_PRIGROUP_4_4;
  
  rbSCB.SHPR[SCB_SHPR_MEM_FLT] = __PRIO_MEMFAULT;
  rbSCB.SHPR[SCB_SHPR_BUS_FLT] = __PRIO_BUSFAULT;
  rbSCB.SHPR[SCB_SHPR_USG_FLT] = __PRIO_USGFAULT;
  rbSCB.SHPR[SCB_SHPR_SVC    ] = __PRIO_SVC;
  rbSCB.SHPR[SCB_SHPR_PSV    ] = __PRIO_PSV;
  rbSCB.SHPR[SCB_SHPR_STK    ] = __PRIO_STK;

  SetPrio(EXTIRQ_RTC_WKUP      , __PRIO_RTC_WKUP);
  SetPrio(EXTIRQ_RTC_ALARM     , __PRIO_RTC_ALARM);

  SetPrio(EXTIRQ_FLASH         , __PRIO_FLASH);

  SetPrio(EXTIRQ_TIM01_BR_TIM09, __PRIO_TIM01_BR_TIM09);
  SetPrio(EXTIRQ_TIM01_UE_TIM10, __PRIO_TIM01_UE_TIM10);
  SetPrio(EXTIRQ_TIM01_TR_TIM11, __PRIO_TIM01_TR_TIM11);
  SetPrio(EXTIRQ_TIM01_CC      , __PRIO_TIM01_CC);
  SetPrio(EXTIRQ_TIM02         , __PRIO_TIM02); 
  SetPrio(EXTIRQ_TIM03         , __PRIO_TIM03);
  SetPrio(EXTIRQ_TIM04         , __PRIO_TIM04);
  SetPrio(EXTIRQ_TIM05         , __PRIO_TIM05);
  SetPrio(EXTIRQ_TIM06_DAC     , __PRIO_TIM06);
  SetPrio(EXTIRQ_TIM07         , __PRIO_TIM07);
  SetPrio(EXTIRQ_TIM08_BR_TIM12, __PRIO_TIM08_BR_TIM12);
  SetPrio(EXTIRQ_TIM08_UE_TIM13, __PRIO_TIM08_UE_TIM13);
  SetPrio(EXTIRQ_TIM08_TR_TIM14, __PRIO_TIM08_TR_TIM14);
  SetPrio(EXTIRQ_TIM08_CC      , __PRIO_TIM08_CC);

  SetPrio(EXTIRQ_EXTI00        , __PRIO_EXTI00);
  SetPrio(EXTIRQ_EXTI01        , __PRIO_EXTI01);
  SetPrio(EXTIRQ_EXTI02        , __PRIO_EXTI02);
  SetPrio(EXTIRQ_EXTI03        , __PRIO_EXTI03);
  SetPrio(EXTIRQ_EXTI04        , __PRIO_EXTI04);
  SetPrio(EXTIRQ_EXTI05TO09    , __PRIO_EXTI05TO09);
  SetPrio(EXTIRQ_EXTI10TO15    , __PRIO_EXTI10TO15);

  SetPrio(EXTIRQ_USART1        , __PRIO_USART1);
  SetPrio(EXTIRQ_USART2        , __PRIO_USART2);
  SetPrio(EXTIRQ_USART3        , __PRIO_USART3);
  SetPrio(EXTIRQ_UART4         , __PRIO_UART4);
  SetPrio(EXTIRQ_UART5         , __PRIO_UART5);
  SetPrio(EXTIRQ_USART6        , __PRIO_USART6);

  SetPrio(EXTIRQ_SPI1          , __PRIO_SPI1);
  SetPrio(EXTIRQ_SPI2          , __PRIO_SPI2);
  SetPrio(EXTIRQ_SPI3          , __PRIO_SPI3);

  SetPrio(EXTIRQ_I2C1_EV       , __PRIO_I2C1_EV);
  SetPrio(EXTIRQ_I2C1_ER       , __PRIO_I2C1_ER);
  SetPrio(EXTIRQ_I2C2_EV       , __PRIO_I2C2_EV);
  SetPrio(EXTIRQ_I2C2_ER       , __PRIO_I2C2_ER);
  SetPrio(EXTIRQ_I2C3_EV       , __PRIO_I2C3_EV);
  SetPrio(EXTIRQ_I2C3_ER       , __PRIO_I2C3_ER);

  SetPrio(EXTIRQ_ADC           , __PRIO_ADC);

  SetPrio(EXTIRQ_DMA1_STREAM0  , __PRIO_DMA1_STREAM0);
  SetPrio(EXTIRQ_DMA1_STREAM1  , __PRIO_DMA1_STREAM1);
  SetPrio(EXTIRQ_DMA1_STREAM2  , __PRIO_DMA1_STREAM2);
  SetPrio(EXTIRQ_DMA1_STREAM3  , __PRIO_DMA1_STREAM3);
  SetPrio(EXTIRQ_DMA1_STREAM4  , __PRIO_DMA1_STREAM4);
  SetPrio(EXTIRQ_DMA1_STREAM5  , __PRIO_DMA1_STREAM5);
  SetPrio(EXTIRQ_DMA1_STREAM6  , __PRIO_DMA1_STREAM6);
  SetPrio(EXTIRQ_DMA1_STREAM7  , __PRIO_DMA1_STREAM7);
  SetPrio(EXTIRQ_DMA2_STREAM0  , __PRIO_DMA2_STREAM0);
  SetPrio(EXTIRQ_DMA2_STREAM1  , __PRIO_DMA2_STREAM1);
  SetPrio(EXTIRQ_DMA2_STREAM2  , __PRIO_DMA2_STREAM2);
  SetPrio(EXTIRQ_DMA2_STREAM3  , __PRIO_DMA2_STREAM3);
  SetPrio(EXTIRQ_DMA2_STREAM4  , __PRIO_DMA2_STREAM4);
  SetPrio(EXTIRQ_DMA2_STREAM5  , __PRIO_DMA2_STREAM5);
  SetPrio(EXTIRQ_DMA2_STREAM6  , __PRIO_DMA2_STREAM6);
  SetPrio(EXTIRQ_DMA2_STREAM7  , __PRIO_DMA2_STREAM7);

  SetPrio(EXTIRQ_ETH           , __PRIO_ETH);
}
