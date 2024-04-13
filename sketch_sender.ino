#include <Wire.h>
#include <driver/uart.h>
#include <string.h>

#define TXD_PIN GPIO_NUM_17
#define RXD_PIN GPIO_NUM_16

void setup() {
    Serial.begin(115200);

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

void loop() {
    uint8_t data[] = { 'P', 'L', 'E', 'A','S','E', '\n' }; // Sending bytes explicitly
    uart_write_bytes(UART_NUM_1, (char*)data, sizeof(data));
    delay(2000);
}
