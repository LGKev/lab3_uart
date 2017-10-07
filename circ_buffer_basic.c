/*
 * circ_buffeR_basic.c
 *
 *  Created on: Oct 6, 2017
 *      Author: kk
 */

#include "circular_buffer.h"
#include <stdlib.h>
#include "lab3.h"

extern pointerToCircBuffer;


void initBuffBasic(CircBuf_t **myBase, uint8_t _length){
    myBase = (CircBuf_t * )malloc(_length*sizeof(uint8_t));

           &myBase ->num_items =0;
           myBase ->tailPosition = 34;
           myBase ->length = _length;
           myBase ->head = &myBase;
           myBase ->tail = &myBase;
           myBase ->buffer = &myBase;


           pointerToCircBuffer = &myBase;

}


void addBuffer(CircBuf_t *buf, uint8_t item){

}
