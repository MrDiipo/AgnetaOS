section .asm

extern int21h_handler
extern no_interrupt_handler
extern isr80h_handler

global int21h
global idt_load
global no_interrupt
global enable_interrupts
global disable_interrupts;
global isr80h_wrapper

enable_interrupts:
        sti
        ret

disable_interrupts:
        cli
        ret
idt_load:
        push ebp
       mov ebp, esp

       mov ebx, [ebp+4]
       lidt  [ebx]

       pop ebp
       ret

init21h:
        pushad
        call int21h_handler
        popad
        iret

no_interrupt:
        pushad
        call no_interrupt_handler
        popad
        iret

isr80h_wrapper:
        ; INTERRUPT FRAME START
        ; ALREADY PUSHED TO US BY THE PROCESSOR UPON ENTRY
        ; TO THIS INTERRUPT
        ; Pushes the general purpose registers
        pushad

        ; INTERRUPT FRAME END

        ; Push the stack pointer so that we are pointing the interrupt frame
        push esp

        ;EAX holds our command, lets push it to the stack for isr80h_handler
        push eax
        call isr80h_handler
        mov dword[tmp_res], eax
        add esp, 8

        ; Restore general purpose register for userland
        popad
        mov eax, [tmp_res]

section .data
; Inside here is stored the return result from isr80h_handler
tmp_res: dd 0

