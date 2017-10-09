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

#define WORKING_Circ

#define Ascii_num_offset          (48)

#define ARC_LENGTH                  (22.5)

//#define ZOIDBERG_TEST

/*
 * Clock DCO is being modified to be used with UART.
 * Clock determines baud rate accuracy.
 * Desired Baud: 9600 with a clock of 10Mhz
 * */
void configure_clocks(void);

/* Sets up the interrupt and buttons 1 and 4 of port 1.
 * TODO: set up interrupt for IR beam break.
 * */
void configure_ports(void);


//Conversions
void reverse(char str[], int len);
int intToStr(int value, char str[], int length);


char itoa(int value, char str[], int base);          //Integer to ASCII (should return ascii)

char ftoa(float f, char str[], int point);         //Float to ASCII (should return ascii)


#endif /* LAB3_H_ */
