#include "Scheduler.h"

Scheduler::Scheduler() {

}

// Einfuegen eines neuen Elements in die Ready-Liste.
void Scheduler::schedule(Schedulable* sched) {
    readylist.append(sched);
}

// Entfernen eines Elements von der Ready-Liste.
void Scheduler::remove(Schedulable* sched) {
    readylist.remove(sched);
}

// Aktiviert das vorderste Element der Liste mittels activate.
void Scheduler::reschedule() {
    if (readylist.isEmpty()) {
        return;
    }

    Schedulable* to = readylist.getFirst();
    readylist.remove(to);
    activate(to);
}

void Scheduler::activate(Schedulable* to) {
    to ->activate();
}
