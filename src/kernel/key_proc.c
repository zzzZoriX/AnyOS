#include "key_proc.h"

int process_key(const char key, char* command_buffer, unsigned int* command_buffer_pos, char* OS_STATUS, char* in_command){
    if(key == '\n'){
        command_buffer[*command_buffer_pos] = '\0';

        kernel_newline();

        if(*command_buffer_pos > 0){
            if(compare(command_buffer, CMD_OFF_OS) == 0){
                *OS_STATUS = 0;
                return 0;
            }

            process_command(command_buffer);
        }

        kernel_std_out(STD_PROMPT);

        *in_command = 1;
        *command_buffer_pos = 0;
    }
    else if(key == '\b'){
        if(*command_buffer_pos > 0){
            --(*command_buffer_pos);

            kernel_backspace();
        }
    }
    else if(key >= 2){
        command_buffer[(*command_buffer_pos)++] = key;

        kernel_std_put_char(key);

        if(!*in_command)
            *in_command = 1;
    }
    
    return 1;
}