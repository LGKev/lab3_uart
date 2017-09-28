/*
 * circular_buffer.c
 *
 *  Created on: Sep 24, 2017
 *      Author: kevinKuwata1
 */
#ifdef working

#include "circular_buffer.h"

/*
 *  Initialize the circular buffer type
 * */
CB_Status CB_initialize_buffer(CircBuf_t * buf, uint32_t length);

/*
 * Clears the elements in the buffer. Sets num_items = 0.
 * */
CB_Status CB_clear_buffer(CircBuf_t * buf);


/*
 * Clears the buffer, and then deletes the reference to the pointer to the base of the buffer.
 * Necessary to prevent memory leaks.
 * */
CB_Status CB_delete_buffer(CircBuf_t * buf);

/*
 * Returns if the buffer is full.
 * Checks by comparing number of items in the buffer to the max length.
 * Returns 1 if full, 0 if not full.
 * */
int8_t CB_is_buffer_full(CircBuf_t * buf){
    if(buf->num_items == buf->length){
        return 1;
    }
    else{
        return 0;
    }
}

/*
 * Returns non zero if the buffer is empty.
 * Checks by comparing number of items in the buffer, if equal to 0 , buffer is empty.
 * Return 0 if empty, and 1 if not empty.
 * */
int8_t CB_is_buffer_empty(CircBuf_t * buf){
    if(buf->length == 0){
        return 0;
    }
    else{
        return 1;
    }
}


/*
 * Adds item to the buffer, adds item to the current tail, then increments tail one position.
 * Checks to see buffer isn't full
 * */
CB_Status CB_add_item_to_buffer(CircBuf_t * buf, uint8_t item);

/* Removes Item from the HEAD of the buffer, decrements the item number
 * checks to see if buffer is empty.
 * */
CB_Status CB_remove_item_from_buffer(CircBuf_t * buf){
  //check if empty
    if(buf->num_items == 0){
       // return  //what is the equivalent of null or return an error?
    }
    else{
        buf->num_items --; //decrement
        CB_Status oldHead = buf->head;
        buf->head--;
        return oldHead;
    }

}
#endif
