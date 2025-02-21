#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "Potentiometer.h"

static const char *TAG = "Potentiometer";

void Potentiometer::init(adc1_channel_t adc_pin)
{
    this->adc_pin = adc_pin;
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(adc_pin, ADC_ATTEN_DB_0);
}

int Potentiometer::getValue(){
    return this->value;
}

void Potentiometer::update()
{
    this->value = adc1_get_raw(this->adc_pin);
    //ESP_LOGI(TAG, "update value: %d", value);

    
    if(this->risingEdge == true)
    {
        if(value > this->threshold && this->thresholdState == false && this->onThresholdCallback != nullptr) // Check if the value is above the threshold
        {
            this->onThresholdCallback(this->adc_pin, value); // Call the callback
            this->thresholdState = true; // threshold has been crossed one time
        } else if (value < this->threshold) {
            this->thresholdState = false;
        }
    } else if (this->risingEdge == false) {
        if(value < this->threshold && this->thresholdState == false && this->onThresholdCallback != nullptr) // Check if the value is above the threshold
        {
            this->onThresholdCallback(this->adc_pin, value); // Call the callback
            this->thresholdState = true; // threshold has been crossed one time
        } else if (value > this->threshold) {
            this->thresholdState = false;
        }
    }
}

void Potentiometer::setOnThreshold(int threshold, bool risingEdge, void (*callback)(int pin_adc, int value))
{
    this->threshold = threshold;
    this->risingEdge = risingEdge;
    this->onThresholdCallback = callback;
}