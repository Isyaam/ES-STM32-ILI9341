//
// RB_SPI.h
//

/// \file RB_SPI.h
/// Deklaration der SPI-Registerbänke.

#ifndef guard_RB_SPI_H
# define guard_RB_SPI_H

# include <RB.h>

/// Datentyp für SPI-Registerbank, s. RM0033 Reference Manual, Abschnitt 25.5.
typedef struct __regbank_SPI
{
  HWRD CR1;                     ///< Control register 1.
  HWRD reseved01;

  HWRD CR2;                     ///< Control register 2.
  HWRD reseved02;

  HWRD SR;                      ///< Status register.
  HWRD reseved03;

  /// Data register.
  union {
    HWRD DRhwrd; 
    BYTE DRbyte; 
  };
  HWRD reseved04;
  
  WORD CPCPR;                   ///< CRC polynomial register.
  WORD RXCRCR;                  ///< RX CRC register.
  WORD TXCRCR;                  ///< TX CRC register.
  
  WORD I2SCFGR;                 ///< I2S configuration register  
  WORD I2SPR;                   ///< I2S prescaler register.
} RegbankTypeSPI;

extern RegbankTypeSPI volatile rbSPI1;                ///< SPI1-Registerbank.
extern RegbankTypeSPI volatile rbSPI2;                ///< SPI2-Registerbank.
extern RegbankTypeSPI volatile rbSPI3;                ///< SPI3-Registerbank.
extern RegbankTypeSPI volatile rbSPI4;
extern RegbankTypeSPI volatile rbSPI5;
extern RegbankTypeSPI volatile rbSPI6;

/// \cond RB_DEFS

// CR1

# define INDX_SPI_CR1_DFF       11
# define MASK_SPI_CR1_DFF       (HWRD)REG_BITMASK(SPI_CR1_DFF)

# define INDX_SPI_CR1_SSM       9
# define MASK_SPI_CR1_SSM       (HWRD)REG_BITMASK(SPI_CR1_SSM)

# define INDX_SPI_CR1_SSI       8
# define MASK_SPI_CR1_SSI       (HWRD)REG_BITMASK(SPI_CR1_SSI)

# define INDX_SPI_CR1_LSBFIRST  7
# define MASK_SPI_CR1_LSBFIRST  (HWRD)REG_BITMASK(SPI_CR1_LSBFIRST)

# define INDX_SPI_CR1_SPE       6
# define MASK_SPI_CR1_SPE       (HWRD)REG_BITMASK(SPI_CR1_SPE)

# define INDX_SPI_CR1_BR        3
# define MASK_SPI_CR1_BR        (HWRD)(0x7U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_DIV002 (HWRD)(0x0U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_DIV004 (HWRD)(0x1U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_DIV008 (HWRD)(0x2U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_DIV016 (HWRD)(0x3U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_DIV032 (HWRD)(0x4U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_DIV064 (HWRD)(0x5U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_DIV128 (HWRD)(0x6U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_DIV256 (HWRD)(0x7U << INDX_SPI_CR1_BR)

# define INDX_SPI_CR1_MSTR      2
# define MASK_SPI_CR1_MSTR      (HWRD)REG_BITMASK(SPI_CR1_MSTR)

# define INDX_SPI_CR1_CPOL      1
# define MASK_SPI_CR1_CPOL      (HWRD)REG_BITMASK(SPI_CR1_CPOL)

# define INDX_SPI_CR1_CPHA      0
# define MASK_SPI_CR1_CPHA      (HWRD)REG_BITMASK(SPI_CR1_CPHA)

// CR2

# define INDX_SPI_CR2_RXDMAEN   0

# define INDX_SPI_CR2_TXDMAEN   1
# define MASK_SPI_CR2_TXDMAEN   (HWRD)REG_BITMASK(SPI_CR2_TXDMAEN)

# define INDX_SPI_CR2_SSOE      2
# define MASK_SPI_CR2_SSOE      (HWRD)REG_BITMASK(SPI_CR2_SSOE)

# define INDX_SPI_CR2_RXNEIE    6
# define MASK_SPI_CR2_RXNEIE    (HWRD)REG_BITMASK(SPI_CR2_RXNEIE)

# define INDX_SPI_CR2_TXEIE     7
# define MASK_SPI_CR2_TXEIE     (HWRD)REG_BITMASK(SPI_CR2_TXEIE)

// SR

# define INDX_SPI_SR_BSY        7
# define MASK_SPI_SR_BSY        (HWRD)REG_BITMASK(SPI_SR_BSY) 

# define INDX_SPI_SR_OVR        6
# define MASK_SPI_SR_OVR        (HWRD)REG_BITMASK(SPI_SR_OVR)

# define INDX_SPI_SR_UDR        3
# define MASK_SPI_SR_UDR        (HWRD)REG_BITMASK(SPI_SR_UDR)

# define INDX_SPI_SR_TXE        1
# define MASK_SPI_SR_TXE        (HWRD)REG_BITMASK(SPI_SR_TXE)

# define INDX_SPI_SR_RXNE       0
# define MASK_SPI_SR_RXNE       (HWRD)REG_BITMASK(SPI_SR_RXNE)

/// \endcond 

#endif

