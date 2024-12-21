#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *pg1;
    lv_obj_t *btn1;
    lv_obj_t *btn2;
    lv_obj_t *btn3;
    lv_obj_t *btn4;
    lv_obj_t *txt1;
    lv_obj_t *txt2;
    lv_obj_t *txt3;
    lv_obj_t *txt4;
    lv_obj_t *txt5;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_PG1 = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_pg1();
void tick_screen_pg1();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/