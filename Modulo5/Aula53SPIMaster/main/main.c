// MASTER -> 0x5e -> SLAVE -> CONTADOR

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/spi_master.h"
#include "esp_spi_flash.h"

#include "driver/gpio.h"

#define GPIO_MOSI 14
#define GPIO_MISO 27
#define GPIO_SCLK 26
#define GPIO_CS 25

#define REQUEST_BYTE 0x5E //94 em decimal

void spi_master_task(void *arg){ //Task pra utilizar o SPI.
    uint8_t* data_tx = (uint8_t*) malloc(sizeof(uint8_t));
    uint8_t* data_rx = (uint8_t*) malloc(sizeof(uint8_t));

    spi_device_handle_t spi;

    spi_bus_config_t buscfg={
        .miso_io_num=GPIO_MISO,
        .mosi_io_num=GPIO_MOSI,
        .sclk_io_num=GPIO_SCLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=0
    };

    spi_device_interface_config_t devcfg={
        .command_bits=0,
        .address_bits=0,
        .dummy_bits=0,
        .clock_speed_hz=100*1000,
        .duty_cycle_pos=128,
        .mode=0,
        .spics_io_num=GPIO_CS,
        .cs_ena_posttrans=3, // Delay pra comutar CS, garantindo pegar informação correta.
        .queue_size=1,
        .pre_cb=NULL,
    };

    gpio_set_pull_mode(GPIO_MOSI, GPIO_PULLUP_ENABLE);
    gpio_set_pull_mode(GPIO_SCLK, GPIO_PULLUP_ENABLE);
    gpio_set_pull_mode(GPIO_CS, GPIO_PULLUP_ENABLE);

    ESP_ERROR_CHECK(spi_bus_initialize(HSPI_HOST,&buscfg,1));
    ESP_ERROR_CHECK(spi_bus_add_device(HSPI_HOST,&devcfg,&spi));

    spi_transaction_t transaction; 					//Variável para transação de comunicação.
    memset(&transaction,0,sizeof(transaction));		//Setando a estrutura.
    transaction.length=8; 							//Quantos bits vão ser enviados
    data_tx[0]=REQUEST_BYTE;						//Dado a ser enviado.
    transaction.tx_buffer=data_tx;					//Os buffers são ponterios.
    transaction.rx_buffer=data_rx;

    while(1){
        data_tx[0] = REQUEST_BYTE;

        ESP_ERROR_CHECK(spi_device_transmit(spi, &transaction));

        data_tx[0]=0;
        ESP_ERROR_CHECK(spi_device_transmit(spi, &transaction));  // Essa função tanto envia quanto escreve, já que SPI é Full Duplex
        printf("Dado recebido: %d\n", data_rx[0]);

        vTaskDelay(200/portTICK_PERIOD_MS);
    }
    free(data_rx);
    free(data_tx);
    ESP_ERROR_CHECK(spi_bus_remove_device(spi)); // Desligando o BUS SPI
}

void app_main(void)
{
    xTaskCreate(spi_master_task,"spi_master_task", 2048, NULL, 5, NULL); //Task de alta prioridade.
}