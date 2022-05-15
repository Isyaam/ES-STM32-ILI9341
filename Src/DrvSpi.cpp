#include <DrvSpi.h>

ISpi::ISpi()
{
}


uint8_t ISpi::SPI_Send(uint8_t data) const {
	if(!rbSPI5.CR1 & MASK_SPI_CR1_SPE) return 1;
	while(SPI_BSY);
	rbSPI5.DRbyte = data;
	while(SPI_BSY);
	return rbSPI5.DRbyte;
}


void ISpi::initSPI() const {
	
	APBClockEnable(PERIPHERY_APB_SPI5);
	AHBClockEnable(PERIPHERY_AHB_GPIOF);
	
	static constexpr BYTE const pins[] = {7,8,9};
	EnableAF(rbGPIOF, MASK_GPIO_AFR_AF05, MASK_GPIO_OSPEEDR_HIGH, MASK_GPIO_OTYPER_PP, pins, 3U);
	
	rbSPI5.CR1 &= ~MASK_SPI_CR1_SPE;
	rbSPI5.CR1 |= MASK_SPI_CR1_SSM;
	rbSPI5.CR1 |= MASK_SPI_CR1_SSI;
	rbSPI5.CR1 |= MASK_SPI_CR1_MSTR;
	rbSPI5.CR1 |= MASK_SPI_CR1_SPE;
}
