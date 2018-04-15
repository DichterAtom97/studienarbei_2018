#include "msp430g2553.h"
#include "uart.h" // ATTACH THE UART FILE WITH THE MAIN CODE
#include "gsm.h"


int main(void)
{
    char phone_number[]="+436765051591", text[]= "hello";
   // int status_signal;

    WDTCTL = WDTPW + WDTHOLD;           // Stop WDT
    DCOCTL = 0;                          // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;               // Set DCO
    DCOCTL = CALDCO_1MHZ;
    P1SEL &= 0x00;
    P1SEL2 &= 0x00;
    P2DIR |= 0xFF;                       // All P2.x outputs
    P2OUT &= 0x00;                       // All P2.x reset

    UART_init(); // CALL THE UART INIT FUNCTION WHICH IS AVAILAIBLE IN THE FILE
    GSM_pwr();

    __enable_interrupt();// ENABLE INTERRUPT
    __delay_cycles(4000000);

   GSM_testCommunication();


   GSM_sendMessage(phone_number, text);// CALL THE GSM FUNCTION


   //status_signal = GSM_getSignalQuality();

}


