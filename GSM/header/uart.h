/*
 * uart.h
 *      Author: Christoph
 */

#ifndef UART_H_
#define UART_H_

// constant defines
#define CR       (0x0D)
#define LF       (0x0A)
#define SEND     (0x1A)
#define EMPTY    (0x00)
#define NUM_HELP (0x22)

/*rx_flag
* This flag is to be used by other modules to check and see if a new transmission has happened.
* This is READ ONLY. Do not write to it or the UART may crash.
*/
extern volatile unsigned int rx_flag;

/*uart_init
* Sets up the UART interface via USCI
* INPUT: None
* RETURN: None
*/
void UART_init(void);

/*uart_getc
* Get a char from the UART. Waits till it gets one
* INPUT: None
* RETURN: Char from UART
*/
unsigned char UART_getc();

/*uart_gets
* Get a string of known length from the UART. Strings terminate when enter is pressed or string buffer fills
* Will return when all the chars are received or a carriage return (\r) is received. Waits for the data.
* INPUT: Array pointer and length
* RETURN: None
*/
void UART_gets(char* Array, int echo_len, int length);

/*uart_putc
* Sends a char to the UART. Will wait if the UART is busy
* INPUT: Char to send
* RETURN: None
*/
void UART_putc(unsigned char c);

/*uart_puts
* Sends a string to the UART. Will wait if the UART is busy
* INPUT: Pointer to String to send
* RETURN: None
*/
void UART_puts(char *str);

#endif /* UART_H_ */
