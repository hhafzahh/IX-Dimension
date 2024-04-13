#include <Wire.h>
#include <driver/uart.h>
#include <string.h>
#include <freertos/FreeRTOS.h>

// UART DEFINITIONS
#define TXD_PIN (GPIO_NUM_17)   // GPIO pin for TX
#define RXD_PIN (GPIO_NUM_16)   // GPIO pin for RX

// UART initialization  settings
void INITIALIZE_UART() {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_1, 1024, 1024, 0, NULL, 0);
}

void setup() {
    // Serial baud rate
    Serial.begin(115200);

    // Initialize UART connection
    INITIALIZE_UART();
}

void loop() {
    // Send "HELLO" message every 2 seconds
    uart_write_bytes(UART_NUM_1, "test\n", strlen("test\n"));
    delay(2000);
}
