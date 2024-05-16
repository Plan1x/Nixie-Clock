/*
 * Encoder.c
 *
 *  Created on: Apr 17, 2024
 *      Author: irubt
 */
#include "Encoder.h"

uint8_t prev_status, counter_for_time_setting;

uint16_t Time;

int8_t ptr_counter_vertical;

volatile bool flag_for_vertical_ptr, flag_for_horizontal_ptr;

RTC_TimeTypeDef sTime;

void Enc_init(void) {
	if (HAL_GPIO_ReadPin(GPIOA, S1_Pin) && HAL_GPIO_ReadPin(GPIOA, S2_Pin)) // S1 - B, S2 - A
			{
		prev_status = 0x11;
	} else if (!HAL_GPIO_ReadPin(GPIOA, S1_Pin) && HAL_GPIO_ReadPin(GPIOA, S2_Pin)) //Clockwise
					{
		prev_status = 0x10;
	} else if (HAL_GPIO_ReadPin(GPIOA, S1_Pin) && !HAL_GPIO_ReadPin(GPIOA, S2_Pin)) //Counterclockwise
					{
		prev_status = 0x01;
	} else if (!HAL_GPIO_ReadPin(GPIOA, S1_Pin) && !HAL_GPIO_ReadPin(GPIOA, S2_Pin))
	{
		prev_status = 0x00;
	}
}
void Enc_rotating_handler(void) {
	uint8_t status;

	if (HAL_GPIO_ReadPin(GPIOA, S1_Pin) && HAL_GPIO_ReadPin(GPIOA, S2_Pin)) // S1 - B, S2 - A
			{
		status = 0x11;
	} else if (!HAL_GPIO_ReadPin(GPIOA, S1_Pin)
			&& HAL_GPIO_ReadPin(GPIOA, S2_Pin)) //Counterclockwise
					{
		status = 0x10;
	} else if (HAL_GPIO_ReadPin(GPIOA, S1_Pin)
			&& !HAL_GPIO_ReadPin(GPIOA, S2_Pin)) //Clockwise
					{
		status = 0x01;
	} else if (!HAL_GPIO_ReadPin(GPIOA, S1_Pin)
			&& !HAL_GPIO_ReadPin(GPIOA, S2_Pin)) {
		status = 0x00;
	}
	if (prev_status == 0x10 && status == 0x11)
	{
		if (HAL_GetTick() - Time > 100)
		{
			if (ptr_counter_vertical < 127)
			{
				if (flag_for_vertical_ptr)
				{
					ptr_counter_vertical = (ptr_counter_vertical < 1 && ptr_counter_vertical >= 0) ? (ptr_counter_vertical + 1) : ptr_counter_vertical;

				} else if (flag_for_horizontal_ptr)
				{
					switch (counter_for_time_setting)
					{
					case 0:
						sTime.Hours = (sTime.Hours >= 0 && sTime.Hours < 23) ? (sTime.Hours + 1) : sTime.Hours;
						//sTime.Hours = (sTime.Hours == 24) ? 0 : sTime.Hours;
						break;
					case 1:
						sTime.Minutes = (sTime.Minutes >= 0 && sTime.Minutes < 59) ? (sTime.Minutes + 1) : sTime.Minutes;
						//sTime.Minutes = (sTime.Minutes == 60) ? 0 : sTime.Minutes;
						break;
					case 2:
						sTime.Seconds = (sTime.Seconds >= 0 && sTime.Seconds < 59) ? (sTime.Seconds + 1) : sTime.Seconds;
						//sTime.Seconds = (sTime.Seconds == 60) ? 0 : sTime.Seconds;
						break;
					}
				}

			}

			Time = HAL_GetTick();
		}

	} else if (prev_status == 0x01 && status == 0x00)
	{

		if (HAL_GetTick() - Time > 100)
		{
			if (ptr_counter_vertical < 127)
			{
				if (flag_for_vertical_ptr)
				{
					ptr_counter_vertical = (ptr_counter_vertical < 1 && ptr_counter_vertical >= 0) ? (ptr_counter_vertical + 1) : ptr_counter_vertical;
				} else if (flag_for_horizontal_ptr)
				{
					switch (counter_for_time_setting)
					{
					case 0:
						sTime.Hours = (sTime.Hours >= 0 && sTime.Hours < 23) ? (sTime.Hours + 1) : sTime.Hours;
						//sTime.Hours = (sTime.Hours == 24) ? 0 : sTime.Hours;
						break;
					case 1:
						sTime.Minutes = (sTime.Minutes >= 0 && sTime.Minutes < 59) ? (sTime.Minutes + 1) : sTime.Minutes;
						//sTime.Minutes = (sTime.Minutes == 60) ? 0 : sTime.Minutes;
						break;
					case 2:
						sTime.Seconds = (sTime.Seconds >= 0 && sTime.Seconds < 59) ? (sTime.Seconds + 1) : sTime.Seconds;
						//sTime.Seconds = (sTime.Seconds == 60) ? 0 : sTime.Seconds;
						break;
					}
				}
			}

			Time = HAL_GetTick();
		}

	}

	if (prev_status == 0x11 && status == 0x10) {
		prev_status = 0x10;

	} else if (prev_status == 0x00 && status == 0x01) {
		prev_status = 0x01;

	}

	else if (prev_status == 0x10 && status == 0x00) {

		if (HAL_GetTick() - Time > 100) {
			if (ptr_counter_vertical > -127) {
				if (flag_for_vertical_ptr) {
					ptr_counter_vertical = (ptr_counter_vertical > 0 && ptr_counter_vertical <= 1) ? (ptr_counter_vertical - 1) : ptr_counter_vertical;
				} else if (flag_for_horizontal_ptr) {
					switch (counter_for_time_setting) {
					case 0:
						sTime.Hours = (sTime.Hours <= 23 && sTime.Hours > 0) ? (sTime.Hours - 1) : sTime.Hours;
						sTime.Hours = (sTime.Hours == 255) ? 23 : sTime.Hours;
						break;
					case 1:
						sTime.Minutes = (sTime.Minutes > 0 && sTime.Minutes <= 59) ? (sTime.Minutes - 1) : sTime.Minutes;

						break;
					case 2:
						sTime.Seconds = (sTime.Seconds > 0 && sTime.Seconds <= 59) ? (sTime.Seconds - 1) : sTime.Seconds;
						break;
					}
				}

			}

			Time = HAL_GetTick();
		}

	}

	else if (prev_status == 0x01 && status == 0x11)
	{
		if (HAL_GetTick() - Time > 100)
		{
			if (ptr_counter_vertical > -127)
			{
				if (flag_for_vertical_ptr)
				{
					ptr_counter_vertical =(ptr_counter_vertical > 0 && ptr_counter_vertical <= 1) ? (ptr_counter_vertical - 1) :ptr_counter_vertical;
				}else if (flag_for_horizontal_ptr) {
					switch (counter_for_time_setting) {
					case 0:
						sTime.Hours = (sTime.Hours <= 23 && sTime.Hours > 0) ? (sTime.Hours - 1) : sTime.Hours;
						//sTime.Hours = (sTime.Hours == 255) ? 23 : sTime.Hours;
						break;
					case 1:
						sTime.Minutes = (sTime.Minutes > 0 && sTime.Minutes <= 59) ? (sTime.Minutes - 1) : sTime.Minutes;
						break;
					case 2:
						sTime.Seconds = (sTime.Seconds > 0 && sTime.Seconds <= 59) ? (sTime.Seconds - 1) : sTime.Seconds;
						break;
					}
				}
			}

			Time = HAL_GetTick();
		}

	}
	prev_status = status;

}

