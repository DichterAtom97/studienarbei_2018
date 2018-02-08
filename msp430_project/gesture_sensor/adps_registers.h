/*
 * adps_registers.h
 *
 *  Created on: 03.02.2018
 *      Author: Christoph
 */

#ifndef ADPS_REGISTERS_H_
#define ADPS_REGISTERS_H_

//adps9960-register
#define ENABLE    0x80 //enable register, R/W
#define CONFIG1   0x8D //config register 1, R/W
#define CONFIG2   0x90 //config register 2, R/W
#define STATUS    0x93 //device status, R
#define GPENTH    0xA0 //gesture proximity entry threshold, R/W
#define GEXTH     0xA1 //gesture exit threshold, R/W
#define GCONFIG1  0xA2 //gesture config one, R/W
#define GCONFIG2  0XA3 //gesture config two, R/W
#define GOFFSET_U 0xA4 //gesture offset, UP, R/W
#define GOFFSET_D 0xA5 //gesture offset, DOWN, R/W
#define GPULSE    0xA6 //gesture pulse count and length, R/W
#define GOFFSET_L 0xA7 //gesture offset, LEFT, R/W
#define GOFFSET_R 0xA9 //gesture offset, RIGHT, R/W
#define GCONFIG3  0xAA //gesture config 3, R/W
#define GCONFIG4  0xAB //gesture config 4, R/W
#define GFLVL     0xAE //gesture FIFO level, R
#define GSTATUS   0xAF //gesture status, R
#define GFIFO_U   0xFC //gesture FIFO data, UP, R
#define GFIFO_D   0xFD //gesture FIFO data, DOWN, R
#define GFIFO_L   0xFE //gesture FIFO data, LEFT, R
#define GFIFO_R   0xFF //gesture FIFO data, RIGHT, R


//adps9960-bit commands
#define ENABLE_RESET     0x00
#define ALL_DIRECTIONS   0x00
#define DEFAULT_OFF_D    0x00
#define DEFAULT_OFF_U    0x00
#define DEFAULT_OFF_L    0x00
#define DEFAULT_OFF_R    0x00
#define GCONFIG2_DEFAULT 0x01
#define UP_DOWN          0x01
#define RIGTH_LEFT       0x02
#define GESTURE_INT      0x03
#define FIFO_EXIT        0x40
#define GESTURE_MODE     0x41
#define EXIT_THRESHOLD   0x1E
#define DEFAULT_GPULSE   0xC9


#endif /* ADPS_REGISTERS_H_ */
