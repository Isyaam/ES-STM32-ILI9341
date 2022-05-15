#ifndef DRVLTDC_H
#define DRVLTDC_H

#include <RB_RCC.h>
#include <RB_LTDC.h>
#include <RB_GPIO.h>
#include <Dma2d.h>



class ILtdc final {
	public:
		ILtdc();
		ILtdc(ILtdc const &ltdc) = delete;
		ILtdc(ILtdc &ltdc) = delete;
	
		/**
		* Initalsierien des LTDC, setzten der Layer,
		*	erstellen der Rechtecke und Kreis über DMA2D
		*	und bewegen des Kreis
		*/
		void initLTDC() const;
	
		///Setzten der Pins für den LTDC
		void setPins() const;	
	
		static constexpr HWRD const width = 240U;
		static constexpr HWRD const height = 320U; 
		static constexpr BYTE const hSync = 10;               ///< Typischer HSYNC-Wert laut ILI3941-Manual (in Vielfachen von Pixeltakt DOTCLK)
		static constexpr BYTE const vSync =  2;               ///< Typischer VSYNC-Wert laut ILI3941-Manual (in Vielfachen von Pixeltakt DOTCLK)
		static constexpr BYTE const horBackPorch = 20;
		static constexpr BYTE const verBackPorch =  2;
		static constexpr BYTE const horFrntPorch = 10;
		static constexpr BYTE const verFrntPorch =  4;
		static constexpr unsigned const dotcklFrequency = 6000000U;
		static constexpr unsigned const osccklFrequency = 615000U; ///< Internal oscilator clock frequency.
		static constexpr BYTE const pcdivFactor = (dotcklFrequency + (osccklFrequency / 2U)) / osccklFrequency;
		static constexpr BYTE const pcdivValue  = (pcdivFactor / 2U) - 1U;
		static constexpr unsigned const horTotal = hSync + horBackPorch + width  + horFrntPorch;
		static constexpr unsigned const verTotal = vSync + verBackPorch + height + verFrntPorch;
		static constexpr unsigned const frameRate = dotcklFrequency / (horTotal * verTotal);
};

#endif
