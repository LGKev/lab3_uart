#include "msp.h"
#include <stdint.h>
#include "uart.h"
#include <stdlib.h>

#include "circular_buffer.h"
#include "lab3.h"


/**
 * main.c
 */

 char const myShortTest[9]={"Test123\n"};


 CircBuf_t * myBufferPTR;







void main(void)
{
//    CircBuf_t *myBuffPTR;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    CircBuf_t * myBuffPTR;


    UART_config();
    configure_clocks(); //probably so change up




    //enable the interrupts for RX buffer
    __enable_irq();

#ifdef UART_PUTCHAR_TEST

    uint8_t myData[3] = {98,99,100};
    uint8_t mySentence[13]={72,101, 108,108, 111, 32, 87,111,114, 108, 100,33,33 };//Hello World!! = 13
    //uint8_t test[1] ={01010101};



CB_initialize_buffer(myBuffPTR, 10);


    while(1){
    }

#endif


#ifdef UART_RX_TEST
    P2SEL0 &= ~BLUE_LED;
    P2SEL1 &= ~BLUE_LED;
    P2DIR |= BLUE_LED; //output
    P2OUT &= ~BLUE_LED;
#endif


#ifdef UART_TX_TEST
    uint8_t letter = 0;
	while(1){
	   for(letter = 30; letter < 122; letter++){
	    UART_putchar(letter);
	    UART_putchar(32);//space
	   }

	    }
#endif


while(1);
}


void HSMCLK_OUT(){

    //primary mode, clock output HSMCLK
    //page 10.2.6
    P4SEL0 |= BIT4;
    P4SEL1 &= ~BIT4;

    P4DIR |= BIT4;


}