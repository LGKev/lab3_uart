/*
 * circ_buffer_basic.h
 *
 *  Created on: Oct 6, 2017
 *      Author: kk
 */

#include "circular_buffer.h"

#ifndef CIRC_BUFFER_BASIC_H_
#define CIRC_BUFFER_BASIC_H_


void initBuffBasic(CircBuf_t **buf, uint8_t _length);

void addBuffer(CircBuf_t *buf, uint8_t item);



#endif /* CIRC_BUFFER_BASIC_H_ */
