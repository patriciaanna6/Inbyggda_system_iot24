#include <stdio.h>
#include "analog_led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
 
 
static const char *TAG = "AnalogLed";
 
#define DUTY_CYCLE_MAX 200
#define DUTY_CYCLE_MIN 0
#define DUTY_CYCLE_RANGE (DUTY_CYCLE_MAX - DUTY_CYCLE_MIN)
 
 
// Initialize the LED configuration
void AnalogLed::init(gpio_num_t pin)
{
    ESP_LOGI(TAG, "Initializing LED on GPIO %d", pin);
    this->pin = pin;
   
    // Configure the PWM timer
    this->ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,    // Use low-speed mode
        .duty_resolution = PWM_RESOLUTION,    // Resolution
        .timer_num = PWM_TIMER,               // Timer number
        .freq_hz = PWM_FREQ,                  // Frequency
        .clk_cfg = LEDC_AUTO_CLK             // Use the internal clock
    };
    ledc_timer_config(&ledc_timer);
 
    // Configure the PWM channel
    this->ledc_channel = {
        .gpio_num = pin,               // GPIO pin connected to the LED
        .speed_mode = LEDC_LOW_SPEED_MODE,    // Use low-speed mode
        .channel = PWM_CHANNEL,               // PWM channel
        .intr_type = LEDC_INTR_DISABLE,       // No interrupt
        .timer_sel = PWM_TIMER,               // Use the specified timer
        .duty = 0,                            // Initial duty cycle
        .hpoint = 0                           // Not used
    };
    ledc_channel_config(&ledc_channel);
}
 
// void update. ingen aning vad den gör
 
// Set the duty cycle of the PWM signal on the LED
void AnalogLed::setLed(int value)
{
    ledc_set_duty(this->ledc_channel.speed_mode, this->ledc_channel.channel, value);
    ledc_update_duty(this->ledc_channel.speed_mode, this->ledc_channel.channel);
}
 
// Create a sin wave with the LED. Period in ms
void AnalogLed::sin(int period)
{
    ESP_LOGI(TAG, "LED in sin wave");
 
    int delay = (period / 2) / DUTY_CYCLE_RANGE;
 
    for (int i = 0; i < 5; i++) {
        // Brightness decreasing from max to min
        for (int dutyCycle = DUTY_CYCLE_MAX; dutyCycle >= DUTY_CYCLE_MIN; dutyCycle--) {
            ledc_set_duty(this->ledc_channel.speed_mode, this->ledc_channel.channel, dutyCycle);
            ledc_update_duty(this->ledc_channel.speed_mode, this->ledc_channel.channel);
            vTaskDelay(pdMS_TO_TICKS(delay));  // Delay to control dimming speed
        }
 
        // Brightness increasing from min to max
        for (int dutyCycle = DUTY_CYCLE_MIN; dutyCycle < DUTY_CYCLE_MAX; dutyCycle++) {
            ledc_set_duty(this->ledc_channel.speed_mode, this->ledc_channel.channel, dutyCycle);
            ledc_update_duty(this->ledc_channel.speed_mode, this->ledc_channel.channel);
            vTaskDelay(pdMS_TO_TICKS(delay));  // Delay to control dimming speed
        }
    }
}