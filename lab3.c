/*
 * lab3.c
 *
 *  Created on: Sep 24, 2017
 *      Author: kevinKuwata1
 */


#include "msp.h"
#include <stdint.h>

void configure_clocks(void){
    CS->KEY = 0x695A; //unlock 5.3.1
    CS->CTL0 = 0 ;
    CS->CTL0 |= CS_CTL0_DCOEN | CS_CTL0_DCORSEL_2;  //enable DCO, then mode 3 for 8 to 16 Mhz
    CS->CTL0 |= 100111000; //and should be 4MHZ

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
