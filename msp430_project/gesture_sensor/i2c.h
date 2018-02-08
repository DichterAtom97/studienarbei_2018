/*
 * i2c.h
 *
 *  Created on: 03.02.2018
 *      Author: Christoph
 */

#ifndef I2C_H_
#define I2C_H_

#define ONEBYTEADDR 1
#define TWOBYTEADDR 2
#define WRITE       0                       // ISR mode WRITE or READ
#define READ        1
#define NOACK       2

void i2c_init(void);
void i2c_tx(unsigned char slave_addr, unsigned char *txdata, unsigned char bufSize, unsigned char reg_addr);
void i2c_rx(unsigned char, unsigned char *, unsigned char, unsigned char, unsigned char);
void usdelay(int);


typedef struct
{
    volatile unsigned char *data_buf;       // address of tx or rx data buffer
    volatile unsigned char buf_size;        // size of the buffer
    volatile unsigned char buf_index;       // index in the buffer
    volatile unsigned char addr_index;      // index of the byte address (0,1)
    volatile unsigned char isr_mode;        // Tx or Rx affects the interrupt logic
    volatile unsigned char addr_reg;        // register address
    volatile unsigned char addr_type;       // two bytes like eeprom or 1 byte like RTC for example
} i2c_t;

#endif /* I2C_H_ */
