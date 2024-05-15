/*
 * Oledmenu.h
 *
 *  Created on: Apr 18, 2024
 *      Author: irubt
 */

#ifndef INC_OLEDMENU_H_
#define INC_OLEDMENU_H_
#include "main.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"
#include "stdio.h"
#include "stdbool.h"


typedef struct
{

	uint8_t counter;
	uint8_t buff_time[20];//buffer for labels
	uint16_t timer;//for blinking pointer
	bool flag_for_ptr_horizontal;
	uint8_t hours,minutes,seconds;
	bool color;

}Oled;

void intro_anim(unsigned char **  devils_eyes_bitmapallArray, unsigned char ** loading_bitmap);
void intro_menu(uint8_t ptr_argument_vertical, uint8_t ptr_argument_horizontal ,uint8_t counter);
void updating_time_buffer(void);
void ptr_for_setting_time(uint8_t ptr_position);
#endif /* INC_OLEDMENU_H_ */
