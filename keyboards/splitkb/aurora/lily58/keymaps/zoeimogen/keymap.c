#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#ifdef OLED_ENABLE
void render_logo(void);
void render_space(void);
void render_layer_state(void);
void render_mod_status_gui_alt(uint8_t modifiers);
void render_mod_status_ctrl_shift(uint8_t modifiers);
void render_kb_LED_state(void);

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        return true;
    }

    render_logo();
    render_space();
    render_layer_state();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
    render_kb_LED_state();

    char wpm_str[4];
    oled_write_P(PSTR("WPM "), false);
    sprintf(wpm_str, "%3d", get_current_wpm());
    oled_write(wpm_str, false);

    return false;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            rgb_matrix_set_color_all(RGB_RED);
            rgb_matrix_update_pwm_buffers();
            oled_write_P(PSTR("LOAD"), false);
            oled_render_dirty(true);
        }
    }
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return false;
}
#endif

/* #ifdef OTHER_KEYMAP_C
   #    include OTHER_KEYMAP_C
   #endif // OTHER_KEYMAP_C */

