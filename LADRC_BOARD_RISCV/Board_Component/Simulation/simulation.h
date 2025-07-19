#ifndef SIMULATION_H
#define SIMULATION_H

#include "debug.h"
#include "drv_config.h"
#include "user_peripheral_driver.h"
#include "vofa.h"
#include "LADRC.h"

#define Simulation_Cycle 5

extern Mode_Para USR_Sim_Mode;
extern LADRC_NUM USR_Ladrc_Mode;

void Simulation_Init(void);
void Simulation_TD_Callback(MultiTimer* timer, void* userData);
void Simulation_LOOP_Callback(MultiTimer* timer, void* userData);

#endif // SIMULATION_H
