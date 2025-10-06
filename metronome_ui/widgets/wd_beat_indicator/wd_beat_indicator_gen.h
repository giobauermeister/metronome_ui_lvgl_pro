/**
 * @file wd_beat_indicator_gen.h
 *
 */

#ifndef WD_BEAT_INDICATOR_GEN_H
#define WD_BEAT_INDICATOR_GEN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#include "metronome_ui_gen.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a wd_beat_indicator object
 * @param parent pointer to an object, it will be the parent of the new wd_beat_indicator
 * @return pointer to the created wd_beat_indicator
 */
lv_obj_t * wd_beat_indicator_create(lv_obj_t * parent);
;

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*WD_BEAT_INDICATOR_GEN_H*/