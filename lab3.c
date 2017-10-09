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

extern uint32_t global_number_Of_Beam_Breaks;
extern uint8_t Calculate_Distance;

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

/* IR Beam Break configure on pin 0 of port 3. */
     P3->SEL0 &=~BIT0;
     P3->SEL1 &=~BIT0;
     P3->REN |= BIT0; //pullup
     P3->IFG &=~BIT0;
     P3->IE |= BIT0;
     P3->IES |= BIT0;

     NVIC_EnableIRQ(PORT3_IRQn);
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


void PORT3_IRQHandler(){
if(P3->IFG & BIT0){
    P3->IFG &=~BIT0;

    global_number_Of_Beam_Breaks++;
    if(global_number_Of_Beam_Breaks %14 == 0){
        Calculate_Distance = 1;
    }
}

}


static void reverse(char str[], int len)        //function to reverse string to get it readable and not backwards
{
    int start, end;
    char temp;
    for (start=0, end = len-1; start<end; start++, end--)
    {
        temp = *(str+start);
        *(str+start)= *(str+end);
        *(str+end) = temp;
    }
}

static int intToStr(int value, char str[], int length)
{
    int i = 0;
    while (value)
    {
        str[i++] = (value%10) + '0';
        value = value/10;
    }
    while (i < length)
    {
        str[i++] = '0';
    }
    reverse(str,i);
    str[i] = '\0';
    return i;
}

extern char itoa (int value, char str[], int base)           //integer to string function
{
    int  i = 0;
    int sign;

    if ((sign = value) < 0){        //What to do if values is negative
        value = -value;         //make value positive so we can work with
    }

    do{
        str[i++] = value % base + '0';
    }while ((value /= base) > 0);

    if (sign < 0){
        str[i++] = '-';
    }
    str[i] = '\0';
    reverse(str,i);

}

extern char ftoa(float f, char str[], int afterpoint)           //float to string function
{
    int ipart = (int)f;

    float fpart = f - (float)ipart;

    int i = intToStr(ipart, str, 0);

    if (afterpoint != 0)
    {
        str[i] = '.';

        fpart = fpart * pow(10,afterpoint);

        intToStr((int)fpart, str + i + 1, afterpoint);
    }
}
