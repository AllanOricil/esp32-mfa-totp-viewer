// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"
#include "totp-map.h"
#include "constants.h"

extern char keys[MAX_NUMBER_OF_SERVICES][MAX_SERVICE_NAME_LENGTH];
extern char totps[MAX_NUMBER_OF_SERVICES][MAX_TOTP_LENGTH];
extern int size;

#define LV_LABEL_SCROLL_SPEED (15)

lv_obj_t* create_totp_component(
	lv_obj_t* parent,
    const char* service, 
	const char* totp, 
	int barMax, 
	int barValue
){
    lv_obj_t* container = lv_obj_create(parent);
    lv_obj_set_width(container, 150);
    lv_obj_set_height(container, 70);
    lv_obj_set_height(container, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_bg_color(container, lv_color_hex(0x060C14), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(container, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(container, 5, 0);
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t* totp_service = lv_label_create(container);
    lv_label_set_text(totp_service, service);
    lv_obj_set_width(totp_service, LV_PCT(100));
    lv_obj_set_style_text_opa(totp_service, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(totp_service, lv_color_hex(0xFEFEFE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(totp_service, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(totp_service, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_label_set_long_mode(totp_service, LV_LABEL_LONG_SCROLL_CIRCULAR);

    lv_obj_t* totp_label = lv_label_create(container);
    lv_label_set_text(totp_label, totp);
    lv_obj_set_style_text_opa(totp_label, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(totp_label, lv_color_hex(0xFEFEFE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(totp_label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(totp_label, &lv_font_montserrat_22, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_t* totp_counter = lv_bar_create(container);
    lv_bar_set_range(totp_counter, 0, barMax);
    lv_bar_set_value(totp_counter, barValue, LV_ANIM_OFF);
    lv_bar_set_start_value(totp_counter, 0, LV_ANIM_OFF);
    lv_obj_set_width(totp_counter, LV_PCT(100));
    lv_obj_set_height(totp_counter, 5);
    lv_obj_set_style_pad_top(totp_counter, 2, 0);
    lv_obj_set_style_bg_color(totp_counter, lv_color_hex(0x25324C), LV_PART_MAIN);
    lv_obj_set_style_bg_color(totp_counter, lv_color_hex(0x25C4F4), LV_PART_INDICATOR);

	lv_obj_add_event_cb(totp_label, ui_event_totp_component_label, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(totp_counter, ui_event_totp_component_bar, LV_EVENT_ALL, NULL);

    return container;
}

void ui_totp_screen_screen_init(void){
	ui_totp_screen = lv_obj_create(NULL);
	lv_obj_add_flag( ui_totp_screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(ui_totp_screen, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_bg_color(ui_totp_screen, lv_color_hex(0x121C2F), LV_PART_MAIN | LV_STATE_DEFAULT );
	lv_obj_set_style_bg_opa(ui_totp_screen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui_totp_screen, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

	// NOTE: set up flex container properties for the screen
    lv_obj_set_flex_flow(ui_totp_screen, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui_totp_screen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_layout(ui_totp_screen, LV_LAYOUT_FLEX);

    // NOTE: create 1 component for each TOTP
	for(int i = 0; i < size; i++){
        create_totp_component(ui_totp_screen, keys[i], totps[i], 30, 30);
    }
}


