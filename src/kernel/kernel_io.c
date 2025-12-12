#include "kernel_io.h"

void kernel_clear_screen(void){
    for(unsigned i = 0; i < SCREEN_SIZE;){
        VGA[i++] = ' ';
        VGA[i++] = 0x0f;
    }

    vgai = 0;
}

void kernel_std_out(char* msg){
    int size = 0;

    GET_STR_LENGTH(size, msg);

    for(int msgi = 0; msgi < size; ++msgi)
        kernel_std_put_char(msg[msgi]);
}

void kernel_newline(void){
    unsigned line_size = SYMBOL_SIZE * SCREEN_COLUMNS;
    vgai = vgai + (line_size - vgai % (line_size));
}

void kernel_backspace(void){
    if(vgai >= 2){
        vgai -= 2;

        VGA[vgai] = ' ';
        VGA[vgai + 1] = 0x0f;
    }
}

void kernel_std_put_char(const char c){
    VGA[vgai++] = c;
    VGA[vgai++] = 0x0f;
}

void kernel_buffer_init(void){
    buffer.count = 0;
    buffer.head = 0;
    buffer.tail = 0;
}

char kernel_buffer_has_data(void){
    return buffer.count > 0;
}

char kernel_buffer_get(void){
    if(buffer.count == 0)
        return 0;

    unsigned char charcode = buffer.data[buffer.tail];
    buffer.tail = (buffer.tail + 1) % BUFFER_SIZE;
    --buffer.count;

    return charcode;
}

void kernel_buffer_put(const char c){
    if(buffer.count >= BUFFER_SIZE)
        return;

    buffer.data[buffer.head] = c;
    buffer.head = (buffer.head + 1) % BUFFER_SIZE;
    ++buffer.count;
}