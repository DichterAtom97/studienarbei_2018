/*
 * gsm.h
 *
 *  Created on: 13.01.2018
 *      Author: Christoph
 */

#ifndef GSM_H_
#define GSM_H_

//define types
#define STATUS int

//define status constant
#define BAD       0x00
#define NOT_OK    0x00
#define OK        0x01
#define GOOD      0x02
#define EXCELLENT 0x03

//define AT commands
#define AT           "AT"
#define TEXT_MODE    "AT+CMGF=1"
#define GET_STRENGTH "AT+CSQ"

STATUS GSM_testCommunication(void);
void GSM_sendMessage(char phone_number[], char text[]);
STATUS GSM_getSignalQuality(void);
void GSM_pwr(void);


#endif /* GSM_H_ */
