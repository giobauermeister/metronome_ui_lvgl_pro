/**
 * @file tap_area_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "tap_area_gen.h"
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

lv_obj_t * tap_area_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    lv_obj_t * lv_obj_0 = lv_obj_create(parent);
    lv_obj_set_name_static(lv_obj_0, "tap_area_#");
    lv_obj_set_width(lv_obj_0, 350);
    lv_obj_set_height(lv_obj_0, 350);
    lv_obj_set_style_radius(lv_obj_0, 250, 0);
    lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0xB8B8B8), 0);
    lv_obj_set_style_border_width(lv_obj_0, 0, 0);
    lv_obj_set_align(lv_obj_0, LV_ALIGN_CENTER);

    lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
    lv_obj_set_style_text_align(lv_label_0, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(lv_label_0, 90);
    lv_label_set_text(lv_label_0, "TAP TEMPO");
    lv_obj_set_style_text_font(lv_label_0, font_oxanium_semibold_25, 0);
    lv_obj_set_style_text_color(lv_label_0, lv_color_hex(0x666C70), 0);
    lv_obj_set_align(lv_label_0, LV_ALIGN_RIGHT_MID);
    lv_obj_set_x(lv_label_0, -7);
    
    lv_obj_add_event_cb(lv_obj_0, tap_tempo_clicked_cb, LV_EVENT_CLICKED, NULL);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

