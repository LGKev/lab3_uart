/*
 * circular_buffer.c
 *
 *  Created on: Sep 24, 2017
 *      Author: kevinKuwata1
 */

#include <stdlib.h>
#include "lab3.h"




#include "circular_buffer.h"





extern CircBuf_t * myBufferPTR;
extern CircBuf_t ** pointerToCircBuffer;



/*
 *  Initialize the circular buffer type
 * */
void CB_initialize_buffer(CircBuf_t * buf, uint32_t length){
    //good practice to check if pointer exists
//    if(buf != NULL){ //this is equivalent to if(buf != NULL)

        buf = (CircBuf_t *) malloc(length*sizeof(uint8_t));


       // buf->buffer = myBufferPTR;

       buf->num_items = 0;
        buf->tailPosition =0;

        buf->head = buf;
        buf->tail = buf;


}

/*extern
 * Clears the elements in the buffer. Sets num_items = 0.
 * */
void CB_clear_buffer(CircBuf_t * buf){
    //check to see if valid
    if(!buf){
        //clear buffer
        buf->head = buf;//set head back to beginning
        buf->tail = buf; //set tail back to begining
        buf->num_items = 0 ;// says we can write it over again

        //note: we don't actually clear data, we just say that its available to be written again.
        //do not clear the buffer pointer, we will lose access to it.we are clearning not deleting
    }
    else{
        //maybe log bad data, for now do nothing.
    }
}


/*
 * Clears the buffer, and then deletes the reference to the pointer to the base of the buffer.
 * Necessary to prevent memory leaks.
 * */
uint8_t CB_delete_buffer(CircBuf_t * buf){
    //again check if valid
    if(!buf){
        //we will free the buffer. technically not required to clear buffer first. just delete allocation
        free(buf);
        return 1; //successful deletion.
    }
    else{
        return 0; // error
    }
}

/*
 * Returns if the buffer is full.
 * Checks by comparing number of items in the buffer to the max length.
 * Returns 1 if full, 0 if not full.
 * */
int8_t CB_is_buffer_full(CircBuf_t * buf){
    if(!buf){
        if(buf->num_items == buf->length){
                return 1;
            }
            else{
                return 0;
            }
    }
    else{
        return -1; //error
    }
}

/*
 * Returns non zero if the buffer is empty.
 * Checks by comparing number of items in the buffer, if equal to 0 , buffer is empty.
 * Return 0 if empty, and 1 if not empty.
 * */
int8_t CB_is_buffer_empty(CircBuf_t * buf){
    if(!buf){
        if(buf->num_items == 0){
                return 0;
            }
            else{
                return 1; //this way we can check that if(CB_is_BUFFER_EMPTY(buf)) and it will return 1 if true.
            }
    }
    return -1; // error
}


/*
 * Adds item to the buffer, adds item to the current tail, then increments tail one position.
 * Checks to see buffer isn't full
 * */
uint8_t CB_add_item_to_buffer(CircBuf_t * buf,  uint8_t item){
    //check if legit



        //Case 1: Empty
        if(CB_is_buffer_empty(buf)){
            //just add the item to the head and move head
            *buf->head =  item; //dereference the buffer head and put the value into that address.?
             buf->head++;
             buf->num_items++;//increment the number of items
             return 1;
        }
        else{
        //Case 2: Not empty, not full
            if(buf->num_items != buf->length){
                //then were not full.
                *(buf->head) = item;
                buf->head++;
                buf->num_items++;
                return 1;
            }
            else{        //Case 3: Full, requires loop around.
                buf->head = buf;//loops back
                buf->tail++; //tail moves one spot ahead, old tail gets over written.
                *(buf->head) = item;
                //number of items stays the same cuz were full.
                return 1;
            }
        }
        return 1;
    }


/* Removes Item from the tail of the buffer, decrements the item number
 * checks to see if buffer is empty.
 * */
CircBuf_t * CB_remove_item_from_buffer(CircBuf_t * buf){
  //check to make sure legit pointer
    if(!buf){
        if(CB_is_buffer_empty(buf)){        // CASE 1: Empty
              return NULL; //not valid
           }
           else{
               CircBuf_t * popped_value = NULL;
               //CASE 2: not full, no loop over
               if((buf->head) - (buf->tail) >= 0 ){
                   //simplly remove the tail, move it and decrement count

                popped_value = buf->tail;
                buf->tail++;//increment tail to next spot
                buf->num_items--; //decrease by 1.
                buf->tailPosition++;
                   return popped_value;
               }
               else{
                // CASE 3: full and had a loop over
                   //must be that we had a loop over/ head will be before tail tehrefore negative
                   //think carefully how the tail will move when its at the end!

                   popped_value = buf->tail;
                   if(buf->tailPosition == buf->length ){ // make length so that portable.//either 255 or 256 because of tailPosition++ when tail moves .
                       //must be at the end so move to head
                       buf->tail = buf->baseConst;
                       buf->tailPosition = 0;
                   }
                   return popped_value;

               }

           }
    }
    else{
        return NULL;
    }

    //check if empty


}

