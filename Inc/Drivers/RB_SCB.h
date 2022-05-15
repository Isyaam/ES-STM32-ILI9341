//
// RB_SCB.h
//

/// \file RB_SCB.h
/// System control block (SCB, core periphery).

#ifndef guard_RB_SCB_H
# define guard_RB_SCB_H

# include <RB.h>

/// Datentyp für SCB-Registerbank.
typedef struct __regbank_SCB
{
  WORD CPUID;                                         ///< CPU ID base register.
  WORD ICSR;                                          ///< Interrupt control and state register.
  WORD VTOR;                                          ///< Vector table offset register.
  WORD AIRCR;                                         ///< Application interrupt and reset control register.

  WORD SCR;                                           ///< System control register.
  WORD CCR;                                           ///< Configuration and control register.

  BYTE SHPR[12];                                      ///< System handler priority registers.

  WORD SHCSR;                                         ///< System handler control and state register.

  union {
    WORD CFSR;                                        ///< Configurable fault status register.
    struct {
      BYTE MFSR;                                      ///< Mem fault status register.
      BYTE BFSR;                                      ///< Bus fault status register.
      HWRD UFSR;                                      ///< Usage fault status register.
    };
  };

  WORD HFSR;                                          ///< Offset: 0x02C, Hard fault status register.
  WORD DFSR;                                          ///< Offset: 0x030 (R/W) Debug Fault Status Register.
  WORD MMFAR;                                         ///< Memory management fault address register.
  WORD BFAR;                                          ///< Bus fault address register.
  WORD AFSR;                                          ///< Auxilliary fault address register.

  WORD PFR[2];                                        ///< Offset: 0x040 (R) Processor Feature Register.
  WORD DFR;                                           ///< Offset: 0x048 (R) Debug Feature Register.
  WORD AFR;                                           ///< Offset: 0x04C (R) Auxiliary Feature Register.
  WORD MMFR[4];                                       ///< Offset: 0x050 (R) Memory Model Feature Register.
  WORD ISAR[5];                                       ///< Offset: 0x060 (R) Instruction Set Attributes Register.
  WORD reserved0[1];
  WORD CLIDR;                                         ///< Offset: 0x078 (R) Cache Level ID register.
  WORD CTR;                                           ///< Offset: 0x07C (R) Cache Type register.
  WORD CCSIDR;                                        ///< Offset: 0x080 (R) Cache Size ID Register.
  WORD CSSELR;                                        ///< Offset: 0x084 (R/W) Cache Size Selection Register.
  WORD CPACR;                                         ///< Offset: 0x088 (R/W) Coprocessor Access Control Register.
} RegbankTypeSCB;

extern RegbankTypeSCB volatile rbSCB;                 ///< SCB-Registerbank.

extern WORD volatile WRITEONLY regSTIR;               ///< Software Triggered Interrupt Register.
extern WORD volatile WRITEONLY regICIALLU;            ///< Instruction cache invalidate all to the Point of Unification (PoU).
extern WORD volatile WRITEONLY regICIMVAU;            ///< Instruction cache invalidate by address to the PoU.
extern WORD volatile WRITEONLY regDCIMVAC;            ///< Data cache invalidate by address to the Point of Coherency (PoC).
extern WORD volatile WRITEONLY regDCISW;              ///< Data cache invalidate by set/way.
extern WORD volatile WRITEONLY regDCCMVAU;            ///< Data cache clean by address to the PoU.
extern WORD volatile WRITEONLY regDCCMVAC;            ///< Data cache clean by address to the PoC.
extern WORD volatile WRITEONLY regDCCSW;              ///< Data cache clean by set/way.
extern WORD volatile WRITEONLY regDCCIMVAC;           ///< Data cache clean and invalidate by address to the PoC.
extern WORD volatile WRITEONLY regDCCISW;             ///< Data cache clean and invalidate by set/way.

extern WORD volatile             regITCMCR;           ///< Instruction Tightly-Coupled Memory Control Register.
extern WORD volatile             regDTCMCR;           ///< Data Tightly-Coupled Memory Control Registers.
extern WORD volatile             regAHBPCR;           ///< AHBP Control Register.
extern WORD volatile             regCACR;             ///< L1 Cache Control Register.
extern WORD volatile             regAHBSCR;           ///< AHB Slave Control Register.
extern WORD volatile             regABFSR;            ///< Auxiliary Bus Fault Status Register.

/// \cond RB_DEFS

// CCR

# define INDX_SCB_CCR_USERSETMPEND 1
# define MASK_SCB_CCR_USERSETMPEND (WORD)REG_BITMASK(SCB_CCR_USERSETMPEND)

# define INDX_SCB_CCR_UNALIGN_TRP 3
# define MASK_SCB_CCR_UNALIGN_TRP  (WORD)REG_BITMASK(SCB_CCR_UNALIGN_TRP)

# define INDX_SCB_CCR_DIVZERO_TRP 4

# define INDX_SCB_CCR_DC        16                    ///< Data cache enable bit position 
# define MASK_SCB_CCR_DC        (WORD)REG_BITMASK(SCB_CCR_DC) 

# define INDX_SCB_CCR_IC        17                    ///< Instruction cache enable bit position 
# define MASK_SCB_CCR_IC        (WORD)REG_BITMASK(SCB_CCR_IC) 

# define INDX_SCB_CCR_BP        18                    ///< Branch prediction enable bit position 
# define MASK_SCB_CCR_BP        (WORD)REG_BITMASK(SCB_CCR_BP) 

// SHPR

# define SCB_SHPR_MEM_FLT       0
# define SCB_SHPR_BUS_FLT       1
# define SCB_SHPR_USG_FLT       2
# define SCB_SHPR_SVC           7
# define SCB_SHPR_PSV           10
# define SCB_SHPR_STK           11

// ICSR definitions

# define INDX_SCB_ICSR_PENDSVCSET 28
# define MASK_SCB_ICSR_PENDSVCSET (WORD)REG_BITMASK(SCB_ICSR_PENDSVCSET)

# define INDX_SCB_ICSR_PENDSVCCLR 27
# define MASK_SCB_ICSR_PENDSVCCLR (WORD)REG_BITMASK(SCB_ICSR_PENDSVCCLR)

# define INDX_SCB_ICSR_ISRPENDING 22
# define MASK_SCB_ICSR_ISRPENDING (WORD)REG_BITMASK(SCB_ICSR_ISRPENDING)

// SHCSR definitions

# define INDX_SCB_SHCSR_SYSTICKACT 11
# define MASK_SCB_SHCSR_SYSTICKACT (WORD)REG_BITMASK(SCB_SHCSR_SYSTICKACT)

# define INDX_SCB_SHCSR_PENDSVACT 10
# define MASK_SCB_SHCSR_PENDSVACT (WORD)REG_BITMASK(SCB_SHCSR_PENDSVACT)

# define INDX_SCB_SHCSR_SVCALLACT 7
# define MASK_SCB_SHCSR_SVCALLACT (WORD)REG_BITMASK(SCB_SHCSR_SVCALLACT)

# define MASK_SCB_SHCSR_SYSTEMACT (MASK_SCB_SHCSR_SYSTICKACT | MASK_SCB_SHCSR_PENDSVACT | MASK_SCB_SHCSR_SVCALLACT)

# define INDX_SCB_SHCSR_USGFAULTACT 3

# define INDX_SCB_SHCSR_BUSFAULTACT 1

# define INDX_SCB_SHCSR_MEMFAULTACT 0

// AIRCR definitions

# define INDX_SCB_AIRCR_SYSRESETREQ 2
# define MASK_SCB_AIRCR_SYSRESETREQ (WORD)(1U << INDX_SCB_AIRCR_SYSRESETREQ)

# define INDX_SCB_AIRCR_PRIGROUP 8
# define MASK_SCB_AIRCR_PRIGROUP_4_4 (WORD)(0x3U << INDX_SCB_AIRCR_PRIGROUP)
# define MASK_SCB_AIRCR_PRIGROUP_3_5 (WORD)(0x4U << INDX_SCB_AIRCR_PRIGROUP)

# define MASK_SCB_AIRCR_VECTKEY_WR 0x05FA0000U     // on write: magic number defined by core, must be written to AIRCR to unlock
# define MASK_SCB_AIRCR_VECTKEY_RD 0xFA050000U     // on read

// HFSR definitions

# define INDX_SCB_HFSR_DEBUGEVT 31

# define INDX_SCB_HFSR_FORCED   30
# define MASK_SCB_HFSR_FORCED   (WORD)REG_BITMASK(SCB_HFSR_FORCED)

# define INDX_SCB_HFSR_VECTTBL  1

/// \endcond

#endif
