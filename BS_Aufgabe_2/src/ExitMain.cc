#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/Coroutine.h"

class Hello : public Coroutine {
public:
	Hello(const char* name, PrintStream& out)
		: cout(out), name(name), next(nullptr)
	{}

	Hello(const char* name, PrintStream& out, void* sp)
		: Coroutine(sp), cout(out), name(name), next(nullptr)
	{}

	void link(Coroutine& next) {
		this->next = &next;
	}

	void body() override {
		cout.print(name);
		cout.println(" says hello");

		if (next != nullptr)
			resume(next);
	}

	void exit() override {
		cout.print(name);
		cout.println(" reached exit.");
		while (true);
		
		
	}

private:
	PrintStream& cout;
	const char* name;
	Coroutine* next;
};

// Globale Objekte für die Ausgabe
CgaChannel cga;
PrintStream out(cga);

// Stacks für die Coroutinen
unsigned stack0[1024];

extern "C" int main() {
	Hello anton("Anton", out);                   // läuft auf main-Stack
	Hello berta("Berta", out, &stack0[1024]);    // eigener Stack

	anton.link(berta); // Anton übergibt an Berta

	anton.body(); // Starte Anton über Coroutine-Mechanik (→ startup → body → resume)

	return 0;
}
