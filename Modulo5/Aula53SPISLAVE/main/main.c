//SLAVE

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//#include "esp_log.h"
#include "driver/spi_slave.h"
#include "driver/gpio.h"


#define GPIO_MOSI 27
#define GPIO_MISO 32
#define GPIO_SCLK 33
#define GPIO_CS 25

#define REQUEST_BYTE 0x5E //94 em decimal

void spi_slave_task(void *arg)
{


    uint8_t* data_rx = (uint8_t*) malloc(sizeof(uint8_t));
    uint8_t* data_tx = (uint8_t*) malloc(sizeof(uint8_t));   

    data_tx[0] = 0;
    data_rx[0] = 0;

    //Configuration for the SPI bus
    spi_bus_config_t buscfg={
        .mosi_io_num=GPIO_MOSI,
        .miso_io_num=GPIO_MISO,
        .sclk_io_num=GPIO_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };

    //Configuration for the SPI slave interface
    spi_slave_interface_config_t slvcfg={
        .mode=0,
        .spics_io_num=GPIO_CS,
        .queue_size=1,
        .flags=0,

    };

    //Enable pull-ups on SPI lines so we don't detect rogue pulses when no master is connected.
    gpio_set_pull_mode(GPIO_MOSI, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(GPIO_SCLK, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(GPIO_CS, GPIO_PULLUP_ONLY);

    //Initialize SPI slave interface
    printf("Inicializando... ");
    spi_slave_initialize(HSPI_HOST, &buscfg, &slvcfg, SPI_DMA_CH_AUTO);
    printf("ok \n");

    //Contador
    uint8_t counter = 0;

    spi_slave_transaction_t transaction;
    memset(&transaction, 0, sizeof(transaction));
    transaction.length=8;
    transaction.tx_buffer=data_tx;
    transaction.rx_buffer=data_rx;

    while (1) {        
        counter++;
        data_tx[0] = 0;

        ESP_ERROR_CHECK(spi_slave_transmit(HSPI_HOST, &transaction, portMAX_DELAY)); // Aguarda aqui até a transmissão vier.
        printf("RequisiÃ§Ã£o: %i \n", (int)data_rx[0] );

        // Check if the received byte is the request byte
        if (data_rx[0] == REQUEST_BYTE) {           
            data_tx[0] = counter;
            ESP_ERROR_CHECK(spi_slave_transmit(HSPI_HOST, &transaction, portMAX_DELAY));                      
        }  
    }
    free(data_rx);
    free(data_tx);
    ESP_ERROR_CHECK(spi_slave_free(HSPI_HOST));
}

void app_main()
{
    xTaskCreate(spi_slave_task, "spi_slave_task", 2048, NULL, 5, NULL);
}