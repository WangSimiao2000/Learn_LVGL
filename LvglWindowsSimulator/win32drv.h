﻿/**
 * @file win32drv.h
 *
 */

#ifndef LV_WINDOWS_DRV_H
#define LV_WINDOWS_DRV_H

/*********************
 *      INCLUDES
 *********************/

#include "lvgl/lvgl.h"

#include <windows.h>

#if _MSC_VER >= 1200
 // Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C       extern "C"
#else
#define EXTERN_C       extern
#endif
#endif // !EXTERN_C

/*********************
 *      DEFINES
 *********************/

#define LVGL_SIMULATOR_WINDOW_CLASS L"LVGL.SimulatorWindow"

/**********************
 *      TYPEDEFS
 **********************/

typedef struct _lv_windows_pointer_device_context_t
{
    lv_indev_state_t state;
    lv_point_t point;
} lv_windows_pointer_device_context_t;

typedef struct _lv_windows_keypad_queue_item_t
{
    uint32_t key;
    lv_indev_state_t state;
} lv_windows_keypad_queue_item_t;

typedef struct _lv_windows_keypad_device_context_t
{
    CRITICAL_SECTION mutex;
    lv_ll_t queue;
    uint16_t utf16_high_surrogate;
    uint16_t utf16_low_surrogate;
} lv_windows_keypad_device_context_t;

typedef struct _lv_windows_encoder_device_context_t
{
    lv_indev_state_t state;
    int16_t enc_diff;
} lv_windows_encoder_device_context_t;

typedef struct _lv_windows_window_context_t
{
    lv_disp_t* display_device_object;
    lv_indev_t* mouse_device_object;
    lv_indev_t* mousewheel_device_object;
    lv_indev_t* keyboard_device_object;

    void* display_draw_buffer_base;
    size_t display_draw_buffer_size;
    volatile bool display_refreshing;
    HDC display_framebuffer_context_handle;
    uint32_t* display_framebuffer_base;
    size_t display_framebuffer_size;

    lv_windows_pointer_device_context_t pointer;
    lv_windows_keypad_device_context_t keypad;
    lv_windows_encoder_device_context_t encoder;

} lv_windows_window_context_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

EXTERN_C bool lv_windows_quit_signal;

EXTERN_C lv_indev_t* lv_windows_pointer_device_object;
EXTERN_C lv_indev_t* lv_windows_keypad_device_object;
EXTERN_C lv_indev_t* lv_windows_encoder_device_object;

EXTERN_C void lv_windows_add_all_input_devices_to_group(
    lv_group_t* group);

EXTERN_C lv_windows_window_context_t* lv_windows_get_window_context(
    HWND window_handle);

EXTERN_C bool lv_windows_init_window_class();

EXTERN_C HWND lv_windows_create_display_window(
    const wchar_t* window_title,
    int32_t hor_res,
    int32_t ver_res,
    HINSTANCE instance_handle,
    HICON icon_handle,
    int show_window_mode);

EXTERN_C bool lv_windows_init(
    HINSTANCE instance_handle,
    int show_window_mode,
    int32_t hor_res,
    int32_t ver_res,
    HICON icon_handle);

/**********************
 *      MACROS
 **********************/

#endif /*LV_WINDOWS_DRV_H*/
