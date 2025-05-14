#ifndef CgaChar_h
#define CgaChar_h

#include "CgaAttr.h"

/*
 * CgaChar:
 * 
 *	Diese Klasse stellt den Prototyp eines
 *	Zeichens des Bildschirms dar.
 *	Dieses besteht aus darstellbarem Zeichen
 *	und Darstellungsattributen.
 */


class CgaChar {

public:

	CgaChar();

	// setzen des Zeichens
	void setChar(char c);
	
	// auslesen des Zeichens
	char getChar() const;
	
	// setzen der Darstellungsattribure
	void setAttr(const CgaAttr& attr);
	
	// auslesen der Darstellungsattribute
	CgaAttr getAttr() const;

private:
	unsigned short data; // 16 Bit, 8 für Char u. 8 für Attribute
};

#endif

