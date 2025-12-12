#include "kernel_io.h"
#include "keyboard.h"
#include "key_proc.h"

#define true    1
#define false   0

static char OS_STATUS = true; // true - turned on / false - turned off


void kernel_main(void){
    kernel_clear_screen();

    char* welcome_msg = "Welcome to AnyOS!\0";

    kernel_std_out(welcome_msg);
    kernel_newline();

    idt_init();
    keyboard_init();

    asm volatile("sti");


    char in_command = false;
    char command[BUFFER_SIZE];
    unsigned command_pos = 0; 


    while(OS_STATUS){
        while(kernel_buffer_has_data()){
            const char c = kernel_buffer_get();

            if(!process_key(c, command, &command_pos, &OS_STATUS, &in_command))
                break; // OS_STATUS = false
        }

        if(!in_command){
            kernel_std_out(STD_PROMPT);
            in_command = true;
        }

        asm volatile("hlt");        
    }
}