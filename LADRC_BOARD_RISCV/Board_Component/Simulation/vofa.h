#ifndef VOFA_H
#define VOFA_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "uart2.h"
#include "ladrc.h"

#define CMD_BUFFER_SIZE 32
#define MAX_TYPE_LEN 8

typedef void (*CommandHandler)(const char*);

typedef struct{
    char type[MAX_TYPE_LEN];
    CommandHandler handler;
} Command;

void parse_command(Command *commands, int cmd_count);
#endif // VOFA_H
