/*
 * adps_gesture.h
 *
 *  Created on: 03.02.2018
 *      Author: Christoph
 */

#ifndef ADPS_GESTURE_H_
#define ADPS_GESTURE_H_

#include "adps_registers.h"

#define ADPS99_ADDR 0x39

void adps_init(void);
void adps_gestureMode(void);

#endif /* ADPS_GESTURE_H_ */
