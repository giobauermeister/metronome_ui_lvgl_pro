/**
 * @file wd_beat_indicator.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "wd_beat_indicator_private_gen.h"
#include "metronome_ui.h"

/*********************
 *      DEFINES
 *********************/
#define COL_GAP 14

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    lv_obj_t * dots[BEATS_MAX];
    int count;
    lv_observer_t * obs_beats;
    lv_observer_t * obs_tick;
    lv_observer_t * obs_play_pause;
} beat_ctx_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void styles_init_once(void);
static void set_active(beat_ctx_t * ctx, int idx);
static void rebuild(lv_obj_t * root, beat_ctx_t * ctx, int beats);
static void beats_obs(lv_observer_t * o, lv_subject_t * s);
static void tick_obs(lv_observer_t * o, lv_subject_t * s);
static void play_pause_obs(lv_observer_t * o, lv_subject_t * s);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_style_t s_style_root;
static lv_style_t s_style_dot_inactive;
static lv_style_t s_style_dot_active;
static bool s_styles_inited = false;

/**********************
 *      MACROS
 **********************/
#define CLAMPI(v,lo,hi) ((v)<(lo)?(lo):((v)>(hi)?(hi):(v)))

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void wd_beat_indicator_constructor_hook(lv_obj_t * obj)
{
    styles_init_once();
    lv_obj_add_style(obj, &s_style_root, 0);

    /* per-instance context */
    beat_ctx_t * ctx = lv_malloc_zeroed(sizeof(* ctx));
    LV_ASSERT_MALLOC(ctx);
    lv_obj_set_user_data(obj, ctx);

    /* initial build */
    int beats = lv_subject_get_int(&subject_beats_per_measure);

    rebuild(obj, ctx, beats);

    /* subscribe (auto-removed on obj delete) */
    ctx->obs_beats = lv_subject_add_observer_obj(&subject_beats_per_measure, beats_obs, obj, NULL);
    ctx->obs_tick  = lv_subject_add_observer_obj(&subject_current_beat, tick_obs, obj, NULL);
    ctx->obs_play_pause  = lv_subject_add_observer_obj(&subject_play_pause, play_pause_obs, obj, NULL);
}

void wd_beat_indicator_destructor_hook(lv_obj_t * obj)
{
    beat_ctx_t *ctx = (beat_ctx_t *)lv_obj_get_user_data(obj);
    if(!ctx) return;

    for(int i=0;i<ctx->count;i++){
        if(ctx->dots[i]) lv_obj_delete(ctx->dots[i]);
        ctx->dots[i] = NULL;
    }
    lv_free(ctx);
    lv_obj_set_user_data(obj, NULL);
}

void wd_beat_indicator_event_hook(lv_event_t * e)
{

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void styles_init_once(void)
{
    if(s_styles_inited) return;

    /* root style: flex row with column gap; transparent bg */
    lv_style_init(&s_style_root);
    lv_style_set_width(&s_style_root, LV_SIZE_CONTENT);
    lv_style_set_height(&s_style_root, 50);
    lv_style_set_pad_all(&s_style_root, 0);
    lv_style_set_layout(&s_style_root, LV_LAYOUT_FLEX);
    lv_style_set_flex_flow(&s_style_root, LV_FLEX_FLOW_ROW);
    lv_style_set_flex_cross_place(&s_style_root, LV_FLEX_ALIGN_CENTER);
    lv_style_set_flex_track_place(&s_style_root, LV_FLEX_ALIGN_CENTER);
    lv_style_set_pad_column(&s_style_root, COL_GAP);
    lv_style_set_bg_opa(&s_style_root, LV_OPA_TRANSP);

    /* inactive dot */
    lv_style_init(&s_style_dot_inactive);
    lv_style_set_width(&s_style_dot_inactive, 35);
    lv_style_set_height(&s_style_dot_inactive, 35);
    lv_style_set_radius(&s_style_dot_inactive, 35);
    lv_style_set_bg_color(&s_style_dot_inactive, lv_color_hex(0xB6BABF));
    lv_style_set_border_width(&s_style_dot_inactive, 0);
    lv_style_set_bg_opa(&s_style_dot_inactive, LV_OPA_COVER);

    /* active dot */
    lv_style_init(&s_style_dot_active);
    lv_style_set_width(&s_style_dot_active, 50);
    lv_style_set_height(&s_style_dot_active, 50);
    lv_style_set_radius(&s_style_dot_active, 50);
    lv_style_set_bg_color(&s_style_dot_active, lv_color_hex(0x6DC868));
    lv_style_set_border_width(&s_style_dot_active, 0);
    lv_style_set_bg_opa(&s_style_dot_active, LV_OPA_COVER);

    s_styles_inited = true;
}

static void set_active(beat_ctx_t * ctx, int idx)
{
    // LV_LOG_USER("set_active");
    if(idx < 0 || idx >= ctx->count) return;

    /* Set all to inactive, then one to active (no animation) */
    for(int i=0;i<ctx->count;i++){
        lv_obj_remove_style_all(ctx->dots[i]);
        lv_obj_add_style(ctx->dots[i], &s_style_dot_inactive, 0);
    }
    lv_obj_remove_style_all(ctx->dots[idx]);
    lv_obj_add_style(ctx->dots[idx], &s_style_dot_active, 0);
}

static void rebuild(lv_obj_t * root, beat_ctx_t * ctx, int beats)
{
    // LV_LOG_USER("rebuild");
    beats = CLAMPI(beats, BEATS_MIN, BEATS_MAX);

    /* delete old */
    for(int i=0;i<ctx->count;i++){
        if(ctx->dots[i]) lv_obj_del(ctx->dots[i]);
        ctx->dots[i] = NULL;
    }
    ctx->count = 0;

    /* create new */
    for(int i=0;i<beats;i++){
        lv_obj_t * d = lv_obj_create(root);
        lv_obj_remove_style_all(d);
        lv_obj_add_style(d, &s_style_dot_inactive, 0);
        ctx->dots[i] = d;
    }
    ctx->count = beats;
}

static void beats_obs(lv_observer_t * o, lv_subject_t * s)
{
    // LV_LOG_USER("beats_obs");
    LV_UNUSED(s);

    lv_obj_t * root = (lv_obj_t *)lv_observer_get_target_obj(o);
    beat_ctx_t * ctx = (beat_ctx_t *)lv_obj_get_user_data(root);

    int beats = lv_subject_get_int(&subject_beats_per_measure);
    rebuild(root, ctx, beats);
}

static void tick_obs(lv_observer_t * o, lv_subject_t * s)
{
    // LV_LOG_USER("tick_obs");
    LV_UNUSED(s);

    lv_obj_t * root = (lv_obj_t *)lv_observer_get_target_obj(o);
    beat_ctx_t * ctx = (beat_ctx_t *)lv_obj_get_user_data(root);

    int idx   = lv_subject_get_int(&subject_current_beat);
    int beats = lv_subject_get_int(&subject_beats_per_measure);

    if(beats != ctx->count) rebuild(root, ctx, beats);
    if(idx < 0) return;
    set_active(ctx, CLAMPI(idx, 0, ctx->count - 1));
}

static void play_pause_obs(lv_observer_t * o, lv_subject_t * s)
{
    // LV_LOG_USER("play_pause_obs");
    LV_UNUSED(s);

    lv_obj_t * root = (lv_obj_t *)lv_observer_get_target_obj(o);
    beat_ctx_t * ctx = (beat_ctx_t *)lv_obj_get_user_data(root);

    int play_pause = lv_subject_get_int(&subject_play_pause);

    if(play_pause == 0) { /* pause was pressed */
        /* Clear any active dot: make them all inactive */
        for(int i = 0; i < ctx->count; i++) {
            lv_obj_remove_style_all(ctx->dots[i]);
            lv_obj_add_style(ctx->dots[i], &s_style_dot_inactive, 0);
        }
    }
}