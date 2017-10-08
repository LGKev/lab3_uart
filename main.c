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

  uint8_t Calculate_Stats = 0; // set to 1, either full or enter pressed.


  uint8_t count[5]={0,0,0,0,0};
=======
void create_Test_Buffer();


void main(void)
{
    uint8_t data =0;
    uint8_t count_letter =0;
    uint8_t count_number = 0;
    uint8_t count_puntuation=0;
    uint8_t count_white_space =0;
    uint8_t count_other_character =0;
    uint8_t i;




    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    UART_config();
    configure_clocks(); //probably so change up


<<<<<<< HEAD
    initialize_Circ_Buffer(&myBufferPTR, 15);
=======
    initialize_Circ_Buffer(&myBufferPTR, 20);
    //create_Test_Buffer();
>>>>>>> 0327730c222a51ab4bdb1d0a0b20c8dcd165ac84


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


#ifdef ZOIDBERG_TEST
	uint8_t letter = 0;
	while(1){


        UART_putchar(67);
        UART_putchar(69);
//        UART_putchar(101);



	}
#endif

	/*stats*/

while(1){
	if(Calculate_Stats == 1){
	    uint8_t number_of_item = myBufferPTR -> num_items;
	     for ( i=0; i< number_of_item; i++){
	         data = remove_From_Buffer(&myBufferPTR);
	         if(64<data & data<91 | 96<data & data <123){
	             count_letter ++;
	         }
	             else if (47<data & data<58){
	                 count_number ++;
	             }
	             else if (32<data & data<35|38<data& data<42|data ==46|57<data& data<60|data == 63){
	                 count_puntuation ++;
	                 }
	             else if (data == 32){ ////TODO: horizontal tab too
	                 count_white_space ++;
	             }
	             else
	             {
	                count_other_character++;
	             }
	     }
	     count[0] = count_letter + Ascii_num_offset;
	     count[1]= count_number+ Ascii_num_offset;
	     count[2]= count_puntuation+ Ascii_num_offset;
	     count[3] = count_white_space+ Ascii_num_offset;
	     count[4]= count_other_character+ Ascii_num_offset;

	     uint8_t index =0;

	     for(index = 0; index < 5; index++){
	         UART_putchar(count[index]);
	     }


	     Calculate_Stats = 0;
	}
}




}


void HSMCLK_OUT(){

    //primary mode, clock output HSMCLK
    //page 10.2.6
    P4SEL0 |= BIT4;
    P4SEL1 &= ~BIT4;

    P4DIR |= BIT4;


}


void create_Test_Buffer(){
    uint8_t array[30];
    uint8_t index =0;
    for(index=0; index< 30; index++){
        add_To_Buffer(&myBufferPTR, index);
    }
}
