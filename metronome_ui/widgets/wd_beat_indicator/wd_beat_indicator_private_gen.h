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

#include "lvgl_private.h"
#include "wd_beat_indicator.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    lv_obj_t obj;  /* Base widget to extend */
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