#include "../../include/device/CgaChar.h"

/**
 * Initialisieren eines chars
 * mit den Standardwerten weiß auf schwarz, no blink
 */
CgaChar::CgaChar()
: data((static_cast<unsigned short>(' ') & 0x00FF) | 
(static_cast<unsigned short>(0x04) << 8))
{
}


/**
 * Löscht die unteren 8 Bit und setzt das Zeichen,
 * der cast sorgt dafür, dass es kein Vorzeichen hat (damit auch genau 1 Byte)
 * Die oberen 8 Bit (für die Attribute) werden gespeichert 
 */
void CgaChar::setChar(char c) {
    data = (data & 0xFF00) | c; //(static_cast<unsigned char>(c)); 
}

/**
 * Gibt die unteren 8 Bit zurück und löscht die oberen 8 Bit
 */
char CgaChar::getChar() const {
    return static_cast<char>(data & 0x00FF);
}

/**
 * & ist eine Referenz auf bereits existierendes Objekt
 * unsigned short ist 16 Bit
 * Verschoben um 8 Bit, damit der Attributwert in oberen 8 Bit von Data landet
 */
void CgaChar::setAttr(const CgaAttr& attr) {

    /**
     * verwende const Methode (getForeground etc.) in einer nicht-const
     * Methode
    */  
    CgaAttr nonConstAttr = attr;

    unsigned short fg = static_cast<unsigned short>(nonConstAttr.getForeground());
    unsigned short bg = static_cast<unsigned short>(nonConstAttr.getBackground());
    unsigned short blink = static_cast<unsigned short>(nonConstAttr.getBlinkState());

    // Attribut-Byte zusammensetzen (Bits 8–15)
    unsigned short attrByte = (blink << 7) | (bg << 4) | fg;

    // In den oberen 8 Bits speichern, Zeichen (untere 8 Bits) behalten
    data = (attrByte << 8) | (data & 0x00FF);

}

CgaAttr CgaChar::getAttr() const
{
    CgaAttr::Color fg = static_cast<CgaAttr::Color>((data >> 8) & 0x0F);
    CgaAttr::Color bg = static_cast<CgaAttr::Color>((data >> 12) & 0x07);
    bool blink = ((data >> 15) & 0x01) != 0;

    return CgaAttr(fg, bg, blink);
}

