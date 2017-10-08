/*
 * circ_buffeR_basic.c
 *
 *  Created on: Oct 6, 2017
 *      Author: kk
 */

#include "circular_buffer.h"
#include <stdlib.h>
#include "lab3.h"

void initialize_Circ_Buffer(CircBuf_t **myBase, uint8_t _length)
{

    //tests

    if (*myBase != NULL)
    {
        uint8_t *_buffer = (uint8_t *) malloc(_length * sizeof(uint8_t));

        if (_buffer != NULL)
        {
            (*myBase)->baseConst = _buffer;
            (*myBase)->num_items = 0;
            (*myBase)->tailPosition = 0;
            (*myBase)->length = _length;
            (*myBase)->head = _buffer;
            (*myBase)->tail = _buffer;
        }
        else
        {
            //TODO: Error Logging, Malloc Failed
        }
    }
    else
    {
        //TODO: Error Logging       bad pointer        Enum:CB_STATUS
    }
}

void add_To_Buffer(CircBuf_t **buf, uint8_t item)
{
    if (*buf != NULL)
    {
        if (is_Circ_Buf_Empty(buf))
        {
            //Case 1: Empty
            (*buf)->num_items++;
            *(*buf)->head = item; //* once to derefefernce doulbe pointer, then *again to deref head.
            (*buf)->head++; //move the head 1 spot.
        }
        else
        {
            //Case 2: Not Empty, Not Full
            if ((*buf)->num_items != (*buf)->length)
            {
                *(*buf)->head = item; //* once to derefefernce doulbe pointer, then *again to deref head.
                (*buf)->num_items++;
                    if((*buf)->num_items == (*buf)->length){
                        //loop head around
                        (*buf)->head = (*buf)->baseConst; //loop around
                    }
                    else{
                        (*buf)->head++; //move the head 1 spot.
                    }
            }
            else{
             // Case 3: Full circular buffer, do not overwrite?
                //TODO: what happens when full?
                return;
            }
        }
    }
}

int8_t remove_From_Buffer(CircBuf_t ** buf)
{
    if (*buf != NULL)
    {
        if (is_Circ_Buf_Empty(buf)) //Case 1: Empty
        {
            return -1;
        }
        else{
            uint8_t oldTail = *(*buf)->tail;
            (*buf)->num_items--;

            //Case 2: Not Empty, tail before head
            if(((*buf)->head - (*buf)->tail) > 0){
                (*buf)->tail++;
                (*buf)->tailPosition++;
            return oldTail;
            }
            else if(((*buf)->head - (*buf)->tail) < 0){
                // Case 3: Not Empty, but head is before tail (loop around)
                //check if tail is at the end or not
                if((*buf)->tailPosition == (*buf)->length){
                    //must require a loop around of the tail
                    (*buf)->tailPosition = 0;
                    (*buf)->tail = (*buf)->baseConst; //send tail back to front.
                }
                else{ //we are not at the end but there was a loop around

                    (*buf)->tail++;
                    (*buf)->tailPosition++;

                }
                return oldTail;
            }
            else{           //Final Case: Not Empty, Not full, 1 item only.
                    (*buf)->tail++;
                    (*buf)->tailPosition++;

            }

        }
    }
}

/*
 *  Helper Functions
 *
 * */

int8_t is_Circ_Buf_Full(CircBuf_t **buf)
{
    if ((*buf)->num_items == (*buf)->length)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t is_Circ_Buf_Empty(CircBuf_t **buf)
{
    if ((*buf)->num_items == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint16_t currentSize(CircBuf_t **buf){
    return (*buf)->num_items;
}

