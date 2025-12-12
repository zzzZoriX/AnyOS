#ifndef CMDS_H
#define CMDS_H

#define CMD_HELP    "help"
#define CMD_CLEAR   "clr"
#define CMD_ECHO    "echo "
#define CMD_OFF_OS  "-off-any"

#include "kernel_io.h"
#include "stdstr.h"


void process_command(char* command_buffer);

#endif // CMDS_H