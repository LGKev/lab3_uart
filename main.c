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


//typedef struct CircBuf_t * myBufferPTR;

//
//
// typedef struct{
//     uint8_t * buffer;                       // pointer to the base of the buffer in heap
//     volatile uint8_t * head;                // Pointer to first item //start of buffer  // FIFO
//     volatile uint8_t * tail;                // Marks the end of buffer, where new things are added. so head only moves when we pop out. and tail moves when we add.
//     volatile uint32_t  num_items;          // good to know how many items are in the buffer , so array may be 50 long, but only 3 spots are filled. we don't want to go from 4 to 50.
//     const uint32_t length;               // Max number of items that can be held
//     volatile uint16_t tailPosition  ;         //This will be useful to know if there was a loop around, if there was then we don't want tail to go past
//                                             //out of bounds so if tailPosition == 255 count, then move tail to buf. loop back.
// } CircBuf_t;


 CircBuf_t * myBuffPTR;


void main(void)
{
//    CircBuf_t *myBuffPTR;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer


    UART_config();
    configure_clocks(); //probably so change up




    //enable the interrupts for RX buffer
    __enable_irq();

#ifdef UART_PUTCHAR_TEST

    uint8_t myData[3] = {98,99,100};
    uint8_t mySentence[13]={72,101, 108,108, 111, 32, 87,111,114, 108, 100,33,33 };//Hello World!! = 13
    //uint8_t test[1] ={01010101};

    //initialize buffer size of 10;
  //  const CircBuf_t  bufferLocationPtr;

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
