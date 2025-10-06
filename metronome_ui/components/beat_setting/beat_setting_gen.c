/**
 * @file beat_setting_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "beat_setting_gen.h"
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

lv_obj_t * beat_setting_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_arc_bg;
    static lv_style_t style_arc_knob;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_arc_bg);
        lv_style_set_arc_color(&style_arc_bg, lv_color_hex(0x666C70));

        lv_style_init(&style_arc_knob);
        lv_style_set_pad_all(&style_arc_knob, 12);
        lv_style_set_bg_color(&style_arc_knob, lv_color_hex(0x4CF543));

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(parent);
    lv_obj_set_width(lv_obj_0, 350);
    lv_obj_set_height(lv_obj_0, 350);
    lv_obj_set_style_radius(lv_obj_0, 250, 0);
    lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0xB8B8B8), 0);
    lv_obj_set_style_border_width(lv_obj_0, 0, 0);
    lv_obj_set_align(lv_obj_0, LV_ALIGN_CENTER);

    lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
    lv_label_bind_text(lv_label_0, &subject_beats_per_measure, NULL);
    lv_obj_set_style_text_font(lv_label_0, font_gemunu_medium_60, 0);
    lv_obj_set_style_text_color(lv_label_0, lv_color_hex(0x666C70), 0);
    lv_obj_set_align(lv_label_0, LV_ALIGN_LEFT_MID);
    lv_obj_set_x(lv_label_0, 25);
    
    lv_obj_t * lv_arc_0 = lv_arc_create(lv_obj_0);
    lv_arc_bind_value(lv_arc_0, &subject_beats_per_measure);
    lv_obj_set_align(lv_arc_0, LV_ALIGN_LEFT_MID);
    lv_obj_set_x(lv_arc_0, -202);
    lv_obj_set_width(lv_arc_0, 300);
    lv_obj_set_height(lv_arc_0, 300);
    lv_arc_set_rotation(lv_arc_0, -40);
    lv_arc_set_start_angle(lv_arc_0, 0);
    lv_arc_set_end_angle(lv_arc_0, 80);
    lv_arc_set_bg_start_angle(lv_arc_0, 0);
    lv_arc_set_bg_end_angle(lv_arc_0, 80);
    lv_arc_set_min_value(lv_arc_0, 2);
    lv_arc_set_max_value(lv_arc_0, 7);
    lv_arc_set_mode(lv_arc_0, LV_ARC_MODE_REVERSE);
    lv_obj_add_style(lv_arc_0, &style_arc_bg, LV_PART_MAIN);
    lv_obj_add_style(lv_arc_0, &style_arc_bg, LV_PART_INDICATOR);
    lv_obj_add_style(lv_arc_0, &style_arc_knob, LV_PART_KNOB);

    LV_TRACE_OBJ_CREATE("finished");

    lv_obj_set_name(lv_obj_0, "beat_setting_#");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

