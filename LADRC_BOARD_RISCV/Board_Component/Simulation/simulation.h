#ifndef SIMULATION_H
#define SIMULATION_H

#include "debug.h"
#include "user_peripheral_driver.h"
#include "LADRC.h"
#include "vofa.h"

#define Simulation_Cycle 5

typedef struct {
    uint8_t state;
    uint8_t TD_state;
    double init_val;
    double real_val;
    double expect_val;
} Mode_TypeDef;

extern Mode_TypeDef USR_Sim_Mode;
extern LADRC_TypeDef USR_Ladrc_Mode;
extern Command extended_commands[];
extern int vofa_cmd_cnt;

void cmd_r_callback(const char* data);
void cmd_h_callback(const char* data);
void cmd_wo_callback(const char* data);
void cmd_wc_callback(const char* data);
void cmd_bo_callback(const char* data);
void cmd_init_callback(const char* data);
void cmd_expe_callback(const char* data);
void cmd_run_callback(const char* data);
void cmd_TD_callback(const char* data);
void cmd_res_callback(const char* data);

void SIMULATION_DINIT(Mode_TypeDef * Usr_Mode_TypeDef);
void SIMULATION_INIT(void);
void Simulation_TD_Callback(MultiTimer* timer, void* userData);
void Simulation_LOOP_Callback(MultiTimer* timer, void* userData);

#endif // SIMULATION_H
