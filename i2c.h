#ifndef I2C_H
#define I2C_H
#include <stdint.h>

#define I2C_FASTMODE 0x2D
#define I2C_STDMODE 0xB4

void i2c_init(uint8_t i2c_num);
void i2c_start(uint8_t i2c_num);
void i2c_write(uint8_t i2c_num, uint8_t address, uint8_t data[], uint64_t length);
void I2C_adress(uint8_t i2c_num, uint8_t address, uint8_t r_w);
void I2C_Data(uint8_t i2c_num, uint8_t data);
void i2c_stop(uint8_t i2c_num);

#endif