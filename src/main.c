/**
 * main.c
 */

#include <stdio.h>
#include <stdint.h>
#include "msp430g2553.h"
#include "i2c_std.h"
#include "adps_gesture.h"


int main(void)
{
    //uint8_t SlaveType0 [TYPE_0_LENGTH] = {0};
    //uint8_t data1[] = {0x1};
    //uint8_t data2[]={0xC9};

    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    initClockTo16MHz();
    initI2C();
    adps_init();
    __delay_cycles(10000000);
/*
    I2C_Master_WriteReg(SLAVE_ADDR, 0xAA, data1, TYPE_0_LENGTH);
    __delay_cycles(5000);
    I2C_Master_ReadReg(SLAVE_ADDR, 0xAA, TYPE_0_LENGTH);
    CopyArray(ReceiveBuffer, SlaveType0, TYPE_0_LENGTH);
    __delay_cycles(5000);
    I2C_Master_WriteReg(SLAVE_ADDR, 0xA6, data2, TYPE_0_LENGTH);
    __delay_cycles(5000);
    I2C_Master_ReadReg(SLAVE_ADDR, 0xA6, TYPE_1_LENGTH);
    CopyArray(ReceiveBuffer, SlaveType0, TYPE_0_LENGTH);
*/
    adps_resetSensor();
    __delay_cycles(5000);
    adps_setDefault();
    adps_startGestureMode();
    __delay_cycles(150000); // wait to get into Idle state

    /*read status */
    I2C_Master_ReadReg(SLAVE_ADDR, ID, TYPE_0_LENGTH);
    __delay_cycles(5000);
    I2C_Master_ReadReg(SLAVE_ADDR, STATUS, TYPE_0_LENGTH);
    __delay_cycles(5000);
    I2C_Master_ReadReg(SLAVE_ADDR, GFIFO_U, TYPE_1_LENGTH);
    __delay_cycles(5000);
    I2C_Master_ReadReg(SLAVE_ADDR, GFIFO_D, TYPE_1_LENGTH);
    __delay_cycles(5000);
    I2C_Master_ReadReg(SLAVE_ADDR, GFIFO_L, TYPE_1_LENGTH);
    __delay_cycles(5000);
    I2C_Master_ReadReg(SLAVE_ADDR, GFIFO_R, TYPE_1_LENGTH);
    __delay_cycles(5000);
    I2C_Master_ReadReg(SLAVE_ADDR, STATUS, TYPE_0_LENGTH);
    __delay_cycles(5000);

    adps_startProcess(); //start receiving process 


    __bis_SR_register(LPM0_bits + GIE);
    //waiting


    return 0;
}
