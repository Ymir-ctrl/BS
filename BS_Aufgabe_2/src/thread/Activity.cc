#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

extern ActivityScheduler scheduler;

//Konstruktor für normale aktivitäten (Stack)
Activity::Activity(void* tos)
    : Coroutine(tos), state(BLOCKED){
        //bleibt blocked bis wakup()
}

//Konstruktor für Hauptprozess (main)
Activity::Activity()
    :Coroutine(nullptr), state(RUNNING){
        scheduler.start(this);
}

//Destuktor
Activity::~Activity() {
    if (!isZombie()){
        exit();
    }
}

// CPU abgeben 
void Activity::yield(){
    scheduler.reschedule(); //nächste reade aktivität aufrufen
}

// Aktivität blockieren
void Activity::sleep(){
    changeTo(BLOCKED);
    scheduler.suspend(); //aus der Ready Liste nehmen
}

//Aktivität wieder lauffähig machen
void Activity::wakeup(){
    if (isBlocked()){
        changeTo(READY);
        scheduler.schedule(this);
    }
}

//benden der aktivität
void Activity::exit(){
    changeTo(ZOMBIE);
    scheduler.exit();
}

//auf beendigung einer andere Aktivität warten
void Activity::join(){
    if(!isZombie()){
        sleep();
    }
}
