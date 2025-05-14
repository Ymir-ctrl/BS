#include "thread/ActivityScheduler.h"

ActivityScheduler scheduler;

/**  
 *  Setzt den Zustand der Aktivität danne erst auf READY, damit sie
 *  Fügt die Aktivität der Ready-Liste hinzu und startet sie.
 *  Wird nur einmal aufgerufen.
 */
void ActivityScheduler::start(Activity* act) {
    act->changeTo(Activity::READY);
    schedule(act);
    activate(act);
}

/**  
 *  Setzt den Zustand der Aktivität auf BLOCKED, damit sie nicht mehr
 *  aktiv ist. Startet die nächste Aktivität, die bereit ist.
 */
void ActivityScheduler::suspend() {
    if (active != nullptr) {
        active->changeTo(Activity::BLOCKED);
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
        active->changeTo(Activity::ZOMBIE);
        reschedule();
    } else {
        act->changeTo(Activity::ZOMBIE);
        remove(act);
    }

/* Terminieren des aktiven Prozesses,
 * und Wechsel zum naechsten lauffaehigen Prozess
 */    
void ActivityScheduler::exit() {
    active ->changeTo(Activity::ZOMBIE);
    reschedule();
}

/* Der aktive Prozess ist, sofern er sich nicht im Zustand
 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
 * zu übergeben.
 */
void ActivityScheduler::activate(Schedulable* to) {
    if (active != nullptr &&
    active->isBlocked() == 0 &&
    active->isZombie() == 0) {
    // setzt den Zustand auf READY und fügt ihn in die Readylist ein
    active->setState(Activity::READY)
    Scheduler::schedule(active);
    }

    Activity* activityTo = static_cast<Activity*>(to);
    activityTo->changeTo(Activity::RUNNING);
    Dispatcher::dispatch(activityTo);
}

}