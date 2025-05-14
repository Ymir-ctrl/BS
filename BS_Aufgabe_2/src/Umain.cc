#include "../include/device/CgaChannel.h"
#include "../include/io/PrintStream.h"

CgaChannel cga;		// unser CGA-Ausgabekanal
PrintStream out(cga);	// unseren PrintStream mit Ausgabekanal verknuepfen

CgaAttr redAttr(CgaAttr::Color::RED, CgaAttr::Color::LIGHT_GRAY, true);
CgaAttr cyanAttr(CgaAttr::Color::CYAN, CgaAttr::Color::MAGENTA, true);
CgaAttr greenAttr(CgaAttr::Color::WHITE, CgaAttr::Color::GREEN, false);
CgaAttr blackAttr(CgaAttr::Color::WHITE, CgaAttr::Color::BLACK, false);

extern "C" int main()
{
	//Vordefinierte Tests
	out.println("Hello World");

	for(int i = 0; i < 1000; i++) {
		out.print("Dezimal ");
		out.print(i);
		out.print(" Binaer ");
		out.print(i, 2);
		out.print(" Hexadezimal ");
		out.print(i, 16);
		out.println();
	}

	out.println("done");


	// Eigene Tests
	// -- test1 CgaAttr --
	out.println("TEST CgaAttr");
	
	cga.setAttr(greenAttr);
	out.print(" Foreground: ");
	out.print((int)greenAttr.getForeground());
	out.print(" Background: ");
	out.print((int)greenAttr.getBackground());
	out.print(" Blink: ");
	out.print((int)greenAttr.getBlinkState());
	cga.setAttr(blackAttr);
	out.println();

	cga.setAttr(cyanAttr);
	out.print(" Foreground: ");
	out.print((int)cyanAttr.getForeground());
	out.print(" Background: ");
	out.print((int)cyanAttr.getBackground());
	out.print(" Blink: ");
	out.print((int)cyanAttr.getBlinkState());
	cga.setAttr(blackAttr);
	out.println();
	//cga.blueScreen("ERROR!");
	
	cga.setAttr(blackAttr);
	out.println("changed color= WHITE,BLACK and Blink=false");
	out.print("Test fuer negative Zahlen : ");
	out.print(-1);
	out.println();
	
	int x=100;
	out.print("Speicheradresse von x, mit dem Wert ");
	out.print(x,10);
	out.print(" hat folgende Adresse: ");
	out.print(&x);
	out.println();

	// -- tests 2 CgaChar --
	out.println("Test CgaChar");
	CgaChar ch;
	ch.setAttr(redAttr);
	ch.setChar('A');
	

	out.print("Char mit getChar: ");
	out.print(ch.getChar());
	out.println();
	out.print("Char mit show: ");
	cga.show(ch.getChar(), ch.getAttr());
	out.println();

	CgaAttr attr = ch.getAttr(); 
	out.print("Foreground: ");
	out.print((int)attr.getForeground());
	out.print(" Background: ");
	out.print((int)attr.getBackground());
	out.print(" Blink: ");
	out.print((int)attr.getBlinkState());
	out.println();
	while(1){}

	return 0;
}
