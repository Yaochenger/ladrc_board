/**
 * @file auto_init.h
 * @brief RT-Thread style automatic initialization support.
 */

#ifndef COMPONENTS_UTILITIES_AUTO_INIT_AUTO_INIT_H_
#define COMPONENTS_UTILITIES_AUTO_INIT_AUTO_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*auto_init_fn_t)(void);

typedef struct
{
    auto_init_fn_t fn;
    const char *name;
} auto_init_entry_t;

#if defined(__CC_ARM) || defined(__CLANG_ARM) || defined(__GNUC__)
#define AUTO_INIT_SECTION(x) __attribute__((section(x), used))
#elif defined(__IAR_SYSTEMS_ICC__)
#define AUTO_INIT_SECTION(x) @ x
#define AUTO_INIT_USED __root
#else
#define AUTO_INIT_SECTION(x)
#define AUTO_INIT_USED
#endif

#ifndef AUTO_INIT_USED
#define AUTO_INIT_USED
#endif

#define AUTO_INIT_EXPORT(fn, level) \
    AUTO_INIT_USED const auto_init_entry_t auto_init_##fn AUTO_INIT_SECTION(".auto_init_fn." level) = {fn, #fn}

#define INIT_BOARD_EXPORT(fn)         AUTO_INIT_EXPORT(fn, "1")
#define INIT_PREV_EXPORT(fn)          AUTO_INIT_EXPORT(fn, "2")
#define INIT_DEVICE_EXPORT(fn)        AUTO_INIT_EXPORT(fn, "3")
#define INIT_COMPONENT_EXPORT(fn)     AUTO_INIT_EXPORT(fn, "4")
#define INIT_ENV_EXPORT(fn)           AUTO_INIT_EXPORT(fn, "5")
#define INIT_APP_EXPORT(fn)           AUTO_INIT_EXPORT(fn, "6")

int auto_init_run(void);

#ifdef __cplusplus
}
#endif

#endif /* COMPONENTS_UTILITIES_AUTO_INIT_AUTO_INIT_H_ */
