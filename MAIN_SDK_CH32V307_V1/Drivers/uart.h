#ifndef USER_DRIVERS_UART_H_
#define USER_DRIVERS_UART_H_

#include "ch32v30x.h"
#include "sdkconfig.h"

/**
 * @brief Initialize enabled UART peripherals from sdkconfig.
 */
void UART_GPIO_Init(void);

#endif /* USER_DRIVERS_UART_H_ */
