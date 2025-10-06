/**
 * @file metronome_ui_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "metronome_ui_gen.h"

#if LV_USE_XML
#include "widgets/wd_beat_indicator/wd_beat_indicator_private_gen.h"
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/*----------------
 * Translations
 *----------------*/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Fonts
 *----------------*/

lv_font_t * font_oxanium_semibold_16;
extern lv_font_t font_oxanium_semibold_16_data;
lv_font_t * font_oxanium_semibold_20;
extern lv_font_t font_oxanium_semibold_20_data;
lv_font_t * font_oxanium_semibold_25;
extern lv_font_t font_oxanium_semibold_25_data;
lv_font_t * font_gemunu_light_110;
extern lv_font_t font_gemunu_light_110_data;
lv_font_t * font_gemunu_light_130;
extern lv_font_t font_gemunu_light_130_data;
lv_font_t * font_gemunu_bold_20;
extern lv_font_t font_gemunu_bold_20_data;
lv_font_t * font_gemunu_medium_60;
extern lv_font_t font_gemunu_medium_60_data;

/*----------------
 * Images
 *----------------*/

const void * img_note;
extern const void * img_note_data;
const void * img_play;
extern const void * img_play_data;
const void * img_pause;
extern const void * img_pause_data;
const void * img_scale_gradient;
extern const void * img_scale_gradient_data;
const void * img_lvgl_logo;
extern const void * img_lvgl_logo_data;

/*----------------
 * Subjects
 *----------------*/

lv_subject_t subject_bpm;
lv_subject_t subject_beats_per_measure;
lv_subject_t subject_current_beat;
lv_subject_t subject_play_pause;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void metronome_ui_init_gen(const char * asset_path)
{
    char buf[256];

    /*----------------
     * Global styles
     *----------------*/

    /*----------------
     * Fonts
     *----------------*/

    /* get font 'font_oxanium_semibold_16' from a C array */
    font_oxanium_semibold_16 = &font_oxanium_semibold_16_data;
    /* get font 'font_oxanium_semibold_20' from a C array */
    font_oxanium_semibold_20 = &font_oxanium_semibold_20_data;
    /* get font 'font_oxanium_semibold_25' from a C array */
    font_oxanium_semibold_25 = &font_oxanium_semibold_25_data;
    /* get font 'font_gemunu_light_110' from a C array */
    font_gemunu_light_110 = &font_gemunu_light_110_data;
    /* get font 'font_gemunu_light_130' from a C array */
    font_gemunu_light_130 = &font_gemunu_light_130_data;
    /* get font 'font_gemunu_bold_20' from a C array */
    font_gemunu_bold_20 = &font_gemunu_bold_20_data;
    /* get font 'font_gemunu_medium_60' from a C array */
    font_gemunu_medium_60 = &font_gemunu_medium_60_data;


    /*----------------
     * Images
     *----------------*/
    img_note = &img_note_data;
    img_play = &img_play_data;
    img_pause = &img_pause_data;
    img_scale_gradient = &img_scale_gradient_data;
    img_lvgl_logo = &img_lvgl_logo_data;

    /*----------------
     * Subjects
     *----------------*/
    lv_subject_init_int(&subject_bpm, 40);
    lv_subject_set_min_value_int(&subject_bpm, 40);
    lv_subject_set_max_value_int(&subject_bpm, 200);
    lv_subject_init_int(&subject_beats_per_measure, 4);
    lv_subject_set_min_value_int(&subject_beats_per_measure, 2);
    lv_subject_set_max_value_int(&subject_beats_per_measure, 7);
    lv_subject_init_int(&subject_current_beat, -1);
    lv_subject_set_min_value_int(&subject_current_beat, -1);
    lv_subject_set_max_value_int(&subject_current_beat, 6);
    lv_subject_init_int(&subject_play_pause, 0);
    lv_subject_set_min_value_int(&subject_play_pause, 0);
    lv_subject_set_max_value_int(&subject_play_pause, 1);

    /*----------------
     * Translations
     *----------------*/

#if LV_USE_XML
    /* Register widgets */
    wd_beat_indicator_register();

    /* Register fonts */
    lv_xml_register_font(NULL, "font_oxanium_semibold_16", font_oxanium_semibold_16);
    lv_xml_register_font(NULL, "font_oxanium_semibold_20", font_oxanium_semibold_20);
    lv_xml_register_font(NULL, "font_oxanium_semibold_25", font_oxanium_semibold_25);
    lv_xml_register_font(NULL, "font_gemunu_light_110", font_gemunu_light_110);
    lv_xml_register_font(NULL, "font_gemunu_light_130", font_gemunu_light_130);
    lv_xml_register_font(NULL, "font_gemunu_bold_20", font_gemunu_bold_20);
    lv_xml_register_font(NULL, "font_gemunu_medium_60", font_gemunu_medium_60);

    /* Register subjects */
    lv_xml_register_subject(NULL, "subject_bpm", &subject_bpm);
    lv_xml_register_subject(NULL, "subject_beats_per_measure", &subject_beats_per_measure);
    lv_xml_register_subject(NULL, "subject_current_beat", &subject_current_beat);
    lv_xml_register_subject(NULL, "subject_play_pause", &subject_play_pause);

    /* Register callbacks */
    lv_xml_register_event_cb(NULL, "on_bmp_scroll_cb", on_bmp_scroll_cb);
    lv_xml_register_event_cb(NULL, "bpm_scale_size_change_cb", bpm_scale_size_change_cb);
    lv_xml_register_event_cb(NULL, "tap_tempo_clicked_cb", tap_tempo_clicked_cb);
    lv_xml_register_event_cb(NULL, "toggle_panel_cb", toggle_panel_cb);
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
    lv_xml_register_image(NULL, "img_note", img_note);
    lv_xml_register_image(NULL, "img_play", img_play);
    lv_xml_register_image(NULL, "img_pause", img_pause);
    lv_xml_register_image(NULL, "img_scale_gradient", img_scale_gradient);
    lv_xml_register_image(NULL, "img_lvgl_logo", img_lvgl_logo);
#endif

#if LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manaully from XML using lv_xml_create() */
#endif
}

/* Callbacks */
#if defined(LV_EDITOR_PREVIEW)
void __attribute__((weak)) on_bmp_scroll_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_bmp_scroll_cb was called\n");
}
void __attribute__((weak)) bpm_scale_size_change_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("bpm_scale_size_change_cb was called\n");
}
void __attribute__((weak)) tap_tempo_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("tap_tempo_clicked_cb was called\n");
}
void __attribute__((weak)) toggle_panel_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("toggle_panel_cb was called\n");
}
#endif

/**********************
 *   STATIC FUNCTIONS
 **********************/