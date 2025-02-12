#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"
#include <portmacro.h>
#include "freertos/projdefs.h"


class Button {
private:
    gpio_num_t pin;     
    bool active_high;   // True om knappen är aktiv hög, annars aktiv låg
    bool last_stable_state;
    bool current_state;
    bool onPressed;
    bool onReleased;
    TickType_t startTickButton;
    //const TickType_t debounce_delay = pdMS_TO_TICKS(10); //debounce

public:
    Button(gpio_num_t pin, bool active_high = false);

    void init();

    void update();

    // Kontrollera om knappen är tryckt
    bool is_pressed();
};

#endif // BUTTON_H

