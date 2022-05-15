#include "DrvLayer.h"

ILayer::ILayer(){}
	
void ILayer::initLayer() const{
	/*rbLTDC.Layer0.CACR = 255;
	rbLTDC.Layer0.PFCR = MASK_LTDC_Lx_PFCR_ARGB8888;
	rbLTDC.Layer0.WHPCR |= (hSync + horBackPorch) << INDX_LTDC_Lx_WHPCR_WHSTPOS;	// Start Position
	rbLTDC.Layer0.WHPCR |= (hSync + horBackPorch + width) << INDX_LTDC_Lx_WHPCR_WHSPPOS; 	// Stop Position
	rbLTDC.Layer0.WVPCR |= (vSync + verBackPorch ) << INDX_LTDC_Lx_WVPCR_WVSTPOS;	// Start Pos
	rbLTDC.Layer0.WVPCR |= (vSync + verBackPorch + height) << INDX_LTDC_Lx_WVPCR_WVSPPOS;	// Stop Pos
	rbLTDC.Layer0.CFBAR = 0xD0000000U;
	rbLTDC.Layer0.CFBLR |= ((bufWidth * 4) << 16U) | (bufWidth + 3);
	rbLTDC.Layer0.CFBLNR |= bufHeight;
	*/
}
