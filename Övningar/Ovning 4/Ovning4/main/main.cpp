#include "sdkconfig.h"
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_task_wdt.h"

#define TWDT_TIMEOUT_MS         3000      
#define TASK_RESET_PERIOD_MS    2000      
#define MAIN_DELAY_MS           10000

extern "C" void app_main(void)
{	
    esp_task_wdt_config_t config = {
		.timeout_ms = TWDT_TIMEOUT_MS,
		.idle_core_mask = 0, 
		.trigger_panic= 0 
	};
    esp_err_t err = esp_task_wdt_init(&config);
};