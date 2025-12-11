#ifndef KERNEL_IO
#define KERNEL_IO

#define GET_MSG_LENGTH(sptr, msg) for(char* ptr = (msg); *ptr != '\0'; ++ptr, ++(sptr));
#define SCREEN_SIZE     80 * 25 * 2
#define SCREEN_COLUMNS  80
#define SCREEN_ROWS     25
#define SYMBOL_SIZE     2

static unsigned vgai = 0;

static char* VGA = (char*)0xb8000;


void kernel_clear_screen(void);

void kernel_std_out(char* msg);

void kernel_newline(void);

#endif // KERNEL_IO