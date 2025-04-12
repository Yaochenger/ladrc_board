#ifndef VOFA_H
#define VOFA_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uart2.h"

#define MAX_TYPE_LEN 8

typedef void (*CommandHandler)(const char*);

typedef struct{
    char type[MAX_TYPE_LEN];
    CommandHandler handler;
} Command;


extern Command extended_commands[];
extern uint32_t vofa_cmd_cnt;

void cmd_r_callback(const char* data);
void cmd_h_callback(const char* data);
void cmd_wo_callback(const char* data);
void cmd_wc_callback(const char* data);
void cmd_bo_callback(const char* data);
void cmd_init_callback(const char* data);
void cmd_expe_callback(const char* data);
void cmd_start_callback(const char* data);
void cmd_stop_callback(const char* data);

void parse_command(Command* commands, int cmd_count);
#endif // VOFA_H
