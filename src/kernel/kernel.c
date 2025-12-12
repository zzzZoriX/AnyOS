#include "command.h"
#include "kernel_io.h"
#include "keyboard.h"
#include "stdstr.h"

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

            if(c == '\n'){
                command[command_pos] = '\0';

                if(command_pos > 0){
                    if(compare(command, CMD_OFF_OS) == 0){
                        OS_STATUS = false;
                        break;
                    }

                    kernel_newline();

                    process_command(command);
                }

                kernel_std_out(STD_PROMPT);
                
                command_pos = 0;
                in_command = true;
            }
            else if(c == '\b'){
                if(command_pos > 0){
                    --command_pos;

                    kernel_backspace();
                }
            }
            else if(c >= 2){
                command[command_pos++] = c;

                kernel_std_put_char(c);

                if(!in_command)
                    in_command = true;
            }
        }

        if(!in_command){
            kernel_std_out(STD_PROMPT);
            in_command = true;
        }

        asm volatile("hlt");        
    }
}