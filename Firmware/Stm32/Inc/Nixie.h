/*
 * Nixie.h
 *
 *  Created on: Apr 6, 2024
 *      Author: irubt
 */

#ifndef INC_NIXIE_H_
#define INC_NIXIE_H_
#include "main.h"

#define DEL_PARAM 1

void init(uint8_t *parr);
void decoder_set(uint8_t number);
void show(uint8_t *parr);

#endif /* INC_NIXIE_H_ */
