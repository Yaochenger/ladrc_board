/**
 * @file shell_ext.h
 * @author Letter (NevermindZZT@gmail.com)
 * @brief Shell extension interface.
 * @version 3.0.0
 * @date 2019-12-31
 *
 * @copyright (c) 2019 Letter
 */

#ifndef __SHELL_EXT_H__
#define __SHELL_EXT_H__

#include "shell.h"
#include "stdio.h"

/**
 * @brief Numeric parameter type.
 */
typedef enum
{
    NUM_TYPE_DEC,                                           /**< Decimal integer. */
    NUM_TYPE_BIN,                                           /**< Binary integer. */
    NUM_TYPE_OCT,                                           /**< Octal integer. */
    NUM_TYPE_HEX,                                           /**< Hexadecimal integer. */
    NUM_TYPE_FLOAT                                          /**< Floating-point value. */
} ShellNumType;

#if SHELL_SUPPORT_ARRAY_PARAM == 1
typedef struct
{
    unsigned short size;
    unsigned char elementBytes;
} ShellArrayHeader;
#endif /* SHELL_SUPPORT_ARRAY_PARAM == 1 */

int shellExtParsePara(Shell *shell, char *string, char *type, size_t *result);
#if SHELL_USING_FUNC_SIGNATURE == 1
int shellExtCleanerPara(Shell *shell, char *type, size_t param);
#endif /* SHELL_USING_FUNC_SIGNATURE == 1 */
#if SHELL_SUPPORT_ARRAY_PARAM == 1
int shellGetArrayParamSize(void *param);
#endif /* SHELL_SUPPORT_ARRAY_PARAM == 1 */
int shellExtRun(Shell *shell, ShellCommand *command, int argc, char *argv[]);

#endif /* __SHELL_EXT_H__ */
