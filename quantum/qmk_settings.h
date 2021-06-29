#pragma once

#include <inttypes.h>
#include <stddef.h>

/* take qmk config macros and set up helper variables for default settings */

/* ========================================================================== */
/* Grave escape                                                               */
/* ========================================================================== */
#ifdef GRAVE_ESC_ALT_OVERRIDE
#define GRAVE_ESC_ALT_OVERRIDE_Defined 1
#else
#define GRAVE_ESC_ALT_OVERRIDE_Defined 0
#endif

#ifdef GRAVE_ESC_CTRL_OVERRIDE
#define GRAVE_ESC_CTRL_OVERRIDE_Defined 1
#else
#define GRAVE_ESC_CTRL_OVERRIDE_Defined 0
#endif

#ifdef GRAVE_ESC_GUI_OVERRIDE
#define GRAVE_ESC_GUI_OVERRIDE_Defined 1
#else
#define GRAVE_ESC_GUI_OVERRIDE_Defined 0
#endif

#ifdef GRAVE_ESC_SHIFT_OVERRIDE
#define GRAVE_ESC_SHIFT_OVERRIDE_Defined 1
#else
#define GRAVE_ESC_SHIFT_OVERRIDE_Defined 0
#endif

#ifdef QMK_SETTINGS
/* dynamic settings framework is enabled */

/* actual settings - stored in RAM and backed by EEPROM */
typedef struct {
    uint8_t grave_esc_override;
} qmk_settings_t;

/* setting prototype - describes how to get/set settings, stored in flash */
typedef struct {
    uint16_t qsid;
    uint16_t sz;
    void *ptr;
} qmk_settings_proto_t;

int qmk_settings_get(uint16_t qsid, void *setting, size_t maxsz);
int qmk_settings_set(uint16_t qsid, const void *setting, size_t maxsz);

extern qmk_settings_t QS;

/* Grave escape */
#define QS_grave_esc_alt_override (QS.grave_esc_override & 1)
#define QS_grave_esc_ctrl_override (QS.grave_esc_override & 2)
#define QS_grave_esc_gui_override (QS.grave_esc_override & 4)
#define QS_grave_esc_shift_override (QS.grave_esc_override & 8)

#else
/* dynamic settings framework is disabled => hardcode the settings and let the compiler optimize extra branches out */


/* Grave escape */
#define QS_grave_esc_alt_override GRAVE_ESC_ALT_OVERRIDE_Defined
#define QS_grave_esc_ctrl_override GRAVE_ESC_CTRL_OVERRIDE_Defined
#define QS_grave_esc_gui_override GRAVE_ESC_GUI_OVERRIDE_Defined
#define QS_grave_esc_shift_override GRAVE_ESC_SHIFT_OVERRIDE_Defined

#endif