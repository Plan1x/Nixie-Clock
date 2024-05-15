/*
 * Oledmenu.c
 *
 *  Created on: Apr 18, 2024
 *      Author: irubt
 */
#include "Oledmenu.h"

Oled Oled_1; //Global structure



void intro_anim( unsigned char **  devils_eyes_bitmapallArray,  unsigned char ** loading_bitmap) //Intro animation
{
	ssd1306_DrawBitmap(4, 0, (devils_eyes_bitmapallArray[5]), 124, 40, White);
	 for(uint8_t i = 0; i < 165 ; i++)
	 {

		 ssd1306_DrawBitmap(0, 50, (loading_bitmap[i]), 124, 7, White);
		 ssd1306_FillRectangle(118, 50, 128, 60, Black);
		 ssd1306_UpdateScreen();
	 }

	for(uint8_t i = 0; i < 18; i++)
	 {
		 ssd1306_DrawBitmap(4, 0, (devils_eyes_bitmapallArray[i]), 124, 40, White);

		  ssd1306_UpdateScreen();

	 }

		HAL_Delay(300);
		ssd1306_Fill(Black);
		ssd1306_UpdateScreen();



}
void intro_menu(uint8_t ptr_argument_vertical, uint8_t ptr_argument_horizontal,uint8_t counter)//state machine for menu
{

	switch(counter)
	{
	case 0:

			//flag_for_menu = 0;
			ssd1306_Fill(Black);
			ssd1306_SetCursor(0, 0);
			ssd1306_WriteString("Press btn to set", Font_7x10, White);
			ssd1306_SetCursor(0, 10);
			ssd1306_WriteString("the Time",Font_7x10, White);
			ssd1306_SetCursor(0, 35);
			//updating_time_buffer();


	ssd1306_UpdateScreen();
		break;
	case 1:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Setting the Time", Font_7x10, White);
		ssd1306_SetCursor(10, 35);
		updating_time_buffer();
		ptr_for_setting_time(ptr_argument_vertical);
		ssd1306_SetCursor(10, 50);
		ssd1306_WriteString("Save", Font_7x10, White);
		if(Oled_1.flag_for_ptr_horizontal)
		{
		switch(ptr_argument_horizontal)
		{
			case 0:
				ssd1306_FillRectangle(46, 44, 57, 46, Oled_1.color);
				break;
			case 1:
				ssd1306_FillRectangle(67, 44, 78, 46, Oled_1.color);
				break;
			case 2:
				ssd1306_FillRectangle(88, 44, 99, 46, Oled_1.color);
				break;
			default:
				ssd1306_FillRectangle(46, 44, 64, 46, Black);
				break;
		}
		}
	ssd1306_UpdateScreen();
		break;

	}
	//ssd1306_UpdateScreen();
}
void updating_time_buffer(void) // Main display buffer
{
		if(Oled_1.hours < 10 && Oled_1.minutes > 9 && Oled_1.seconds > 9)
		{
			snprintf(Oled_1.buff_time, 60,"Time:0%u:%u:%u", Oled_1.hours, Oled_1.minutes,Oled_1.seconds);
			ssd1306_WriteString(Oled_1.buff_time, Font_7x10, White);
		}else if(Oled_1.minutes < 10 &&  Oled_1.hours > 9 && Oled_1.seconds > 9)
		{
			snprintf(Oled_1.buff_time, 60,"Time:%u:0%u:%u", Oled_1.hours, Oled_1.minutes,Oled_1.seconds);
			ssd1306_WriteString(Oled_1.buff_time, Font_7x10, White);
		}else if(Oled_1.seconds < 10 && Oled_1.minutes > 9 &&  Oled_1.hours > 9)
		{
			snprintf(Oled_1.buff_time, 60,"Time:%u:%u:0%u", Oled_1.hours, Oled_1.minutes,Oled_1.seconds);
			ssd1306_WriteString(Oled_1.buff_time, Font_7x10, White);
		}else if(Oled_1.minutes < 10 && Oled_1.hours < 10 && Oled_1.seconds > 9)
		{
			snprintf(Oled_1.buff_time, 60,"Time:0%u:0%u:%u", Oled_1.hours, Oled_1.minutes,Oled_1.seconds);
			ssd1306_WriteString(Oled_1.buff_time, Font_7x10, White);
		}else if(Oled_1.seconds < 10 && Oled_1.hours < 10 && Oled_1.minutes > 9)
		{
			snprintf(Oled_1.buff_time, 60,"Time:0%u:%u:0%u", Oled_1.hours, Oled_1.minutes,Oled_1.seconds);
			ssd1306_WriteString(Oled_1.buff_time, Font_7x10, White);
		}else if(Oled_1.seconds < 10 && Oled_1.minutes < 10 && Oled_1.hours > 9)
		{
			snprintf(Oled_1.buff_time, 60,"Time:%u:0%u:0%u", Oled_1.hours, Oled_1.minutes,Oled_1.seconds);
			ssd1306_WriteString(Oled_1.buff_time, Font_7x10, White);
		}else if(Oled_1.seconds < 10 && Oled_1.minutes < 10 && Oled_1.hours < 10)
		{
			snprintf(Oled_1.buff_time, 60,"Time:0%u:0%u:0%u", Oled_1.hours, Oled_1.minutes,Oled_1.seconds);
			ssd1306_WriteString(Oled_1.buff_time, Font_7x10, White);
		}else
		{
			snprintf(Oled_1.buff_time, 60,"Time:%u:%u:%u", Oled_1.hours, Oled_1.minutes,Oled_1.seconds);
			ssd1306_WriteString(Oled_1.buff_time, Font_7x10, White);
		}




}
void ptr_for_setting_time(uint8_t ptr_position) // Vertical pointer control
{
	switch(ptr_position)
	{
		case 0:
			ssd1306_FillRectangle(0, 30, 6, 64, Black);
			ssd1306_SetCursor(0, 35);
			ssd1306_WriteChar('>', Font_7x10, White);

			break;
		case 1:
			ssd1306_FillRectangle(0, 30, 6, 64, Black);
			ssd1306_SetCursor(0, 50);
			ssd1306_WriteChar('>', Font_7x10, White);

			break;

	}
}
