#include "kernel_io.h"

void kernel_main(void){
    kernel_clear_screen();

    char* welcome_msg = "Welcome to AnyOS!\0";

    kernel_std_out(welcome_msg);
}