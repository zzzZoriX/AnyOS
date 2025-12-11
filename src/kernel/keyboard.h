#ifndef KEYBOARD_H
#define KEYBOARD_H

#define IDT_SIZE                256
#define INTERPUT_GATE           0x8e
#define KB_STATUS_PORT          0x64
#define KB_DATA_PORT            0x60
#define KERNEL_CODE_SEG_OFFSET  0x08

#define PIC1_COMMAND_PORT       0x20
#define PIC2_COMMAND_PORT       0xa0
#define PIC1_DATA_PORT          0x21
#define PIC2_DATA_PORT          0xa1

#define ENTER_KEYCODE           0x1c

#include "kernel_io.h"

typedef struct {
    unsigned short  lower_bits;
    unsigned int    selector;
    unsigned char   zero;
    unsigned char   gate;
    unsigned short  hightest_bits;
} IDT_elem;

static IDT_elem IDT[IDT_SIZE];


extern void load_idt(unsigned long* idt_ptr);
extern void write_port(unsigned short port, unsigned char data);
extern char read_port(unsigned short port);
extern void keyboard_handler(void);


void idt_init(void);

void kernel_keyboard_init(void);

void kernel_keyboard_handler(void);

#endif // KEYBOARD_H