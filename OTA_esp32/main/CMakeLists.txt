idf_component_register(
    SRCS "OTA_esp32_main.c" "../src/wifi_station.c" "../src/tcp_client_v4.c" "../src/async_uart.c"
    PRIV_REQUIRES "spi_flash"
    INCLUDE_DIRS "." "../inc"
    REQUIRES "driver"  "esp_wifi" "nvs_flash" # add the components as a requirement
)
