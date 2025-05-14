#include "../../include/device/CgaScreen.h"


/**
 * Konstruktor mit Attributen, Indexport, Dataport, reinterpretiert den
 * Speicherbereich als Zeiger auf Reihe von CgaChar Objekten
 * dadurch kann Inhalt von VRAM direkt manipuliert werden
 * 
 * 18 interne Register, 2 I/O Register :
 * Indexport: bestimmt Register, welches verwendet werden soll
 * Dataport: erlaubt Zugriff (lesen und schreiben) auf das gewählte Register
 */
CgaScreen::CgaScreen()
    : attr(), index(INDEX_PORT), data(DATA_PORT), 
    screen(reinterpret_cast<CgaChar*>(V_RAM)) {
    clear(); 
}

// wie obiges, nur mit vordefinierten Attributen
CgaScreen::CgaScreen(CgaAttr attr)
    : attr(attr), index(INDEX_PORT), data(DATA_PORT), 
    screen(reinterpret_cast<CgaChar*>(V_RAM)) {
    clear();  
}

void CgaScreen::clear() {
    for (int i = 0; i < ROWS * COLUMNS; ++i) {
        screen[i].setAttr(attr);
        screen[i].setChar(' ');
    }
    setCursor(0, 0);
}

void CgaScreen::scroll() {
    // Alle Zeilen eine nach oben schieben
    for (int row = 1; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            screen[(row - 1) * COLUMNS + col] = screen[row * COLUMNS + col];
        }
    }

    // Letzte Zeile leeren
    for (int col = 0; col < COLUMNS; col++) {
        // berechnet Cursorpositionen, wobei letzte Zeile ausgelassen wird
        screen[(ROWS - 1) * COLUMNS + col].setChar(' ');
        screen[(ROWS - 1) * COLUMNS + col].setAttr(attr);
    }
}

void CgaScreen::setCursor(int column, int row) {
    // berechnet die Position des Cursors
    unsigned short position = row * COLUMNS + column;
    // sagt in welches Register geschrieben werden soll
    index.write(CURSOR_HIGH);
    // schreibt die obersten 8 Bit ins data Register
    data.write((position >> 8) & 0xFF);
    index.write(CURSOR_LOW);
    data.write(position & 0xFF);
}

/**
 * liest die high und low Register aus und
 * speichert deren Werte in 16 bit 
 */
void CgaScreen::getCursor(int& column, int& row) {
    index.write(CURSOR_HIGH);
    unsigned short high = data.read();
    index.write(CURSOR_LOW);
    unsigned short low = data.read();
    unsigned short position = (high << 8) | low;
    // berechnet die Zeile, wobei COLUMNS immer 80
    row = position / COLUMNS;
    // column ist der Rest wenn geteilt
    column = position % COLUMNS;
}

void CgaScreen::show(char ch, const CgaAttr& attr) {
    int col, row;
    getCursor(col, row);
    int pos = row * COLUMNS + col;
    screen[pos].setChar(ch);
    screen[pos].setAttr(attr);

    // Cursor eins nach rechts verschieben
    ++col;
    if (col >= COLUMNS) {
        col = 0;
        ++row;
        if (row >= ROWS) {
            scroll();
            row = ROWS - 1;
        }
    }
    setCursor(col, row);
}

void CgaScreen::setAttr(const CgaAttr& a) {
    attr = a;
}

void CgaScreen::getAttr(CgaAttr& a) {
    a = attr;
}

void CgaScreen::show(char ch) {
    show(ch, attr);
}
