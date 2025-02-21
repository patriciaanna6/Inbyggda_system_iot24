#include "driver/adc.h"
#include "driver/gpio.h"

class Potentiometer
{
private:
    adc1_channel_t adc_pin;
    int threshold = 0;
    bool risingEdge = true;
    bool thresholdState = false;
    void(*onThresholdCallback)(int adc_pin, int value) = nullptr;
public:
    void init(adc1_channel_t adc_pin);
    void update();
    int getValue();
    void setOnThreshold(int threshold, bool risingEdge, void(*callback)(int adc_pin, int value));
};