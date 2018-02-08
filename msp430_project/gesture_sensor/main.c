/**
 * main.c
 */

#include <msp430.h>
#include "i2c.h"
#include "adps_gesture.h"

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                // Stop WDT
    BCSCTL1 = CALBC1_1MHZ;                   // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ;
    i2c_init();                              // Initialize I2C
    adps_init();
                                                 // Address is High byte then low byte
    i2c_tx(EEPROM_ADDR, txdataEEPROM, sizeof(txdataEEPROM)-1,TWOBYTEADDR,0x01,0x00);//i2c TX 115 bytes starting @ address 01:00
    i2c_tx(EEPROM_ADDR, txdataEEPROM, sizeof(txdataEEPROM)-1,TWOBYTEADDR,0x02,0x00);//i2c TX 115 bytes starting @ address 02:00
    i2c_tx(EEPROM_ADDR, txdataEEPROM, sizeof(txdataEEPROM)-1,TWOBYTEADDR,0x03,0x00);//i2c TX 115 bytes starting @ address 03:00
    i2c_tx(DS3231_ADDR, txdataDS3231, 7,ONEBYTEADDR,0x00,0x00);//i2c TX 7 bytes "HELLO WORLD" starting @ address 00
    i2c_tx(DS3231_ADDR, txdataDS3231, 7,ONEBYTEADDR,0x00,0x00);//i2c TX 7 bytes "HELLO WORLD" starting @ address 00

    i2c_rx(EEPROM_ADDR, rxdata, 115,TWOBYTEADDR,0x01,0x00);//i2c RX 115 bytes from EEPROM starting @ address 01:00
    i2c_rx(EEPROM_ADDR, rxdata, 115,TWOBYTEADDR,0x02,0x00);//i2c RX 115 bytes from EEPROM starting @ address 02:00
    i2c_rx(EEPROM_ADDR, rxdata, 115,TWOBYTEADDR,0x03,0x00);//i2c RX 115 bytes from EEPROM starting @ address 03:00

    i2c_rx(DS3231_ADDR, rxdata, 7,ONEBYTEADDR,0x00,0x00);//i2c RX 7 bytes from DS3231 starting @ address 00:00

    LPM0;                                    // Enter LPM0 w/ interrupts
}
