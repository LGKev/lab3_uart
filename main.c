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

    UART_config();
    configure_clocks(); //probably so change up
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer


    //primary mode, clock output HSMCLK
    //page 10.2.6
    P4SEL0 |= BIT4;
    P4SEL1 &= ~BIT4;

    P4DIR |= BIT4;


	while(1);
}


void HSMCLK_OUT(){

    //primary mode, clock output HSMCLK
    //page 10.2.6
    P4SEL0 |= BIT4;
    P4SEL1 &= ~BIT4;

    P4DIR |= BIT4;


}
