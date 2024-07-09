/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "rtc.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Nixie.h"
#include "Encoder.h"
#include "Oledmenu.h"
#include "stdbool.h"
#include "ssd1306.h"
#include "Btmp.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


uint8_t time_arr[6] = { 0, };

volatile bool extra_flag = 0;
volatile bool flag_for_menu = 0;
volatile bool flag_entering_setting_menu;
volatile bool flag_for_stop_time_ticking = 1;
volatile bool flag_for_refreshing_indicators = 0;
volatile bool flag_for_btn = 0;
volatile bool flag_for_starting_system = 0;

volatile uint8_t counter_overflow = 0;
volatile uint8_t btn_counter = 0;
volatile uint8_t counter = 0;

volatile uint16_t timer = 0;


extern volatile bool flag_for_horizontal_ptr;
extern volatile bool flag_for_vertical_ptr;

extern uint8_t prev_status;

extern int8_t ptr_counter_vertical;
extern int8_t counter_for_time_setting;

extern uint16_t Time, Time_old;

extern Oled Oled_1;
extern RTC_TimeTypeDef sTime;

RTC_DateTypeDef DateToUpdate = { 0 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t* divider(uint8_t *parr);
void button_handler(void);
void refreshing_indicators_handler(void);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(flag_for_starting_system)
	{
	if (htim->Instance == TIM2)
	{
		refreshing_indicators_handler();
	} else if(htim -> Instance == TIM3)
	{

		Oled_1.color = !Oled_1.color;

/////////////////////////////////////////// INDICATORS BACKLIGHT
//		HAL_GPIO_TogglePin(GPIOB, Led_1_Pin);
//		HAL_GPIO_TogglePin(GPIOB, Led_2_Pin);
//		HAL_GPIO_TogglePin(GPIOB, Led_3_Pin);
//		HAL_GPIO_TogglePin(GPIOA, Led_4_Pin);
/////////////////////////////////////////// INDICATORS BACKLIGHT
	}
	else if (htim->Instance == TIM1)
	{

		button_handler();
		Enc_rotating_handler();
	}
	}

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
//////////////////////////////////////////MAGIC NUMBERS
	flag_entering_setting_menu = 0;
	flag_for_vertical_ptr = 0;
	flag_for_horizontal_ptr = 0;
	counter_for_time_setting = -1;
	Oled_1.timer = 0;
//////////////////////////////////////////MAGIC NUMBERS
	Enc_init(); // Encoder Init


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	ssd1306_Init();
	intro_anim(devils_eyes_bitmapallArray, epd_bitmap_allArray);
	flag_for_starting_system = 1;
	intro_menu(ptr_counter_vertical,counter_for_time_setting, counter);
	init(time_arr); // Refreshing Indicators
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{


       show(divider(time_arr));//showing time on nixie tubes
		if (flag_for_refreshing_indicators)//Refreshing Indicators
		{
			flag_for_refreshing_indicators = 0;
			init(time_arr);
		}

///////////////////////////////////////////////Updating the display time
		Oled_1.hours = sTime.Hours;
		Oled_1.minutes = sTime.Minutes;
		Oled_1.seconds = sTime.Seconds;
///////////////////////////////////////////////Updating the display time

		if(flag_for_menu)
		{
			intro_menu(ptr_counter_vertical,counter_for_time_setting, counter);// Oled menu
		}
		if(extra_flag)
		{
			intro_menu(ptr_counter_vertical,counter_for_time_setting, 0);// Oled menu
			extra_flag = 0;
		}




		if (flag_for_stop_time_ticking)
		{
			HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);//Getting time from rtc
		}





    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
uint8_t* divider(uint8_t *parr) // Method for displaying numbers on Nixie tubes
{
	parr[0] = sTime.Hours / 10;
	parr[1] = sTime.Hours % 10;
	parr[2] = sTime.Minutes / 10;
	parr[3] = sTime.Minutes % 10;
	parr[4] = sTime.Seconds / 10;
	parr[5] = sTime.Seconds % 10;
	return parr;
}
void button_handler(void)//Button handler
{
	Oled_1.flag_for_ptr_horizontal = flag_for_horizontal_ptr;// updating horizontal pointer
	if (HAL_GetTick() - timer > 50)
	{
		timer = HAL_GetTick();
		if (!HAL_GPIO_ReadPin(GPIOA, Btn_Pin) && !flag_for_btn)
		{
			flag_for_btn = 1;
		} else if (HAL_GPIO_ReadPin(GPIOA, Btn_Pin) && flag_for_btn)
		{
			flag_for_btn = 0;

			if(counter == 0)
			{
				counter = 1;
				flag_entering_setting_menu = 1;
				flag_for_vertical_ptr = 1;
				flag_for_stop_time_ticking = 0;
				flag_for_menu = 1;
			}else if(flag_entering_setting_menu && ptr_counter_vertical == 0)
			{
				flag_for_vertical_ptr = 0;
				flag_for_horizontal_ptr = 1;
				counter_for_time_setting++;
				if(counter_for_time_setting > 2)
				{
					counter_for_time_setting = -1;
					flag_for_vertical_ptr = 1;
					flag_for_horizontal_ptr = 0;
				}

			}else if(flag_entering_setting_menu && ptr_counter_vertical == 1)
			{

				flag_for_menu = 0;
				counter = 0;
				HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN); //Setting time
				flag_entering_setting_menu = 0;
				flag_for_vertical_ptr = 0;
				flag_for_stop_time_ticking = 1;
				extra_flag = 1;//Kostyl
				ptr_counter_vertical = 0;


			}


	}
}

}
void refreshing_indicators_handler(void)// 1 minute timer
{
counter_overflow++;
flag_for_refreshing_indicators = (counter_overflow == 2) ? true : false;
counter_overflow = (counter_overflow == 2) ? 0 : counter_overflow;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
/* User can add his own implementation to report the HAL error return state */
__disable_irq();
while (1) {
}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
