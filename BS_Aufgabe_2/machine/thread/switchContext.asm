; Ich hab mal den Header weg gelassen weil der irgendwie nicht funktioniert???
; eventuell sollte hier noch mal etwas verbessert werden

; %include "../machine/csym.inc"	 -- auskommentiert      ; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

; csym switchContext       -- auskommentiert

; [GLOBAL switchContext]  -- auskommentiert

; IMPLEMENTIERUNG DER FUNKTIONEN

; [SECTION .text]   -- auskommentiert

; switchContext: Der Coroutinenwechsel
;
; C-Prototyp:
;
;     void switchContext (void*& from, void*& to);
;

global switchContext          

section .text

switchContext:
    ;	fuegt hier Euren Code ein!

    ; Parameter:
    ; [esp + 4] = from
    ; [esp + 8] = to

    ; Register retten
    push ebp
    push ebx
    push esi
    push edi

    ; speichere aktuellen Stackpointer in from
    mov eax, [esp + 20]     ; eax = Adresse von from
    lea edx, [esp + 20]     ; aktuelle Adresse auf Stack nach Pushes
    mov [eax], edx          ; from = esp

    ; lade neuen Stackpointer aus to
    mov eax, [esp + 24]     ; eax = Adresse von to
    mov esp, [eax]          ; esp = to

    ; Register wiederherstellen (umgekehrte Reihenfolge)
    pop edi
    pop esi
    pop ebx
    pop ebp

    ret
