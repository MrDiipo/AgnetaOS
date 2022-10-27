section .asm

extern int21h_handler
extern no_interrupt_handler

global int21_handler
global idt_load
global no_interrupt

idt_load:
        push ebp
       mov ebp, esp

       mov ebx, [ebp+4]
       lidt  [ebx]

       pop ebp
       ret

init21h:
        cli
        pushad
        call init21h_handler
        popad
        sti
        iret

no_interrupt:
        cli
        pushad
        call no_interrupt_handler
        popad
        sti
        iret
