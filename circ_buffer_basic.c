/*
 * circ_buffeR_basic.c
 *
 *  Created on: Oct 6, 2017
 *      Author: kk
 */


#include "circular_buffer.h"
#include <stdlib.h>
#include "lab3.h"



void initBuffBasic(CircBuf_t **myBase, uint8_t _length){
  uint8_t  *buffer = (uint8_t * )malloc(_length*sizeof(uint8_t));

          (*myBase) ->num_items =0;
          (*myBase) ->tailPosition = 0;
          (*myBase) ->length = _length;
          (*myBase) ->head = buffer;
          (*myBase) ->tail = buffer;
          (*myBase) ->buffer = buffer;



}


void addBuffer(CircBuf_t **buf, uint8_t item){
    (*buf)->num_items++;
    *(*buf)->head = item; //* once to derefefernce doulbe pointer, then *again to deref head.
    (*buf) ->head++;//move the head 1 spot.

}

uint8_t popValue(CircBuf_t ** buf){

    uint8_t  oldTail = *(*buf)->tail;
    (*buf)->num_items--;
    (*buf)->tail++;
    (*buf)->tailPosition++;
            return oldTail;
}
