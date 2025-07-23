#ifndef VOFA_H
#define VOFA_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uart2.h"
#include "ladrc.h"

#define MAX_TYPE_LEN 8

typedef void (*CommandHandler)(const char*);

typedef struct{
    char type[MAX_TYPE_LEN];
    CommandHandler handler;
} Command;

typedef struct {
    uint8_t state;
    uint8_t TD_state;
    double init_val;
    double real_val;
    double expect_val;
} Mode_Para;

extern Command extended_commands[];
extern int vofa_cmd_cnt;

void cmd_r_callback(const char* data);
void cmd_h_callback(const char* data);
void cmd_wo_callback(const char* data);
void cmd_wc_callback(const char* data);
void cmd_bo_callback(const char* data);
void cmd_init_callback(const char* data);
void cmd_expe_callback(const char* data);
void cmd_run_callback(const char* data);
void cmd_TD_callback(const char* data);
void cmd_res_callback(const char* data);

void SIMULATION_DINIT(Mode_Para * Usr_Mode_Para);

void parse_command(Command *commands, int cmd_count);
#endif // VOFA_H
