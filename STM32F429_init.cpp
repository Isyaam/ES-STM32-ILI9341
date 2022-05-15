//
// STM32F429_init.cpp
// 

/// \file STM32F429_init.cpp
/// Haupt-Initialisierung des Micro-Controllers.

// <<< Use Configuration Wizard in Context Menu >>>

// <h> General settings
//   <o0> HSE (High Speed External) clock [MHz] <4-26>
//   <q12> Use HSI (High Speed Internal) oscillator instead of HSE clock
//   <i> Value for the used HSE Clock.
//   <q3> Setup vector table offset
//   <e4> Enable fault exception and traps
//     <o6.16> Enable memory fault (MEMFAULTENA)
//     <o6.17> Enable bus fault (BUSFAULTENA)
//     <o6.18> Enable usage fault (USGFAULTENA)
//     <h> Unalignment trap (UNALIGN_TRP)
//       <o7.3> Enable unalignment trap (debug)
//       <o8.3> Enable unalignment trap (relase)
//     </h>
//     <i> If this bit is set to true, an unaligned WORD of HWRD access generates a usage fault.
//     <i> Unaligned LDM, STM, LDRD, and STRD instructions always fault irrespective of whether this bit is set or not.
//     <o5.4> Enable divide by zero trap (DIV_0_TRP)
//     <i> Enables faulting when the processor executes an SDIV or UDIV instruction with a divisor of 0:
//     <i> When this bit is set to false, a divide by zero returns a quotient of 0.
//     <o5.1> Enable unprivileged software access to the STIR (USERSETMPEND )
//   </e>
//   <e9.31> Spread spectrum modulation enable
//     <o9.30> Spread select
//     <0=> Center
//     <1=> Down
//     <o10> Modulation frequency [kHz] <1-10>
//     <o11> Modulation depth [1/4 %] <1-8>
//   </e>
//   <h> PLLI2C configuration
//   </h>
//   <h> PLLSAI configuration
//     <o13> VCO output clock frequency [MHz] <48-200:4>
//     <o14> LCD/TFT output clock frequency [MHz] <16-64>
//     <i> must be divider of VCO output clock frequency (==> divider PLLSAIR) 
//     <o15> Pixel clock (DOTCCLK) divider 
//     <0=> Divide LCD/TFT clock by 2
//     <1=> Divide LCD/TFT clock by 4
//     <2=> Divide LCD/TFT clock by 8
//     <3=> Divide LCD/TFT clock by 16
//   </h>
// </h>
#define __HSE_MHZ               8U
#define __HSI_MHZ               16U
#define __LSI_KHZ               32U
#define __SCB_VTOR_SETUP        0  
#define __SCB_FAULTS_SETUP      1                     // # 4  
#define __SCB_CCR_RAW           0x00000212            // # 5
#define __SCB_SHCSR             0x00070000            // # 6
#define __SCB_CCR_UNALIGN_TRP_DEBUG       0x00000008  // # 7
#define __SCB_CCR_UNALIGN_TRP_RELEASE     0x00000000  // # 8
#define __RCC_SSCGR             0x00000000            // # 9
#define __SSCGR_FMOD_KHZ        1
#define __SSCGR_MD_PERCENT_DIV_4 4
#define __DONT_USE_HSE          0                     // #12
#define __PLLSAI_OUTPUT         192                   // #13
#define __PLLSAI_LCD_TFT_CLOCK  48                    // #14
#define __PLLSAI_DOTCLK_DIV     2                     // #15

#ifdef DEBUG
# define __SCB_CCR              (__SCB_CCR_RAW | __SCB_CCR_UNALIGN_TRP_DEBUG)
#else
# define __SCB_CCR              (__SCB_CCR_RAW | __SCB_CCR_UNALIGN_TRP_RELEASE)
#endif


// <e0> System Tick [STK]
//   <o1.2> System timer clock source selection
//     <i> Default: SYSTICKCLK = HCLK/8
//     <0=> SYSTICKCLK = HCLK/8
//     <1=> SYSTICKCLK = HCLK
//   <o2> SYSTICK period [ms] <1-100>
//     <i> Set the timer period for System Timer.
//     <i> Default: 1 (= 1 ms)
//   <e1.1> Enable interrupt
//     <o3> IRQ priority <0-15><#*16>
//   </e>
// </e>
#define __STK_SETUP             1
#define __STK_CTRL_VAL          0x00000006
#define __STK_PERIOD            1
#define __SCB_SHPR_PRI15        48


// <e0> Independent watchdog [IWDG]
//   <o1> Cycle time [s] <1-30><#*10>
// </e>
#define __IWDG_SETUP            0
#define __IWDG_CYCLE            30000  


#include <Compiler.h>
#include <Cortex.h>

#include "STM32F429_init.h"

#include <RB.h>
#include <RB_RCC.h>
#include <RB_SCB.h>
#include <RB_PWR.h>
#include <RB_FLASH.h>
#include <RB_GPIO.h>
#include <RB_FMC.h>

#if __DONT_USE_HSE
# define PLL_M_VALUE            4U

# define SRC_CLK_MHZ            __HSI_MHZ
# define PLLSRC_VALUE           0U                    // 0 == HSI
# define ENABLE_CLOCK()                               ///< Dummy; HSI ist nach Reset immer aktiviert und wird auch nie daktiviert.
# define INFO_TEXT              "HSI"
#else
# if (__HSE_MHZ & 1U) == 0U
#  if (__HSE_MHZ & 3U) == 0U
#   define PLL_M_VALUE          (__HSE_MHZ / 4U)
#  else
#   define PLL_M_VALUE          (__HSE_MHZ / 2U)
#  endif
# else
#  define PLL_M_VALUE           (__HSE_MHZ / 1U)
# endif

# define SRC_CLK_MHZ            __HSE_MHZ
# define PLLSRC_VALUE           MASK_RCC_PLLCFGR_PLLSRC

/// HSE-Takt aktivieren und warten, bis der Takt gültig ist.
static inline void EnableClock() noexcept
{
  do
  {
    SET_REG_BIT(RCC, CR, HSEON);
  } while ( ! GET_REG_BIT(RCC, CR, HSERDY) );
}

# define ENABLE_CLOCK           EnableClock
# define INFO_TEXT              "HSE"
#endif

#if SYSCLK_MHZ > 168
# include <RB_PWR.h>

static inline void EnableOverdrive() noexcept
{
  APBClockEnable(PERIPHERY_APB_PWR);

  do
  {
    SET_REG_BIT(PWR, CR, ODEN);
  } while ( ! GET_REG_BIT(PWR, CSR, ODRDY) );

  do
  {
    SET_REG_BIT(PWR, CR, ODSWEN);
  } while ( ! GET_REG_BIT(PWR, CSR, ODSWRDY) );
}

# define ENABLE_OVERDRIVE       EnableOverdrive
#else
# define ENABLE_OVERDRIVE()
#endif

#define OUT_CLK_MHZ             SYSCLK_MHZ            // Ausgangstakt des VCO; wird in der nachfolgenden Initialisierung als SYSCLK eingestellt

#define CLK_VCO_O_MHZ           (SYSCLK_MHZ * 2U)

// CLK_VCO_I = (HSI oder HSE) / M

#define CLK_VCO_I_MHZ           (SRC_CLK_MHZ / PLL_M_VALUE)

// OUT_CLK = CLK_VCO_O / P ==> P = CLK_VCO_O / OUT_CLK
// PLLP in PLLCFGR des RCC: 00: P=2, 01: P=4, 10: P=6, 11: P=8

#define PLL_P_FACTOR            (CLK_VCO_O_MHZ / OUT_CLK_MHZ)
#define PLL_P_VALUE             ((PLL_P_FACTOR / 2U) - 1U)

// USB OTG FS, SDIO und RNG brauchen einen Takt von genau 48 MHz; dieser wird durch den Teiler PLLQ eingestellt.
// SDIO und RNG brauchen einen Takt von maximal 48 MHz, kann jedoch auch weniger sein.
// ==> Bei Übertaktung (Systemtakt von 180 MHz) kann man den VCO-Ausgang auf 2*180 MHz = 360 MHz einstellen.
// Damit kann man dann jedoch keinen USB-Takt von 48 MHz erreichen. 

#define PLL_Q_VALUE             (CLK_VCO_O_MHZ / 48U)

// CLK_VCO_O = CLK_VCO_I * N ==> N = CLK_VCO_O / CLK_VCO_I

#define PLL_N_VALUE             (CLK_VCO_O_MHZ / CLK_VCO_I_MHZ)

#if (__RCC_SSCGR & 0x80000000) != 0
# define SSCGR_MODPER          ((1000U * CLK_VCO_I_MHZ) / (4U * __SSCGR_FMOD_KHZ))
# define SSCGR_INCSTEP         ((0xFFFFU * __SSCGR_MD_PERCENT_DIV_4 * PLL_N_VALUE) / (4U * 500U * SSCGR_MODPER))

static inline void EnableSSCGR() noexcept
{
  rbRCC.SSCGR = __RCC_SSCGR | (SSCGR_MODPER << INDX_RCC_SSCGR_MODPER) | (SSCGR_INCSTEP << INDX_RCC_SSCGR_INCSTEP);
}

# define ENABLE_SSCGR           EnableSSCGR
#else
# define ENABLE_SSCGR()
#endif

void InitSDRAM() noexcept;

extern "C" void VeryFirstInit(void) noexcept
{
  Cortex::SetBASEPRI_privileged(PRIO_GRANULARITY);

  AHBClockEnable(PERIPHERY_AHB_CCM);
  AHBClockEnable(PERIPHERY_AHB_BKPSRAM); 
  
  /// Enabling the FPU: 
  /// The FPU is disabled from reset. You must enable it before you can use any floating-point instructions. 
  /// The processor must be in privileged mode to read from and write to the CPACR.
  /// Set bits 20-23 to enable CP10 and CP11 coprocessors.
  // Die FPU muss bereits hier initialisiert werden, weil die FP-Lib zur Initialisierung bereits die FPU braucht 
  // (unabhängig davon, welches FPU-Modell man wählt, als auch bei fpu=none; klingt seltsam, ist aber so).

  Cortex::FpuEnable();
  
  ENABLE_CLOCK();
  
  // HCLK = SYSCLK, PCLK1 = HCLK / 4 (low speed), PCLK2 = HCLK / 2 (high speed)

  rbRCC.CFGR = MASK_RCC_CFGR_HPRE_001 | MASK_RCC_CFGR_PPRE2_02 | MASK_RCC_CFGR_PPRE1_04;

  // Aktivierung des PLL mit Einstellung der gewünschten Takte-Quelle (HSI oder HSE).

  rbRCC.PLLCFGR = PLLSRC_VALUE
  |               (PLL_M_VALUE << INDX_RCC_PLLCFGR_PLLM) 
  |               (PLL_N_VALUE << INDX_RCC_PLLCFGR_PLLN)
  |               (PLL_P_VALUE << INDX_RCC_PLLCFGR_PLLP)
  |               (PLL_Q_VALUE << INDX_RCC_PLLCFGR_PLLQ);

  ENABLE_SSCGR();

  // Warten, bis PLL stabil (ggf. wird ewig gewartet, wenn z.B. kein Quarz angeschlossen).
  
  do
  {
    SET_REG_BIT(RCC, CR, PLLON); 
  } while ( ! GET_REG_BIT(RCC, CR, PLLRDY) );

  // Für die STM32F42x/STM32F43x-Prozessoren kann man hier den Over-drive aktivieren, um den Takt auf bis zu 180 MHz
  // zu erhöhen. Die STM32F40x/STM32F41x-Prozessoren gehen bis maximal 168 MHz.
  
  ENABLE_OVERDRIVE();
  
  /// Bei einer Versorgungsspannung > 2,7 V und einem (einzustellenden) Systemtakt (HCLK) von > 150 MHz müssen 
  /// für den FLASH-Zugriff 5 WS eingestellt werden; zusätzlich auch Beschleuniger und Caches aktivieren.
  
  rbFLASH.ACR = MASK_FLASH_ACR_PRFTEN | MASK_FLASH_ACR_ICEN | MASK_FLASH_ACR_DCEN | MASK_FLASH_ACR_LATENCY_5WS;
  
  // Nachfolgend wird der Systemtakt vom PLL übernommen.
  
  do
  {
    SET_REG_BIT(RCC, CFGR, SW_PLL);
  } while ( (rbRCC.CFGR & MASK_RCC_CFGR_SWS) != MASK_RCC_CFGR_SWS_PLL );

  rbSCB.VTOR = IROM1_START;

  rbRCC.PLLSAICFGR = 
  ((__PLLSAI_OUTPUT /          CLK_VCO_I_MHZ) << INDX_RCC_PLLSAICFGR_PLLSAIN) | // VCO-Output
  (                                        7U << INDX_RCC_PLLSAICFGR_PLLSAIQ) | 
  ((__PLLSAI_OUTPUT / __PLLSAI_LCD_TFT_CLOCK) << INDX_RCC_PLLSAICFGR_PLLSAIR);  // LCD-Clock = VCO-Output / PLLSAIR

  rbRCC.DCKCFGR = (rbRCC.DCKCFGR & ~MASK_RCC_DCKCFGR_PLLSAIDIVR) | 
  (__PLLSAI_DOTCLK_DIV << INDX_RCC_DCKCFGR_PLLSAIDIVR);

  do
  {
    SET_REG_BIT(RCC, CR, PLLSAION); 
  } while ( ! GET_REG_BIT(RCC, CR, PLLSAIRDY) ); 
  
  InitSDRAM();
}

unsigned HClk() noexcept
{
  switch(rbRCC.CFGR & MASK_RCC_CFGR_HPRE)
  {
    default:                     return SYSCLK;
    case MASK_RCC_CFGR_HPRE_002: return SYSCLK /   2U;
    case MASK_RCC_CFGR_HPRE_004: return SYSCLK /   4U;
    case MASK_RCC_CFGR_HPRE_008: return SYSCLK /   8U;
    case MASK_RCC_CFGR_HPRE_016: return SYSCLK /  16U;
    case MASK_RCC_CFGR_HPRE_064: return SYSCLK /  64U;
    case MASK_RCC_CFGR_HPRE_128: return SYSCLK / 128U;
    case MASK_RCC_CFGR_HPRE_256: return SYSCLK / 256U;
    case MASK_RCC_CFGR_HPRE_512: return SYSCLK / 512U;
  }
}

unsigned PClk1() noexcept
{
  auto const hclk = HClk();
  
  switch(rbRCC.CFGR & MASK_RCC_CFGR_PPRE1)
  {
    default:                     return hclk;
    case MASK_RCC_CFGR_PPRE1_02: return hclk /  2U;
    case MASK_RCC_CFGR_PPRE1_04: return hclk /  4U;
    case MASK_RCC_CFGR_PPRE1_08: return hclk /  8U;
    case MASK_RCC_CFGR_PPRE1_16: return hclk / 16U;
  }
}
    
unsigned PClk2() noexcept
{
  auto const hclk = HClk();
  
  switch(rbRCC.CFGR & MASK_RCC_CFGR_PPRE2)
  {
    default:                     return hclk;
    case MASK_RCC_CFGR_PPRE2_02: return hclk /  2U;
    case MASK_RCC_CFGR_PPRE2_04: return hclk /  4U;
    case MASK_RCC_CFGR_PPRE2_08: return hclk /  8U;
    case MASK_RCC_CFGR_PPRE2_16: return hclk / 16U;
  }
}
    
#if __STK_SETUP == 1
# include <RB_STK.h>
# include <RB_SCB.h>

# if ( (__STK_CTRL_VAL & MASK_STK_CTRL_CLKSOURCE) == 0 )
#  define STK_CLK()             HClk()
# else
#  define STK_CLK()             (HClk() / 8U)
# endif

static inline void Init_STK() noexcept
{
  unsigned const clock = STK_CLK();

  rbSTK.CSR = 0U;
  rbSTK.RVR = ((__STK_PERIOD * clock) / 1000U) - 1U;
  rbSTK.CVR = 0U; 
  rbSTK.CSR = __STK_CTRL_VAL | MASK_STK_CTRL_ENABLE; // don't forget to enable the counter
}

#else
# define Init_STK()
#endif

#if defined(__IWDG_SETUP) && __IWDG_SETUP == 1
# include <RB_IWDG.h>

static void Init_IWDG(void) noexcept 
{
  rbIWDG.KR = MASK_IWDG_KR_UNLOCK;
  rbIWDG.PR = MASK_IWDG_PR_DIV256;
  rbIWDG.RLR = __IWDG_CYCLE / 8;
  rbIWDG.KR = MASK_IWDG_KR_START;

  ITM_PUTS("Watchdog initialized");
}

#else
# define Init_IWDG()
#endif

#if __SCB_VTOR_SETUP == 1

static inline void Init_SCB_VTOR() noexcept 
{
  EXTERN_C WORD __Vectors[];
  
  rbSCB.VTOR = (WORD)__Vectors;
}

#else
# define Init_SCB_VTOR()
#endif

#if __SCB_FAULTS_SETUP == 1

static inline void Init_SCB_FAULTS() noexcept
{
  rbSCB.SHCSR = __SCB_SHCSR;
  rbSCB.CCR = __SCB_CCR;
}

#else
# define Init_SCB_FAULTS()
#endif

static __attribute__((constructor(102))) void LocalInit(void) noexcept 
{
  // Diese Funktion wird durch die Laufzeitumgebung (RTE) nach Initialisierung der RTE jedoch noch vor Aufruf von main() aufgerufen.

  Cortex::SetPRIMASK_privileged();

  rbMPU.RNR  = 0;
  rbMPU.RBAR = IROM1_START;
  rbMPU.RASR = MASK_MPU_RASR_ENABLE | MASK_MPU_RASR_SIZE_001MB | MASK_MPU_RASR_C                   | MASK_MPU_RASR_AP_RW_RO;

  rbMPU.RNR  = 1;
  rbMPU.RBAR = IRAM1_START;
  rbMPU.RASR = MASK_MPU_RASR_ENABLE | MASK_MPU_RASR_SIZE_128KB | MASK_MPU_RASR_C | MASK_MPU_RASR_S | MASK_MPU_RASR_AP_RW_RW | MASK_MPU_RASR_XN;

  rbMPU.RNR  = 2;
  rbMPU.RBAR = IRAM2_START;
  rbMPU.RASR = MASK_MPU_RASR_ENABLE | MASK_MPU_RASR_SIZE_064KB | MASK_MPU_RASR_C | MASK_MPU_RASR_B | MASK_MPU_RASR_AP_RW_RW | MASK_MPU_RASR_XN;

  // Achtung: 'Bit band alias' (Cortex-M4) liegt im Bereich 0x42000000 bis 0x43FFFFFF (32 MB)
  // Peripherie (ab 0x40000000) muss dehalb mindestens 64 MB umfassen.
  // Wenn AHB2 verwendet werden soll, dann sogar entsprechend mehr.
  // Der Cortex-M7 hat aus Performance-Gründen kein bit banding mehr!
  
  rbMPU.RNR  = 3;
  rbMPU.RBAR = 0x40000000U;
  rbMPU.RASR = MASK_MPU_RASR_ENABLE | MASK_MPU_RASR_SIZE_512MB | MASK_MPU_RASR_B | MASK_MPU_RASR_S | MASK_MPU_RASR_AP_RW_RW | MASK_MPU_RASR_XN;
  
  // SDRAM ab 0xD0000000, 8 MB
  
  rbMPU.RNR  = 4;
  rbMPU.RBAR = 0xD0000000U;
  rbMPU.RASR = MASK_MPU_RASR_ENABLE | MASK_MPU_RASR_SIZE_008MB | MASK_MPU_RASR_C | MASK_MPU_RASR_S | MASK_MPU_RASR_AP_RW_RW | MASK_MPU_RASR_XN;
  
  // PBP ab 0xE0000000
  // Nachfolgende Einstellung funktioniert noch nicht richtig. Sinn dieser Maßnahme wäre es, auf die SCB-Register auch im 
  // nicht-privilegierten zugreifen zu können. Es ist jedoch fraglich, ob das überhaupt einstellbar ist.

  rbMPU.RNR  = 5; 
  rbMPU.RBAR = 0xE0000000U;
  rbMPU.RASR = MASK_MPU_RASR_ENABLE | MASK_MPU_RASR_SIZE_001MB | MASK_MPU_RASR_AP_RW_RW | MASK_MPU_RASR_XN; 
  
  rbMPU.CTRL = MASK_MPU_CTRL_ENABLE;

  Cortex::DSB();
  Cortex::ISB();
    
	static WORD stack[0x4000 / sizeof(WORD)] __attribute__((section("CCM")));

  Cortex::SwitchStack(stack);

  Init_SCB_VTOR();
  Init_SCB_FAULTS();
  Init_STK();
  Init_IWDG();

  // Prioritäten der wichtigsten Core-IRQs einstellen. 
  
  rbSCB.SHPR[SCB_SHPR_MEM_FLT] = PRIO_GRANULARITY *  0U;
  rbSCB.SHPR[SCB_SHPR_BUS_FLT] = PRIO_GRANULARITY *  0U;
  rbSCB.SHPR[SCB_SHPR_MEM_FLT] = PRIO_GRANULARITY *  0U;
  rbSCB.SHPR[SCB_SHPR_SVC    ] = PRIO_GRANULARITY *  1U;
  rbSCB.SHPR[SCB_SHPR_PSV    ] = PRIO_GRANULARITY * 15U;
  rbSCB.SHPR[SCB_SHPR_STK    ] = __SCB_SHPR_PRI15; 

  Cortex::SetBASEPRI_privileged(Cortex::GetMinPrio());
  Cortex::ClrPRIMASK_privileged();
}

extern "C" void UndefinedIRQ(void)
{
  DEBUG_BREAK(1); 

  for ( ;; ) 
  {
    Cortex::Reset();
  }
}

extern "C" __weak void HandleSVC   (WORD *) { for ( ;; ) DEBUG_BREAK(1); }

extern "C" __weak void HandleHrdFlt(WORD *) { for ( ;; ) DEBUG_BREAK(1); }
extern "C" __weak void HandleUsgFlt(WORD *) { for ( ;; ) DEBUG_BREAK(1); }
extern "C" __weak void HandleBusFlt(WORD *) { for ( ;; ) DEBUG_BREAK(1); }
extern "C" __weak void HandleMemFlt(WORD *) { for ( ;; ) DEBUG_BREAK(1); }
