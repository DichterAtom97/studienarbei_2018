/*
 * adps_gesture.c
 *
 *  Created on: 03.02.2018
 *      Author: Christoph
 */

#include <msp430.h>
#include "adps_gesture.h"
#include "i2c_std.h"


/**
 * \brief initialize P2.5 as input and enables interrupt at falling edge
 *
 */
void adps_init(void)
{
    P2SEL  &= 0x00;    //P2.x is GPIO
    P2SEL2 &= 0x00;
    P2DIR  &= (~BIT5); //P2.x is input
    P2IES  |= (BIT5);  //Falling Edge 1->0
    P2IFG  &= (~BIT5); //clear interrupt flag
    P2IE   |= (BIT5);  //enable interrupt
    //usdelay(6000);     //POR -> SLEEP state
}

void adps_startGestureMode(void)
{
    uint8_t data[] = {0x41};
    I2C_Master_WriteReg(SLAVE_ADDR, ENABLE, data, ONE_MESSAGE);
}

void adps_resetSensor(void)
{
    uint8_t data[] = {0x00};
    I2C_Master_WriteReg(SLAVE_ADDR, ENABLE, data, ONE_MESSAGE);
}

void adps_setGestureInt(void)
{
    uint8_t data[] = {0x3};
    I2C_Master_WriteReg(SLAVE_ADDR, GCONFIG4, data, ONE_MESSAGE);
}

void adps_setGestureDirection(void)
{
    uint8_t data[] = {0x00};
    I2C_Master_WriteReg(SLAVE_ADDR, GCONFIG3, data, ONE_MESSAGE);
}

void adps_setGestureProximityEnter(void)
{
    uint8_t data[] = {0x28};
    I2C_Master_WriteReg(SLAVE_ADDR, GPENTH, data, ONE_MESSAGE);
}

void adps_setGestureExitThreshold(void)
{
    uint8_t data[] = {0x1E};
    I2C_Master_WriteReg(SLAVE_ADDR, GEXTH, data, ONE_MESSAGE);
}

void adps_setGestureFIFOExit(void)
{
    uint8_t data[] = {0x40};
    I2C_Master_WriteReg(SLAVE_ADDR, GCONFIG1, data, ONE_MESSAGE);
}

void adps_setGestureGain(void)
{
    uint8_t data[] = {0x42};
    I2C_Master_WriteReg(SLAVE_ADDR, GCONFIG2, data, ONE_MESSAGE); //set Gain, wait and LED current
}

void adps_setGestureOffset(void)
{
    uint8_t data[] = {0x00};
    I2C_Master_WriteReg(SLAVE_ADDR, GOFFSET_U, data, ONE_MESSAGE); //set Offset
    __delay_cycles(5000);
    I2C_Master_WriteReg(SLAVE_ADDR, GOFFSET_D, data, ONE_MESSAGE); //set Offset
    __delay_cycles(5000);
    I2C_Master_WriteReg(SLAVE_ADDR, GOFFSET_L, data, ONE_MESSAGE); //set Offset
    __delay_cycles(5000);
    I2C_Master_WriteReg(SLAVE_ADDR, GOFFSET_R, data, ONE_MESSAGE); //set Offset
}

void adps_setGesturePulse(void)
{
    uint8_t data[] = {0xC9};
    I2C_Master_WriteReg(SLAVE_ADDR, GPULSE, data, ONE_MESSAGE);
}



#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P2IFG &= (~BIT5); // P2.5 IFG clear
}
