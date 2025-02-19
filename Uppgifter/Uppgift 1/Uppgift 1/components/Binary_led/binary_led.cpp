#include <stdio.h>
#include "esp_log.h"
#include "binary_led.h"
#include <portmacro.h>

static const char *TAG = "BinaryLed"; //for printing 

void BinaryLed::init(gpio_num_t pin_input){
    ESP_LOGI(TAG, "Initializing LED on GPIO %d", pin_input);
    this->pin = pin_input;

    gpio_reset_pin(this->pin); //Reset the GPIO to its default state
    gpio_set_direction(this->pin, GPIO_MODE_OUTPUT); //Set the GPIO as a output
    last_toggle_time = xTaskGetTickCount();
    }

void BinaryLed::update(){
    TickType_t now = xTaskGetTickCount();
    int interval = led_state ? blink_on_time : blink_off_time; //If condition, checks the ledstate 1 = ontime, 0 = offtime

    if(now - last_toggle_time >= interval/portTICK_PERIOD_MS){ //converting ms to tick
        led_state = !led_state; //flip the state
        setLed(led_state); //Lights on or off
        last_toggle_time = now;
    }
}

void BinaryLed::setLed(bool led_state)
{
    this->led_state = led_state;
    gpio_set_level(this->pin, led_state);
    ESP_LOGI(TAG, "SET LED TO:%d", led_state);
}

void BinaryLed::blink(int milliseconds_on, int milliseconds_off){
    blink_on_time = milliseconds_on;
    blink_off_time = milliseconds_off;
}


