/*
 * lab3.h
 *
 *  Created on: Sep 24, 2017
 *      Author: kevinKuwata1
 */

#include "msp.h"

#ifndef LAB3_H_
#define LAB3_H_


//#define UART_TX_TEST      //only sends the ascii values from 32 to 122.
#define BLUE_LED        (BIT2)      //Sets up blue led with bit 2 for more descriptive

#define UART_RX_TEST        // only tests the RX interrupt and mask.

#define UART_PUTCHAR_TEST       // only tests to loop sending data as a byte.

/*
 * Clock DCO is being modified to be used with UART.
 * Clock determines baud rate accuracy.
 * Desired Baud: 9600 with a clock of 10Mhz
 * */
void configure_clocks(void);






#endif /* LAB3_H_ */
