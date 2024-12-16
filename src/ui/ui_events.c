#include <time.h>
#include <string.h>
#include "ui.h"
#include "totp-map.h"
#include "esp_log.h"
#include "constants.h"
#include "pin.h"

int calculate_new_bar_value()
{
    struct tm *timeinfo;
    time_t now;
    time(&now);
    timeinfo = localtime(&now);
    int val = TOTP_PERIOD - timeinfo->tm_sec % TOTP_PERIOD;
    return val;
}

void on_totp_component_label_value_changed(lv_event_t *e)
{
    LV_LOG_TRACE("on_totp_component_label_value_changed");
    lv_obj_t *label = lv_event_get_target(e);
    TotpValueChangeEvent *data = (TotpValueChangeEvent *)lv_event_get_param(e);
    char *totp = get_totp_by_index(data->index);

    LV_LOG_TRACE("totp: %s index: %d", totp, data->index);
    // NOTE: a copy of the value stored at *totp (ref) is created so that it can be dealocated or changed without compromising what is currently being displayed
    char *temp = strdup(totp);
    if (temp)
    {
        lv_label_set_text(label, temp);
        free(temp);
    }
}

void on_totp_component_bar_value_changed(lv_event_t *e)
{
    LV_LOG_TRACE("on_totp_component_bar_value_changed");
    lv_obj_t *bar = lv_event_get_target(e);
    int val = calculate_new_bar_value();
    lv_bar_set_value(bar, val, LV_ANIM_OFF);
}

void on_keyboard_button_clicked(lv_event_t *e)
{
    lv_obj_t *keyboard = lv_event_get_target(e);
    uint32_t btn_id = lv_btnmatrix_get_selected_btn(keyboard);
    printf("Debug message: %u\n", btn_id);

    if (btn_id != LV_BTNMATRIX_BTN_NONE)
    {
        const char *btn_text = lv_btnmatrix_get_btn_text(keyboard, btn_id);

        if (strcmp(btn_text, "DEL") == 0)
            lv_textarea_del_char(ui_pin_textarea);
        else if (strcmp(btn_text, "CLEAR") == 0)
            lv_textarea_set_text(ui_pin_textarea, "");
        else if (strcmp(btn_text, "OK") == 0)
            lv_event_send(ui_pin_textarea, LV_EVENT_READY, NULL);
        else
            lv_textarea_add_text(ui_pin_textarea, btn_text);
    }
}

void on_validate_pin(lv_event_t *e)
{
    lv_obj_t *textarea = lv_event_get_target(e);
    const char *pin = lv_textarea_get_text(textarea);

    if (!validate_pin(pin))
    {
        _number_of_wrong_unlock_attempts--;

        if (!_number_of_wrong_unlock_attempts)
        {
            lv_obj_center(lv_msgbox_create(NULL, "ERROR", "BOARD LOCKED", NULL, false));
            return;
        }

        char message[128];
        sprintf(message, "Wrong PIN\nAttempts left: %d", _number_of_wrong_unlock_attempts);
        lv_obj_center(lv_msgbox_create(NULL, "ERROR", message, NULL, true));
        return;
    }

    _number_of_wrong_unlock_attempts = _max_number_of_wrong_unlock_attempts;

    lv_scr_load(ui_totp_screen);
}