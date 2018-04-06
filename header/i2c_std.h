/*
 * i2c_std.h
 *
 *  Created on: 23.03.2018
 *      Author: Christoph
 */

#ifndef I2C_STD_H_
#define I2C_STD_H_

#include <stdint.h>
#include <stdbool.h>
#include "msp430g2553.h"

#define SLAVE_ADDR  0x39

#define MAX_BUFFER_SIZE     20

#define TYPE_0_LENGTH   1
#define TYPE_1_LENGTH   2
#define TYPE_2_LENGTH   6
#define TYPE_4_LENGTH   4

uint8_t ReceiveBuffer[MAX_BUFFER_SIZE];

//******************************************************************************
// General I2C State Machine ***************************************************
//******************************************************************************


typedef enum I2C_ModeEnum{
    IDLE_MODE,
    NACK_MODE,
    TX_REG_ADDRESS_MODE,
    RX_REG_ADDRESS_MODE,
    TX_DATA_MODE,
    RX_DATA_MODE,
    SWITCH_TO_RX_MODE,
    SWITHC_TO_TX_MODE,
    TIMEOUT_MODE
} I2C_Mode;
void initI2C(void);

void initClockTo16MHz(void);


/* I2C Write and Read Functions */

/* For slave device with dev_addr, writes the data specified in *reg_data
 *
 * dev_addr: The slave device address.
 *           Example: SLAVE_ADDR
 * reg_addr: The register or command to send to the slave.
 *           Example: CMD_TYPE_0_MASTER
 * *reg_data: The buffer to write
 *           Example: MasterType0
 * count: The length of *reg_data
 *           Example: TYPE_0_LENGTH
 *  */
I2C_Mode I2C_Master_WriteReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t count);

/* For slave device with dev_addr, read the data specified in slaves reg_addr.
 * The received data is available in ReceiveBuffer
 *
 * dev_addr: The slave device address.
 *           Example: SLAVE_ADDR
 * reg_addr: The register or command to send to the slave.
 *           Example: CMD_TYPE_0_SLAVE
 * count: The length of data to read
 *           Example: TYPE_0_LENGTH
 *  */
I2C_Mode I2C_Master_ReadReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t count);

void CopyArray(uint8_t *source, uint8_t *dest, uint8_t count);


#endif /* I2C_STD_H_ */
