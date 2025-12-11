[bits 16]
global disk_load

disk_load:
push dx
push bx

mov ah, 0x02         ; BIOS read
mov ch, 0            ; cylinder
mov dh, 0            ; head
mov cl, 2            ; sector (starts at 1 → so kernel starts at 2)

int 0x13
jc disk_err            ; ошибка чтения

pop bx
pop dx

ret

disk_err:
mov si, DISK_ERR_MSG

.print:
lodsb
or al, al
jz halt
mov ah, 0x0e
int 0x10
jmp .print

halt:
hlt
jmp $

DISK_ERR_MSG:
    db "Disk read error", 0