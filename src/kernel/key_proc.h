#ifndef KEYP_H
#define KEYP_H

#include "kernel_io.h"
#include "command.h"
#include "stdstr.h"

int process_key(
    const char  key,
    char*       command_buffer,
    unsigned*   command_buffer_pos,
    char*       OS_STATUS,
    char*       in_command
);

#endif // KEYP_H