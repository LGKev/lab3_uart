/*
 * circ_buffeR_basic.c
 *
 *  Created on: Oct 6, 2017
 *      Author: kk
 */


#include "circular_buffer.h"
#include <stdlib.h>
#include "lab3.h"



void initialize_Circ_Buffer(CircBuf_t **myBase, uint8_t _length){

    uint8_t  *_buffer = (uint8_t * )malloc(_length*sizeof(uint8_t));

          (*myBase) ->baseConst = _buffer;
          (*myBase) ->num_items = 0;
          (*myBase) ->tailPosition = 0;
          (*myBase) ->length = _length;
          (*myBase) ->head = _buffer;
          (*myBase) ->tail = _buffer;
}


void add_To_Buffer(CircBuf_t **buf, uint8_t item){
    (*buf)->num_items++;
    *(*buf)->head = item; //* once to derefefernce doulbe pointer, then *again to deref head.
    (*buf) ->head++;//move the head 1 spot.

}

uint8_t remove_From_Buffer(CircBuf_t ** buf){

    uint8_t  oldTail = *(*buf)->tail;
    (*buf)->num_items--;
    (*buf)->tail++;
    (*buf)->tailPosition++;
            return oldTail;
}


uint8_t is_Circ_Buf_Full(CircBuf_t **buf){
    if((*buf)->num_items == (*buf)->length){
        return 1;
    }
    else{
        return 0;
    }
}

uint8_t is_Circ_Buf_Empty(CircBuf_t **buf){
    if((*buf)->num_items == 0){
        return 1;
    }
    else{
        return 0;
    }
}


