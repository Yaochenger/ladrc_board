/**
 * @file lshell_port.h
 * @brief Letter shell platform port interface.
 */

#ifndef USER_PERIPHERAL_DRIVER_LETTER_SHELL_LSHELL_PORT_H_
#define USER_PERIPHERAL_DRIVER_LETTER_SHELL_LSHELL_PORT_H_

#include "debug.h"
#include "shell.h"
#include "log.h"

/**
 * @brief Initialize the shell instance and bind the UART backend.
 */
void Shell_INIT(void);

/**
 * @brief Write one log buffer to the shell backend.
 * @param buffer Log buffer.
 * @param len Buffer length.
 */
void uartLogWrite(char *buffer, short len);

#endif /* USER_PERIPHERAL_DRIVER_LETTER_SHELL_LSHELL_PORT_H_ */
