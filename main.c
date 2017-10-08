#include "msp.h"
#include <stdint.h>
#include "uart.h"
#include <stdlib.h>

#include "circular_buffer.h"
#include "lab3.h"

//delete later
#include "circ_buffer_basic.h"

/**
 * main.c
 */

 char  myShortTest[9]={"Test123\n"};

  CircBuf_t myBuffer;


  CircBuf_t * myBufferPTR = &myBuffer;

  uint8_t zoid[17] = {87,104,121,32,78,111,116,32,90,111,105,100,98,101,114,103,63};


void main(void)
{


    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    UART_config();
    configure_clocks(); //probably so change up


    initialize_Circ_Buffer(&myBufferPTR, 10);

//    uint8_t empty = is_Circ_Buf_Empty(&myBufferPTR);
//
//    int8_t emptyError = remove_From_Buffer(&myBufferPTR); //I expect a -1 for error
//
//    add_To_Buffer(&myBufferPTR, 54);
//     empty = is_Circ_Buf_Empty(&myBufferPTR);
//     uint8_t full = is_Circ_Buf_Full(&myBufferPTR);
//
//    add_To_Buffer(&myBufferPTR, 67);
//     full = is_Circ_Buf_Full(&myBufferPTR);
//
//     add_To_Buffer(&myBufferPTR, 69);
//
//
//    uint8_t value = remove_From_Buffer(&myBufferPTR);
//     full = is_Circ_Buf_Full(&myBufferPTR);

    __enable_irq();


    P2SEL0 &= ~BLUE_LED;
    P2SEL1 &= ~BLUE_LED;
    P2DIR |= BLUE_LED; //output
    P2OUT &= ~BLUE_LED;


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
