# SFUD使用日志

## 1.不修改 SFUD_FLASH_DEVICE_TABLE

```c
#ifndef _SFUD_CFG_H_
#define _SFUD_CFG_H_

#define SFUD_DEBUG_MODE

#define SFUD_USING_SFDP

// #define SFUD_USING_FAST_READ

#define SFUD_USING_FLASH_INFO_TABLE

enum {
    SFUD_XXXX_DEVICE_INDEX = 0,
};

#define SFUD_FLASH_DEVICE_TABLE                                                \
{                                                                              \
    [SFUD_XXXX_DEVICE_INDEX] = {.name = "XXXX", .spi.name = "SPIX"},           \
}

#define SFUD_USING_QSPI

#endif /* _SFUD_CFG_H_ */

```

只支持遵循**SFDP** 格式的`FLASH`，无法打印输出`FLASH`具体型号；

```shell

 _         _   _                  _          _ _
| |    ___| |_| |_ ___ _ __   ___| |__   ___| | |
| |   / _ \ __| __/ _ \ '__| / __| '_ \ / _ \ | |
| |__|  __/ |_| ||  __/ |    \__ \ | | |  __/ | |
|_____\___|\__|\__\___|_|    |___/_| |_|\___|_|_|

Build:       Apr  5 2024 08:53:42
Version:     3.2.3
Copyright:   (c) 2020 Letter

Ladrc:/$ ID ef4015
[SFUD](../User_Peripheral_Driver/sfud/src/sfud.c:116) Start initialize Serial Flash Universal Driver(SFUD) V1.1.0.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud.c:117) You can get the latest version on https://github.com/armink/SFUD .
[SFUD](../User_Peripheral_Driver/sfud/src/sfud.c:881) The flash device manufacturer ID is 0xEF, memory type ID is 0x40, capacity ID is 0x15.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:132) Check SFDP header is OK. The reversion is V1.5, NPN is 0.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:175) Check JEDEC basic flash parameter header is OK. The table id is 0, reversion is V1.5, length is 16, parameter table pointer is 0x000080.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:203) JEDEC basic flash parameter table info:
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:204) MSB-LSB  3    2    1    0
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0001] 0xFF 0xF9 0x20 0xE5
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0002] 0x00 0xFF 0xFF 0xFF
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0003] 0x6B 0x08 0xEB 0x44
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0004] 0xBB 0x42 0x3B 0x08
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0005] 0xFF 0xFF 0xFF 0xFE
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0006] 0x00 0x00 0xFF 0xFF
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0007] 0xEB 0x40 0xFF 0xFF
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0008] 0x52 0x0F 0x20 0x0C
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0009] 0x00 0x00 0xD8 0x10
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:215) 4 KB Erase is supported throughout the device. Command is 0x20.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:234) Write granularity is 64 bytes or larger.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:245) Target flash status register is non-volatile.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:271) 3-Byte only addressing.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:305) Capacity is 2097152 Bytes.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:312) Flash device supports 4KB block erase. Command is 0x20.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:312) Flash device supports 32KB block erase. Command is 0x52.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:312) Flash device supports 64KB block erase. Command is 0xD8.
[SFUD]Found a Winbond flash chip. Size is 2097152 bytes.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud.c:859) Flash device reset success.
[SFUD]XXXX flash device initialized successfully.

```

## 2.修改 SFUD_FLASH_DEVICE_TABLE

```c
#ifndef _SFUD_CFG_H_
#define _SFUD_CFG_H_

#define SFUD_DEBUG_MODE

#define SFUD_USING_SFDP

// #define SFUD_USING_FAST_READ

#define SFUD_USING_FLASH_INFO_TABLE

enum {
    SFUD_W25Q16_DEVICE_INDEX  = 0,
};

#define SFUD_FLASH_DEVICE_TABLE                                                \
{                                                                              \
    [SFUD_W25Q16_DEVICE_INDEX ] = {.name = "W25Q16JV", .spi.name = "SPI2"},    \
}

//#define SFUD_USING_QSPI

#endif /* _SFUD_CFG_H_ */
```

首先检查`FLASH`信息表：`SFUD_FLASH_DEVICE_TABLE`，若未找到，在查询支持遵循**SFDP** 格式的`FLASH`，可以打印`FLASH`具体型号；

```shell

 _         _   _                  _          _ _
| |    ___| |_| |_ ___ _ __   ___| |__   ___| | |
| |   / _ \ __| __/ _ \ '__| / __| '_ \ / _ \ | |
| |__|  __/ |_| ||  __/ |    \__ \ | | |  __/ | |
|_____\___|\__|\__\___|_|    |___/_| |_|\___|_|_|

Build:       Apr  5 2024 08:46:36
Version:     3.2.3
Copyright:   (c) 2020 Letter

Ladrc:/$ ID ef4015
[SFUD](../User_Peripheral_Driver/sfud/src/sfud.c:116) Start initialize Serial Flash Universal Driver(SFUD) V1.1.0.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud.c:117) You can get the latest version on https://github.com/armink/SFUD .
[SFUD](../User_Peripheral_Driver/sfud/src/sfud.c:881) The flash device manufacturer ID is 0xEF, memory type ID is 0x40, capacity ID is 0x15.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:132) Check SFDP header is OK. The reversion is V1.5, NPN is 0.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:175) Check JEDEC basic flash parameter header is OK. The table id is 0, reversion is V1.5, length is 16, parameter table pointer is 0x000080.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:203) JEDEC basic flash parameter table info:
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:204) MSB-LSB  3    2    1    0
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0001] 0xFF 0xF9 0x20 0xE5
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0002] 0x00 0xFF 0xFF 0xFF
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0003] 0x6B 0x08 0xEB 0x44
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0004] 0xBB 0x42 0x3B 0x08
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0005] 0xFF 0xFF 0xFF 0xFE
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0006] 0x00 0x00 0xFF 0xFF
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0007] 0xEB 0x40 0xFF 0xFF
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0008] 0x52 0x0F 0x20 0x0C
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:207) [0009] 0x00 0x00 0xD8 0x10
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:215) 4 KB Erase is supported throughout the device. Command is 0x20.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:234) Write granularity is 64 bytes or larger.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:245) Target flash status register is non-volatile.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:271) 3-Byte only addressing.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:305) Capacity is 2097152 Bytes.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:312) Flash device supports 4KB block erase. Command is 0x20.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:312) Flash device supports 32KB block erase. Command is 0x52.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud_sfdp.c:312) Flash device supports 64KB block erase. Command is 0xD8.
[SFUD]Found a Winbond flash chip. Size is 2097152 bytes.
[SFUD](../User_Peripheral_Driver/sfud/src/sfud.c:859) Flash device reset success.
[SFUD]W25Q16JV flash device initialized successfully.
```

