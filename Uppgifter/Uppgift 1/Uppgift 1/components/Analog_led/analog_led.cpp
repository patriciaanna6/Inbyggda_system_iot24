#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "analog_led.h"

static const char *TAG = "AnalogLed";

// Initialize the LED configuration
void AnalogLed::init(gpio_num_t pin)
{
    ESP_LOGI(TAG, "Initializing AnalogLed on GPIO %d", pin);
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

// Decrease or increase the brightness of the LED
void AnalogLed::update()
{
    TickType_t now = xTaskGetTickCount();

    if(now - this->last_update_time >= this->interval_per_step){ // Check if it's time to update
        if(this->is_going_up){
            ESP_LOGI(TAG, "GOING UP %lu", this->ledc_channel.duty);
            setLed(this->ledc_channel.duty + DUTY_CYCLE_STEP);
            
            // Check if it's time to flip the direction
            if(this->ledc_channel.duty >= DUTY_CYCLE_MAX){
                this->is_going_up = 0; // Flip the direction
            }
        } else {
            ESP_LOGI(TAG, "GOING DOWN %lu", this->ledc_channel.duty);
            setLed(this->ledc_channel.duty - DUTY_CYCLE_STEP);

            // Check if it's time to flip the direction
            if(this->ledc_channel.duty <= DUTY_CYCLE_MIN){
                this->is_going_up = 1; // Flip the direction
            }
        }
        this->last_update_time = now; // Set current time for the next update/reset the timer. 
    }
}

// Set the duty cycle of the PWM signal on the LED
void AnalogLed::setLed(int value)
{
    this->ledc_channel.duty = value;
    ledc_set_duty(this->ledc_channel.speed_mode, this->ledc_channel.channel, value); //Setting the value as PWM duty
    ledc_update_duty(this->ledc_channel.speed_mode, this->ledc_channel.channel);
}

// Set period for a sin wave with the LED. Period in ms
void AnalogLed::sin(int period) // In ms    
{
    ESP_LOGI(TAG, "LED in sin wave");
    
    // interval_per_step is how long we should wait before we change the LED brightness
    // How to calculate:
    // If period is 1 second, then the led will decrease brightness in 0.5 seconds and increase brightness in 0.5 seconds
    // During decrease, LED will start from max (200) down to min (0). Every step is 10
    // So, there is 20 steps in 0.5 seconds. So, 40 steps in 1 second
    // 1 second = 1000 ms. 1 way is (1000/2)=500ms
    // Then 500ms / 20 steps = 25ms per step
    this->interval_per_step = pdMS_TO_TICKS((period / 2) / (DUTY_CYCLE_RANGE / DUTY_CYCLE_STEP));
}