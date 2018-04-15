/******************************************************************************/
/*                  Westsaechsische Hochschule Zwickau                        */
/*                                                                            */
/* File Name:   main.c                                                        */
/* Autor:       Kamil Krenek                                                  */
/* Version:     V1.10                                                         */
/* Date:        14/07/2017                                                    */
/* Description: BASISSOFTWARE FÜR SSD1306 DISPLAY                             */
/******************************************************************************/
/* History:     V1.00  creation    14/07/2017    I2C ANSTEURUNG               */
/******************************************************************************/
/* History:     V1.10  creation    06/01/2018      Erweiterung TEXTAUSGABE    */
/******************************************************************************/

#include <msp430G2553.h>
#include "stdint.h"
#include "ascii_char.h"

#define OLED_CONTROL_BYTE_CMD_SINGLE    0x80 // command befehl einzeln
#define OLED_CONTROL_BYTE_CMD_STREAM    0x00 // command stream
#define OLED_CONTROL_BYTE_DATA_STREAM   0x40 // data stream

// Fundamental commands (pg.28)
#define OLED_CMD_SET_CONTRAST           0x81    // follow with 0x7F
#define OLED_CMD_DISPLAY_RAM            0xA4
#define OLED_CMD_DISPLAY_ALLON          0xA5
#define OLED_CMD_DISPLAY_NORMAL         0xA6
#define OLED_CMD_DISPLAY_INVERTED       0xA7
#define OLED_CMD_DISPLAY_OFF            0xAE
#define OLED_CMD_DISPLAY_ON             0xAF

// Addressing Command Table (pg.30)
#define OLED_CMD_SET_MEMORY_ADDR_MODE   0x20    // follow with 0x00 = HORZ mode = Behave like a KS108 graphic LCD
#define OLED_CMD_SET_COLUMN_RANGE       0x21    // can be used only in HORZ/VERT mode - follow with 0x00 + 0x7F = COL127
#define OLED_CMD_SET_PAGE_RANGE         0x22    // can be used only in HORZ/VERT mode - follow with 0x00 + 0x07 = PAGE7

// Hardware Config (pg.31)
#define OLED_CMD_SET_DISPLAY_START_LINE 0x40
#define OLED_CMD_SET_SEGMENT_REMAP      0xA1
#define OLED_CMD_SET_MUX_RATIO          0xA8    // follow with 0x3F = 64 MUX
#define OLED_CMD_SET_COM_SCAN_MODE      0xC8
#define OLED_CMD_SET_DISPLAY_OFFSET     0xD3    // follow with 0x00
#define OLED_CMD_SET_COM_PIN_MAP        0xDA    // follow with 0x12

// Timing and Driving Scheme (pg.32)
#define OLED_CMD_SET_DISPLAY_CLK_DIV    0xD5    // follow with 0x80
#define OLED_CMD_SET_PRECHARGE          0xD9    // follow with 0x22
#define OLED_CMD_SET_VCOMH_DESELCT      0xDB    // follow with 0x30

// Charge Pump (pg.62)
#define OLED_CMD_SET_CHARGE_PUMP        0x8D    // follow with 0x14

// NOP
#define OLED_CMD_NOP                    0xE3

unsigned char *PTXData;                         // pointer for TXDATA
unsigned char TXByteCtr;                        // counter for TX

uint16_t i;
uint8_t j,c,s,b;

const unsigned char init_cmd_array[] = { 0x00,0xAE,0xA8,0x3F,0xD3,0x00,0x40,0xA1,0xC8,0xDA,0x12,0x81,0x7F,0xA4,0xA6,0xD5,0x80,0x8D,0x14,0xD9,0x22,0xDB,0x30,0x20,0x00,0xAF};
/*const unsigned char init_cmd_array[] = {

    OLED_CONTROL_BYTE_CMD_STREAM,

    // Follow instructions on pg.64 of the dataSheet for software configuration of the SSD1306
    // Turn the Display OFF
    OLED_CMD_DISPLAY_OFF,
    // Set mux ration tp select max number of rows - 64
    OLED_CMD_SET_MUX_RATIO,
    0x3F,
    // Set the display offset to 0
    OLED_CMD_SET_DISPLAY_OFFSET,
    0x00,
    // Display start line to 0
    OLED_CMD_SET_DISPLAY_START_LINE,

    // Mirror the x-axis. In case you set it up such that the pins are north.
    // Wire.write(0xA0); - in case pins are south - default
    OLED_CMD_SET_SEGMENT_REMAP,

    // Mirror the y-axis. In case you set it up such that the pins are north.
    // Wire.write(0xC0); - in case pins are south - default
    OLED_CMD_SET_COM_SCAN_MODE,

    // Default - alternate COM pin map
    OLED_CMD_SET_COM_PIN_MAP,
    0x12,
    // set contrast
    OLED_CMD_SET_CONTRAST,
    0x7F,
    // Set display to enable rendering from GDDRAM (Graphic Display Data RAM)
    OLED_CMD_DISPLAY_RAM,
    // Normal mode!
    OLED_CMD_DISPLAY_NORMAL,
    // Default oscillator clock
    OLED_CMD_SET_DISPLAY_CLK_DIV,
    0x80,
    // Enable the charge pump
    OLED_CMD_SET_CHARGE_PUMP,
    0x14,
    // Set precharge cycles to high cap type
    OLED_CMD_SET_PRECHARGE,
    0x22,
    // Set the V_COMH deselect volatage to max
    OLED_CMD_SET_VCOMH_DESELCT,
    0x30,
    // Horizonatal addressing mode - same as the KS108 GLCD
    OLED_CMD_SET_MEMORY_ADDR_MODE,
    0x00,
    // Turn the Display ON
    OLED_CMD_DISPLAY_ON

};
*/
const unsigned char WriteInit[] = { 0x00, 0x21, 0x00, 0x7F, 0x22, 0x00, 0x07 };                                     // write INIT array

const unsigned char TX[] = {0x00,0x7E,0x42,0x42,0x42,0x42,0x7E,0x00,0x00,0x7E,0x42,0x42,0x42,0x42,0x7E,0x00};       // QUADRATISCHES MUSTER
//const unsigned char TX[] = {0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81,0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81};     // RAUTE MUSTER


const unsigned char TEST[]= {"sucess"};                                                                             // TEXTSTRING

unsigned char buffer[100];
unsigned int value;
/******************************************************************************/
/*            U N T E R P R O G R A M M:    strlen()                          */
/*                                                                            */
/* Aufgabe:  Returns the length of the given byte string                      */
/* Input:    const unsigned char * str                                        */
/* return:                                                                    */
/******************************************************************************/
int strlen(const unsigned char * str)
{
    const unsigned char *len;
    for (len = str; *len; ++len);
    return(len - str);
}
/******************************************************************************/
/*            U N T E R P R O G R A M M:    WriteString()                     */
/*                                                                            */
/* Aufgabe:  write string into buffer from ascii_table                        */
/* Input:    const unsigned char* character)                                  */
/* return:                                                                    */
/******************************************************************************/
int WriteString(const unsigned char* character)
{
    unsigned int size = strlen(character);

    for (s = 0; s < size; s++)
        {
          for (c = 0; c < 5; c++)
          {
            buffer[b] = ascii_table[(unsigned int) *character][c];
            b++;
          }
          *character++;
          if (b == size)
          {
            b = 0;
            character = 0;
          }
        }
    return size;
}
/******************************************************************************/
/*            U N T E R P R O G R A M M:    WriteOLED                         */
/*                                                                            */
/* Aufgabe:   Versenden von Arrays                                            */
/* Input:     (const unsigned char* data, unsigned char size)                 */
/* return:                                                                    */
/******************************************************************************/
void WriteOLED(const unsigned char* data, unsigned char size)
{
    PTXData = (unsigned char*)data;
    TXByteCtr = size;

    while (UCB0CTL1 & UCTXSTP);
    UCB0CTL1 |= UCTR + UCTXSTT;
}
/******************************************************************************/
/*            U N T E R P R O G R A M M:    WriteBYTE                         */
/*                                                                            */
/* Aufgabe:   Kann dafür verwendet werden wenn nur 1 BYTE verschickt wird     */
/* Input:     (const unsigned char* data)                                     */
/* return:                                                                    */
/******************************************************************************/

void WriteBYTE(const unsigned char* data)
{
    PTXData = (unsigned char*)data;
    TXByteCtr = 1;

    while (UCB0CTL1 & UCTXSTP);
    UCB0CTL1 |= UCTR + UCTXSTT;
}

/******************************************************************************/
/*            U N T E R P R O G R A M M:    OLEDinit()                        */
/*                                                                            */
/* Aufgabe:   Initialisierung des OLED-Display über ein Array                 */
/* Input:                                                                     */
/* return:                                                                    */
/******************************************************************************/
void OLEDInit()
{
    WriteOLED(init_cmd_array, sizeof(init_cmd_array));      // output of desired init array to display
    __delay_cycles(160000);                             // delay
}

/******************************************************************************/
/*                                MAIN function                               */
/******************************************************************************/
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

    BCSCTL1=CALBC1_16MHZ;                     //DCO setting to 16 Mhz
    DCOCTL=CALDCO_16MHZ;                      //DCO setting to 16 Mhz

    P1DIR |= BIT0;                            // P1.0 Output

    P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
    P1SEL2 |= BIT6 + BIT7;                    // Assign I2C pins to USCI_B0

    UCB0CTL1 |= UCSWRST;                      // Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
    UCB0BR0 = 12;
    UCB0BR1 = 0;
    UCB0I2CSA = 0x3C;                         // Slave Address
    UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
    IE2 |= UCB0TXIE;                          // Enable TX interrupt

    __enable_interrupt();

    OLEDInit();                               // init of the OLEDDISPLAY
    value = (WriteString(TEST)*5);
    WriteOLED(WriteInit, sizeof(WriteInit));
            for (i = 0; i < 1024; i++) {
                WriteOLED((unsigned char*)OLED_CONTROL_BYTE_DATA_STREAM,1);
                for (j = 1; j < 16; j++) { //j=1 for text
                    WriteOLED((unsigned char*)0x81,1);
                    WriteOLED((unsigned char*)0x02,1);
                    //WriteOLED(TX, sizeof(TX)); //Test array
                   WriteOLED(buffer, value); //Text

                    i++;
                }
                i--;
            }
            __delay_cycles(160000);
}
/******************************************************************************/
/*                     Interrupt Service Routine                              */
/******************************************************************************/

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
      if(TXByteCtr!=0)                                 // Check TX byte counter
          {
              UCB0TXBUF = *PTXData++;                  // Load TX buffer
              TXByteCtr--;                             // Decrement TX byte counter
          }
      else if(TXByteCtr==0)
          {
              UCB0CTL1 |= UCTXSTP;                     // I2C stop condition
              IFG2 &= ~UCB0TXIFG;                      // Clear USCI_B0 TX interrupt flag
          }
    P1OUT ^= BIT0;                                     // set LED
}
