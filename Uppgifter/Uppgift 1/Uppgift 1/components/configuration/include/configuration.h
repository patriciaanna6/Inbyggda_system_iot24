
#include "nvs_flash.h"
#include "nvs.h"
#include <cstring>

class Config{
    private: 
    nvs_handle_t nvsHandle;
    char deviceName[];
    char serialNumber[];


    public:
    Config(); //constructor
    ~Config(); //destructor

    esp_err_t init(); //Initiating from NVS
    const char* getDeviceName(); //Returning device name from "arbetsminne"
    const char* getSerialNumber(); //Returning device name from "arbetsminne"
    esp_err_t setDeviceName(const char* deviceName); //Set and saving devicename
    esp_err_t setSerialNumber(const char* setSerialNumber); //Set an saving serialnumber


};
