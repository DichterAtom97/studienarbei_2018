/*
 * adps_gesture.c
 *
 *  Created on: 03.02.2018
 *      Author: Christoph
 */

#include <msp430.h>
#include "adps_gestures.h"
#include "i2c.h"

void adps_init(void)
{
    P2SEL  &= 0x00; //P2.x is GPIO
    P2SEL2 &= 0x00;
    P2DIR  &= (~BIT5); //P2.x is input
    P2IES  |= (BIT5);  //Falling Edge 1->0
    P2IFG  &= (~BIT5); //clear interrupt flag
    P2IE   |= (BIT5);  //enable interrupt
}

void adps_gestureMode(void)
{

}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P2IFG &= (~BIT5); // P2.5 IFG clear
}
