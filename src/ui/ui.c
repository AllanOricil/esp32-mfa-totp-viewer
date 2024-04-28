// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

// CUSTOM EVENTS
uint32_t LV_EVENT_SETUP_COMPLETE;

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_totp_screen
lv_obj_t *ui_totp_screen;
lv_obj_t *ui_pin_screen;
lv_obj_t *ui_load_screen;
lv_obj_t *ui_pin_textarea;
lv_obj_t *ui____initial_actions0;
void ui_totp_screen_screen_init(void);
void ui_pin_screen_screen_init(void);
void ui_event_totp_component_label(lv_event_t *e);
void ui_event_totp_component_bar(lv_event_t *e);
void ui_event_keyboard_button(lv_event_t *e);
void ui_event_pin_textarea(lv_event_t *e);

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_totp_component_label(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED) {
        on_totp_component_label_value_changed(e);
    }
}

void ui_event_totp_component_bar(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED) {
        on_totp_component_bar_value_changed(e);
    }
}

void ui_event_keyboard_button(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED) {
        on_keyboard_button_clicked(e);
    }
}

void ui_event_pin_textarea(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_READY) {
        on_validate_pin(e);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init( void ){
    lv_disp_t *disp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(
        disp, 
        lv_palette_main(LV_PALETTE_BLUE), 
        lv_palette_main(LV_PALETTE_RED), 
        true, 
        LV_FONT_DEFAULT
    );
    LV_EVENT_SETUP_COMPLETE = lv_event_register_id();
    lv_disp_set_theme(disp, theme);
    ui_totp_screen_screen_init();
    ui_pin_screen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_pin_screen);
}


void refresh_totp_labels() {
    LV_LOG_INFO("refresh_totp_labels");
    lv_obj_t *container;
    lv_obj_t *label;
    int index = 0;

    container = lv_obj_get_child(ui_totp_screen, index);
    while (container) {
        label = lv_obj_get_child(container, 1);
        TotpValueChangeEvent event;
        event.index = index;
        lv_event_send(label, LV_EVENT_VALUE_CHANGED, &event);
        index++;
        container = lv_obj_get_child(ui_totp_screen, index);
    }
}

void refresh_counter_bars(){
    LV_LOG_INFO("refresh_counter_bars");
    lv_obj_t *container;
    lv_obj_t *bar;
    int index = 0;

    container = lv_obj_get_child(ui_totp_screen, index);
    while (container) {
        bar = lv_obj_get_child(container, 2);
        TotpValueChangeEvent event;
        event.index = index;
        lv_event_send(bar, LV_EVENT_VALUE_CHANGED, &event);
        index++;
        container = lv_obj_get_child(ui_totp_screen, index);
    }
}
