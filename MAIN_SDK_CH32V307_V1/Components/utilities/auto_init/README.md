# auto_init

`auto_init` provides an RT-Thread-style automatic initialization mechanism for this project.

## Features

- Registers init functions by linker section
- Executes them in level order during startup
- Keeps `main()` simple

## Init Levels

- `INIT_BOARD_EXPORT(fn)`: board-level initialization
- `INIT_PREV_EXPORT(fn)`: pre-device initialization
- `INIT_DEVICE_EXPORT(fn)`: device initialization
- `INIT_COMPONENT_EXPORT(fn)`: component initialization
- `INIT_ENV_EXPORT(fn)`: environment/service initialization
- `INIT_APP_EXPORT(fn)`: application initialization

## Function Signature

Registered functions must use:

```c
static int my_init(void)
{
    return 0;
}
```

Then export with one of the macros:

```c
#include "auto_init.h"

static int my_init(void)
{
    return 0;
}
INIT_COMPONENT_EXPORT(my_init);
```

## Startup Entry

Call the runner once during startup:

```c
#include "auto_init.h"

int main(void)
{
    auto_init_run();
    while (1) {
    }
}
```

## Notes

- Initialization order is controlled by the export macro level.
- Functions inside the same level run in linker order.
- Return values are collected; the first non-zero value is returned by `auto_init_run()`.
