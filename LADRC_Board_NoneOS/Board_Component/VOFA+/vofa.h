#ifndef VOFA_H
#define VOFA_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uart2.h"
void send_to_vofa_fw(float *data, int num_channels);
#endif // VOFA_H
