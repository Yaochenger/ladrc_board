#ifndef SIMULATION_H
#define SIMULATION_H

#include "debug.h"
#include "user_peripheral_driver.h"
#include "LADRC.h"
#include "vofa.h"

#define Simulation_Cycle 5

enum  SIMULATION_MODE_Type
{
    TD_MODE,
    LOOP_MODE,
    NULL_MODE
};

typedef struct {
    enum SIMULATION_MODE_Type mode;
    double init_val;
    double real_val;
    double expect_val;
} SIMULATION_MODE_TypeDef;

void cmd_r_callback(const char* data);
void cmd_h_callback(const char* data);
void cmd_wo_callback(const char* data);
void cmd_wc_callback(const char* data);
void cmd_bo_callback(const char* data);
void cmd_init_callback(const char* data);
void cmd_expe_callback(const char* data);
void cmd_run_callback(const char* data);
void cmd_res_callback(const char* data);

void SIMULATION_DINIT(void);
void SIMULATION_INIT(void);
void Simulation_TD_Callback(MultiTimer* timer, void* userData);
void Simulation_LOOP_Callback(MultiTimer* timer, void* userData);
void Simulation_parse_command(void);
#endif // SIMULATION_H
