#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"
#include <portmacro.h>
#include "freertos/projdefs.h"


class Button {
private:
    gpio_num_t pin;     
    bool last_stable_state;
    bool current_state;
    bool buttonReleased;
    bool released;
    TickType_t startTickButton;
    void(*onPressedCallback)(int pin) = nullptr;
   

public:
    Button(gpio_num_t pin);
    void init();
    void update();
    bool is_pressed();
    void setOnPressed(void(*callback)(int pin));
};

#endif // BUTTON_H

