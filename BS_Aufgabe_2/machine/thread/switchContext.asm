%include "../machine/csym.inc"	; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym switchContext

[GLOBAL switchContext]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; switchContext: Der Coroutinenwechsel
;
; C-Prototyp:
;
;     void switchContext (void*& from, void*& to);
;

switchContext:
;	fuegt hier Euren Code ein!
	mov eax, [esp + 4]     ; eax = &from
    mov ecx, [esp + 8]     ; ecx = &to

	push ebp
    	push edi
	push esi
   	push ebx

    mov [eax], esp         ; alter Stackpointer =*from  

    mov esp, [ecx]         ; hier esp = *to (neuer Kontext)

    pop ebx
    pop esi
    pop edi
    pop ebp
	ret		; Ruecksprung zum Aufrufer

