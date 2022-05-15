//
// RB_I2C.h
//

/// \file RB_I2C.h
/// Deklaration der I2C-Registerbänke.

#ifndef guard_RB_I2C_H
# define guard_RB_I2C_H

# include <RB.h>

/// Datentyp für I2C-Registerbank, s. RM0033 Reference Manual, Kapitel 23.
typedef struct __regbank_I2C
{
  HWRD CR1;                                           ///< Control register 1.
  HWRD reserved00;
  
  HWRD CR2;                                           ///< Control register 2.
  HWRD reserved01;

  WORD OAR1;
  WORD OAR2;

	BYTE DR;                                            ///< Data register.
  BYTE reserved04a;
  HWRD reserved04b;

	HWRD SR1;                                           ///< Status register 1.
  HWRD reserved05;
  
  WORD SR2;                                           ///< Status register 2.
  HWRD reserved06;

  HWRD CCR;
  HWRD reserved07;

  BYTE TRISE;
  BYTE reserved08a;
  HWRD reserved08b;
} RegbankTypeI2C;

extern RegbankTypeI2C volatile rbI2C1;
extern RegbankTypeI2C volatile rbI2C2;
extern RegbankTypeI2C volatile rbI2C3;

/// \cond RB_DEFS

// CR1

# define INDX_I2C_CR1_PE        0                     ///< Periphery Enable.
# define MASK_I2C_CR1_PE        (HWRD)REG_BITMASK(I2C_CR1_PE)     

# define INDX_I2C_CR1_SMBUS     1                     ///< SM BUS Mode (0 = I2C, 1 = SMBUS).
# define MASK_I2C_CR1_SMBUS     (HWRD)REG_BITMASK(I2C_CR1_SMBUS)

# define INDX_I2C_CR1_SMBTYPE   3                     ///< SM BUS Type  (0 = Device, 1 = Host).
# define MASK_I2C_CR1_SMBTYPE   (HWRD)REG_BITMASK(I2C_CR1_SMBTYPE)

# define INDX_I2C_CR1_ENARP     4                     ///< Enable ARP.
# define MASK_I2C_CR1_ENARP     (HWRD)REG_BITMASK(I2C_CR1_ENARP)

# define INDX_I2C_CR1_ENPEC     5                     ///< PEC Enable.
# define MASK_I2C_CR1_ENPEC     (HWRD)REG_BITMASK(I2C_CR1_ENPEC)

# define INDX_I2C_CR1_ENGC      6                     ///< General Call Enable.
# define MASK_I2C_CR1_ENGC      (HWRD)REG_BITMASK(I2C_CR1_ENGC)

# define INDX_I2C_CR1_NOSTRETCH 7                     ///< Clock Stretching Disable.
# define MASK_I2C_CR1_NOSTRETCH (HWRD)REG_BITMASK(I2C_CR1_NOSTRETCH)

# define INDX_I2C_CR1_START     8                     ///< Start Generation.
# define MASK_I2C_CR1_START     (HWRD)REG_BITMASK(I2C_CR1_START)

# define INDX_I2C_CR1_STOP      9                     ///< Stop Generation.
# define MASK_I2C_CR1_STOP      (HWRD)REG_BITMASK(I2C_CR1_STOP)

# define INDX_I2C_CR1_ACK       10                    ///< Acknowledge Enable.
# define MASK_I2C_CR1_ACK       (HWRD)REG_BITMASK(I2C_CR1_ACK)

# define INDX_I2C_CR1_POS       11                    ///< Ack/Pec position for data receive
# define MASK_I2C_CR1_POS       (HWRD)REG_BITMASK(I2C_CR1_POS)

# define INDX_I2C_CR1_PEC       12                    ///< Packet error checking.
# define MASK_I2C_CR1_PEC       (HWRD)REG_BITMASK(I2C_CR1_PEC)

# define INDX_I2C_CR1_ALERT     13                    ///< SM BUS Alert.
# define MASK_I2C_CR1_ALERT     (HWRD)REG_BITMASK(I2C_CR1_ALERT)

# define INDX_I2C_CR1_SWRST     15                    ///< Software Reset (0 = off, 1 = on)
# define MASK_I2C_CR1_SWRST     (HWRD)REG_BITMASK(I2C_CR1_SWRST)

// CR2

# define INDX_I2C_CR2_FREQ      0                     ///< baud rate control (bits 3..5).
# define MASK_I2C_CR2_FREQ_10MHZ (HWRD)(10U << INDX_I2C_CR2_FREQ)
# define MASK_I2C_CR2_FREQ_15MHZ (HWRD)(15U << INDX_I2C_CR2_FREQ)
# define MASK_I2C_CR2_FREQ_30MHZ (HWRD)(30U << INDX_I2C_CR2_FREQ) 

# define INDX_I2C_CR2_ITERREN   8                     ///< Error Interrupt Enable.
# define MASK_I2C_CR2_ITERREN   (HWRD)REG_BITMASK(I2C_CR2_ITERREN)

# define INDX_I2C_CR2_ITEVTEN   9                     ///< Event Interrupt Enable.
# define MASK_I2C_CR2_ITEVTEN   (HWRD)REG_BITMASK(I2C_CR2_ITEVTEN)

# define INDX_I2C_CR2_ITBUFEN   10                    ///< Buffer Interrupt Enable.
# define MASK_I2C_CR2_ITBUFEN   (HWRD)REG_BITMASK(I2C_CR2_ITBUFEN)

# define INDX_I2C_CR2_DMAEN     11                    ///< DMA Request Enable. 
# define MASK_I2C_CR2_DMAEN     (HWRD)REG_BITMASK(I2C_CR2_DMAEN)

# define INDX_I2C_CR2_LAST      12                    ///< DMA Last Transfer.
# define MASK_I2C_CR2_LAST      (HWRD)REG_BITMASK(I2C_CR2_LAST)

// SR1

# define INDX_I2C_SR1_SB        0                     ///< Sart Bit.
# define MASK_I2C_SR1_SB        (HWRD)REG_BITMASK(I2C_SR1_SB)

# define INDX_I2C_SR1_ADDR      1                     ///< Adress sent, ACK matched.
# define MASK_I2C_SR1_ADDR      (HWRD)REG_BITMASK(I2C_SR1_ADDR)

# define INDX_I2C_SR1_BTF       2                     ///< Byte Transfer finished.
# define MASK_I2C_SR1_BTF       (HWRD)REG_BITMASK(I2C_SR1_BTF)

# define INDX_I2C_SR1_ADD10     3                     ///< 10-bit Header sent, Master has sent first adress Byte (header).
# define MASK_I2C_SR1_ADD10     (HWRD)REG_BITMASK(I2C_SR1_ADD10)

# define INDX_I2C_SR1_STOPF     4                     ///< Stop Detection.
# define MASK_I2C_SR1_STOPF     (HWRD)REG_BITMASK(I2C_SR1_STOPF)

# define INDX_I2C_SR1_RXNE      6                     ///< Rx Not Empty.
# define MASK_I2C_SR1_RXNE      (HWRD)REG_BITMASK(I2C_SR1_RXNE)

# define INDX_I2C_SR1_TXE       7                     ///< Tx Empty.
# define MASK_I2C_SR1_TXE       (HWRD)REG_BITMASK(I2C_SR1_TXE)

# define INDX_I2C_SR1_BERR      8                     ///< Bus Error.
# define MASK_I2C_SR1_BERR      (HWRD)REG_BITMASK(I2C_SR1_BERR)

# define INDX_I2C_SR1_ARLO      9                     ///< Arbitration Lost.
# define MASK_I2C_SR1_ARLO      (HWRD)REG_BITMASK(I2C_SR1_ARLO)

# define INDX_I2C_SR1_AF        10                    ///< ACKnowledge Failure.
# define MASK_I2C_SR1_AF        (HWRD)REG_BITMASK(I2C_SR1_AF)

# define INDX_I2C_SR1_OVR       11                    ///< Overrun/Underrun Error
# define MASK_I2C_SR1_OVR       (HWRD)REG_BITMASK(I2C_SR1_OVR)

# define INDX_I2C_SR1_PECERR    12                    ///< PEC Error in Reception.
# define MASK_I2C_SR1_PECERR    (HWRD)REG_BITMASK(I2C_SR1_PECERR)

# define INDX_I2C_SR1_TIMEOUT   14                    ///< Timeout or Tlow Error.
# define MASK_I2C_SR1_TIMEOUT   (HWRD)REG_BITMASK(I2C_SR1_TIMEOUT)

# define INDX_I2C_SR1_SMBALERT  15                    ///< SMB Alert.
# define MASK_I2C_SR1_SMBALERT  (HWRD)REG_BITMASK(I2C_SR1_SMBALERT)

// SR2

# define INDX_I2C_SR2_MSL       0                     ///< Master/Slave.
# define MASK_I2C_SR2_MSL       (HWRD)REG_BITMASK(I2C_SR2_MSL)

# define INDX_I2C_SR2_BUSY      1                     ///< Bus Busy.
# define MASK_I2C_SR2_BUSY      (HWRD)REG_BITMASK(I2C_SR2_BUSY)

# define INDX_I2C_SR2_TRA       2                     ///< Transmitter/Receiver.
# define MASK_I2C_SR2_TRA       (HWRD)REG_BITMASK(I2C_SR2_TRA)

# define INDX_I2C_SR2_GENCALL   4                     ///< General Call Adress (slave).
# define MASK_I2C_SR2_GENCALL   (HWRD)REG_BITMASK(I2C_SR2_GENCALL)

# define INDX_I2C_SR2_SMBDEFAULT 5                     ///< SMBus device default adress (slave).
# define MASK_I2C_SR2_SMBDEFAULT (HWRD)REG_BITMASK(I2C_SR2_SMBDEFAULT)

# define INDX_I2C_SR2_SMBHOST   6                     ///< SMBus Host Header (slave).
# define MASK_I2C_SR2_SMBHOST   (HWRD)REG_BITMASK(I2C_SR2_SMBHOST)

# define INDX_I2C_SR2_DUALF     7                     ///< Dual Flag.
# define MASK_I2C_SR2_DUALF     (HWRD)REG_BITMASK(I2C_SR2_DUALF)

# define INDX_I2C_SR2_PEC       8                     ///< Packet Error Checking Register.
# define MASK_I2C_SR2_PEC       (HWRD)(0xFF << INDX_I2C_SR2_PEC)

/// \endcond

#endif
