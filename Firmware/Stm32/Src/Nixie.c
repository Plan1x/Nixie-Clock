/*
 * Nixie.c
 *
 *  Created on: Apr 6, 2024
 *      Author: irubt
 */
#include "Nixie.h"

void init(uint8_t *parr)//Refreshing Indicators
{
	for (uint8_t i = 0; i < 10; i++)
	{
		for (uint8_t j = 0; j < 6; j++)
		{
			parr[j] = i;

		}
		show(parr);

	}
}
void decoder_set(uint8_t number) //Decoder control method
{
	switch (number) {
	case 0:
		HAL_GPIO_WritePin(GPIOB, A_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, B_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, C_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, D_Pin, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, A_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, B_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, C_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, D_Pin, 0);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, A_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, B_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, C_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, D_Pin, 0);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, A_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, B_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, C_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, D_Pin, 0);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOB, A_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, B_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, C_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, D_Pin, 0);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOB, A_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, B_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, C_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, D_Pin, 0);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOB, A_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, B_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, C_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, D_Pin, 0);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOB, A_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, B_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, C_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, D_Pin, 0);
		break;
	case 8:
		HAL_GPIO_WritePin(GPIOB, A_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, B_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, C_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, D_Pin, 1);
		break;
	case 9:
		HAL_GPIO_WritePin(GPIOB, A_Pin, 1);
		HAL_GPIO_WritePin(GPIOB, B_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, C_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, D_Pin, 1);
		break;
	}
}
void show(uint8_t *parr) //Displaying time
{

	decoder_set(parr[0]); // setting hours
	HAL_GPIO_WritePin(GPIOB, Red_indicator_Pin, 1);
	HAL_Delay(DEL_PARAM);
	HAL_GPIO_WritePin(GPIOB, Red_indicator_Pin, 0);


	decoder_set(parr[1]); // setting hours
	HAL_GPIO_WritePin(GPIOB, Black_indicator_Pin, 1);
	HAL_Delay(DEL_PARAM);
	HAL_GPIO_WritePin(GPIOB, Black_indicator_Pin, 0);


	decoder_set(parr[2]); // setting minutes
	HAL_GPIO_WritePin(GPIOB, White_indicator_Pin, 1);
	HAL_Delay(DEL_PARAM);
	HAL_GPIO_WritePin(GPIOB, White_indicator_Pin, 0);


	decoder_set(parr[3]); // setting minutes
	HAL_GPIO_WritePin(GPIOA, Yellow_indicator_Pin, 1);
	HAL_Delay(DEL_PARAM);
	HAL_GPIO_WritePin(GPIOA, Yellow_indicator_Pin, 0);


	decoder_set(parr[4]); // setting seconds
	HAL_GPIO_WritePin(GPIOA, Green_indicator_Pin, 1);
	HAL_Delay(DEL_PARAM);
	HAL_GPIO_WritePin(GPIOA, Green_indicator_Pin, 0);

	decoder_set(parr[5]); // setting seconds
	HAL_GPIO_WritePin(GPIOA, Blue_indicator_Pin, 1);
	HAL_Delay(DEL_PARAM);
	HAL_GPIO_WritePin(GPIOA, Blue_indicator_Pin, 0);

}

