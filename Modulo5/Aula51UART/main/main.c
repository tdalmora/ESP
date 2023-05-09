#include <stdio.h>
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"

#define TXD1_PIN 26
#define RXD1_PIN 25

#define RX_BUX_SIZE 1024

char UART1_BUF[RX_BUX_SIZE];


void app_main(void)
{
    memset(UART1_BUF, 0, sizeof(UART1_BUF));

    uart_config_t uart1Conf = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_param_config(UART_NUM_1,&uart1Conf);
    uart_set_pin(UART_NUM_1,TXD1_PIN,RXD1_PIN,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_1,RX_BUX_SIZE,0,0,NULL,0);

    while(1){
        if (uart_read_bytes(UART_NUM_1,(uint8_t *) UART1_BUF,RX_BUX_SIZE,pdMS_TO_TICKS(250)) > 0 ){
            uart_write_bytes(UART_NUM_1,UART1_BUF,sizeof(UART1_BUF));
            uart_write_bytes(UART_NUM_1,"\n",sizeof("\n"));
            uart_write_bytes(UART_NUM_1,"\r",sizeof("\r"));
        }
    }
}