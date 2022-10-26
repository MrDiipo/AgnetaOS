section .asm

global idt_load
idt_load:
        push ebp
       mov ebp, esp

       mov ebx, [ebp+4]
       lidt  [ebx]

       pop ebp
       ret