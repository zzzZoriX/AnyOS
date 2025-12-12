#include "command.h"

void process_command(char* command_buffer){
    if(compare(command_buffer, CMD_HELP) == 0){
        kernel_std_out("Available commands:");
        kernel_newline();

        kernel_std_out("  help          - print command info message(this)");
        kernel_newline();

        kernel_std_out("  clr           - clear screen space");
        kernel_newline();

        kernel_std_out("  echo \"msg\"    - repeat your message");
        kernel_newline();

        kernel_std_out("  -off-any      - turn off OS");
        kernel_newline();
    }

    else if(compare(command_buffer, CMD_CLEAR) == 0)
        kernel_clear_screen();

    else if(ncompare(command_buffer, CMD_ECHO, 5) == 0){
        kernel_std_out(&command_buffer[5]);
        kernel_newline();
    }

    else{
        kernel_std_out("Unknown command: ");
        kernel_std_out(command_buffer);
        kernel_newline();

        kernel_std_out("For command list type \"help\"");
        kernel_newline();
    }
}