#include "keyboard.h"

const char kb_map[128] = {
0, 27, 
'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
'-', '=', '\b', '\t',
'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
'`', 0,
'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
'*', 
0,      // alt
' ',    // space
0,      // caps lock
0,      // 59 - f1 >> ...
0, 0, 0, 0, 0, 0, 0, 0,
0,      // ... << f10
0,      // 69 - num lock
0,      // scroll lock
0,      // home key
0,      // up arrow
0,      // page up
'-',
0,      // left arrow
0,
0,      // right arrow
'+',
0,      // 79 - end key
0,      // down arrow
0,      // page down
0,      // insert key
0,      // delete key
0, 0, 0,
0,      // f11
0,      // f12
0,      // all others key undefined
};


void idt_init(void){
    unsigned long   kb_addr = (unsigned long)keyboard_handler,
                    idt_addr,
                    idt_ptr[2];

    IDT[0x21].lower_bits = kb_addr & 0xffff;
    IDT[0x21].hightest_bits = (kb_addr & 0xffff0000) >> 16;
    IDT[0x21].gate = INTERPUT_GATE;
    IDT[0x21].zero = 0;
    IDT[0x21].selector = KERNEL_CODE_SEG_OFFSET;


    /* ICW1 */
    write_port(PIC1_COMMAND_PORT, 0x11);
    write_port(PIC2_COMMAND_PORT, 0x11);

    /* ICW2 */
    write_port(PIC1_DATA_PORT, 0x20);
    write_port(PIC2_DATA_PORT, 0x28);

    /* ICW3 */
    write_port(PIC1_DATA_PORT, 0x00);
    write_port(PIC2_DATA_PORT, 0x00);

    /* ICW4 */
    write_port(PIC1_DATA_PORT, 0x01);
    write_port(PIC2_DATA_PORT, 0x01);

    /* interrputs mask */
    write_port(PIC1_DATA_PORT, 0xff);
    write_port(PIC2_DATA_PORT, 0xff);


    idt_addr = (unsigned long)IDT;
    idt_ptr[0] = (sizeof(IDT_elem) * IDT_SIZE) + ((idt_addr & 0xffff) << 16);
    idt_ptr[1] = idt_addr >> 16;

    load_idt(idt_ptr);
}

void kernel_keyboard_handler(void){
    unsigned char status;
    char keycode;

    write_port(PIC1_COMMAND_PORT, 0x20);

    status = read_port(KB_STATUS_PORT);
    if(status & 0x01){
        keycode = read_port(KB_DATA_PORT);
        if(keycode < 0)
            return;

        if(keycode == ENTER_KEYCODE){
            kernel_newline();
            return;
        }

        VGA[vgai++] = kb_map[(unsigned char)keycode];
        VGA[vgai++] = 0x0f;
    }
}

void kernel_keyboard_init(void){
    write_port(PIC1_DATA_PORT, 0xfd);
}