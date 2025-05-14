#include "io/PrintStream.h"
#include "io/OutputChannel.h"
#include "lib/tools.h"

// Erwartet Zeiger auf ein OutputChannelobjekt, speichert referenz im channel
PrintStream::PrintStream(OutputChannel* chan)
    : channel(*chan) {}

//alternativer Konstruktor für direkte refrenz, anstelle von Zeiger
PrintStream::PrintStream(OutputChannel& chan)
    : channel(chan) {}

// übergibt ein zeichen an channel
void PrintStream::print(char ch) {
    channel.write(ch);
}

// geht ein string durch und gibt diesen an den channel weiter
void PrintStream::print(const char* str) {
    while (*str ) {
        channel.write(*str++);
    }
}

// siehe Zeile 19 zusätzlich hier nuch der zeilen Umbruch
void PrintStream::println(const char* str) {
    print(str);
    print('\n');
}

// Zeilen Umbruch
void PrintStream::println() {
    print('\n');
}

//überprüft  ob eine zahl negativ ist, wenn ja wird vorzeichen geprintet 
//und der rest an Zeile 46 weiter gegeben
void PrintStream::print(int x, int base) {
    if (base <= 1) {
    	base = 2;
    }

    if (x < 0) {
        print('-');
        x = -x;
    }
    print(static_cast<unsigned int>(x), base);
}
// übergibt Zahlen an den Buffer bin, dezimal , Hex
void PrintStream::print(unsigned int x, int base) {
	if (base <= 1) {
    		base = 2;
    	}
    char buffer[32];
    int i = 0;

    if (x == 0) {
        channel.write('0');
        return;
    }
    //legt zahlen in den buffer
    while (x > 0) {
        unsigned int digit = x % base; 		//ermittelt den rest der div
        if (digit < 10) {			//dezimal oder Binär
            buffer[i++] = '0' + digit;
        } else {				//Hex
            buffer[i++] = 'A' + (digit - 10);
        }
        x /= base;
    }
    //buffer rückwärts ausgeben 
    while (i > 0) {
        channel.write(buffer[--i]);
    }
}

// Gibt eine Adresse aus von einem objekt und gibt diese als Hex Zahl aus
void PrintStream::print(void* p) {
    unsigned int address = reinterpret_cast<unsigned int>(p);
    print("0x");  // Vorne ein 0x anhängen für Hex zahlen

    char buffer[8];
    int i = 0;

    if (address == 0) {
        channel.write('0');
        return;
    }

    while (address > 0) {
        int digit = address & 0xF;
        if (digit < 10) {
            buffer[i++] = '0' + digit;
        } else {
            buffer[i++] = 'A' + (digit - 10);
        }
        address >>= 4;
    }

    while (i > 0) {
        channel.write(buffer[--i]);
    }
}
