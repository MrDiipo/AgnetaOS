ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


_start:
        jmp short start
        nop

; FAT16 Header
OEMIdentifier               db 'AGNETAOS'
BytesPerSector             dw 0x200
SectorsPerCluster         db 0x80
ReservedSectors           dw 200
FATCopies                   db 0x02
RootDirEntries             dw 0x40
NumSectors                dw 0x00
MediaType                  db 0xF8
SectorsPerFat              dw 0x100
SectorsPerTrack          dw 0x20
NumberOfHeads         dw 0x40
HiddenSectors            dd 0x00
SectorsBig                  dd 0x773594

; Extended BPB (Dos 4.0)
DriveNumber            db 0x80
WinNTBit                 db 0x00
Signature                 db 0x29
VolumeID                dd 0xD105
VolumeIDString       db 'AGNETAOS BOO'
SystemIDString        db 'FAT16'

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
        lgdt[gdt_descriptor]
        mov eax, cr0
        or eax, 0x1
        mov cr0, eax
        jmp CODE_SEG : load32
;       jmp $


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


[BITS 32]
load32:
        mov eax, 1
        mov ecx, 100
        mov edi, 0x0100000
        call ata_lba_read

ata_lba_read:
        mov ebx, eax, ; Back up the LBA
        ; Send the highest 8 bits of the lba to hard disk controller
        shr eax, 24
        mov dx, 0x1f6
        out dx, al
        ; Finished sending the highest 8 bits of the lba

        mov eax, ecx
        mov dx, 0x1F2
        out dx, al


times 510-($ - $$) db 0
dw 0xAA55
