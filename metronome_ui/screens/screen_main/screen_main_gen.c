/**
 * @file screen_main_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "screen_main_gen.h"
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

lv_obj_t * screen_main_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_main;
    static lv_style_t style_button;
    static lv_style_t style_button_checked;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_main);
        lv_style_set_bg_color(&style_main, lv_color_hex(0xDADDE5));

        lv_style_init(&style_button);
        lv_style_set_bg_opa(&style_button, 0);
        lv_style_set_bg_color(&style_button, lv_color_hex(0xB8B8B8));
        lv_style_set_shadow_opa(&style_button, 0);
        lv_style_set_radius(&style_button, 250);
        lv_style_set_text_color(&style_button, lv_color_hex(0x495465));
        lv_style_set_pad_all(&style_button, 0);

        lv_style_init(&style_button_checked);
        lv_style_set_radius(&style_button_checked, 250);
        lv_style_set_bg_color(&style_button_checked, lv_color_hex(0xB8B8B8));

        style_inited = true;
    }

    lv_obj_t * screen_main = lv_obj_create(NULL);
    lv_obj_set_name_static(screen_main, "screen_main_#");
    lv_obj_set_name(screen_main, "screen_main");
    lv_obj_set_flag(screen_main, LV_OBJ_FLAG_SCROLLABLE, false);

    lv_obj_add_style(screen_main, &style_main, 0);
    lv_obj_t * lv_image_0 = lv_image_create(screen_main);
    lv_image_set_src(lv_image_0, img_lvgl_logo);
    lv_obj_set_align(lv_image_0, LV_ALIGN_TOP_MID);
    lv_obj_set_y(lv_image_0, 18);
    
    lv_obj_t * lv_label_0 = lv_label_create(screen_main);
    lv_label_set_text(lv_label_0, "METRONOME");
    lv_obj_set_style_text_font(lv_label_0, font_oxanium_semibold_20, 0);
    lv_obj_set_align(lv_label_0, LV_ALIGN_TOP_MID);
    lv_obj_set_y(lv_label_0, 60);
    lv_obj_set_style_text_color(lv_label_0, lv_color_hex(0x878F9A), 0);
    
    lv_obj_t * wd_beat_indicator_0 = wd_beat_indicator_create(screen_main);
    lv_obj_set_align(wd_beat_indicator_0, LV_ALIGN_TOP_MID);
    lv_obj_set_y(wd_beat_indicator_0, 110);
    
    lv_obj_t * bpm_stepper_0 = bpm_stepper_create(screen_main);
    lv_obj_set_align(bpm_stepper_0, LV_ALIGN_CENTER);
    
    lv_obj_t * bpm_scale = bpm_scale_create(screen_main);
    lv_obj_set_name(bpm_scale, "bpm_scale");
    lv_obj_set_align(bpm_scale, LV_ALIGN_CENTER);
    lv_obj_set_y(bpm_scale, 105);
    
    lv_obj_t * button_tap_tempo = lv_button_create(screen_main);
    lv_obj_set_name(button_tap_tempo, "button_tap_tempo");
    lv_obj_set_width(button_tap_tempo, 60);
    lv_obj_set_height(button_tap_tempo, 60);
    lv_obj_set_x(button_tap_tempo, 120);
    lv_obj_set_y(button_tap_tempo, 383);
    lv_obj_set_flag(button_tap_tempo, LV_OBJ_FLAG_CHECKABLE, true);
    lv_obj_add_style(button_tap_tempo, &style_button, 0);
    lv_obj_add_style(button_tap_tempo, &style_button_checked, LV_STATE_CHECKED);
    lv_obj_t * lv_label_1 = lv_label_create(button_tap_tempo);
    lv_label_set_text(lv_label_1, "TAP");
    lv_obj_set_style_text_font(lv_label_1, font_oxanium_semibold_20, 0);
    lv_obj_set_style_text_color(lv_label_1, lv_color_hex(0x71777A), 0);
    lv_obj_set_align(lv_label_1, LV_ALIGN_CENTER);
    lv_obj_set_style_pad_top(lv_label_1, 3, 0);
    
    lv_obj_add_event_cb(button_tap_tempo, toggle_panel_cb, LV_EVENT_VALUE_CHANGED, "tap_area");
    
    lv_obj_t * button_beat_setting = lv_button_create(screen_main);
    lv_obj_set_name(button_beat_setting, "button_beat_setting");
    lv_obj_set_width(button_beat_setting, 60);
    lv_obj_set_height(button_beat_setting, 60);
    lv_obj_set_x(button_beat_setting, 310);
    lv_obj_set_y(button_beat_setting, 379);
    lv_obj_set_flag(button_beat_setting, LV_OBJ_FLAG_CHECKABLE, true);
    lv_obj_add_style(button_beat_setting, &style_button, 0);
    lv_obj_add_style(button_beat_setting, &style_button_checked, LV_STATE_CHECKED);
    lv_obj_t * lv_image_1 = lv_image_create(button_beat_setting);
    lv_image_set_src(lv_image_1, img_note);
    lv_obj_set_align(lv_image_1, LV_ALIGN_CENTER);
    
    lv_obj_add_event_cb(button_beat_setting, toggle_panel_cb, LV_EVENT_VALUE_CHANGED, "beat_setting");
    
    lv_obj_t * lv_button_0 = lv_button_create(screen_main);
    lv_obj_set_width(lv_button_0, 60);
    lv_obj_set_height(lv_button_0, 60);
    lv_obj_set_x(lv_button_0, 210);
    lv_obj_set_y(lv_button_0, 407);
    lv_obj_add_subject_toggle_event(lv_button_0, &subject_play_pause, LV_EVENT_CLICKED);
    lv_obj_add_style(lv_button_0, &style_button, 0);
    lv_obj_t * lv_image_2 = lv_image_create(lv_button_0);
    lv_image_set_src(lv_image_2, img_play);
    lv_obj_set_align(lv_image_2, LV_ALIGN_CENTER);
    lv_obj_bind_flag_if_eq(lv_image_2, &subject_play_pause, LV_OBJ_FLAG_HIDDEN, 1);
    
    lv_obj_t * lv_image_3 = lv_image_create(lv_button_0);
    lv_image_set_src(lv_image_3, img_pause);
    lv_obj_set_align(lv_image_3, LV_ALIGN_CENTER);
    lv_obj_bind_flag_if_eq(lv_image_3, &subject_play_pause, LV_OBJ_FLAG_HIDDEN, 0);
    
    lv_obj_t * tap_area = tap_area_create(screen_main);
    lv_obj_set_name(tap_area, "tap_area");
    lv_obj_set_align(tap_area, LV_ALIGN_LEFT_MID);
    lv_obj_set_x(tap_area, -420);
    
    lv_obj_t * beat_setting = beat_setting_create(screen_main);
    lv_obj_set_name(beat_setting, "beat_setting");
    lv_obj_set_align(beat_setting, LV_ALIGN_RIGHT_MID);
    lv_obj_set_x(beat_setting, 420);

    LV_TRACE_OBJ_CREATE("finished");

    return screen_main;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

