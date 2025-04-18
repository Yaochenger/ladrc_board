#include "vofa.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CMD_BUFFER_SIZE 32
static char cmd_buffer[CMD_BUFFER_SIZE];

extern Mode_Para USR_Sim_Mode;
extern LADRC_NUM USR_Ladrc_Mode;

Command extended_commands[] = {
    {"r", cmd_r_callback},
    {"h", cmd_h_callback},
    {"wo", cmd_wo_callback},
    {"wc", cmd_wc_callback},
    {"bo", cmd_bo_callback},
    {"init", cmd_init_callback},
    {"expe", cmd_expe_callback},
    {"run", cmd_run_callback},
};

int vofa_cmd_cnt = sizeof(extended_commands) / sizeof(extended_commands[0]);

void cmd_r_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.r = value;
    printf("R command received, value: %d\r\n", value);
}

void cmd_h_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.h = value;
    printf("H command received, value: %d\r\n", value);
}

void cmd_wo_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.w0 = value;
    printf("W0 command received, value: %d\r\n", value);
}

void cmd_wc_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.wc = value;
    printf("Wc command received, value: %d\r\n", value);
}

void cmd_bo_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.b0 = value;
    printf("b0 command received, value: %d\r\n", value);
}

void cmd_init_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.h = value;
    printf("init command received, value: %d\r\n", value);
}

void cmd_expe_callback(const char* data)
{
    int value = atoi(data);
    USR_Sim_Mode.expect_val = value;
    printf("expe command received, value: %d\r\n", value);
}

void cmd_run_callback(const char* data)
{
    int value = atoi(data);
    USR_Sim_Mode.state = value;
    printf("run command received, value: %d\r\n", value);
}

void USR_Sim_Para_DInit(Mode_Para * Usr_Mode_Para)
{
    Usr_Mode_Para->state = 0;
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
            char cmd_data[16] = {0};           // 存储命令数据 (: 后面的部分)
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
