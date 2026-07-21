/**
 * @file wd_beat_indicator_private_gen.h
 *
 */

#ifndef WD_BEAT_INDICATOR_PRIVATE_H
#define WD_BEAT_INDICATOR_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl_private.h"
#else
    #include "lvgl/lvgl_private.h"
#endif
#include "wd_beat_indicator.h"

/*********************
 *      DEFINES
 *********************/

#ifndef WD_BEAT_INDICATOR_USER_DATA
#define WD_BEAT_INDICATOR_USER_DATA
#endif

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    lv_obj_t obj;  /* Base widget to extend */
    WD_BEAT_INDICATOR_USER_DATA
} wd_beat_indicator_t;

extern const lv_obj_class_t wd_beat_indicator_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

#if LV_USE_XML
    void wd_beat_indicator_register(void);
#endif

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*WD_BEAT_INDICATOR_PRIVATE_H*/