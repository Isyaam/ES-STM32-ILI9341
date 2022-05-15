#ifndef DMA2D_H
#define DMA2D_H

#include <RB_DMA2D.h>
#include <RB_RCC.h>

class Dma2d{
	public:
		Dma2d();
		Dma2d(Dma2d const &) = delete;
		Dma2d(Dma2d &) = delete;
	
		/// Zeichnet das Rechteck
		/// \param[in] xp Koordinate in der Weite
		/// \param[in] yp Koordinate in der Höhe
		/// \param[in] width die Weite der Zeichnung
		/// \param[in] height die Höhe der Zeichnung
		/// \param[in] color Farbe der Zeichnung
		/// \param[in] memory Angabe der Speicheradresse
		/// \param[in] displayWidth Angabe der Layerbreite
		void drawRectangle(uint16_t xp, uint16_t yp, uint16_t width, uint16_t height, uint32_t color, uint32_t memory, uint32_t layerWidth);
	
		/// Zeichnet den Kreis
		/// \param[in] x Koordinate in der Weite
		/// \param[in] y Koordinate in der Höhe
		/// \param[in] radius Radius des Kreises
		/// \param[in] color Farbe der Zeichnung
		/// \param[in] memory Angabe der Speicheradresse
		/// \param[in] displayWidth Angabe der Layerbreite
		void drawCircle( uint32_t radius,uint32_t color, uint32_t memory, uint32_t layerWidth);	
		
		/// Setzt den Memory für den DMA
		/// \param[in] memoryAddr legt den Speicher für die Zeichnung fest
		/// \param[in] offset setzt den Output Offset Register
		/// \param[in] width die Weite der Zeichnung
		/// \param[in] height die Höhe der Zeichnung
		void SetMemory(uint32_t memoryAddr, uint32_t offset, uint32_t width, uint16_t height);
		
		/// Wartet so lange bis der Kanal wieder frei ist
		void waitToInit();
	private:
		
		static constexpr HWRD const width = 240U;
		static constexpr HWRD const height = 320U;
};

#endif
