/*
 * adps_gesture.c
 *
 *  Created on: 03.02.2018
 *      Author: Christoph
 */

#include <msp430.h>
#include "adps_gesture.h"
#include "adps_calc.h"
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
    P2IFG &= (~BIT6); // P2.5 IFG clear
    P2IFG &= (~BIT7); // P2.5 IFG clear
    P2IE   |= (BIT5);  //enable interrupt
    //usdelay(6000);     //POR -> SLEEP state
}

void adps_startGestureMode(void)
{
    uint8_t data[] = {0x65};
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
    uint8_t data[] = {0x4};
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



void adps_setDefault(void)
{
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
}

MOTION adps_startProcess(void)
{
    gesture_type FIFO_mem; 
    MOTION direction = none;

    do
    {

        while (ack_gesture != 1)
        {
            //waiting for gesture FIFO overflow
        }

        ack_gesture = 0;

        I2C_Master_ReadReg(SLAVE_ADDR, STATUS, TYPE_0_LENGTH);
        __delay_cycles(5000);
        I2C_Master_ReadReg(SLAVE_ADDR, GFIFO_U, TYPE_4_LENGTH);
        CopyArray(ReceiveBuffer, FIFO_mem.up, TYPE_4_LENGTH);
        __delay_cycles(5000);
        I2C_Master_ReadReg(SLAVE_ADDR, GFIFO_D, TYPE_4_LENGTH);
        CopyArray(ReceiveBuffer, FIFO_mem.down, TYPE_4_LENGTH);
        __delay_cycles(5000);
        I2C_Master_ReadReg(SLAVE_ADDR, GFIFO_L, TYPE_4_LENGTH);
        CopyArray(ReceiveBuffer, FIFO_mem.left, TYPE_4_LENGTH);
        __delay_cycles(5000);
        I2C_Master_ReadReg(SLAVE_ADDR, GFIFO_R, TYPE_4_LENGTH);
        CopyArray(ReceiveBuffer, FIFO_mem.right, TYPE_4_LENGTH);
        __delay_cycles(5000);
        I2C_Master_ReadReg(SLAVE_ADDR, STATUS, TYPE_0_LENGTH);
        __delay_cycles(5000);

        gesture_find(&FIFO_mem);
    }
    while(direction == none);

    return direction;
}



#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    ack_gesture = 1;
    P2IFG &= (~BIT5); // P2.5 IFG clear

}

