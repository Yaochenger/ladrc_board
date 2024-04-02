/*
 * lshell_port.c
 *
 *  Created on: 2024��4��2��
 *      Author: MCU
 */

#include "lshell_port.h"

Shell shell;
char shellBuffer[512];

short userShellWrite(char *data, unsigned short len)
{

    int i;

    for(i=0;i<len;i++){
        USART_SendData(USART1, (uint8_t) data[i]);
        /* �ȴ�������� */
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }

    return len;
}

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void)
{
  uint8_t ch;  //�����жϻ���

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
}




