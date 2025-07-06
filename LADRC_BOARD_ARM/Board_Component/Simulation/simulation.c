#include "simulation.h"

Mode_Para USR_Sim_Mode;
LADRC_NUM USR_Ladrc_Mode;

static MultiTimer timer_td;
static MultiTimer timer_loop;

void Simulation_Init(void)
{
    multiTimerStart(&timer_td, 50, Simulation_TD_Callback, NULL); // 50ms repeating
    multiTimerStart(&timer_loop, 50, Simulation_LOOP_Callback, NULL); // 50ms repeating
}

void Simulation_TD_Callback(MultiTimer* timer, void* userData)
{
    if (!USR_Sim_Mode.TD_state)
    {
        LADRC_TD(&USR_Ladrc_Mode, USR_Sim_Mode.expect_val);

        ladrc_printf(USART2, "%.2f,%.2f\n", USR_Ladrc_Mode.v1,
                USR_Ladrc_Mode.v2);
    }
    multiTimerStart(timer, Simulation_Cycle, Simulation_TD_Callback, NULL);
}

void Simulation_LOOP_Callback(MultiTimer* timer, void* userData)
{
    USR_Sim_Mode.real_val += USR_Ladrc_Mode.u;

    if (!USR_Sim_Mode.state)
    {
        LADRC_Loop(&USR_Ladrc_Mode, &USR_Sim_Mode.expect_val, &USR_Sim_Mode.real_val);

        ladrc_printf(USART2, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                                                 USR_Ladrc_Mode.v1,
                                                 USR_Ladrc_Mode.v2,
                                                 USR_Ladrc_Mode.z1,
                                                 USR_Ladrc_Mode.z2,
                                                 USR_Ladrc_Mode.z3,
                                                 USR_Sim_Mode.expect_val,
                                                 USR_Sim_Mode.real_val);
    }
    multiTimerStart(timer, Simulation_Cycle, Simulation_LOOP_Callback, NULL);
}
