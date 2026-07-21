/**
 * @file metronome_ui_gen.h
 */

#ifndef METRONOME_UI_GEN_H
#define METRONOME_UI_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
    #include "lvgl_private.h"
#else
    #include "lvgl/lvgl.h"
    #include "lvgl/lvgl_private.h"
#endif

#ifdef LV_USE_XML
    #include "lv_xml/lv_xml.h"
#endif



/* Prototypes for target functions, needed by responsive const definitions */

void metronome_ui_set_target(uint32_t target);
uint32_t metronome_ui_get_target(void);
bool metronome_ui_check_target(uint32_t target);

/*********************
 *      DEFINES
 *********************/

#define METRONOME_UI_TARGET_UNDEFINED  (0 << 1)
#define METRONOME_UI_TARGET_TARGET1    (1 << 1)
#define METRONOME_UI_TARGET_ALL        0x0FFFFFFF

/* By default compile for all targets, allowing to switch to any targets at runtime */
#ifndef METRONOME_UI_COMPILE_TARGET
#define METRONOME_UI_COMPILE_TARGET METRONOME_UI_TARGET_ALL
#endif

#define METRONOME_UI_CHECK_COMPILE_TARGET(target) (METRONOME_UI_COMPILE_TARGET & (target) ? 1 : 0)

/**
 * global BPM min value
 */
#define BPM_MIN 40
/**
 * global BPM max value
 */
#define BPM_MAX 200
/**
 * global beats min value
 */
#define BEATS_MIN 2
/**
 * global beats max value
 */
#define BEATS_MAX 7


#ifndef LV_XML_EVAL_STRING_BUF_SIZE
    #define LV_XML_EVAL_STRING_BUF_SIZE 256
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/*-------------------
 * Permanent screens
 *------------------*/

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Fonts
 *----------------*/

/* Targets: any */
extern lv_font_t * font_oxanium_semibold_16;
extern lv_font_t * font_oxanium_semibold_20;
extern lv_font_t * font_oxanium_semibold_25;
extern lv_font_t * font_gemunu_light_110;
extern lv_font_t * font_gemunu_light_130;
extern lv_font_t * font_gemunu_bold_20;
extern lv_font_t * font_gemunu_medium_60;


/*----------------
 * Images
 *----------------*/

/* Targets: any */
extern const void * img_note;
extern const void * img_play;
extern const void * img_pause;
extern const void * img_scale_gradient;
extern const void * img_lvgl_logo;

/*----------------
 * Subjects
 *----------------*/

extern lv_subject_t subject_bpm;
extern lv_subject_t subject_beats_per_measure;
extern lv_subject_t subject_current_beat;
extern lv_subject_t subject_play_pause;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*----------------
 * Event Callbacks
 *----------------*/

void on_bmp_scroll_cb(lv_event_t * e);
void bpm_scale_size_change_cb(lv_event_t * e);
void tap_tempo_clicked_cb(lv_event_t * e);
void toggle_panel_cb(lv_event_t * e);

/**
 * Initialize the component library
 */

void metronome_ui_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

/**********************
 *   POST INCLUDES
 **********************/

/*Include all the widgets, components and screens of this library*/
#include "components/beat_dot/beat_dot_gen.h"
#include "components/beat_setting/beat_setting_gen.h"
#include "components/bpm_scale/bpm_scale_gen.h"
#include "components/bpm_stepper/bpm_stepper_gen.h"
#include "components/tap_area/tap_area_gen.h"
#include "screens/screen_main/screen_main_gen.h"
#include "widgets/wd_beat_indicator/wd_beat_indicator_gen.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*METRONOME_UI_GEN_H*/