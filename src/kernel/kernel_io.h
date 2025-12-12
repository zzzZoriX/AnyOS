#ifndef KERNEL_IO
#define KERNEL_IO

#define STR_COMPARE(str)

#define SCREEN_SIZE     80 * 25 * 2
#define SCREEN_COLUMNS  80
#define SCREEN_ROWS     25
#define SYMBOL_SIZE     2
#define BUFFER_SIZE     256

#define STD_PROMPT      "> "

static unsigned vgai = 0;
static char*    VGA = (char*)0xb8000;

typedef struct {
    unsigned char   data[BUFFER_SIZE];
    unsigned        head,   // write
                    tail,   // read
                    count;
} buffer_t;

static buffer_t buffer;

#include "stdstr.h"


void kernel_clear_screen(void);

void kernel_std_out(char* msg);
void kernel_std_put_char(const char c);

void kernel_newline(void);
void kernel_backspace(void);

void kernel_buffer_init(void);
char kernel_buffer_has_data(void);
char kernel_buffer_get(void);
void kernel_buffer_put(const char c);

#endif // KERNEL_IO