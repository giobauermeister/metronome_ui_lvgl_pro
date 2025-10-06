/**
 * @file metronome_ui_api.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "metronome_ui_api.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void set_current_beat_cb(void * p);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

int32_t metronome_ui_api_get_value_bpm(void)
{
    lv_lock();
    int32_t bpm = lv_subject_get_int(&subject_bpm);
    lv_unlock();
    return bpm;
}

bool metronome_ui_api_get_value_play_pause(void)
{
    lv_lock();
    int32_t play_pause = lv_subject_get_int(&subject_play_pause);
    lv_unlock();
    return play_pause;
}

int32_t metronome_ui_api_get_value_beats_per_measure(void)
{
    lv_lock();
    int32_t beats_per_measure = lv_subject_get_int(&subject_beats_per_measure);
    lv_unlock();
    return beats_per_measure;
}

// void metronome_ui_api_set_value_current_beat(int32_t current_beat)
// {
//     lv_lock();
//     lv_subject_set_int(&subject_current_beat, current_beat);
//     lv_unlock();
// }

void metronome_ui_api_set_value_current_beat(int32_t current_beat)
{
    /* no lv_lock here; just schedule on LVGL thread */
    lv_async_call(set_current_beat_cb, (void *)(intptr_t)current_beat);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void set_current_beat_cb(void * p)
{
    int32_t v = (int32_t)(intptr_t)p;
    lv_subject_set_int(&subject_current_beat, v);
}