/**
 * @file wd_beat_indicator_gen.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "wd_beat_indicator_private_gen.h"
#include "lvgl/src/core/lv_obj_class_private.h"
#include "metronome_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  GLOBAL PROTOTYPES
 **********************/

void wd_beat_indicator_constructor_hook(lv_obj_t * obj);
void wd_beat_indicator_destructor_hook(lv_obj_t * obj);
void wd_beat_indicator_event_hook(lv_event_t * e);

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void wd_beat_indicator_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void wd_beat_indicator_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void wd_beat_indicator_event(const lv_obj_class_t * class_p, lv_event_t * e);

/**********************
 *  STATIC VARIABLES
 **********************/

const lv_obj_class_t wd_beat_indicator_class = {
    .base_class = &lv_obj_class,
    .constructor_cb = wd_beat_indicator_constructor,
    .destructor_cb = wd_beat_indicator_destructor,
    .event_cb = wd_beat_indicator_event,
    .instance_size = sizeof(wd_beat_indicator_t),
    .editable = 1,
    .name = "wd_beat_indicator"
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * wd_beat_indicator_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(&wd_beat_indicator_class, parent);
    lv_obj_class_init_obj(obj);

    return obj;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void wd_beat_indicator_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    wd_beat_indicator_t * widget = (wd_beat_indicator_t *)obj;
    static lv_style_t style_root;
    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_root);
        lv_style_set_width(&style_root, LV_SIZE_CONTENT);
        lv_style_set_height(&style_root, 50);
        lv_style_set_pad_all(&style_root, 0);
        lv_style_set_layout(&style_root, LV_LAYOUT_FLEX);
        lv_style_set_flex_flow(&style_root, LV_FLEX_FLOW_ROW);
        lv_style_set_flex_cross_place(&style_root, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_track_place(&style_root, LV_FLEX_ALIGN_CENTER);
        lv_style_set_pad_column(&style_root, 14);
        lv_style_set_bg_opa(&style_root, 0);

        style_inited = true;
    }
    lv_obj_set_name(obj, "root");

    lv_obj_add_style(obj, &style_root, 0);


    wd_beat_indicator_constructor_hook(obj);

    LV_TRACE_OBJ_CREATE("finished");
}

static void wd_beat_indicator_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);

    wd_beat_indicator_destructor_hook(obj);
}

static void wd_beat_indicator_event(const lv_obj_class_t * class_p, lv_event_t * e)
{
    LV_UNUSED(class_p);

    lv_result_t res;

    /* Call the ancestor's event handler */
    res = lv_obj_event_base(&wd_beat_indicator_class, e);
    if(res != LV_RESULT_OK) return;

    wd_beat_indicator_event_hook(e);
}

