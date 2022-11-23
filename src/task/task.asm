[BITS 32]
section .asm

global restore_general_purpose_registers
global task_return
global user_registers

; void task_return(struct registers* regs);
task_return:
        mov ebp, esp
        ; PUSH THE DATA SEGMENT (SS WILL BE FINE)
        ; PUSH THE STACK ADDRESS
        ; PUSH THE FLAGS
        ; PUSH THE CODE SEGMENT
        ; PUSH THE IP

        ; Access structure passed
        mov ebx, [ebp+4]
        ; push the data/stack register
        push dword [ebx+44]
        ; push stack pointer
        push dword [ebx+40]

        ; push the flags
        pushf
        pop eax
        or eax, 0x200
        push eax

        ; push the code segment
        push dword [ebx+32]
        ; push the ip to execute
        push dword [ebx+28]

        ; setup some segment registers
        mov ax, [ebx+44]
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        push dword [ebx+4]
        call restore_general_purpose_registers
        add esp, 4

        ; leave kernel land and execute in use land
        iretd

; void restore_general_purpose_registers(Struct registers* regs);
restore_general_purpose_registers:
        push ebp
        mov ebp, esp
        mov ebx, [ebp+8]
        mov edi, [ebx]
        mov esi, [ebx+4]
        mov ebp. [ebx+8]
        mov edx, [ebx+16]
        mov ecx, [ebx+20]
        mov eax, [ebx+24]
        mov ebx, [ebx+12]
        pop esp
        ret


; void user_registers()
user_registers:
        mov ax, 0x23
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        ret