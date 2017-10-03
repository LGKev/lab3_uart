#include "msp.h"
#include <stdint.h>
#include "uart.h"

#include "circular_buffer.h"
#include "lab3.h"



/**
 * main.c
 */
 char const myShortTest[9]={"Test123\n"};

void main(void)
{

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer


    UART_config();
    configure_clocks(); //probably so change up




    //enable the interrupts for RX buffer
    __enable_irq();

#ifdef UART_PUTCHAR_TEST

    uint8_t myData[3] = {98,99,100};
    uint8_t mySentence[13]={72,101, 108,108, 111, 32, 87,111,114, 108, 100,33,33 };//Hello World!! = 13
    //uint8_t test[1] ={01010101};

    while(1){
       // UART_putchar(10); //new line
    // uart_putchar_n(mySentence, 13);
//     uart_putchar_n(myShortTest,9);
      // uart_putchar_n(myData, 3);
       // UART_putchar(10); //new line
     //
    //uart_putchar_n(test, 1);

        UART_putchar(0xAA);

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
