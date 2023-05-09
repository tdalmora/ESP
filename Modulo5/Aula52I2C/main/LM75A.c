#include "LM75A.h"

// Função pra leitura de temperatura. 
float lm75aGetValues(){
    uint8_t rawData[2]; // O valor cru vem aqui.
    bool neg = 0;
    int16_t data = 0;
    float temperatura = 0;

    i2c_cmd_handle_t cmd_handle = i2c_cmd_link_create(); //Comanda o barramento.
    i2c_master_start(cmd_handle);
    i2c_master_write_byte(cmd_handle,(LM75A_ADDR << 1) | I2C_MASTER_READ,true); // O valor ele vem do data sheet. O shift é pro causa disso, é o bit de leitura.
    i2c_master_read(cmd_handle,(uint8_t *) rawData,2,I2C_MASTER_ACK);
    i2c_master_stop(cmd_handle);
    i2c_master_cmd_begin(I2C_NUM_0, cmd_handle, pdMS_TO_TICKS(250)); // Aplicando tudo. Se o chip não responder em 250ms deu algo errado.
    i2c_cmd_link_delete(cmd_handle);

    if (rawData[0] >> 8 == 1){ // Se o valor é negativo.
        neg = true;
        rawData[0] = rawData[0] & 0b01111111;
    }

    data = (rawData[0] << 8 | rawData[1]) >> 5;   // Tratamento do dado pelo data sheet.
    temperatura = (data * 0.125);					// Escala
    if (neg == 1){
        temperatura = temperatura*(-1);			// Mada pra positivo.
    }

    return temperatura;
}