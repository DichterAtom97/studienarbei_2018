/*
 * adps_registers.h
 *
 *  Created on: 03.02.2018
 *      Author: Christoph
 */

#ifndef ADPS_REGISTERS_H_
#define ADPS_REGISTERS_H_

#define ENABLE    0x80 //enable register
#define CONFIG1   0x8D //config register 1
#define CONFIG2   0x90 //config register 2
#define STATUS    0x93 //device status
#define GPENTH    0xA0 //gesture proximity entry threshold
#define GEXTH     0xA1 //gesture exit threshold
#define GCONFIG1  0xA2 //gesture config one
#define GCONFIG2  0XA3 //gesture config two
#define GOFFSET_U 0xA4 //gesture offset, UP
#define GOFFSET_D 0xA5 //gesture offset, DOWN
#define GPULSE    0xA6 //gesture pulse count and length
#define GOFFSET_L 0xA7 //gesture offset, LEFT
#define GOFFSET_R 0xA9 //gesture offset, RIGHT
#define GCONFIG3  0xAA //gesture config 3
#define GCONFIG4  0xAB //gesture config 4
#define GFLVL     0xAE //gesture FIFO level
#define GSTATUS   0xAF //gesture status
#define GFIFO_U   0xFC //gesture FIFO data, UP
#define GFIFO_D   0xFD //gesture FIFO data, DOWN
#define GFIFO_L   0xFE //gesture FIFO data, LEFT
#define GFIFO_R   0xFF //gesture FIFO data, RIGHT

#endif /* ADPS_REGISTERS_H_ */
