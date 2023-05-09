#include <stdio.h>
#include "esp_log.h"

void app_main(void)
{
    ESP_LOGI(CONFIG_ADS1115_TAG, "SDA PIN: %d", CONFIG_ADS1115_SDA);
    ESP_LOGI(CONFIG_ADS1115_TAG, "SCL PIN: %d", CONFIG_ADS1115_SCL);

    bool ADS1115_ENABLE = 0;
    #ifdef  CONFIG_ADS1115_ENABLE
        ADS1115_ENABLE = 1;
    #else
        ADS1115_ENABLE = 0;
    #endif

    ESP_LOGI(CONFIG_ADS1115_TAG, "ADS 1115 STATUS: %s", ADS1115_ENABLE ? "yes" : "no");

    int OP_SAMPLER = 0;

    #ifdef CONFIG_OP_1
        OP_SAMPLER = 1;
    #elif CONFIG_OP_2
        OP_SAMPLER = 2;
    #elif CONFIG_OP_3
        OP_SAMPLER = 3;
    #else 
        OP_SAMPLER = 4;
    #endif

    ESP_LOGI(CONFIG_ADS1115_TAG, "SAMPLE RATE OPTION %d", OP_SAMPLER );
}