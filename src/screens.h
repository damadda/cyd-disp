#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *scrch1;
    lv_obj_t *btn1;
    lv_obj_t *btn1l;
    lv_obj_t *btn2;
    lv_obj_t *btn2l;
    lv_obj_t *btn3;
    lv_obj_t *btn3l;
    lv_obj_t *btn4;
    lv_obj_t *btn4l;
    lv_obj_t *lbl1;
    lv_obj_t *lbl2;
    lv_obj_t *lbl3;
    lv_obj_t *lbl4;
    lv_obj_t *btns1;
    lv_obj_t *txtfeld;
    lv_obj_t *txt1;
    lv_obj_t *txt2;
    lv_obj_t *txt3;
    lv_obj_t *txt4;
    lv_obj_t *btnexit;
    lv_obj_t *obj0;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SCRCH1 = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_scrch1();
void tick_screen_scrch1();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/