#include "kernel_io.h"
#include "keyboard.h"

#define true    1
#define false   2

void kernel_main(void){
    kernel_clear_screen();

    char* welcome_msg = "Welcome to AnyOS!\0";

    kernel_std_out(welcome_msg);
    kernel_newline();

    idt_init();
    kernel_keyboard_init();

    kernel_std_out("> ");
    
    kernel_keyboard_handler();

    while(true);
}