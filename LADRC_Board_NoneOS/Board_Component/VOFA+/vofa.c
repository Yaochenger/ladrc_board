#include "vofa.h"

#define MAX_BUFFER_SIZE 128

void send_to_vofa_fw(float *data, int num_channels)
{
    char buffer[MAX_BUFFER_SIZE];
    int pos = 0;
    const int max_write = MAX_BUFFER_SIZE - 2;

    for (int i = 0; i < num_channels; i++) {

        int written = snprintf(buffer + pos, max_write - pos, "%.2f", data[i]); // 返回格式化的字符串的长度 不包含\0

        if (written < 0 || (pos + written) >= max_write) {
            printf("Buffer overflow!\n"); //buffer yi'chu
            return;
        }
        pos += written; // 设置写偏移

        if (i < num_channels - 1) {
            if (pos < max_write) {
                buffer[pos++] = ','; // 添加数据分隔符
            } else {
                printf("Buffer overflow!\n");
                return;
            }
        }
    }

    if (pos < MAX_BUFFER_SIZE - 1) { // 设置换行符
        buffer[pos++] = '\n';
        buffer[pos] = '\0';
    }
    else {
        buffer[MAX_BUFFER_SIZE - 2] = '\n';
        buffer[MAX_BUFFER_SIZE - 1] = '\0';
    }

    UART2_SendString(buffer);
}
