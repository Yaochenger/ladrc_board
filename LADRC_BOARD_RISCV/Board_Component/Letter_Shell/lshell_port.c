/*
 * lshell_port.c
 *
 *  Created on: 2024年4月2日
 *      Author: MCU
 */

#include "lshell_port.h"

Shell shell;
char shellBuffer[512];

Log uartLog = {
    .write = uartLogWrite,
    .active = 1,
    .level = LOG_DEBUG
};

void uartLogWrite(char *buffer, short len)
{
    if (uartLog.shell)
    {
        shellWriteEndLine(uartLog.shell, buffer, len);
    }
}

short userShellWrite(char *data, unsigned short len)
{

    int i;

    for(i=0;i<len;i++){
        USART_SendData(USART1, (uint8_t) data[i]);
        /* 等待发送完毕 */
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }

    return len;
}

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void)
{
  uint8_t ch;  //接收中断缓冲

  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
      ch = USART_ReceiveData(USART1);
      shellHandler(&shell, ch);
  }
}

void userShellInit(void)
{
    shell.write = userShellWrite;
    shellInit(&shell, shellBuffer, 512);
    logRegister(&uartLog, &shell);
}
