#include "simulation.h"

Mode_TypeDef USR_Sim_Mode;
LADRC_TypeDef USR_Ladrc_Mode;
static MultiTimer timer_td;
static MultiTimer timer_loop;

Command extended_commands[] = {
    {"r", cmd_r_callback},
    {"h", cmd_h_callback},
    {"wo", cmd_wo_callback},
    {"wc", cmd_wc_callback},
    {"bo", cmd_bo_callback},
    {"init", cmd_init_callback},
    {"expe", cmd_expe_callback},
    {"run", cmd_run_callback},
    {"td", cmd_TD_callback},
    {"res", cmd_TD_callback},
};

int vofa_cmd_cnt = sizeof(extended_commands) / sizeof(extended_commands[0]);

void SIMULATION_INIT(void)
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

void cmd_r_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.r = (double)value / 10.0;
    printf("R Command value(/10): %d , r:% f\r\n", value, USR_Ladrc_Mode.r);
}

void cmd_h_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.h = (double)value / 1000.0;
    printf("H Command value: %d (/1000) , h:% f\r\n", value, USR_Ladrc_Mode.h);
}

void cmd_wo_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.w0 = value;
    printf("W0 Command value (/1): %d , w0:% f\r\n", value, USR_Ladrc_Mode.w0);
}

void cmd_wc_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.wc = value;
    printf("WC Command value (/1): %d , wc:% f\r\n", value, USR_Ladrc_Mode.wc);
}

void cmd_bo_callback(const char* data)
{
    int value = atoi(data);
    USR_Ladrc_Mode.b0 = (double)value / 10.0;
    printf("B0 Command value: %d (/10) , b0:% f\r\n", value, USR_Ladrc_Mode.b0);
}

void cmd_init_callback(const char* data)
{
    int value = atoi(data);
    USR_Sim_Mode.init_val = (double)value / 10.0;
    printf("INIT Command value (/10): %d , init:% f\r\n", value, USR_Sim_Mode.init_val);
}

void cmd_expe_callback(const char* data)
{
    int value = atoi(data);
    USR_Sim_Mode.expect_val = (double)value / 10.0;
    printf("EXPE Command value (/10): %d , expe:% f\r\n", value, USR_Sim_Mode.expect_val);
}

void cmd_TD_callback(const char* data)
{
    int value = atoi(data);
    USR_Sim_Mode.TD_state = value;
    printf("TD run command received, value: %d\r\n", value);
}

void cmd_run_callback(const char* data)
{
    int value = atoi(data);
    USR_Sim_Mode.state = value;
    printf("run command received, value: %d\r\n", value);
}

void cmd_res_callback(const char* data)
{
    int value = atoi(data);
    if (value)
    {
        LADRC_INIT(&USR_Ladrc_Mode);
        SIMULATION_DINIT(&USR_Sim_Mode);
    }
    printf("res command received, value: %d\r\n", value);
}

void SIMULATION_DINIT(Mode_TypeDef * Usr_Mode_TypeDef)
{
    Usr_Mode_TypeDef->state = 1;
    Usr_Mode_TypeDef->TD_state = 1;
    Usr_Mode_TypeDef->init_val = 0;
    Usr_Mode_TypeDef->expect_val = 0;
    Usr_Mode_TypeDef->real_val = 0;
}


