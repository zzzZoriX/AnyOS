#include "kernel_io.h"

void kernel_clear_screen(void){
    for(unsigned i = 0; i < SCREEN_SIZE;){
        VGA[i++] = ' ';
        VGA[i++] = 0x0f;
    }
}

void kernel_std_out(char* msg){
    int size = 0;

    GET_MSG_LENGTH(size, msg);

    for(int msgi = 0; msgi < size; ++msgi){
        VGA[vgai++] =     msg[msgi];
        VGA[vgai++] = 0x0f;
    }
}

void kernel_newline(void){
    unsigned line_size = SYMBOL_SIZE * SCREEN_COLUMNS;
    vgai = vgai + (line_size - vgai % (line_size));
}