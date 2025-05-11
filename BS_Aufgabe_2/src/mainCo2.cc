#include <iostream>
#include <string>

// Eine sehr einfache Coroutine-Simulation
// Diese Klasse ist nur eine Platzhalter-Version und ersetzt echte Coroutine-Funktionalität.

class Coroutine {
public:
    Coroutine() = default;
    Coroutine(void* /*stack*/) {}  // Platzhalter, Stack wird ignoriert

    virtual void body() = 0;
    virtual void resume(Coroutine* next) {
        if (next) next->body();
    }
    virtual void exit() {
        std::cout << "Panic!!!!\n";
    }
};

// Hello-Klasse, nutzt jetzt std::cout anstelle von PrintStream
class Hello : public Coroutine {
public:
    Hello(const char* name)
        : name(name), next(nullptr) {}

    Hello(const char* name, void* /*sp*/)
        : name(name), next(nullptr) {}

    void link(Coroutine& next) {
        this->next = &next;
    }

    void body() override {
        for (int i = 0; i < 10; ++i) {  // reduziert für Übersichtlichkeit
            std::cout << name << " " << i << std::endl;
            resume(next);
        }
    }

    const char* name;
    Coroutine* next;
};

// Stacks werden ignoriert, dienen nur der Kompatibilität
unsigned stack0[1024];
unsigned stack1[1024];

int main() {
    Hello anton("Anton");
    Hello berta("Berta", &stack0[1024]);
    Hello caesar("Caesar", &stack1[1024]);

    anton.link(berta);
    berta.link(caesar);
    caesar.link(anton);

    anton.body();

    return 0;
}
