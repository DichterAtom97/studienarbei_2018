/*
 * adps_gesture.h
 *
 *  Created on: 03.02.2018
 *      Author: Christoph
 */

#ifndef ADPS_GESTURE_H_
#define ADPS_GESTURE_H_

#include "adps_registers.h"
#include <stdint.h>

#define ADPS99_ADDR 0x39 //slave address
#define ONE_MESSAGE 1

// basic functions
void adps_init(void);
void adps_startGestureMode(void);
void adps_resetSensor(void);
void adps_setDefault(void);
void adps_startProcess(void);

// set functions
void adps_setGestureInt(void);
void adps_setGestureDirection(void);
void adps_setGestureProximityEnter(void);
void adps_setGestureExitThreshold(void);
void adps_setGestureFIFOExit(void);
void adps_setGestureGain(void);
void adps_setGestureOffset(void);
void adps_setGesturePulse(void);

//gesture structue

typedef struct
{
    uint8_t up[4];
    uint8_t down[4];
    uint8_t left[4];
    uint8_t right[4];
}gesture_type;


volatile int ack_gesture;


#endif /* ADPS_GESTURE_H_ */
