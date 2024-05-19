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
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "ugo_sine.h"

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
int sine1_idx = 0;
int sine2_idx = 107;
int sine3_idx = 211;

int pwm_on = 1;
int pwmn_on = 0;

int pwm_on2 = 0;
int pwmn_on2 = 1;

int pwm_on3 = 1;
int pwmn_on3 = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
long adc_raw;
long tim_val;
char buff[50] = {};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);

  HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_Base_Start_IT(&htim2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  adc_raw = HAL_ADC_GetValue(&hadc1);
	  tim_val = uu_map(adc_raw, 0, 4095, 200, 2000);
	  TIM2->ARR = tim_val;
	  TIM2->EGR |= 1 <<(TIM_EGR_UG_Pos);

	  sprintf(buff, "adc: %d\r\n", adc_raw);
	  HAL_UART_Transmit(&huart2, buff, sizeof(buff), 1000);

	  sprintf(buff, "map: %d\r\n\n", tim_val);
	  HAL_UART_Transmit(&huart2, buff, sizeof(buff), 1000);

	  HAL_Delay(100);

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

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
  // Check which version of the timer triggered this callback and toggle LED
  if (htim == &htim2)
  {
    sine1_idx++;
    sine2_idx++;
    sine3_idx++;

    // Overflow
    if (sine1_idx > 319)
    {
      // Reset
      sine1_idx = 0;
      // Toggle phases
      pwm_on = !pwm_on;
      pwmn_on = !pwmn_on;

      // Channel 1
      if (pwm_on)
      {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
      }
      else
      {
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
      }
    }
    TIM1->CCR1 = sine_vals[sine1_idx];


    if (sine2_idx > 319)
    {
      sine2_idx = 0;
      pwm_on2 = !pwm_on2;
      pwmn_on2 = !pwmn_on2;

      // Channel 2
      if (pwm_on2)
      {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
      }
      else
      {
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
      }
    }
    TIM1->CCR2 = sine_vals[sine2_idx];
    //return;

    if (sine3_idx > 319)
    {
      sine3_idx = 0;
      pwm_on3 = !pwm_on3;
      pwmn_on3 = !pwmn_on3;

      // Channel 3
      if (pwm_on3)
      {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
      }
      else
      {
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
      }
    }
    TIM1->CCR3 = sine_vals[sine3_idx];
  }
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
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
  char err_buff[50] = {};
  while (1)
  {
	  sprintf(err_buff, "ERROR\r\n");
	  HAL_UART_Transmit(&huart2, err_buff, sizeof(err_buff), 1000);
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
