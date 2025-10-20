/**
 * @file bpm_scale_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "bpm_scale_gen.h"
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

lv_obj_t * bpm_scale_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_scroll_container;
    static lv_style_t style_major_ticks;
    static lv_style_t style_minor_ticks;
    static lv_style_t style_main_line;
    static lv_style_t style_scrollbar;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_scroll_container);
        lv_style_set_bg_opa(&style_scroll_container, 0);
        lv_style_set_border_width(&style_scroll_container, 0);

        lv_style_init(&style_major_ticks);
        lv_style_set_length(&style_major_ticks, 26);
        lv_style_set_line_width(&style_major_ticks, 4);
        lv_style_set_line_color(&style_major_ticks, lv_color_hex(0x6DC868));
        lv_style_set_pad_top(&style_major_ticks, 8);

        lv_style_init(&style_minor_ticks);
        lv_style_set_length(&style_minor_ticks, 15);
        lv_style_set_line_width(&style_minor_ticks, 2);
        lv_style_set_line_color(&style_minor_ticks, lv_color_hex(0x71777A));

        lv_style_init(&style_main_line);
        lv_style_set_line_width(&style_main_line, 0);

        lv_style_init(&style_scrollbar);
        lv_style_set_width(&style_scrollbar, 0);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(parent);
    lv_obj_set_name_static(lv_obj_0, "bpm_scale_#");
    lv_obj_set_width(lv_obj_0, 460);
    lv_obj_set_height(lv_obj_0, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

    lv_obj_add_style(lv_obj_0, &style_scroll_container, 0);
    lv_obj_t * bpm_scroll_scale = lv_obj_create(lv_obj_0);
    lv_obj_set_name(bpm_scroll_scale, "bpm_scroll_scale");
    lv_obj_set_width(bpm_scroll_scale, 415);
    lv_obj_set_height(bpm_scroll_scale, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(bpm_scroll_scale, 0, 0);
    lv_obj_set_style_pad_left(bpm_scroll_scale, 230, 0);
    lv_obj_set_style_pad_right(bpm_scroll_scale, 190, 0);
    lv_obj_add_style(bpm_scroll_scale, &style_scroll_container, 0);
    lv_obj_add_style(bpm_scroll_scale, &style_scrollbar, LV_PART_SCROLLBAR);
    lv_obj_t * lv_scale_0 = lv_scale_create(bpm_scroll_scale);
    lv_obj_set_height(lv_scale_0, 50);
    lv_scale_set_min_value(lv_scale_0, 40);
    lv_scale_set_max_value(lv_scale_0, 200);
    lv_scale_set_mode(lv_scale_0, LV_SCALE_MODE_HORIZONTAL_TOP);
    lv_scale_set_total_tick_count(lv_scale_0, 161);
    lv_scale_set_major_tick_every(lv_scale_0, 10);
    lv_obj_set_width(lv_scale_0, 2400);
    lv_obj_set_style_text_font(lv_scale_0, font_gemunu_bold_20, 0);
    lv_obj_set_style_text_color(lv_scale_0, lv_color_hex(0x878F9A), 0);
    lv_obj_add_style(lv_scale_0, &style_major_ticks, LV_PART_INDICATOR);
    lv_obj_add_style(lv_scale_0, &style_minor_ticks, LV_PART_ITEMS);
    lv_obj_add_style(lv_scale_0, &style_main_line, LV_PART_MAIN);
    
    lv_obj_add_event_cb(bpm_scroll_scale, on_bmp_scroll_cb, LV_EVENT_SCROLL, NULL);
    lv_obj_add_event_cb(bpm_scroll_scale, bpm_scale_size_change_cb, LV_EVENT_SIZE_CHANGED, NULL);
    
    lv_obj_t * lv_image_0 = lv_image_create(lv_obj_0);
    lv_image_set_src(lv_image_0, img_scale_gradient);
    lv_obj_set_align(lv_image_0, LV_ALIGN_BOTTOM_LEFT);
    
    lv_obj_t * lv_image_1 = lv_image_create(lv_obj_0);
    lv_image_set_src(lv_image_1, img_scale_gradient);
    lv_obj_set_align(lv_image_1, LV_ALIGN_BOTTOM_RIGHT);
    lv_image_set_rotation(lv_image_1, 1800);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

