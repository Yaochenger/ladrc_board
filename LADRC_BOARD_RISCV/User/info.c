/*
 * info.c
 *
 *  Created on: 2025Äê5ÔÂ13ÈÕ
 *      Author: MCU
 */

#include "log.h"
#include "info.h"
#include "debug.h"
#include "board_config.h"

void board_info(void)
{
    logInfo("BOARD NAME:%s",BOADR_INFO);
    logInfo("CPU:%s",BOADR_CPU);
    logInfo("SystemClk:%d",SystemCoreClock);
}
