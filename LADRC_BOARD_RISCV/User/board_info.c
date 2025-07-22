/*
 * info.c
 *
 *  Created on: 2025Äê5ÔÂ13ÈÕ
 *      Author: MCU
 */

#include <board_info.h>
#include "log.h"
#include "debug.h"
#include "drv_config.h"

void BOARD_INFO(void)
{
    logInfo("BOARD NAME:%s",BOADR_INFO);
    logInfo("CPU:%s",BOADR_CPU);
    logInfo("SystemClk:%d",SystemCoreClock);
}
