/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "wifi_station.h"
#include "tcp_client_v4.h"
#include "async_uart.h"


static const char *TAG = "OTA esp32";

#define BLINK_GPIO 2

// Blink function
void blink_task(void *pvParameter) {
    uint8_t blink_led_state = 0;

    ESP_LOGI(TAG, "Blinking LED,current state:%d", blink_led_state);
    // configure the GPIO
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(BLINK_GPIO, 0);

    while (1) {
        gpio_set_level(BLINK_GPIO, blink_led_state);
        vTaskDelay(2000 / portTICK_PERIOD_MS); // delay 1s
        
        blink_led_state = !blink_led_state; // toggle the led state
    }
}

void hello_ota_esp32(void *pvParameter)
{
    ESP_LOGI(TAG, "Hello OTA_esp32!");

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "This is %s chip with %d CPU core(s), %s%s%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
            (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
            (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    ESP_LOGI(TAG, "silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        ESP_LOGE(TAG, "Get flash size failed");
        return;
    }

    ESP_LOGI(TAG, "%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    ESP_LOGI(TAG, "Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());
    
    fflush(stdout);
    vTaskDelay(2000 / portTICK_PERIOD_MS); // delay 2s
}

void app_main(void)
{
    if (1)
    {
        hello_ota_esp32(NULL);
    }
    else
    {
        wifi_app_main();
    
        uart_app_main();
    
        // create a task to run tcp_client_v4
        xTaskCreate(tcp_app_main, "tcp client", 4096, NULL, 5, NULL);
    
        //create a task to blink the LED
        xTaskCreate(blink_task, "blink_task", 2048, NULL, 5, NULL);
        
    } 
}
