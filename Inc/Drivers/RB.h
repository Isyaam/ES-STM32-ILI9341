//
// RB.h
//

/// \file RB.h
/// Macros zur Definition der Register-Bits für STM32Fxxx.

#ifndef guard_RB_H
# define guard_RB_H

# include <Compiler.h>

# define REG_BITMASK(N)         (1U << INDX_ ## N)

# define SET_REG_BIT(RB, REG, BIT) ( rb ## RB.REG |=  MASK_ ## RB ## _ ## REG ## _ ## BIT)   
# define RES_REG_BIT(RB, REG, BIT) ( rb ## RB.REG &= ~MASK_ ## RB ## _ ## REG ## _ ## BIT)   
# define GET_REG_BIT(RB, REG, BIT) ((rb ## RB.REG &   MASK_ ## RB ## _ ## REG ## _ ## BIT) != 0)   

typedef struct __regbank_MPU
{
  union {
    WORD TYPE;
    struct {
      BYTE res0;
      BYTE TYPE_DREGION;
      BYTE TYPE_IREGION;
      BYTE res3;
    };
  };
  WORD CTRL;                    
  WORD RNR;                     
  WORD RBAR;                    
  WORD RASR;                    
  WORD RBAR_A1;                 
  WORD RASR_A1;                 
  WORD RBAR_A2;                 
  WORD RASR_A2;
  WORD RBAR_A3;
  WORD RASR_A3;
} RegbankTypeMPU;

extern RegbankTypeMPU volatile rbMPU;

# define MASK_MPU_RASR_ENABLE   1U

# define INDX_MPU_RASR_SIZE     1

# define INDX_MPU_RASR_SRD      8

# define INDX_MPU_RASR_B        16
# define MASK_MPU_RASR_B        (1U << INDX_MPU_RASR_B)

# define INDX_MPU_RASR_C        17
# define MASK_MPU_RASR_C        (1U << INDX_MPU_RASR_C)

# define INDX_MPU_RASR_S        18
# define MASK_MPU_RASR_S        (1U << INDX_MPU_RASR_S)

# define INDX_MPU_RASR_TEX      19

# define INDX_MPU_RASR_AP       24

# define INDX_MPU_RASR_XN       28

/// The processor prevents instruction accesses (a fault exception is 
/// generated on execution of an instruction executed from an XN region).
# define MASK_MPU_RASR_XN       (1U << INDX_MPU_RASR_XN) 

// Memory region sizes

# define MASK_MPU_RASR_SIZE_001KB (0x09U << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_002KB (0x0AU << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_004KB (0x0BU << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_008KB (0x0CU << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_016KB (0x0DU << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_032KB (0x0EU << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_064KB (0x0FU << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_128KB (0x10U << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_256KB (0x11U << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_512KB (0x12U << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_001MB (0x13U << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_002MB (0x14U << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_004MB (0x15U << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_008MB (0x16U << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_016MB (0x17U << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_032MB (0x18U << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_064MB (0x19U << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_128MB (0x1AU << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_256MB (0x1BU << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_512MB (0x1CU << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_001GB (0x1DU << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_002GB (0x1EU << INDX_MPU_RASR_SIZE)
# define MASK_MPU_RASR_SIZE_004GB (0x1FU << INDX_MPU_RASR_SIZE)

// Memory region permissions (privileged, user; NA=no access)

#define  MASK_MPU_RASR_AP_NA_NA  (0x0U << INDX_MPU_RASR_AP)
#define  MASK_MPU_RASR_AP_RW_NA  (0x1U << INDX_MPU_RASR_AP)
#define  MASK_MPU_RASR_AP_RW_RO  (0x2U << INDX_MPU_RASR_AP)
#define  MASK_MPU_RASR_AP_RW_RW  (0x3U << INDX_MPU_RASR_AP) ///< Memory region full access (privileged: read/write, user: read/write).
#define  MASK_MPU_RASR_AP_RO_NA  (0x5U << INDX_MPU_RASR_AP) 
#define  MASK_MPU_RASR_AP_RO_RO  (0x6U << INDX_MPU_RASR_AP) 

// Memory region types

#define  MPU_REGION_STRONGLY_ORDERED 0x0
#define  MPU_REGION_DEVICE      MASK_MPU_RASR_B
#define  MPU_REGION_NORMAL_WB   (MASK_MPU_RASR_B | MASK_MPU_RASR_C) ///< Write-back, no write allocate
#define  MPU_REGION_NORMAL_WT   MASK_MPU_RASR_C                     ///< Write-through, no write allocate
#define  MPU_REGION_NORMAL_WBWA (MASK_MPU_RASR_B | MASK_MPU_RASR_C | (1U << INDX_MPU_RASR_TEX)) ///< Write-through, write and read allocate

// Control regiszer values

# define MASK_MPU_CTRL_ENABLE   0x1U

# define MASK_MPU_CTRL_HFNMIENA 0x2U

# define MASK_MPU_CTRL_PRIVDEFENA 0x4U              ///< Enables privileged software access to the default memory map

typedef struct __regbank_DBG
{
  WORD DHCSR;
  WORD DCRSR;
  WORD DCRDR;
  WORD DEMCR;
} RegbankTypeDBG;

extern RegbankTypeDBG volatile rbDBG;

/// \cond RB_DEFS

// DEMCR definitions

# define INDX_DBG_DEMCR_TRCENA  24
# define MASK_DBG_DEMCR_TRCENA  (WORD)REG_BITMASK(DBG_DEMCR_TRCENA)

/// \endcond

// Die ersten drei Hexziffern der Adresse bilden den Prefix für die verschiedenene I/O-Bereiche.

# define PERIPH_ADDR_PREFIX     0x400 ///< Cortex-Mx periphery start address prefix
# define EXTPER_ADDR_PREFIX     0x500
# define DEVICE_ADDR_PREFIX     0xA00 ///< Cortex-Mx external device start address prefix.
# define PRVPER_ADDR_PREFIX     0xE00 ///< Cortex-Mx private peripheral bus (PPB, 1MB) address prefix (first 3 hex digits of address).

void TriggerWatchdog() noexcept;

#endif

