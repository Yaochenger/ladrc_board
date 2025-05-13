/*
 * lshell_port.h
 *
 *  Created on: 2024��4��2��
 *      Author: MCU
 */

#ifndef USER_PERIPHERAL_DRIVER_LETTER_SHELL_LSHELL_PORT_H_
#define USER_PERIPHERAL_DRIVER_LETTER_SHELL_LSHELL_PORT_H_
#include "debug.h"
#include "shell.h"
#include "log.h"

void userShellInit(void);
void uartLogWrite(char *buffer, short len);
#endif /* USER_PERIPHERAL_DRIVER_LETTER_SHELL_LSHELL_PORT_H_ */
