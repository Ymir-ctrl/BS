#include "ActivityScheduler.h"

ActivityScheduler::ActivityScheduler() {
    
}

/**  
 *  Setzt den Zustand der Aktivität danne erst auf READY, damit sie
 *  Fügt die Aktivität der Ready-Liste hinzu und startet sie.
 *  Wird nur einmal aufgerufen.
 */
void ActivityScheduler::start(Activity* act) {
    act->setState(READY);
    schedule(act);
    activate(act);
}

/**  
 *  Setzt den Zustand der Aktivität auf BLOCKED, damit sie nicht mehr
 *  aktiv ist. Startet die nächste Aktivität, die bereit ist.
 */
void ActivityScheduler::suspend() {
    if (active != nullptr) {
        active->setState(BLOCKED);
        reschedule();
    }
}

/**  
 *  Setzt den Zustand der Aktivität auf ZOMBIE, damit sie nicht mehr
 *  aktiv ist, aber der Elternprozess noch abfragen kann, wie 
 *  er beendet wurde. Entfernt die Aktivität aus der Ready-Liste und startet
 *  die nächste Aktivität, die bereit ist.
 */
void ActivityScheduler::kill(Activity* act) {
    if (active == act) {
        active->setState(ZOMBIE);
        reschedule();
    } else {
        act->setState(ZOMBIE);
        remove(act);
    }
}