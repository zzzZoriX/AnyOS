[bits 32]

global write_port
global read_port
global load_idt
global keyboard_handler

extern kernel_keyboard_handler

read_port:
mov edx, [esp + 4]
in al, dx
ret

write_port:
mov edx, [esp + 4]
mov al, [esp + 4 + 4]
out dx, al
ret

load_idt:
mov edx, [esp + 4]
lidt [edx]
sti
ret

keyboard_handler:
call kernel_keyboard_handler
iretd