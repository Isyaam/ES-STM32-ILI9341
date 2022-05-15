#include <Dma2d.h>

Dma2d::Dma2d(){}
		
void Dma2d::drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color, uint32_t memory, uint32_t displayWidth){
	rbDMA_2D.CR |= MASK_DMA2D_CR_MODE_REG2MEM;
	rbDMA_2D.OCOLR = color;
	
	Dma2d::SetMemory(memory + ((x + y * displayWidth)*4),displayWidth - width, width, height);
	
	rbDMA_2D.CR |= MASK_DMA2D_CR_START;
	
	Dma2d::waitToInit();
}

		
void Dma2d::SetMemory(uint32_t memoryAddr, uint32_t offset, uint32_t width, uint16_t height){
	rbDMA_2D.OMAR = memoryAddr;
	rbDMA_2D.OOR = offset;
	rbDMA_2D.NLR = ((width) << 16) | (height);
}

void Dma2d::drawCircle( uint32_t radius, uint32_t color, uint32_t memory, uint32_t layerWidth)
{	
	for(uint32_t i = 0; i < (radius * 2); i++)
		for(uint32_t j = 0; j< (radius * 2); j++)
		{
			if(((i - radius) * (i - radius) + (j - radius) * (j - radius)) <= radius * radius)
			{
				drawRectangle(j, i, 1, 1, color, memory, layerWidth);
			}
		}
}

void Dma2d::waitToInit(){
	DMA2D_WAIT;
	
	rbRCC.AHB1RSTR |= MASK_RCC_AHB1_DMA1;
	rbRCC.AHB1RSTR &= ~MASK_RCC_AHB1_DMA1;
	
	rbDMA_2D.CR |= (WORD)INDX_DMA2D_CR_START;
	
	DMA2D_WAIT;
}
