/**
 * @file auto_init.c
 * @brief RT-Thread style automatic initialization runner.
 */

#include "auto_init.h"
#include <stdio.h>

extern const auto_init_entry_t __auto_init_start[];
extern const auto_init_entry_t __auto_init_end[];

int auto_init_run(void) {
    int result = 0;
    int index = 0;
    const auto_init_entry_t *entry;

    for (entry = __auto_init_start; entry < __auto_init_end; entry++) {
        if (entry->fn != 0) {
            int ret = entry->fn();

            if ((ret != 0) && (result == 0)) {
                result = ret;
            }
            index++;
        }
    }
    
    return result;
}
