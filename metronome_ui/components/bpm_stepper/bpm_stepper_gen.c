/**
 * @file bpm_stepper_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "bpm_stepper_gen.h"
#include "metronome_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * bpm_stepper_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_main;
    static lv_style_t no_style;
    static lv_style_t style_button;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_main);
        lv_style_set_bg_color(&style_main, lv_color_hex(0x495465));
        lv_style_set_border_width(&style_main, 0);

        lv_style_init(&no_style);
        lv_style_set_bg_opa(&no_style, 0);
        lv_style_set_border_width(&no_style, 0);
        lv_style_set_pad_all(&no_style, 0);

        lv_style_init(&style_button);
        lv_style_set_bg_opa(&style_button, 0);
        lv_style_set_shadow_opa(&style_button, 0);
        lv_style_set_text_color(&style_button, lv_color_hex(0x495465));

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(parent);
    lv_obj_set_width(lv_obj_0, 400);
    lv_obj_set_height(lv_obj_0, 141);
    lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);

    lv_obj_add_style(lv_obj_0, &no_style, 0);
    lv_obj_t * lv_button_0 = lv_button_create(lv_obj_0);
    lv_obj_set_width(lv_button_0, 70);
    lv_obj_set_align(lv_button_0, LV_ALIGN_LEFT_MID);
    lv_obj_add_style(lv_button_0, &style_button, 0);
    lv_obj_t * lv_label_0 = lv_label_create(lv_button_0);
    lv_label_set_text(lv_label_0, "-");
    lv_obj_set_style_text_font(lv_label_0, font_gemunu_light_110, 0);
    lv_obj_set_align(lv_label_0, LV_ALIGN_CENTER);
    
    lv_obj_add_subject_increment_event(lv_button_0, &subject_bpm, LV_EVENT_CLICKED, -1, false);
    
    lv_obj_t * lv_label_1 = lv_label_create(lv_obj_0);
    lv_label_bind_text(lv_label_1, &subject_bpm, NULL);
    lv_obj_set_style_text_font(lv_label_1, font_gemunu_light_130, 0);
    lv_obj_set_align(lv_label_1, LV_ALIGN_CENTER);
    
    lv_obj_t * lv_label_2 = lv_label_create(lv_obj_0);
    lv_label_set_text(lv_label_2, "BPM");
    lv_obj_set_style_text_font(lv_label_2, font_oxanium_semibold_20, 0);
    lv_obj_set_style_text_color(lv_label_2, lv_color_hex(0x878F9A), 0);
    lv_obj_set_align(lv_label_2, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_y(lv_label_2, 5);
    
    lv_obj_t * lv_button_1 = lv_button_create(lv_obj_0);
    lv_obj_set_width(lv_button_1, 70);
    lv_obj_set_align(lv_button_1, LV_ALIGN_RIGHT_MID);
    lv_obj_add_style(lv_button_1, &style_button, 0);
    lv_obj_t * lv_label_3 = lv_label_create(lv_button_1);
    lv_label_set_text(lv_label_3, "+");
    lv_obj_set_style_text_font(lv_label_3, font_gemunu_light_110, 0);
    lv_obj_set_align(lv_label_3, LV_ALIGN_CENTER);
    
    lv_obj_add_subject_increment_event(lv_button_1, &subject_bpm, LV_EVENT_CLICKED, 1, false);

    LV_TRACE_OBJ_CREATE("finished");

    lv_obj_set_name(lv_obj_0, "bpm_stepper_#");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

