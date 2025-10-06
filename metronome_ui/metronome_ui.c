/**
 * @file metronome_ui.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "metronome_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void bpm_scale_update_cb(lv_observer_t * observer, lv_subject_t * subject);
static void anim_set_translate_x(lv_anim_t *a, int32_t v);
static void anim_set_opa(lv_anim_t *a, int32_t v);
static void run_side_panel_slide(lv_obj_t *panel, bool reverse);
static inline int32_t clamp_i32(int32_t v, int32_t lo, int32_t hi);

#if defined(LV_EDITOR_PREVIEW)
static inline uint32_t bpm_to_period_ms(int32_t bpm);
static inline int32_t clamp_beats(int32_t b);
static void soft_beeper_timer_cb(lv_timer_t *t);
static void soft_beeper_start(void);
static void soft_beeper_stop(void);
static void soft_play_pause_obs(lv_observer_t *o, lv_subject_t *s);
static void soft_bpm_obs(lv_observer_t *o, lv_subject_t *s);
static void soft_beats_obs(lv_observer_t *o, lv_subject_t *s);
static void soft_beeper_shutdown(void);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/
static bool     s_bounds_inited = false;
static int32_t  s_min_x = 0;   // absolute leftmost scroll_x (can be negative)
static int32_t  s_max_x = 1;   // absolute rightmost scroll_x
static bool     s_updating_from_subject = false;
static bool     s_subject_from_scroll = false;
static uint32_t s_last_tap_ms = 0;

#if defined(LV_EDITOR_PREVIEW)
/* ---------- Soft beeper (Editor-only) ---------- */
static lv_timer_t *   s_soft_timer   = NULL;
static int32_t        s_soft_bpm     = 120;
static int32_t        s_soft_beats   = 4;   // 2..7
static int32_t        s_soft_curbeat = -1;  // -1 = not started

static lv_observer_t *s_obs_play     = NULL;
static lv_observer_t *s_obs_bpm      = NULL;
static lv_observer_t *s_obs_beats    = NULL;
#endif

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void metronome_ui_init(const char * asset_path)
{
    metronome_ui_init_gen(asset_path);

    /* Add your own custom code here if needed */
#if !defined(LV_EDITOR_PREVIEW)
    lv_screen_load(screen_main_create());
#endif

#if defined(LV_EDITOR_PREVIEW)
    /* Editor-only soft beeper */
    s_soft_bpm   = lv_subject_get_int(&subject_bpm);
    s_soft_beats = clamp_beats(lv_subject_get_int(&subject_beats_per_measure));
    s_soft_curbeat = -1;

    s_obs_play  = lv_subject_add_observer(&subject_play_pause,        soft_play_pause_obs,  NULL);
    s_obs_bpm   = lv_subject_add_observer(&subject_bpm,               soft_bpm_obs,         NULL);
    s_obs_beats = lv_subject_add_observer(&subject_beats_per_measure, soft_beats_obs,       NULL);

    if(lv_subject_get_int(&subject_play_pause)) {
        soft_beeper_start();
    } else {
        lv_subject_set_int(&subject_current_beat, -1);
    }
#endif
}

void toggle_panel_cb(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_current_target_obj(e);
    const char * target_name = (const char *)lv_event_get_user_data(e);
    if(!target_name) return;

    // find panel instance on the same screen
    lv_obj_t * screen = lv_obj_get_screen(btn);
    lv_obj_t * panel  = lv_obj_find_by_name(screen, target_name);
    if(!panel) return;

    bool reverse = lv_obj_has_state(btn, LV_STATE_CHECKED);

    run_side_panel_slide(panel, reverse);
}

void on_bmp_scroll_cb(lv_event_t * e)
{
    if(!s_bounds_inited || s_updating_from_subject) return;

    lv_obj_t * obj = lv_event_get_target(e);

    int32_t sx  = lv_obj_get_scroll_x(obj);
    int32_t bpm = lv_map(sx, s_min_x, s_max_x, BPM_MIN, BPM_MAX);

    if(bpm < BPM_MIN) bpm = BPM_MIN;
    if(bpm > BPM_MAX) bpm = BPM_MAX;

    s_subject_from_scroll = true;
    lv_subject_set_int(&subject_bpm, bpm);

    // LV_LOG_USER("sx=%d  map[%d..%d] → BPM=%d",
    //             (int)sx, (int)s_min_x, (int)s_max_x, (int)bpm);
}

void bpm_scale_size_change_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);

    /* Capture absolute extremes ONCE */
    if(!s_bounds_inited) {
        int32_t to_l = lv_obj_get_scroll_left(obj); 
        int32_t to_r = lv_obj_get_scroll_right(obj);

        if((to_l + to_r) <= 0) return;

        int32_t sx = lv_obj_get_scroll_x(obj);
        s_min_x = sx - to_l;
        s_max_x = sx + to_r;
        if(s_max_x == s_min_x) s_max_x = s_min_x + 1;

        s_bounds_inited = true;
    }

    /* Get current subject and map BPM -> scroll_x */
    int32_t bpm = lv_subject_get_int(&subject_bpm);
    if(bpm < BPM_MIN) bpm = BPM_MIN;
    if(bpm > BPM_MAX) bpm = BPM_MAX;

    int32_t target_sx = lv_map(bpm, BPM_MIN, BPM_MAX, s_min_x, s_max_x);
    s_updating_from_subject = true;          // guard programmatic scroll event
    lv_obj_scroll_to_x(obj, target_sx, LV_ANIM_OFF);
    s_updating_from_subject = false;

    lv_subject_add_observer_obj(&subject_bpm, bpm_scale_update_cb, obj, NULL);

    // LV_LOG_USER("BPM=%d -> target_sx=%d  [min=%d..max=%d]",
    //             (int)bpm, (int)target_sx, (int)s_min_x, (int)s_max_x);
}

void tap_tempo_clicked_cb(lv_event_t * e)
{
    // LV_LOG_USER("TAP TEMPO clicked");

    uint32_t now_ms = lv_tick_get();

    if(s_last_tap_ms != 0) {
        uint32_t dt_ms = lv_tick_elaps(s_last_tap_ms);

        if(dt_ms > 0) {
            int32_t bpm = (int32_t)((60000u + (dt_ms / 2u)) / dt_ms);
            bpm = clamp_i32(bpm, BPM_MIN, BPM_MAX);

            lv_subject_set_int(&subject_bpm, bpm);
            // LV_LOG_USER("Tap delta=%u ms -> %d BPM (clamped %d..%d)",
            //             (unsigned)dt_ms, (int)bpm, BPM_MIN, BPM_MAX);
        }
    }

    s_last_tap_ms = now_ms;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void bpm_scale_update_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    lv_obj_t * obj = lv_observer_get_target_obj(observer);

    if(s_subject_from_scroll) {
        s_subject_from_scroll = false;
        return;
    }

    int32_t bpm = lv_subject_get_int(&subject_bpm);
    if(bpm < BPM_MIN) bpm = BPM_MIN;
    if(bpm > BPM_MAX) bpm = BPM_MAX;

    int32_t target_sx = lv_map(bpm, BPM_MIN, BPM_MAX, s_min_x, s_max_x);
    s_updating_from_subject = true;
    lv_obj_scroll_to_x(obj, target_sx, LV_ANIM_OFF);
    s_updating_from_subject = false;
}

static void anim_set_translate_x(lv_anim_t *a, int32_t v) {
    lv_obj_set_style_translate_x((lv_obj_t *)a->var, v, 0);
}

static void anim_set_opa(lv_anim_t *a, int32_t v) {
    lv_obj_set_style_opa((lv_obj_t *)a->var, (lv_opa_t)v, 0);
}

static void run_side_panel_slide(lv_obj_t *panel, bool reverse)
{
    if(!panel) return;

    int sign = (lv_obj_get_x(panel) > 0) ? -1 : +1;

    const int32_t open_from_tx  = 0;
    const int32_t open_to_tx    = 200 * sign;
    const int32_t close_from_tx = open_to_tx;
    const int32_t close_to_tx   = 0;

    const int32_t tx_from  = reverse ? open_from_tx  : close_from_tx;
    const int32_t tx_to    = reverse ? open_to_tx    : close_to_tx;
    const int32_t opa_from = reverse ? 0             : 255;
    const int32_t opa_to   = reverse ? 255           : 0;

    // translate_x
    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, panel);
    lv_anim_set_values(&a1, tx_from, tx_to);
    lv_anim_set_duration(&a1, 300);
    lv_anim_set_custom_exec_cb(&a1, anim_set_translate_x);
    lv_anim_start(&a1);

    // opa
    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, panel);
    lv_anim_set_values(&a2, opa_from, opa_to);
    lv_anim_set_duration(&a2, 400);
    lv_anim_set_custom_exec_cb(&a2, anim_set_opa);
    lv_anim_start(&a2);
}

static inline int32_t clamp_i32(int32_t v, int32_t lo, int32_t hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

#if defined(LV_EDITOR_PREVIEW)
static inline uint32_t bpm_to_period_ms(int32_t bpm)
{
    if(bpm < BPM_MIN) bpm = BPM_MIN;
    if(bpm > BPM_MAX) bpm = BPM_MAX;
    return (uint32_t)(60000 / bpm);
}

static inline int32_t clamp_beats(int32_t b)
{
    if(b < BEATS_MIN) b = BEATS_MIN;
    if(b > BEATS_MAX) b = BEATS_MAX;
    return b;
}

static void soft_beeper_timer_cb(lv_timer_t *t)
{
    LV_UNUSED(t);
    int32_t beats = clamp_beats(s_soft_beats);
    if(s_soft_curbeat < 0) s_soft_curbeat = 0;
    else                   s_soft_curbeat = (s_soft_curbeat + 1) % beats;
    lv_subject_set_int(&subject_current_beat, s_soft_curbeat);
}

static void soft_beeper_start(void)
{
    uint32_t period = bpm_to_period_ms(s_soft_bpm);
    if(!s_soft_timer) s_soft_timer = lv_timer_create(soft_beeper_timer_cb, period, NULL);
    else              lv_timer_set_period(s_soft_timer, period);
    s_soft_curbeat = 0;                           // next tick starts at 0
    lv_subject_set_int(&subject_current_beat, 0);  // immediate visual
    lv_timer_reset(s_soft_timer);
    lv_timer_resume(s_soft_timer);
}

static void soft_beeper_stop(void)
{
    if(s_soft_timer) lv_timer_pause(s_soft_timer);
    s_soft_curbeat = -1;
    lv_subject_set_int(&subject_current_beat, -1);
}

static void soft_play_pause_obs(lv_observer_t *o, lv_subject_t *s)
{
    LV_UNUSED(o); LV_UNUSED(s);
    int32_t play = lv_subject_get_int(&subject_play_pause);
    if(play) soft_beeper_start();
    else     soft_beeper_stop();
}

static void soft_bpm_obs(lv_observer_t *o, lv_subject_t *s)
{
    LV_UNUSED(o); LV_UNUSED(s);
    s_soft_bpm = lv_subject_get_int(&subject_bpm);
    if(s_soft_bpm < BPM_MIN) s_soft_bpm = BPM_MIN;
    if(s_soft_bpm > BPM_MAX) s_soft_bpm = BPM_MAX;
    if(s_soft_timer) lv_timer_set_period(s_soft_timer, bpm_to_period_ms(s_soft_bpm));
}

static void soft_beats_obs(lv_observer_t *o, lv_subject_t *s)
{
    LV_UNUSED(o); LV_UNUSED(s);
    s_soft_beats = clamp_beats(lv_subject_get_int(&subject_beats_per_measure));
    if(s_soft_curbeat >= s_soft_beats) s_soft_curbeat = -1; // restart next tick
}

/* Optional: tidy up on editor shutdown/screen change */
static void soft_beeper_shutdown(void)
{
    if(s_obs_play)  { lv_observer_remove(s_obs_play);  s_obs_play  = NULL; }
    if(s_obs_bpm)   { lv_observer_remove(s_obs_bpm);   s_obs_bpm   = NULL; }
    if(s_obs_beats) { lv_observer_remove(s_obs_beats); s_obs_beats = NULL; }
    if(s_soft_timer){ lv_timer_del(s_soft_timer);      s_soft_timer= NULL; }
}
#endif /* LV_EDITOR_PREVIEW */