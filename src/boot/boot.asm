[org 0x7c00]
[bits 16]

jmp start

; GDT SEGMENT ;
gdt_start:
dq 0x0
dq 0x00cf9a000000ffff
dq 0x00cf92000000ffff
gdt_end:
gdt_descriptor:
dw gdt_end - gdt_start - 1
dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10


start:
cli
xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7c00
mov [BOOT_DRIVE], dl

; KERNEL LOADING ;
mov bx, 0x1000
mov dh, 0
mov dl, [BOOT_DRIVE]
mov al, 15
call disk_load

; SWITCH TO PROTECTED MODE ;
switch_to_pm:
cli
lgdt [gdt_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODE_SEG:pm_entry

[bits 32]
pm_entry:
mov ax, DATA_SEG
mov ds, ax
mov es, ax
mov ss, ax
mov fs, ax
mov gs, ax

mov esp, 0x90000

call KERNEL_LOAD_ADDRESS

boot_halt:
hlt
jmp boot_halt


%include "load_disk.asm"

BOOT_DRIVE: db 0
KERNEL_LOAD_ADDRESS equ 0x1000

times 510 - ($ - $$) db 0
DW 0xaa55