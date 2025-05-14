#ifndef CgaAttr_h
#define CgaAttr_h

/*
 * CgaAttr: 	Softwareprototyp fuer CGA Darstellungsattribute
 *		Hier braucht man Bitoperationen!
 *
 *		Da *alle* Operationen sehr einfach und kurz sind,
 *		duerft Ihr sie direkt in der Klasse
 *		als inline Methoden deklarieren.
 */

class CgaAttr {
private:
	enum AttrMaskAndShifts {
		// ersten 4 Bits (00001111) für Vordergrund
        FG_MASK = 0x0F,
        // Bit 4-6 (01110000) Dez.: 112
        BG_MASK = 0x70,
        // Bit 7 für Blink (10000000) Dez.: 128
        BLINK_MASK = 0x80,
		// muss nicht verschoben werden, da schon in Bit 0-3
		FG_SHIFT = 0,
		/**  muss um 4 Bit verschoben werden auf Position 0-2, damit FG Bits 
		 *	 nicht mit betrachtet werden
		 */
		BG_SHIFT = 4,
		// muss um 7 verschoben werden auf Position 0
		BLINK_SHIFT = 7
	};

public:
	/** 	Diese Aufz�hlung enth�lt die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color {
        BLACK        = 0x0,
        BLUE         = 0x1,
        GREEN        = 0x2,
        CYAN         = 0x3,
        RED          = 0x4,
        MAGENTA      = 0x5,
        BROWN        = 0x6,
        LIGHT_GRAY   = 0x7,
        GRAY	     = 0x8,
        LIGHT_BLUE   = 0x9,
        LIGHT_GREEN  = 0xA,
        LIGHT_CYAN   = 0xB,
        LIGHT_RED    = 0xC,
        LIGHT_MAGENTA= 0xD,
        YELLOW       = 0xE,
        WHITE        = 0xF
    };


	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten f�r
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, 
	  * Blinken deaktiviert)
	  * verwendet.
	  */
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false) 
	{
		/*Bitbelegung: 0-3 = fg, 4-6 = bg, 7 = blink-flag
		* or um die Bits(strings) aneinander zu hängen
		*/
		attribute = (fg & FG_MASK) | ((bg << BG_SHIFT) & BG_MASK);
		if (blink)
    			attribute |= BLINK_MASK;
	}

	// setzen der Schriftfarbe
	void setForeground(Color col) // Vordergrund hat 4 Bits = 16 Farben möglich
	{
		/**
		 * nutzt zuerst bitwise AND, um die ersten 4 Bit auf 0 zu setzen 
		 * (FG_MASK muss zuerst negiert werden mit bitwise NOT)
		 * diese wird dann mit dem bitwise OR zusammengesetzt, ohne die anderen 
		 * Attribute zu verändern
		 */
		attribute = (attribute & ~FG_MASK) | col; 
	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col) // Hintergrund hat 3 Bits = 7 Farben möglich
	{
		/**
		 * nutzt zuerst bitwise AND, um die ersten 4 Bit auf 0 zu setzen 
		 * (FG_MASK muss zuerst negiert werden mit bitwise NOT)
		 * stellt sicher, dass col nur 3 bit groß ist, daher 
		 * bitwise AND mit BG_MASK,
		 * diese wird dann mit dem bitwise OR zusammengesetzt, 
		 * ohne die anderen Attribute zu verändern
		 */
		attribute = (attribute & ~BG_MASK) | ((col << BG_SHIFT) & BG_MASK); 
	}

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
		if (blink == true) {
		attribute = (attribute & ~BLINK_MASK) | 10000000; 
		} else {
		attribute = (attribute & ~BLINK_MASK); 
		}
	}

	// setzen aller Attributwerte (Hintergrund, Vordergrund, Blink)
	void setAttr(CgaAttr attr)
	{
		// kopiert die Attribute eines anderen Objekts auf das aktuelle Objekt
		attribute = attr.attribute;
	}

	// ermitteln der Schriftfarbe
	Color getForeground()
	{
		/** nutzt C++ cast, um die Binärzahl in enum Typ Color umzuwandeln 
		*
		*/
		return static_cast<Color>(attribute & FG_MASK);
	}
	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
		/**  verschiebt die extrahierten BG bits, um sie in Position 
		 * 	 0-2 zu bringen (>> für bitwise Verschiebung)
		 * */
		return static_cast<Color>((attribute & BG_MASK) >> BG_SHIFT);
	}

	// ermitteln ob Blink-Flag gesetzt istecht? da hab ich nur schwarzen text
	bool getBlinkState()
	{
		return ((attribute & BLINK_MASK) >> BLINK_SHIFT);
	}

private:

// uint8_t würde auch gehen, sagt dass es 8 bit sein müssen, brauch library
unsigned short int attribute; 
};

#endif
