# MultiTimer

## Introduction
MultiTimer is a software timer extension module that allows for the expansion of timer tasks as needed, replacing the traditional flag-checking method. It offers a more elegant and convenient way to manage the timing sequences of a program.

## How to Use
1. Configure the system time base interface and install the timer driver:

```c
uint64_t PlatformTicksGetFunc(void)
{
    /* Platform-specific implementation */
}

multiTimerInstall(PlatformTicksGetFunc);
```

2. Instantiate a timer object:

```c
MultiTimer timer1;
```

3. Set the timing, timeout callback function, user data pointer, and start the timer:

```c
int multiTimerStart(MultiTimer* timer, uint64_t timing, MultiTimerCallback_t callback, void* userData);
```

4. Call the timer background processing function in the main loop:

```c
int main(int argc, char *argv[])
{
    ...
    while (1) {
        ...
        multiTimerYield();
    }
}
```

## Limitations
1. The clock frequency of the timer directly affects its accuracy. It is recommended to use ticks with higher precision such as 1ms, 5ms, or 10ms.

2. The callback function of the timer should not perform time-consuming operations, as this may occupy too much time, causing other timers to not timeout properly.

3. Since the timer's callback function is executed within `multiTimerYield`, care should be taken not to use too much stack space to avoid stack overflow.

## Example
The `test_linux.c` file serves as a demo for Linux platforms, showcasing how to use MultiTimer for creating and managing multiple timers with different intervals and behaviors.

```c
#include "MultiTimer.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

// Platform-specific function to get current ticks (milliseconds)
uint64_t getPlatformTicks() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 1000LL + now.tv_usec / 1000;
}

// Callback functions for the timers
void timerCallback1(MultiTimer* timer, void* userData) {
    printf("Timer 1 fired at %lu ms\n", getPlatformTicks());
    multiTimerStart(timer, 500, timerCallback1, NULL); // Restart timer
}

void timerCallback2(MultiTimer* timer, void* userData) {
    printf("Timer 2 fired at %lu ms\n", getPlatformTicks());
    multiTimerStart(timer, 1000, timerCallback2, NULL); // Restart timer
}

void timerCallback3(MultiTimer* timer, void* userData) {
    printf("Timer 3 (one-shot) fired at %lu ms\n", getPlatformTicks());
}

void timerCallback4(MultiTimer* timer, void* userData) {
    printf("Timer 4 is stopping Timer 1 at %lu ms\n", getPlatformTicks());
    multiTimerStop((MultiTimer*)userData);
}

int main() {
    multiTimerInstall(getPlatformTicks);

    MultiTimer timer1, timer2, timer3, timer4;

    multiTimerStart(&timer1, 500, timerCallback1, NULL); // 500 ms repeating
    multiTimerStart(&timer2, 1000, timerCallback2, NULL); // 1000 ms repeating
    multiTimerStart(&timer3, 2000, timerCallback3, NULL); // 2000 ms one-shot
    multiTimerStart(&timer4, 3000, timerCallback4, &timer1); // 3000 ms, stops timer1

    // Main loop to simulate time passage and process timers
    while (1) {
        multiTimerYield();
        usleep(1000); // Sleep for 1 ms
    }

    return 0;
}
```
