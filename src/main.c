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
    initClockTo1MHz();
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
    adps_setGestureInt();
    __delay_cycles(5000);
    adps_setGestureDirection();
    __delay_cycles(5000);
    adps_setGestureProximityEnter();
    __delay_cycles(5000);
    adps_setGestureExitThreshold();
    __delay_cycles(5000);
    adps_setGestureFIFOExit();
    __delay_cycles(5000);
    adps_setGestureGain();
    __delay_cycles(5000);
    adps_setGestureOffset();
    __delay_cycles(5000);
    adps_setGesturePulse();
    __delay_cycles(5000);
    adps_startGestureMode();
    __delay_cycles(10000000);
    while(1)
    {
        __bis_SR_register(LPM0_bits + GIE);
        //waiting
    }


}
