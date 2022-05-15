#include <DrvLtdc.h>
#define RGB(r, g, b)                (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))
#define RED                         RGB(0xFF, 0x00, 0x00)
#define GREEN                       RGB(0x00, 0x8F, 0x00)
#define BLUE 0x8800FFFF
#define LAYER1 0xD0000000U
#define LAYER2 0xD0307200U
#define LAYER1_WIDTH 121
#define LAYER2_WIDTH 101

ILtdc::ILtdc()
{
}

void ILtdc::initLTDC() const {
	
	// VSync HSync setzen
	rbLTDC.SSCR = ((hSync - 1) << INDX_LTDC_SSCR_HSW) | ((vSync - 1) << INDX_LTDC_SSCR_VSH);	
	
	// BackPorch
	rbLTDC.BPCR = ((hSync + horBackPorch - 1) << INDX_LTDC_BPCR_AHBP) | ((vSync + verBackPorch - 1) << INDX_LTDC_BPCR_AVBP);
	
	// Active Width / Height
	rbLTDC.AWCR = ((hSync + horBackPorch + width - 1) << INDX_LTDC_AWCR_AAW) | ((vSync + verBackPorch + height - 1) << INDX_LTDC_AWCR_AAH);

	// Total Width / Height
	rbLTDC.TWCR = ((verTotal - 1) << INDX_LTDC_TWCR_TOTALH) | ((horTotal - 1) << INDX_LTDC_TWCR_TOTALW);
	
	//Layer 0
	rbLTDC.Layer0.CACR = 255;
	// Start und Stop pos für Weite Layer0
	rbLTDC.Layer0.WHPCR = hSync + horBackPorch << INDX_LTDC_Lx_WHPCR_WHSTPOS | hSync + horBackPorch + width << INDX_LTDC_Lx_WHPCR_WHSPPOS;
	// Start und Stop pos für Höhe Layer0
	rbLTDC.Layer0.WVPCR = vSync + verBackPorch << INDX_LTDC_Lx_WVPCR_WVSTPOS | vSync + verBackPorch + height << INDX_LTDC_Lx_WVPCR_WVSPPOS;	
	
	rbLTDC.Layer0.PFCR |= MASK_LTDC_Lx_PFCR_RGB565;
	rbLTDC.Layer0.CFBAR = LAYER1;
	rbLTDC.Layer0.CFBLR |= ((width * 4) << 16 ) | (width * 4);
	rbLTDC.Layer0.CFBLNR |= height;
	
	rbLTDC.Layer1.CACR = 255;
	// Start und Stop pos für Weite Layer1
	rbLTDC.Layer1.WHPCR = hSync + horBackPorch + 70 << INDX_LTDC_Lx_WHPCR_WHSTPOS | hSync + horBackPorch + 170 << INDX_LTDC_Lx_WHPCR_WHSPPOS;
	// Start und Stop pos für Höhe Layer1
	rbLTDC.Layer1.WVPCR = vSync + verBackPorch + 110 << INDX_LTDC_Lx_WVPCR_WVSTPOS | vSync + verBackPorch + 210 << INDX_LTDC_Lx_WVPCR_WVSPPOS;
	
	rbLTDC.Layer1.PFCR |= MASK_LTDC_Lx_PFCR_ARGB8888;
	rbLTDC.Layer1.CFBAR = LAYER2;
	rbLTDC.Layer1.CFBLR |= ((102* 4) << 16 ) | (102 * 4);
	rbLTDC.Layer1.CFBLNR |= 102;
	
	int* addr = (int*)LAYER2;
	for(int i = 0; i < (101 * 101 * 4);i++){
		*addr = 0x00000000;
		addr = addr + 1;
	}
	
	//DMA2D Clock enable
	AHBClockEnable(PERIPHERY_AHB_DMA_2D);
	AHBClockEnable(PERIPHERY_AHB_DMA1);
	AHBClockEnable(PERIPHERY_AHB_DMA2);
	
	Dma2d dma;
	
	int x=0;
	int y=0;
	int z=1;
	for(int i = 0; i < 8; i++){
		x=0;
		for(int j = 0; j < 6; j++){				
			if(z % 2 == 0){
				dma.drawRectangle(x,y,20,40,RED,LAYER1,LAYER1_WIDTH);
			}else{
				dma.drawRectangle(x,y,20,40,GREEN,LAYER1,LAYER1_WIDTH);
			}
			z++;
			x+=20;
		}
		y+=40;
		z++;
	}
	
		//Kreis Zeichnen mit einem Radius von 50
	dma.drawCircle(50,BLUE, LAYER2,LAYER2_WIDTH);
	
		//Reload Layer
	rbLTDC.Layer0.CR |= MASK_LTDC_Lx_CR_LEN;
	rbLTDC.Layer1.CR |= MASK_LTDC_Lx_CR_LEN;
	rbLTDC.SRCR |= MASK_LTDC_SRCR_IMR;
	//enable LTDC
	rbLTDC.GCR |= MASK_LTDC_GCR_LTDCEN;
	
	x = 70;
	int x2 = 170;
	bool rechts = false;
	while(true){
		for(int delay = 1200000; delay > 0; delay--);
		rbLTDC.SRCR |= MASK_LTDC_SRCR_IMR;
		if(x2 < width && rechts){ 
		x++;
		x2++;
		rbLTDC.Layer1.WHPCR = hSync + horBackPorch + x << INDX_LTDC_Lx_WHPCR_WHSTPOS | hSync + horBackPorch +  x2 << INDX_LTDC_Lx_WHPCR_WHSPPOS;
		}else if(x > -1 && !rechts){
			x--;
			x2--;
			rbLTDC.Layer1.WHPCR = hSync + horBackPorch + x << INDX_LTDC_Lx_WHPCR_WHSTPOS | hSync + horBackPorch +  x2 << INDX_LTDC_Lx_WHPCR_WHSPPOS;
		}else  {
			rechts = !rechts;
		}
	}
}

void ILtdc::setPins() const
	{
		//GPIOA																			Blue5, VSYNC, Green2, Red4, Red5
		static constexpr BYTE const aPins[] = 			{	3, 			4,		6, 		11, 	12};
		//GPIOB																			Red3,Red6
		static constexpr BYTE const bPinsFirst[] = 	{	0, 	1};
		//GPIOB																		Blue6, Blue7, Green4, Green5
		static constexpr BYTE const bPinsSecond[] = {8, 	9, 			10, 		11};
		//GPIOC																		HSYNC,Green6,Red2
		static constexpr BYTE const cPins[] = 			{	6, 		7, 	10};
		//GPIOD																		Green7,Blue2
		static constexpr BYTE const dPins[] = 			{	3,	6};
		//GPIOF																			Enable
		static constexpr BYTE const fPins[] = 			{	10};
		//GPIOG																		Red7,	CLK, Blue3
		static constexpr BYTE const gPinsFirst[] = 	{	6,	7, 11};
		//GPIOG																			Green3,	Blue4
		static constexpr BYTE const gPinsSecond[] = { 10, 	12};
		
		APBClockEnable(PERIPHERY_APB_LTDC);
		AHBClockEnable(PERIPHERY_AHB_GPIOA);
		AHBClockEnable(PERIPHERY_AHB_GPIOB);
		AHBClockEnable(PERIPHERY_AHB_GPIOC);
		AHBClockEnable(PERIPHERY_AHB_GPIOD);
		AHBClockEnable(PERIPHERY_AHB_GPIOF);
		AHBClockEnable(PERIPHERY_AHB_GPIOG);
		
		EnableAF(rbGPIOA, MASK_GPIO_AFR_AF14, MASK_GPIO_OSPEEDR_HIGH, MASK_GPIO_OTYPER_PP, aPins);
		EnableAF(rbGPIOB, MASK_GPIO_AFR_AF09, MASK_GPIO_OSPEEDR_HIGH, MASK_GPIO_OTYPER_PP, bPinsFirst);
		EnableAF(rbGPIOB, MASK_GPIO_AFR_AF14, MASK_GPIO_OSPEEDR_HIGH, MASK_GPIO_OTYPER_PP, bPinsSecond);
		EnableAF(rbGPIOC, MASK_GPIO_AFR_AF14, MASK_GPIO_OSPEEDR_HIGH, MASK_GPIO_OTYPER_PP, cPins);
		EnableAF(rbGPIOD, MASK_GPIO_AFR_AF14, MASK_GPIO_OSPEEDR_HIGH, MASK_GPIO_OTYPER_PP, dPins);
		EnableAF(rbGPIOF, MASK_GPIO_AFR_AF14, MASK_GPIO_OSPEEDR_HIGH, MASK_GPIO_OTYPER_PP, fPins);
		EnableAF(rbGPIOG, MASK_GPIO_AFR_AF14, MASK_GPIO_OSPEEDR_HIGH, MASK_GPIO_OTYPER_PP, gPinsFirst);
		EnableAF(rbGPIOG, MASK_GPIO_AFR_AF14, MASK_GPIO_OSPEEDR_HIGH, MASK_GPIO_OTYPER_PP, gPinsSecond);
}
	

