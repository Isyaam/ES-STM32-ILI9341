
#ifndef DRVSPI_H
#define DRVSPI_H

#include "RB.h"
#include "RB_RCC.h"
#include "RB_SPI.h"
#include "RB_GPIO.h"
#define SPI_BSY (rbSPI5.SR & MASK_SPI_SR_BSY) || (rbSPI5.SR & (MASK_SPI_SR_TXE|MASK_SPI_SR_RXNE) == 0)
class ISpi final{
	public:
		ISpi();
		ISpi(ISpi const & spi) = delete;
		ISpi(ISpi &spi) = delete;
		
		/**Initlisiert den SPI5 
		* zuerst wird der Clock der SPI5 und des Port F aktiviert
		* danach die Pins {7,8,9} des SPI5 gesetzt 
		* und mit der Alternativ Funktion aktiviert.*/
		void initSPI() const;
	
		/**Sendet die SPI daten
		@param data senden der Daten */
		uint8_t SPI_Send(uint8_t data) const;
};

#endif
