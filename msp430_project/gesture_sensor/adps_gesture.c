/*
 * adps_gesture.c
 *
 *  Created on: 03.02.2018
 *      Author: Christoph
 */

#include <msp430.h>
#include "adps_gesture.h"
#include "i2c.h"


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
    usdelay(6000);     //POR -> SLEEP state
}

void adps_startGestureMode(void)
{
    i2c_tx(ADPS99_ADDR, GESTURE_MODE, ONE_MESSAGE, ENABLE); //enable PON and gesture mode
}

void adps_stopGestureMode(void)
{
    i2c_tx(ADPS99_ADDR, ENABLE_RESET, ONE_MESSAGE, ENABLE); //->SLEEP mode for adps_config
}

void adps_setGestureInt(void)
{
    i2c_tx(ADPS99_ADDR, GESTURE_INT, ONE_MESSAGE, GCONFIG4); //set GMODE and GIEN(HW-interrupt)
}

void adps_setGestureDirection(unsigned char *direction)
{
    if (direction == UP_DOWN)
    {
        i2c_tx(ADPS99_ADDR, UP_DOWN, sizeof(direction)-1, GCONFIG3); //use all four directions
    }
    else if(direction == RIGTH_LEFT)
    {
        i2c_tx(ADPS99_ADDR, RIGTH_LEFT, sizeof(direction)-1, GCONFIG3); //use all four directions
    }
    else
    {
        i2c_tx(ADPS99_ADDR, ALL_DIRECTIONS, sizeof(direction)-1, GCONFIG3); //use all four directions
    }
}

void adps_getGestureDirection(void)
{

}

void adps_setGestureProximityEnter(void)
{
    i2c_tx(ADPS99_ADDR, ENABLE_RESET, ONE_MESSAGE, GPENTH); //set gesture enter threshold
}

void adps_setGestureExitThreshold(void)
{
    i2c_tx(ADPS99_ADDR, EXIT_THRESHOLD, ONE_MESSAGE, GEXTH); //set gesture exit threshold
}

void adps_setGestureFIFOExit(void)
{
    i2c_tx(ADPS99_ADDR, FIFO_EXIT, ONE_MESSAGE, GCONFIG1); // 4 gesture events for int., 1 for exit
}

void adps_setGestureGain(void)
{
    i2c_tx(ADPS99_ADDR, GCONFIG2_DEFAULT, ONE_MESSAGE, GCONFIG2); //set Gain, wait and LED current
}

void adps_setGestureUDOffset(void)
{
    i2c_tx(ADPS99_ADDR, DEFAULT_OFF_D, ONE_MESSAGE, GOFFSET_D); //set Offset of Down to zero
    i2c_tx(ADPS99_ADDR, DEFAULT_OFF_U, ONE_MESSAGE, GOFFSET_U); //set Offset of Up to zero
}

void adps_setGestureLROffset(void)
{
    i2c_tx(ADPS99_ADDR, DEFAULT_OFF_L, ONE_MESSAGE, GOFFSET_L); //set Offset of Left to zero
    i2c_tx(ADPS99_ADDR, DEFAULT_OFF_R, ONE_MESSAGE, GOFFSET_R); //set Offset of Right to zero
}

void adps_setGesturePulse()
{
    i2c_tx(ADPS99_ADDR, DEFAULT_GPULSE, ONE_MESSAGE, GPULSE); //32us, 10 pulses
}

void adps_setGestureLPM(void)
{
    i2c_tx(ADPS99_ADDR, DEFAULT_GPULSE, ONE_MESSAGE, GPULSE); //32us, 10 pulses
}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P2IFG &= (~BIT5); // P2.5 IFG clear
}