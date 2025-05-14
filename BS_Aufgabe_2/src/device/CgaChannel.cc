#include "../../include/device/CgaChannel.h"
#include "../../include/device/CgaAttr.h"

// Ausgabe mit Standardattributen
CgaChannel::CgaChannel()
    : CgaScreen() {
        setCursor(0,0);
    }

// Ausgabe mit spezifischen Attributen
CgaChannel::CgaChannel(const CgaAttr& attr)
    : CgaScreen(attr) {
    setCursor(0, 0);
}


//Eingabe: Pointer zum Array mit mind. size chars, Anzahl der Chars
int CgaChannel::write(const char* data, int size) {
    int written = 0;

    for (int i = 0; i < size; i++) {
        char ch = data[i];

        switch (ch) {
            case '\n': {
                int col, row;
                getCursor(col, row);
                setCursor(0, row + 1);
                break;
            }

            case '\r': {
                int col, row;
                getCursor(col, row);
                setCursor(0, row);
                break;
            }

            default:
                show(ch);  // Cursor wird von show() verschoben
                written++;
                break;
        }
    }

    return written;
}


// z.B. bei Nullpointer oder kein Nullterminator
void CgaChannel::blueScreen(const char* error) {
    
    //Weiße Schrift auf blauem Hintergrund
    CgaAttr errorAttr;
    errorAttr.setForeground(CgaAttr::Color::WHITE); 
    errorAttr.setBackground(CgaAttr::Color::BLUE);
    setAttr(errorAttr);
    clear();
    setCursor(0, 0);
    //Gibt die Zeichenkette des errors aus
    while (*error) {
        show(*error++);
    }
}
