#include "simulation.h"

static SIMULATION_MODE_TypeDef SIMULATION_MODE_InitStruct;
static LADRC_TypeDef USR_Ladrc_Mode;
static MultiTimer timer_td;
static MultiTimer timer_loop;

static Command extended_commands[] = {
    {"r",    cmd_r_callback},
    {"h",    cmd_h_callback},
    {"wo",   cmd_wo_callback},
    {"wc",   cmd_wc_callback},
    {"bo",   cmd_bo_callback},
    {"init", cmd_init_callback},
    {"expe", cmd_expe_callback},
    {"run",  cmd_run_callback},
    {"res",  cmd_res_callback},
};

static int vofa_cmd_cnt = sizeof(extended_commands) / sizeof(extended_commands[0]);

void SIMULATION_DINIT(void)
{
    SIMULATION_MODE_InitStruct.mode = NULL_MODE;
    SIMULATION_MODE_InitStruct.init_val = 0;
    SIMULATION_MODE_InitStruct.expect_val = 0;
    SIMULATION_MODE_InitStruct.real_val = 0;
}

void SIMULATION_INIT(void)
{
    LADRC_INIT(&USR_Ladrc_Mode);
    multiTimerStart(&timer_td, 50, Simulation_TD_Callback, NULL); // 50ms repeating
    multiTimerStart(&timer_loop, 50, Simulation_LOOP_Callback, NULL); // 50ms repeating
}

void Simulation_TD_Callback(MultiTimer* timer, void* userData)
{
    if (SIMULATION_MODE_InitStruct.mode == TD_MODE)
    {
        LADRC_TD(&USR_Ladrc_Mode, SIMULATION_MODE_InitStruct.expect_val);

        ladrc_printf(USART2, "%.2f,%.2f\n", USR_Ladrc_Mode.v1,
                USR_Ladrc_Mode.v2);
    }
    multiTimerStart(timer, Simulation_Cycle, Simulation_TD_Callback, NULL);
}

void Simulation_LOOP_Callback(MultiTimer* timer, void* userData)
{
    SIMULATION_MODE_InitStruct.real_val += USR_Ladrc_Mode.u;

    if (SIMULATION_MODE_InitStruct.mode == LOOP_MODE)
    {
        LADRC_Loop(&USR_Ladrc_Mode, &SIMULATION_MODE_InitStruct.expect_val, &SIMULATION_MODE_InitStruct.real_val);

        ladrc_printf(USART2, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                                                 USR_Ladrc_Mode.v1,
                                                 USR_Ladrc_Mode.v2,
                                                 USR_Ladrc_Mode.z1,
                                                 USR_Ladrc_Mode.z2,
                                                 USR_Ladrc_Mode.z3,
                                                 SIMULATION_MODE_InitStruct.expect_val,
                                                 SIMULATION_MODE_InitStruct.real_val);
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
    SIMULATION_MODE_InitStruct.init_val = (double)value / 10.0;
    printf("INIT Command value (/10): %d , init:% f\r\n", value, SIMULATION_MODE_InitStruct.init_val);
}

void cmd_expe_callback(const char* data)
{
    int value = atoi(data);
    SIMULATION_MODE_InitStruct.expect_val = (double)value / 10.0;
    printf("EXPE Command value (/10): %d , expe:% f\r\n", value, SIMULATION_MODE_InitStruct.expect_val);
}

void cmd_run_callback(const char* data)
{
    int value = atoi(data);

    if (value == 0)
    {
        SIMULATION_MODE_InitStruct.mode = TD_MODE;
    }
    else if (value == 1)
    {
        SIMULATION_MODE_InitStruct.mode = LOOP_MODE;
    }
    else
    {
        SIMULATION_MODE_InitStruct.mode = NULL_MODE;
    }

    printf("run command received, value: %d\r\n", value);
}

void cmd_res_callback(const char* data)
{
    int value = atoi(data);
    if (value)
    {
        LADRC_INIT(&USR_Ladrc_Mode);
        SIMULATION_DINIT();
    }
    printf("res command received, value: %d\r\n", value);
}

void Simulation_parse_command(void)
{
    parse_command(extended_commands, vofa_cmd_cnt);
}
