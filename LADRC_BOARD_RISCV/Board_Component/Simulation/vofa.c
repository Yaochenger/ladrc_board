#include "vofa.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#define CMD_BUFFER_SIZE 32
static char cmd_buffer[CMD_BUFFER_SIZE];

extern Mode_Para USR_Sim_Mode;
extern LADRC_TypeDef USR_Ladrc_Mode;

Command extended_commands[] = {
    {"r", cmd_r_callback},
    {"h", cmd_h_callback},
    {"wo", cmd_wo_callback},
    {"wc", cmd_wc_callback},
    {"bo", cmd_bo_callback},
    {"init", cmd_init_callback},
    {"expe", cmd_expe_callback},
    {"run", cmd_run_callback},
    {"td", cmd_TD_callback},
    {"res", cmd_TD_callback},
};

int vofa_cmd_cnt = sizeof(extended_commands) / sizeof(extended_commands[0]);

// r = in_val [1,1000]
void cmd_r_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.r = (double)value / 10.0;
    printf("R Command value(/10): %d , r:% f\r\n", value, USR_Ladrc_Mode.r);
}

// h = in_val / 1000.0 [0.1,1]
void cmd_h_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.h = (double)value / 1000.0;
    printf("H Command value: %d (/1000) , h:% f\r\n", value, USR_Ladrc_Mode.h);
}

// w0 = in_val [1,1000]
void cmd_wo_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.w0 = value;
    printf("W0 Command value (/1): %d , w0:% f\r\n", value, USR_Ladrc_Mode.w0);
}

// wc = in_val [1,1000]
void cmd_wc_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.wc = value;
    printf("WC Command value (/1): %d , wc:% f\r\n", value, USR_Ladrc_Mode.wc);
}

// b0 = in_val / 10.0 [0.1,100]
void cmd_bo_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.b0 = (double)value / 10.0;
    printf("B0 Command value: %d (/10) , b0:% f\r\n", value, USR_Ladrc_Mode.b0);
}

// init = in_val [0.1,1000.0]
void cmd_init_callback(const char* data)
{
    int value = atoi(data);
    USR_Sim_Mode.init_val = (double)value / 10.0;
    printf("INIT Command value (/10): %d , init:% f\r\n", value, USR_Sim_Mode.init_val);
}

// expe = in_val [0.1,1000.0]
void cmd_expe_callback(const char* data)
{
    int value = atoi(data);
    USR_Sim_Mode.expect_val = (double)value / 10.0;
    printf("EXPE Command value (/10): %d , expe:% f\r\n", value, USR_Sim_Mode.expect_val);
}

// expe = in_val 0/1
void cmd_TD_callback(const char* data)
{
    int value = atoi(data);
    USR_Sim_Mode.TD_state = value;
    printf("TD run command received, value: %d\r\n", value);
}

void cmd_run_callback(const char* data)
{
    int value = atoi(data);
    USR_Sim_Mode.state = value;
    printf("run command received, value: %d\r\n", value);
}

void cmd_res_callback(const char* data)
{
    int value = atoi(data);
    if (value)
    {
        LADRC_INIT(&USR_Ladrc_Mode);
        SIMULATION_DINIT(&USR_Sim_Mode);
    }
    printf("res command received, value: %d\r\n", value);
}

void SIMULATION_DINIT(Mode_Para * Usr_Mode_Para)
{
    Usr_Mode_Para->state = 1;
    Usr_Mode_Para->TD_state = 1;
    Usr_Mode_Para->init_val = 0;
    Usr_Mode_Para->expect_val = 0;
    Usr_Mode_Para->real_val = 0;
}

static void process_command(const char* cmd_type, const char* cmd_data, const Command* commands, int cmd_count)
{
    for (int i = 0; i < cmd_count; i++) {
        if (strcmp(cmd_type, commands[i].type) == 0 && commands[i].handler != NULL) {
            commands[i].handler(cmd_data);  // 调用对应的处理函数，传入数据
            return;
        }
    }
    printf("Unknown command type: %s\r\n", cmd_type);
}

void parse_command(Command* commands, int cmd_count)
{
    if (*IsUsart1RecvFinsh()) {
        // 读取环形缓冲区数据到 cmd_buffer
        chry_ringbuffer_read(&chry_rbuffer_tid, cmd_buffer, chry_ringbuffer_get_used(&chry_rbuffer_tid));

        // 开始解析
        if (cmd_buffer[0] == '#') {
            char cmd_type[MAX_TYPE_LEN] = {0};  // 存储命令类型 (# 和 : 之间的部分)
            char cmd_data[16] = {0};            // 存储命令数据 (: 后面的部分)
            int i = 1;
            int type_index = 0;
            int data_index = 0;
            int colon_found = 0;

            // 提取命令类型 (# 到 : 之间的部分)
            while (cmd_buffer[i] != '\0' && i < CMD_BUFFER_SIZE - 1) {
                if (cmd_buffer[i] == ':') {
                    colon_found = 1;
                    i++;
                    break;
                }
                if (type_index < MAX_TYPE_LEN - 1) {
                    cmd_type[type_index++] = cmd_buffer[i];
                }
                i++;
            }

            // 如果找到冒号，则提取后面的数据
            if (colon_found) {
                while (cmd_buffer[i] != '\0' && i < CMD_BUFFER_SIZE - 1) {
                    if (data_index < sizeof(cmd_data) - 1) {
                        cmd_data[data_index++] = cmd_buffer[i];
                    }
                    i++;
                }
            }

            // 处理命令
            if (cmd_type[0] != '\0') {
                if (colon_found && cmd_data[0] != '\0') {
                    process_command(cmd_type, cmd_data, commands, cmd_count);
                } else {
                    printf("Invalid command: no data provided for %s\r\n", cmd_type);
                }
            } else {
                printf("Invalid command: empty command type\r\n");
            }
        } else {
            printf("Invalid command: missing '#'\r\n");
        }

        // 清理缓冲区并重置接收标志
        memset(cmd_buffer, 0, sizeof(cmd_buffer));
        *IsUsart1RecvFinsh() = 0;
    }
}
