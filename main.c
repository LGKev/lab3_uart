#include "msp.h"
#include <stdint.h>
#include "uart.h"

#include "circular_buffer.h"
#include "lab3.h"



/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer


    UART_config();
    configure_clocks(); //probably so change up

    P2SEL0 &= ~BLUE_LED;
    P2SEL1 &= ~BLUE_LED;
    P2DIR |= BLUE_LED; //output
    P2DIR &= ~BLUE_LED;


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
