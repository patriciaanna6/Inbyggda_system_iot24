#include <stdio.h>
#include "esp_log.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "blinklamp.h"

#define LEDC_TIMER       LEDC_TIMER_0  
#define LEDC_MODE        LEDC_LOW_SPEED_MODE     
#define LEDC_OUTPUT_IO   (5) // Define the output GPIO      
#define LEDC_CHANNEL     LEDC_CHANNEL_0      
#define LEDC_DUTY_RES    LEDC_TIMER_13_BIT       
#define LEDC_DUTY        (4096)       
#define LEDC_FREQUENCY   (4000)

static void example_ledc_init(void)
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,  
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_channel = {
        .gpio_num        = LEDC_OUTPUT_IO,
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .intr_type       = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER,
        .duty           = 0, 
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}



extern "C" void app_main(void)
{
    /*example_ledc_init();
   
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
    
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));*/

    blink_lamp::ledc_init();
}



