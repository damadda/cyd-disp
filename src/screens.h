#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *scr1;
    lv_obj_t *scrch1;
    lv_obj_t *scrch2;
    lv_obj_t *scrch3;
    lv_obj_t *scrch4;
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
    lv_obj_t *btnhome;
    lv_obj_t *btnch1;
    lv_obj_t *btnch2;
    lv_obj_t *btnch3;
    lv_obj_t *btnch4;
    lv_obj_t *txt1;
    lv_obj_t *obj0;
    lv_obj_t *txt2;
    lv_obj_t *obj1;
    lv_obj_t *txt3;
    lv_obj_t *obj2;
    lv_obj_t *txt4;
    lv_obj_t *obj3;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SCR1 = 2,
    SCREEN_ID_SCRCH1 = 3,
    SCREEN_ID_SCRCH2 = 4,
    SCREEN_ID_SCRCH3 = 5,
    SCREEN_ID_SCRCH4 = 6,
};

void create_screen_main();
void tick_screen_main();

void create_screen_scr1();
void tick_screen_scr1();

void create_screen_scrch1();
void tick_screen_scrch1();

void create_screen_scrch2();
void tick_screen_scrch2();

void create_screen_scrch3();
void tick_screen_scrch3();

void create_screen_scrch4();
void tick_screen_scrch4();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/