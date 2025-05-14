#ifndef Coroutine_h
#define Coroutine_h

/*
 * Coroutine:
 * Diese Klasse implementiert Coroutinen, welche die Basis
 * f�r alle Arten von Prozessen in Co-Stubs sind.
 *
 *	Anmerkung: wir verwenden ein objektorientiertes
 *	Coroutinen-Modell, daher ist diese Klasse abstrakt.
 *	Eine Coroutine muss sich von dieser Klasse ableiten
 *	und eine "body" Methode definieren.
 *	Diese Methode ist dann gewissermassen die "main" Funktion
 *	fuer die Coroutine.
 *
 */

/* Diese Deklaration verweist auf die von Euch zu
 * implementierende Assemblerprozedur "switchContext".
 */
extern "C"
{
	void switchContext(void *&from, void *&to);
}
/* switchContext hat die Aufgabe, die Kontrolle
 * vom Stack der Coroutine "from" auf den Stack der
 * Coroutine "to" zu wechseln und damit einen Kontrolltransfer
 * zu vollziehen.
 *
 * Hinweis: Am einfachsten ist es, einfach die betreffenden Register
 * auf den aktuellen Stack zu retten (pushen) und den Stackpointer (esp)
 * danach an der Adresse auf die "from" verweist, zu sichern.
 * Nachdem das geschehen ist, wird der Stack gewechselt,
 * indem man den neuen Stackpointerwert von der Adresse
 * auf die "to" zeigt in das Stackpointerregister esp laedt.
 * Dadurch haben wir den Stack gewechselt und wir koennen nun
 * einfach alle auf diesem Stack geretteten Register wiederherstellen
 * (in umgekehrter Reihenfolge poppen). Zum Schluss fuehren
 * wir einfach eine "ret" Instruktion aus, die dazu fuehrt,
 * dass die Coroutine "to" an der Stelle weiterlaeuft,
 * an der sie das letzte mal "switchContext" aufgerufen hat.
 * F�r Coroutinen die zum ersten mal aktiviert werden, muss
 * deshalb ein Stackframe existieren, was gleich aussieht mit
 * dem einer Coroutine die "switchContext" aufgerufen hat.
 */

class Coroutine
{
public:
	/* Aufsetzen einer neuen Coroutine.
	 */
	explicit Coroutine(void *tos = 0)
	{
		setup(tos); // top of Stack
	}

	/* Kontrolltransfer von dieser Coroutine zu "next"
	 * Die eigentliche Arbeit erledigt "switchContext"
	 */
	void resume(Coroutine *next)
	{
		switchContext(this->sp, next->sp);
	}

	/* Dies ist der Rumpf der Coroutine
	 * und muss in abgeleiteten Klassen definiert werden.
	 */
	virtual void body() = 0;

	/* Diese Methode wird aufgerufen
	 * wenn der Rumpf unserer Coroutine beendet ist
	 * und muss in abgeleiteten Klassen definiert werden.
	 */
	virtual void exit() = 0;

private:
	/* Diese Funktion hat nur die Aufgabe
	 * den Rumpf der uebergebenen Coroutine aufzurufen
	 * und nach der Rueckkehr exit() aufzurufen,
	 * um die Termination des Rumpfes bekanntzugeben.
	 * Diese Prozedur dient so als eine Bruecke zwischen der
	 * nicht objektorientierten und der objektorientierten Welt
	 * Beachte, das "startup" als "static deklariert ist
	 * und deshalb keinen impliziten "this"-Zeiger uebergeben bekommt.
	 */
	static void startup(Coroutine *obj)
	{
		obj->body();
		obj->exit();
	};

	/* Aufsetzen einer neuen Coroutine.
	 * Der Parameter "tos" (top of stack) ist der
	 * initiale Stackpointerwert fuer die neue Coroutine
	 * ACHTUNG: tos kann NULL sein (siehe Constructor)!
	 */
	void setup(void *tos)
	{
		if (tos == nullptr)  // wenn tos = 0 
		{
			sp = nullptr;
			return;
		}

		// Reserviere den Platz fuer die Ruecksprungadresse und gerettete Register
		void **stack = static_cast<void **>(tos);

		// Platz fuer Register reservieren

		stack -= 6; // Platz fuer exit, saved ebp, ebx, esi, edi  (anzahl der Register + Return + Einstiegspunkt)
		// eax und edx werden fuer Stack benoetigt
		
		// Simuliere Rücksprungadresse fuer "ret" anweisung
		stack[0] = nullptr;										  // fue fruehzeitiges "ret"
		stack[1] = reinterpret_cast<void *>(&Coroutine::startup); // Einstiegspunkt

		// Initialisiere gerettete Register mit Null-Werten
		stack[2] = nullptr; // ebp
		stack[3] = nullptr; // ebx
		stack[4] = nullptr; // esi
		stack[5] = nullptr; // edi

		// Setze Stackpointer
		sp = stack + 1; // zeigt auf "fake return address", die startup(( aufruft
	}

	void *sp; // Der gerettete Stackpointer
};

#endif
