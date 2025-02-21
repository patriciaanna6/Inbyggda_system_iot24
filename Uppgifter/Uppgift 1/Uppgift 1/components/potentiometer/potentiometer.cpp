#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "potentiometer.h"

static const char *TAG = "Potentiometer";


void Potentiometer::init(adc1_channel_t adc_pin)
{
    this->adc_pin = adc_pin;
    //adc1_config_width(ADC_WIDTH_BIT_12);
    //adc1_config_channel_atten(adc1_channel_t channel, adc_atten_t atten);
}

int Potentiometer::getValue()
{
    int value = adc1_get_raw(this->adc_pin);
    return value;
}

void Potentiometer::update()
{
    int value = getValue();
    //ESP_LOGI(TAG, "update value: %d", value);

    if(this->risingEdge && value > this->threshold){ // Check if the value is above the threshold
        if(this->onThresholdCallback != nullptr){
            this->onThresholdCallback(this->adc_pin, value); // Call the callback
        }
    } else if (!this->risingEdge && value < this->threshold) { // Check if the value is below the threshold
        if(this->onThresholdCallback != nullptr){
            this->onThresholdCallback(this->adc_pin, value); // Call the callback
        }
    }
}

void Potentiometer::setOnThreshold(int threshold, bool risingEdge, void (*callback)(int pin_adc, int value))
{
    this->threshold = threshold;
    this->risingEdge = risingEdge;
    this->onThresholdCallback = callback;
}