/**
 * @file beat_dot_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "beat_dot_gen.h"
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

lv_obj_t * beat_dot_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_main;
    static lv_style_t style_active;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_main);
        lv_style_set_width(&style_main, 35);
        lv_style_set_height(&style_main, 35);
        lv_style_set_bg_color(&style_main, lv_color_hex(0xB6BABF));
        lv_style_set_border_width(&style_main, 0);
        lv_style_set_radius(&style_main, 35);

        lv_style_init(&style_active);
        lv_style_set_width(&style_active, 50);
        lv_style_set_height(&style_active, 50);
        lv_style_set_bg_color(&style_active, lv_color_hex(0x6DC868));
        lv_style_set_border_width(&style_active, 0);
        lv_style_set_radius(&style_active, 50);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(parent);

    lv_obj_add_style(lv_obj_0, &style_main, 0);

    LV_TRACE_OBJ_CREATE("finished");

    lv_obj_set_name(lv_obj_0, "beat_dot_#");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

