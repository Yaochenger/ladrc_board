#ifndef USER_DRIVERS_UART2_H_
#define USER_DRIVERS_UART2_H_
#include "drv_config.h"
#include "chry_ringbuffer.h"

extern chry_ringbuffer_t chry_rbuffer_tid;

uint8_t *IsUsart1RecvFinsh(void);
void UART2_GPIO_Init(void);
#endif /* USER_DRIVERS_UART2_H_ */
