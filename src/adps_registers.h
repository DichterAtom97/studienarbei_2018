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


/* Default values */
#define DEFAULT_RESET           (uint8_t *)0x00
#define DEFAULT_ENABLE          (uint8_t *)0x41    // PON, GEN
#define DEFAULT_ATIME           0xDB     // 103ms
#define DEFAULT_WTIME           0xF6     // 27ms
#define DEFAULT_PROX_PPULSE     0x87    // 16us, 8 pulses
#define DEFAULT_GESTURE_PPULSE  0x89    // 16us, 10 pulses
#define DEFAULT_POFFSET_UR      0       // 0 offset
#define DEFAULT_POFFSET_DL      0       // 0 offset
#define DEFAULT_CONFIG1         0x60    // No 12x wait (WTIME) factor
#define DEFAULT_PILT            0       // Low proximity threshold
#define DEFAULT_PIHT            0x32      // High proximity threshold
#define DEFAULT_AILT            0xFFFF  // Force interrupt for calibration
#define DEFAULT_AIHT            0
#define DEFAULT_PERS            0x11    // 2 consecutive prox or ALS for int.
#define DEFAULT_CONFIG2         0x01    // No saturation interrupts or LED boost
#define DEFAULT_CONFIG3         0       // Enable all photodiodes, no SAI
#define DEFAULT_GPENTH          (uint8_t *)0x28      // Threshold for entering gesture mode
#define DEFAULT_GEXTH           (uint8_t *)0x1E      // Threshold for exiting gesture mode
#define DEFAULT_GCONF1          (uint8_t *)0x40    // 4 gesture events for int., 1 for exit
#define DEFAULT_GCONF2          (uint8_t *)0x42    //4x gain, 100mA, 2.8ms
#define DEFAULT_GOFFSET         0       // No offset scaling for gesture mode
#define DEFAULT_GPULSE          (uint8_t *)0xC9    // 32us, 10 pulses
#define DEFAULT_GCONF3          (uint8_t *)0x0       // All photodiodes active during gesture
#define DEFAULT_GCONF4          (uint8_t *)0x3       // Disable gesture interrupts


#endif /* ADPS_REGISTERS_H_ */
