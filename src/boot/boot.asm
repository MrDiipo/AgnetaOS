ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


_start:
        jmp short start
        nop

    times 33 db 0

; command to run nasm -f bin ./boot.asm -o  ./boot.bin
; qemu-system-x86_64 -hda ./boot.bin

start:
        jmp 0 : step2


step2:
        cli ; Clear interrupts
        mov ax, 0x00
        mov ds, ax
        mov es, ax

        mov ss, ax
        mov sp, 0x7c00
        sti ; Enable Interrupts

.load_protected:
        cli
        ldgt[gdt_descriptor]
        mov eax, cr0
        or eax, 0x1
        mov cr0, eax
        jmp CODE_SEG : load32


; Global Descriptor Table (GDT)
gdt_start:

gdt_null:
        dd 0x0
        dd 0x0

; offset 0x8
; Using the DEFAULT values
; Check osdev.org for more details
gdt_code:        ; Code Segment (CS) should point to this
        dw 0xffff ; Segment limit 0-15 bits
        dw 0       ; Base first 0-15 bits
        db 0        ; Base 16-23 bits
        db 0x9a   ; Access byte
        db 11001111b ; High 4 bit flags and low 4 bit flags
        db 0


; offset 0x10
gdt_data:         ; For DS, ES, FS, GS
        dw 0xffff ; Segment limit 0-15 bits
        dw 0       ; Base first 0-15 bits
        db 0        ; Base 16-23 bits
        db 0x92   ; Access byte
        db 11001111b ; High 4 bit flags and low 4 bit flags
        db 0

gdt_end:

gdt_descriptor:
        dw gdt_end - gdt_start - 1
        dw gdt_start


[BITS_32]
load32:
        mov ax, DATA_SEG
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
        mov ebp, 0x00200000
        mov esp, ebp

        ; Enable the A20 line
        in al, 0x92
        or al, 2
        out 0x92, al
        jmp $


times 510-($ - $$) db 0
dw 0xAA55
