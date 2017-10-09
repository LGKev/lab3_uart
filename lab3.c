/*
 * lab3.c
 *
 *  Created on: Sep 24, 2017
 *      Author: kevinKuwata1
 */


#include "msp.h"
#include <stdint.h>
#include "uart.h"
#include "circ_buffer_basic.h"

extern CircBuf_t * myBufferPTR;

void configure_clocks(void){
    CS->KEY = 0x695A; //unlock 5.3.1
    CS->CTL0 = 0 ;
    CS->CTL0 |= CS_CTL0_DCOEN | CS_CTL0_DCORSEL_2;  //enable DCO, then mode 3 for 8 to 16 Mhz
    //CS->CTL0 |=0b1100111000; //and should be 4MHZ, got 4.5 MHZ, -200.5?
   // CS->CTL0 |= 0b1011010100; //goal: 4MHZ, got:  4.016MHZ          @-300
    CS->CTL0 |= 0b1011010001; //DCTO-303


        //we want the baud rate clock to be 4 Mhz

    /*          select clock sources:
     * SELA => ACLK source = reforclock
     * SELS => SMCLK and HSMCLK  = DCO //p 4.4 secondary mode!!
     * SELM => MCLK Source = DCO
     */

    //lets tune the DCO clock with the right frequency. goal is 4MhZ
   // uint32_t myConstant_K = TLV->DCOER_CONSTK_RSEL04; //constant for K_Constant for equation on page 312
    //uint32_t myConstant_FCAL = TLV->DCOIR_FCAL_RSEL04; // constant for F_CAL for equation


    //not a typo definitely needs to be CLT1 and not CTL0
    //lets divide the SMCLK clock by some divisor to get the create the frequency
    CS->CTL1 |= CS_CTL1_SELA__REFOCLK | CS_CTL1_SELS__DCOCLK | CS_CTL1_SELM__DCOCLK;



    CS->KEY = 0; //lock
}

void configure_ports(void){
     P1->SEL0 &= ~BIT4;    //
     P1->SEL1 &= ~BIT4;    //General I/O is enable for P1.4
     P1->OUT |= BIT4;      //enable the pull up register
     P1->DIR &= ~BIT4;     //p1.4 to be input
     P1->REN |= BIT4;      //Enable pull-up resistor for P1.4
     P1 ->IFG &= ~BIT4;
     P1->IE |= BIT4;       //Enable interrupt for P1.4
     P1->IES |= BIT4;      //Interrupt on high to low transition
     P1->SEL0 &= ~BIT1;    //
     P1->SEL1 &= ~BIT1;    //General I/O is enable for P1.1
     P1->OUT |= BIT1;      //enable the pull up register
     P1->DIR &= ~BIT1;     //p1.1 to be input
     P1->REN |= BIT1;      //Enable pull-up resistor for P1.1
     P1 ->IFG &= ~BIT1;
     P1->IE |= BIT1;       //Enable interrupt for P1.1
     P1->IES |= BIT1;      //Interrupt on high to low transition
     NVIC_EnableIRQ(PORT1_IRQn); // enable the interrupts for port 1
}

void PORT1_IRQHandler(){
    int delay;
    for(delay = 0; delay < 200; delay ++ ){}
    if (P1->IFG & BIT1  ){
        P1 -> IFG &=~ BIT1;
        clear_Buffer(&myBufferPTR);
    }
     if(P1->IFG & BIT4){
        P1 ->IFG &=~BIT4;
        print(myBufferPTR);
        P2OUT ^= BIT2;
    }
 }
