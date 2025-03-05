#include "nvs_flash.h"
#include <cstring>

class Storage
{
    private: 
    nvs_handle_t nvsHandle;
    char deviceName[20];
    char serialNumber[20];

    public:
    Storage(); //constructor
    ~Storage(); //destructor

    esp_err_t init(); //Initiating from NVS
    const char* getDeviceName(); //Returning device name from "arbetsminne"
    const char* getSerialNumber(); //Returning device name from "arbetsminne"
    esp_err_t setDeviceName(const char* deviceName); //Set and saving devicename
    esp_err_t setSerialNumber(const char* setSerialNumber); //Set an saving serialnumber
};