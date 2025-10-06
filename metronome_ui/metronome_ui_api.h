/**
 * @file metronome_ui_api.h
 */

#ifndef METRONOME_UI_API_H
#define METRONOME_UI_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "metronome_ui_gen.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
int32_t metronome_ui_api_get_value_bpm(void);
bool metronome_ui_api_get_value_play_pause(void);
int32_t metronome_ui_api_get_value_beats_per_measure(void);
void metronome_ui_api_set_value_current_beat(int32_t current_beat);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*METRONOME_UI_API_H*/