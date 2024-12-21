#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_T1 = 0,
    FLOW_GLOBAL_VARIABLE_T2 = 1,
    FLOW_GLOBAL_VARIABLE_T3 = 2,
    FLOW_GLOBAL_VARIABLE_T4 = 3
};

// Native global variables

extern int32_t get_var_t1();
extern void set_var_t1(int32_t value);
extern int32_t get_var_t2();
extern void set_var_t2(int32_t value);
extern int32_t get_var_t3();
extern void set_var_t3(int32_t value);
extern int32_t get_var_t4();
extern void set_var_t4(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/