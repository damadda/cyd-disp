#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // btn1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn1 = obj;
            lv_obj_set_pos(obj, 29, 45);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // btn1l
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.btn1l = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Button");
                    lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_RELEASED, (void *)0);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // btn2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn2 = obj;
            lv_obj_set_pos(obj, 191, 46);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // btn2l
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.btn2l = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Button");
                    lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_RELEASED, (void *)0);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // btn3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn3 = obj;
            lv_obj_set_pos(obj, 29, 141);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // btn3l
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.btn3l = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Button");
                    lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_RELEASED, (void *)0);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // btn4
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn4 = obj;
            lv_obj_set_pos(obj, 192, 141);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // btn4l
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.btn4l = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Button");
                    lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_RELEASED, (void *)0);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // lbl1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl1 = obj;
            lv_obj_set_pos(obj, 65, 96);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "t1");
        }
        {
            // lbl2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl2 = obj;
            lv_obj_set_pos(obj, 227, 97);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "t2");
        }
        {
            // lbl3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl3 = obj;
            lv_obj_set_pos(obj, 65, 192);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "t3");
        }
        {
            // lbl4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl4 = obj;
            lv_obj_set_pos(obj, 228, 193);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "t4");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 120, 13);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Timekeep");
        }
        {
            // btns1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btns1 = obj;
            lv_obj_set_pos(obj, 267, 5);
            lv_obj_set_size(obj, 49, 33);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "S1");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_main() {
}

void create_screen_scr1() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.scr1 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
    {
        lv_obj_t *parent_obj = obj;
        {
            // btnhome
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btnhome = obj;
            lv_obj_set_pos(obj, 27, 9);
            lv_obj_set_size(obj, 50, 39);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_CLICKED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Home");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // btnch1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btnch1 = obj;
            lv_obj_set_pos(obj, 25, 62);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Change BTN1");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // btnch2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btnch2 = obj;
            lv_obj_set_pos(obj, 196, 62);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Change BTN2");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // btnch3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btnch3 = obj;
            lv_obj_set_pos(obj, 25, 157);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Change BTN3");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // btnch4
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btnch4 = obj;
            lv_obj_set_pos(obj, 197, 158);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Change BTN4");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_scr1() {
}

void create_screen_scrch1() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.scrch1 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // txt1
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.txt1 = obj;
            lv_obj_set_pos(obj, 63, 49);
            lv_obj_set_size(obj, 195, 36);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_placeholder_text(obj, "BTN1 Change");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
        }
        {
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 10, 105);
            lv_obj_set_size(obj, 300, 120);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 41, 20);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Textfeld klicken zum akzeptieren");
        }
    }
    lv_keyboard_set_textarea(objects.obj0, objects.txt1);
}

void tick_screen_scrch1() {
}

void create_screen_scrch2() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.scrch2 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // txt2
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.txt2 = obj;
            lv_obj_set_pos(obj, 63, 49);
            lv_obj_set_size(obj, 195, 36);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_placeholder_text(obj, "BTN2 Change");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
        }
        {
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 10, 105);
            lv_obj_set_size(obj, 300, 120);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 41, 20);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Textfeld klicken zum akzeptieren");
        }
    }
    lv_keyboard_set_textarea(objects.obj1, objects.txt2);
}

void tick_screen_scrch2() {
}

void create_screen_scrch3() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.scrch3 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // txt3
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.txt3 = obj;
            lv_obj_set_pos(obj, 63, 49);
            lv_obj_set_size(obj, 195, 36);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_placeholder_text(obj, "BTN3 Change");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
        }
        {
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 10, 105);
            lv_obj_set_size(obj, 300, 120);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 41, 20);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Textfeld klicken zum akzeptieren");
        }
    }
    lv_keyboard_set_textarea(objects.obj2, objects.txt3);
}

void tick_screen_scrch3() {
}

void create_screen_scrch4() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.scrch4 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // txt4
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.txt4 = obj;
            lv_obj_set_pos(obj, 63, 49);
            lv_obj_set_size(obj, 195, 36);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_placeholder_text(obj, "BTN4 Change");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, action_set_global_eez_event, LV_EVENT_PRESSED, (void *)0);
        }
        {
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 10, 105);
            lv_obj_set_size(obj, 300, 120);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 41, 20);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Textfeld klicken zum akzeptieren");
        }
    }
    lv_keyboard_set_textarea(objects.obj3, objects.txt4);
}

void tick_screen_scrch4() {
}


void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_scr1();
    create_screen_scrch1();
    create_screen_scrch2();
    create_screen_scrch3();
    create_screen_scrch4();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_scr1,
    tick_screen_scrch1,
    tick_screen_scrch2,
    tick_screen_scrch3,
    tick_screen_scrch4,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
