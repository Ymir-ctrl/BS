#include "Scheduler.h"

Scheduler::Scheduler() {

}

// Einfuegen eines neuen Elements in die Ready-Liste.
// Schedulable erbt von Chain, daher ist Typkonvertierung nicht nötig
void Scheduler::schedule(Schedulable* sched) {
    readylist.enqueue(sched);
}

// Entfernen eines Elements von der Ready-Liste.
void Scheduler::remove(Schedulable* sched) {
    readylist.remove(sched);
}

//  Aktiviert das vorderste Element der Liste mittels activate.
//  Nutzt cast, um Chain Objekt in Schedulable* umzuändern
void Scheduler::reschedule() {
    // gibt nullptr zurück, falls Liste leer
    Schedulable* to = static_cast<Schedulable*>(readylist.dequeue());
    
    if (to != nullptr) {
        activate(to);
    }
}

void Scheduler::activate(Schedulable* to) {
    to ->activate();
}
