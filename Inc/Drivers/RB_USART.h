//
// RB_USART.h
//

/// \file RB_USART.h
/// Deklaration der U(S)ART-Registerbänke.

#ifndef guard_RB_USART_H
# define guard_RB_USART_H

# include <RB.h>

/// Datentyp für U(S)ART-Registerbank, s. RM0033 Reference Manual, Kapitel 24.
typedef struct __regbank_USART
{
  HWRD SR;                                            ///< Status register.
  HWRD reserved00;
  
  /// Data register.
  union {
    HWRD DRhwrd; 
    BYTE DRbyte; 
  };
  HWRD reserved01;
  
  HWRD BRR;                                           ///< Baud rate register
  HWRD reserved02;
 
  HWRD CR1;                                           ///< Control register 1.
  HWRD reserved03;

  HWRD CR2;                                           ///< Control register 2.
  HWRD reserved04;

  HWRD CR3;                                           ///< Control register 3.
  HWRD reserved05;

  HWRD GTPR;                                          ///< Guard time and prescaler register.
  HWRD reserved06;
} RegbankTypeUSART;

extern RegbankTypeUSART volatile rbUSART1;            ///< USART1-Registerbank.
extern RegbankTypeUSART volatile rbUSART2;            ///< USART2-Registerbank.
extern RegbankTypeUSART volatile rbUSART3;            ///< USART3-Registerbank.
extern RegbankTypeUSART volatile rbUART4;             ///< UART4-Registerbank.
extern RegbankTypeUSART volatile rbUART5;             ///< UART5-Registerbank.
extern RegbankTypeUSART volatile rbUSART6;            ///< USART6-Registerbank.

/// \cond RB_DEFS

// SR

# define INDX_USART_SR_PE       0                     ///< parity error.
# define MASK_USART_SR_PE       (HWRD)REG_BITMASK(USART_SR_PE)

# define INDX_USART_SR_FE       1                     ///< framing error.
# define MASK_USART_SR_FE       (HWRD)REG_BITMASK(USART_SR_FE)

# define INDX_USART_SR_NE       2                     ///< noise error.
# define MASK_USART_SR_NE       (HWRD)REG_BITMASK(USART_SR_NE)

# define INDX_USART_SR_ORE      3                     ///< overrun error.
# define MASK_USART_SR_ORE      (HWRD)REG_BITMASK(USART_SR_ORE)

# define INDX_USART_SR_IDLE     4                     
# define MASK_USART_SR_IDLE     (HWRD)REG_BITMASK(USART_SR_IDLE)

# define INDX_USART_SR_RXNE     5                     ///< read data register not empty.
# define MASK_USART_SR_RXNE     (HWRD)REG_BITMASK(USART_SR_RXNE)

# define INDX_USART_SR_TC       6                     ///< transmission complete.
# define MASK_USART_SR_TC       (HWRD)REG_BITMASK(USART_SR_TC)
 
# define INDX_USART_SR_TXE      7                     ///< write data register empty.
# define MASK_USART_SR_TXE      (HWRD)REG_BITMASK(USART_SR_TXE)

// CR1

# define INDX_USART_CR1_UE      13                    ///< USART enable.
# define MASK_USART_CR1_UE      (HWRD)REG_BITMASK(USART_CR1_UE)

# define INDX_USART_CR1_M       12                    ///< word length.
# define MASK_USART_CR1_M       (HWRD)REG_BITMASK(USART_CR1_M)

# define INDX_USART_CR1_PCE     10

# define INDX_USART_CR1_PS      9

# define INDX_USART_CR1_PEIE    8
# define MASK_USART_CR1_PEIE    (HWRD)REG_BITMASK(USART_CR1_PEIE)

# define INDX_USART_CR1_TXEIE   7                     ///< write data register empty interrupt enable.
# define MASK_USART_CR1_TXEIE   (HWRD)REG_BITMASK(USART_CR1_TXEIE)

# define INDX_USART_CR1_TCIE    6                     ///< transmission complete interrupt enable.

# define INDX_USART_CR1_RXNEIE  5                     ///< read data register not empty interrupt enable.
# define MASK_USART_CR1_RXNEIE  (HWRD)REG_BITMASK(USART_CR1_RXNEIE)

# define INDX_USART_CR1_IDLEIE  4
# define MASK_USART_CR1_IDLEIE  (HWRD)REG_BITMASK(USART_CR1_IDLEIE)

# define INDX_USART_CR1_TE      3                     ///< transmitter enable.
# define MASK_USART_CR1_TE      (HWRD)REG_BITMASK(USART_CR1_TE)

# define INDX_USART_CR1_RE      2                     ///< receiver enable.
# define MASK_USART_CR1_RE      (HWRD)REG_BITMASK(USART_CR1_RE)

// CR3

# define INDX_USART_CR3_CTSE    9
# define MASK_USART_CR3_CTSE    (HWRD)REG_BITMASK(USART_CR3_CTSE)

# define INDX_USART_CR3_RTSE    8
# define MASK_USART_CR3_RTSE    (HWRD)REG_BITMASK(USART_CR3_RTSE)

# define INDX_USART_CR3_DMAT    7                     ///< enable DMA for TxD.
# define MASK_USART_CR3_DMAT    (HWRD)REG_BITMASK(USART_CR3_DMAT)

# define INDX_USART_CR3_DMAR    6                     ///< enable DMA for RxD.
# define MASK_USART_CR3_DMAR    (HWRD)REG_BITMASK(USART_CR3_DMAR)

# define INDX_USART_CR3_EIE     0
# define MASL_USART_CR3_EIE     (HWRD)REG_BITMASK(USART_CR3_EIE)

/// \endcond 

#endif

