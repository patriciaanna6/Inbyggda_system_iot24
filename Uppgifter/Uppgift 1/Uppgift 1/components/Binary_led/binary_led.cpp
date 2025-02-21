#include <stdio.h>
#include "esp_log.h"
#include "binary_led.h"
#include "portmacro.h"

static const char *TAG = "BinaryLed"; 

void BinaryLed::init(gpio_num_t pin_input) {
    ESP_LOGI(TAG, "Initializing LED on GPIO %d", pin_input);
    this->pin = pin_input;

    gpio_reset_pin(this->pin); 
    gpio_set_direction(this->pin, GPIO_MODE_OUTPUT); 
    last_toggle_time = xTaskGetTickCount();
    led_state = false; 
    gpio_set_level(this->pin, 0);
    is_blinking = true; 
}

void BinaryLed::update() {
    if (!is_blinking) return; // Stop blinking if it's deactivated 

    TickType_t now = xTaskGetTickCount();
    int interval = led_state ? blink_on_time : blink_off_time; 

    if (now - last_toggle_time >= interval / portTICK_PERIOD_MS) { // convertering ms till tick
        led_state = !led_state; //flip the state
        gpio_set_level(this->pin, led_state);
        ESP_LOGI(TAG, "BLINK LED TO: %d", led_state);
        last_toggle_time = now;
    }
}

void BinaryLed::setLed(bool led_state) {
    this->led_state = led_state;
    gpio_set_level(this->pin, led_state);
    ESP_LOGI(TAG, "SET LED TO: %d", led_state);

    is_blinking = false; // if we call setLed(), stop blinking
}

void BinaryLed::blink(int milliseconds_on, int milliseconds_off) {
    blink_on_time = milliseconds_on;
    blink_off_time = milliseconds_off;
    is_blinking = true; // start the blinking
}
