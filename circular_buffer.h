/*
 * circular_buffer.h
 *
 *  Created on: Sep 24, 2017
 *      Author: kevinKuwata1
 */
#ifdef working
#include <stdint.h>

#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_


typedef struct {
    uint8_t * buffer;                       // pointer to the base of the buffer in heap
    volatile uint8_t * head;                // Pointer to first item //start of buffer  // FIFO
    volatile uint8_t * tail;                // Marks the end of buffer, where new things are added. so head only moves when we pop out. and tail moves when we add.
    volatile uint32_t * num_items;          // good to know how many items are in the buffer , so array may be 50 long, but only 3 spots are filled. we don't want to go from 4 to 50.
    volatile uint32_t length;               // Max number of items that can be held
} CircBuf_t;


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
int8_t CB_is_buffer_full(CircBuf_t * buf);

/*
 * Returns non zero if the buffer is empty.
 * Checks by comparing number of items in the buffer, if equal to 0 , buffer is empty.
 * Return 0 if empty, and 1 if not empty.
 * */
int8_t CB_is_buffer_empty(CircBuf_t * buf);


/*
 * Adds item to the buffer, adds item to the current tail, then increments tail one position.
 * Checks to see buffer isn't full
 * */
CB_Status CB_add_item_to_buffer(CircBuf_t * buf, uint8_t item);

/* Removes Item from the HEAD of the buffer, decrements the item number
 * checks to see if buffer is empty.
 * */
CB_Status CB_remove_item_from_buffer(CircBuf_t * buf);

#endif /* CIRCULAR_BUFFER_H_ */
#endif
