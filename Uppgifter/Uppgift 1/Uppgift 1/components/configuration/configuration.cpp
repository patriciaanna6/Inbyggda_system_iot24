#include <stdio.h>
#include <iostream>
#include <cstring>
#include "configuration.h"
#include "esp_log.h"

#define TAG "Storage"

#define KEY_DEVICE "keydevice"
#define KEY_SERIAL "keyserial"

Storage::Storage() {}

Storage::~Storage() {
    printf("NVS flash closing\n");
    nvs_close(this->nvsHandle); // Close NVS handle when the object is destroyed
}

esp_err_t Storage::init() {
    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    if (err != ESP_OK) {
        printf("NVS flash init failed: %s\n", esp_err_to_name(err));
        return err;
    }

    // Create NVS handle and open the storage. Exit if it fails
    nvs_handle_t nvsHandle;
    err = nvs_open("storage", NVS_READWRITE, &nvsHandle);
    if (err != ESP_OK) {
        printf("Failed to open NVS: %s!\n", esp_err_to_name(err));
        return err;
    }

    // Successfully opened NVS
    printf("NVS opened\n");
    this->nvsHandle = nvsHandle;

    // Read device name from NVS, or create a default value if it doesn't exist
    printf("Reading from NVS:\n");
    char deviceName[20];
    size_t nameLength = sizeof(this->deviceName);
    err = nvs_get_str(nvsHandle, KEY_DEVICE, this->deviceName, &nameLength); // Read from NVS, and store in deviceName
    printf("INIT Device name: %s\n", this->deviceName);
    switch (err) {
        case ESP_OK:
            strncpy(this->deviceName, deviceName, sizeof(this->deviceName));
            printf("Device name: %s\n", this->deviceName);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("Device name: not initialized yet\n");
            break;
        default :
            printf("Device name: error (%s) while reading\n", esp_err_to_name(err));
    }

    // Read serial number from NVS, or create a default value if it doesn't exist
    char serialNumber[20];
    size_t numberLength = sizeof(serialNumber);
    err = nvs_get_str(nvsHandle, KEY_SERIAL, serialNumber, &numberLength); // Read from NVS, and store in serialNumber
    switch (err) {
        case ESP_OK:
            strncpy(this->serialNumber, serialNumber, sizeof(this->serialNumber));
            
            printf("Serial number: %s\n", serialNumber);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("Serial number: not initialized yet\n");
            break;
        default :
            printf("Serial number: error (%s) while reading\n", esp_err_to_name(err));
    }

    return ESP_OK;
}

const char* Storage::getDeviceName() {
    return this->deviceName; // Return the device name from memory
}

const char* Storage::getSerialNumber() {
    return this->serialNumber; // Return the serial number from memory
}


esp_err_t Storage::setDeviceName(const char* newDeviceName) {
    // Copy new device name to working memory
    strncpy(this->deviceName, newDeviceName, 10);
    this->deviceName[sizeof(this->deviceName) - 1] = '\0'; // Null-terminate

    // Save device name to NVS
    esp_err_t err = nvs_set_str(this->nvsHandle, KEY_DEVICE, newDeviceName);
    if (err != ESP_OK) {
        printf("setDeviceName: error (%s) while writing\n", esp_err_to_name(err));
        return err;
    }

    err = nvs_commit(nvsHandle);
    if (err != ESP_OK) {
        printf("setDeviceName: failed to commit device name to NVS");
        return err;
    }

    printf("setDeviceName success. New deviceName: %s\n", newDeviceName);
    return ESP_OK;
}

esp_err_t Storage::setSerialNumber(const char* newSerialNumber) {
    // Copy newSerialNumberto working memory
    strncpy(this->serialNumber, newSerialNumber, 10);
    this->serialNumber[sizeof(this->serialNumber) - 1] = '\0'; // Null-terminate

    // Save device name to NVS
    esp_err_t err = nvs_set_str(this->nvsHandle, KEY_SERIAL, this->serialNumber);
    if (err != ESP_OK) {
        printf("setSerialNumber: error (%s) while writing\n", esp_err_to_name(err));
        return err;
    }

    err = nvs_commit(nvsHandle);
    if (err != ESP_OK) {
        printf("setSerialNumber: failed to commit device name to NVS");
        return err;
    }

    printf("setSerialNumber success. New serialNumber: %s\n", this->serialNumber);
    return ESP_OK;
}