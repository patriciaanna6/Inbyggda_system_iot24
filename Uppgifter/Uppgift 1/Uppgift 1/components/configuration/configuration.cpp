#include <stdio.h>
#include <iostream>
#include <cstring> // For strcpy and strncpy
#include "configuration.h"

Config::Config() {}

Config::~Config() {
    nvs_close(nvsHandle); // Close NVS handle when the object is destroyed
}

esp_err_t Config::init() {
    esp_err_t err = nvs_flash_init();
    
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        err = nvs_flash_init();
    }
    
    if (err != ESP_OK) {
        std::cerr << "NVS flash init failed: " << esp_err_to_name(err) << std::endl;
        return err;
    }

    // Open NVS storage
    err = nvs_open("storage", NVS_READWRITE, &nvsHandle);
    if (err != ESP_OK) {
        std::cerr << "Failed to open NVS: " << esp_err_to_name(err) << std::endl;
        return err;
    }

    // Read device name from NVS
    size_t len = sizeof(deviceName);
    err = nvs_get_str(nvsHandle, "device_name", deviceName, &len);
    if (err != ESP_OK) {
        std::cerr << "Failed to read device name from NVS: " << esp_err_to_name(err) << std::endl;
        strcpy(deviceName, "default_device"); // Set a default value
    }

    // Read serial number from NVS
    len = sizeof(serialNumber);
    err = nvs_get_str(nvsHandle, "serial_number", serialNumber, &len);
    if (err != ESP_OK) {
        std::cerr << "Failed to read serial number from NVS: " << esp_err_to_name(err) << std::endl;
        strcpy(serialNumber, "000000"); // Set a default serial number
    }

    return ESP_OK;
}

const char* Config::getDeviceName() {
    return deviceName; // Return the device name from memory
}

const char* Config::getSerialNumber() {
    return serialNumber; // Return the serial number from memory
}

esp_err_t Config::setDeviceName(const char* newDeviceName) {
    if (strlen(newDeviceName) >= sizeof(deviceName)) {
        return ESP_ERR_NVS_INVALID_LENGTH; // Prevent buffer overflow
    }

    // Copy new device name to working memory
    strncpy(deviceName, newDeviceName, sizeof(deviceName) - 1);
    deviceName[sizeof(deviceName) - 1] = '\0'; // Null-terminate

    // Save device name to NVS
    esp_err_t err = nvs_set_str(nvsHandle, "device_name", deviceName);
    if (err != ESP_OK) {
        std::cerr << "Failed to set device name in NVS: " << esp_err_to_name(err) << std::endl;
        return err;
    }

    err = nvs_commit(nvsHandle);
    if (err != ESP_OK) {
        std::cerr << "Failed to commit device name to NVS: " << esp_err_to_name(err) << std::endl;
    }

    return err;
}

esp_err_t Config::setSerialNumber(const char* newSerialNumber) {
    if (strlen(newSerialNumber) >= sizeof(serialNumber)) {
        return ESP_ERR_NVS_INVALID_LENGTH; // Prevent buffer overflow
    }

    // Copy new serial number to working memory
    strncpy(serialNumber, newSerialNumber, sizeof(serialNumber) - 1);
    serialNumber[sizeof(serialNumber) - 1] = '\0'; // Null-terminate

    // Save serial number to NVS
    esp_err_t err = nvs_set_str(nvsHandle, "serial_number", serialNumber);
    if (err != ESP_OK) {
        std::cerr << "Failed to set serial number in NVS: " << esp_err_to_name(err) << std::endl;
        return err;
    }

    err = nvs_commit(nvsHandle);
    if (err != ESP_OK) {
        std::cerr << "Failed to commit serial number to NVS: " << esp_err_to_name(err) << std::endl;
    }

    return err;
}
