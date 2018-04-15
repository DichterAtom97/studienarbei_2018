/*
 * gsm.c
 *
 *  Created on: 13.01.2018
 *      Author: Christoph
 */

#include "msp430g2553.h"
#include "uart.h"
#include "gsm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const char check_response[]="OK";

STATUS GSM_testCommunication(void)
{
    __delay_cycles(20000);
    char response_test[3];
    UART_puts((char *)AT);           // COMMAND FOR INITIALIZING GSM
    UART_putc(CR);
    UART_putc(LF);
    UART_gets(response_test,6, 3);        // wait for response
    if(*response_test == *check_response)
    {
        return OK;
    }
    else
    {
        return NOT_OK;
    }
}

void GSM_sendMessage(char phone_number[], char text[])
{
    char response_text[3];
    __delay_cycles(20000);
    do
    {
        UART_puts((char *)TEXT_MODE);    //text Mode
        UART_putc(CR);
        UART_putc(LF);
        UART_gets(response_text, 14, 3);       // wait for response
    }
    while(*response_text != *check_response);
    __delay_cycles(20000);
    UART_puts((char*)"AT+CMGS=\"");  //SEND A MESSAGE TO PARTICULAR NUMBER
    UART_puts((char*)phone_number);
    UART_putc(NUM_HELP);
    UART_putc(CR);
    UART_putc(LF);
    //UART_gets(response_text,2, 20);        // wait for response
    __delay_cycles(20000);
    UART_puts((char *)text);        //data which should be sent
    UART_putc(SEND);                // send message
}

STATUS GSM_getSignalQuality(void)
{
    unsigned int x=0, i, sig_strength;
    char response_quality[12], status[6], strength[2];
    char status_check[]="+CSQ:";

    do{
        UART_puts((char *)TEXT_MODE);          //text Mode
        UART_putc(CR);
        UART_putc(LF);
        UART_gets(response_quality, 14, 3);          // wait for response
    }while(*response_quality != *check_response);

    __delay_cycles(10000000);                 //WAIT FOR OK
    UART_puts((char*)GET_STRENGTH);
    UART_putc(CR);
    UART_putc(LF);
    UART_gets(response_quality, 11, 12);

    for(i=0;i<5;i++)
    {
        status[i]=response_quality[i];
    }

    if(*status == *status_check)
    {
        for(i=6; i<8; i++)
        {
            strength[x]=response_quality[i];
            x++;
        }

        sig_strength=atoi(strength);

        if(sig_strength>19)
        {
            return EXCELLENT;
        }
        else if(15<=sig_strength<=19)
        {
            return GOOD;
        }
        else if(10<=sig_strength<=14)
        {
            return OK;
        }
        else
        {
            return BAD;
        }

    }
    else
    {
        return NOT_OK;
    }


}


void GSM_pwr(void)
{
    P1DIR |= BIT4;//set P1.4 to output
    P1REN |= BIT4;//enables P1.4 resistor
    P1OUT |= BIT4;//start GSM Modul
}
