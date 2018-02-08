/*
 * adps_gesture.h
 *
 *  Created on: 03.02.2018
 *      Author: Christoph
 */

#ifndef ADPS_GESTURE_H_
#define ADPS_GESTURE_H_

#include "adps_registers.h"

#define ADPS99_ADDR 0x39 //slave address
#define ONE_MESSAGE 1

void adps_init(void);
void adps_startGestureMode(void);
void adps_stopGestureMode(void);
void adps_setGestureInt(void);
void adps_setGestureDirection(char direction);
void adps_setGestureProximityEnter(void);
void adps_setGestureExitThreshold(void);
void adps_setGestureFIFOExit(void);
void adps_setGestureGain(void);
void adps_setGestureUDOffset(void);
void adps_setGestureLROffset(void);
void adps_setGesturePulse(void);

#endif /* ADPS_GESTURE_H_ */
